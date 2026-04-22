#pragma once
#include "ThemeManager.h"
#include "ConexionBD.h" // ¡CONECTADO AL CEREBRO!

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class frmDetalleJuego : public System::Windows::Forms::Form
    {
    private:
        int id_juego_actual;
        String^ titulo_juego;
        String^ precio_juego;

        List<cli::array<System::String^>^>^ carrito_global;

        Panel^ pnlHeader;
        Panel^ pnlContenedorScroll;

        Label^ lblTituloJuego;
        Label^ lblDesarrollador;
        Button^ btnCerrar;
        PictureBox^ picPortada;
        Label^ lblSinopsis;
        Label^ lblDetallesExtra; // ¡NUEVO! Reemplaza a los requisitos
        Label^ lblPrecio;
        Button^ btnComprar;

        Label^ lblSeccionCalificar;
        ComboBox^ cmbPuntuacion;
        Label^ lblCalificacionDB; // ¡NUEVO! Calificación al lado de las estrellas
        Label^ lblSeccionComentarios;
        TextBox^ txtComentario;
        Button^ btnEnviarResena;

    public:
        frmDetalleJuego(int idJuego, String^ titulo, String^ precio, List<cli::array<System::String^>^>^ carrito)
        {
            id_juego_actual = idJuego;
            titulo_juego = titulo;
            precio_juego = precio;
            carrito_global = carrito;

            InitializeComponent();
            ConfigurarDiseno();
            CargarDatosReales();
            ThemeManager::Aplicar(this);
        }

    protected:
        ~frmDetalleJuego() { if (components) { delete components; } }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Text = L"Epsteam - Detalle de Juego";
            this->Size = System::Drawing::Size(900, 600);
            this->MinimumSize = System::Drawing::Size(900, 600);
            this->BackColor = Color::FromArgb(27, 40, 56);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        void ConfigurarDiseno() {
            pnlHeader = gcnew Panel();
            pnlHeader->Dock = DockStyle::Top;
            pnlHeader->Height = 80;
            pnlHeader->BackColor = Color::FromArgb(23, 26, 33);
            this->Controls->Add(pnlHeader);

            lblTituloJuego = gcnew Label();
            lblTituloJuego->Text = "Cargando...";
            lblTituloJuego->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
            lblTituloJuego->ForeColor = Color::White;
            lblTituloJuego->Location = System::Drawing::Point(20, 15);
            lblTituloJuego->AutoSize = true;
            pnlHeader->Controls->Add(lblTituloJuego);

            lblDesarrollador = gcnew Label();
            lblDesarrollador->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Italic);
            lblDesarrollador->ForeColor = Color::FromArgb(102, 192, 244);
            lblDesarrollador->Location = System::Drawing::Point(25, 50);
            lblDesarrollador->AutoSize = true;
            pnlHeader->Controls->Add(lblDesarrollador);

            btnCerrar = gcnew Button();
            btnCerrar->Text = "X";
            btnCerrar->FlatStyle = FlatStyle::Flat;
            btnCerrar->ForeColor = Color::White;
            btnCerrar->BackColor = Color::Crimson;
            btnCerrar->Size = System::Drawing::Size(35, 35);
            btnCerrar->Location = System::Drawing::Point(850, 20);
            btnCerrar->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnCerrar_Click);
            pnlHeader->Controls->Add(btnCerrar);

            pnlContenedorScroll = gcnew Panel();
            pnlContenedorScroll->Location = System::Drawing::Point(0, 80);
            pnlContenedorScroll->Size = System::Drawing::Size(900, 520);
            pnlContenedorScroll->AutoScroll = true;
            this->Controls->Add(pnlContenedorScroll);

            picPortada = gcnew PictureBox();
            picPortada->Location = System::Drawing::Point(30, 20);
            picPortada->Size = System::Drawing::Size(380, 450);
            picPortada->BackColor = Color::FromArgb(40, 40, 40);
            picPortada->SizeMode = PictureBoxSizeMode::StretchImage;
            pnlContenedorScroll->Controls->Add(picPortada);

            // ¡NUEVO! Panel de Información Adicional (reemplaza Requisitos)
            lblDetallesExtra = gcnew Label();
            lblDetallesExtra->Location = System::Drawing::Point(30, 480);
            lblDetallesExtra->Size = System::Drawing::Size(380, 100);
            lblDetallesExtra->ForeColor = Color::LightGray;
            lblDetallesExtra->Font = gcnew System::Drawing::Font("Consolas", 10);
            pnlContenedorScroll->Controls->Add(lblDetallesExtra);

            Label^ lblSinopTitulo = gcnew Label();
            lblSinopTitulo->Text = "SINOPSIS";
            lblSinopTitulo->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblSinopTitulo->ForeColor = Color::FromArgb(102, 192, 244);
            lblSinopTitulo->Location = System::Drawing::Point(440, 20);
            lblSinopTitulo->AutoSize = true;
            pnlContenedorScroll->Controls->Add(lblSinopTitulo);

            lblSinopsis = gcnew Label();
            lblSinopsis->Location = System::Drawing::Point(440, 50);
            lblSinopsis->Size = System::Drawing::Size(420, 90);
            lblSinopsis->AutoSize = false;
            lblSinopsis->ForeColor = Color::White;
            lblSinopsis->Font = gcnew System::Drawing::Font("Arial", 10);
            pnlContenedorScroll->Controls->Add(lblSinopsis);

            lblPrecio = gcnew Label();
            lblPrecio->Font = gcnew System::Drawing::Font("Arial", 22, FontStyle::Bold);
            lblPrecio->ForeColor = Color::LightGreen;
            lblPrecio->Location = System::Drawing::Point(440, 150);
            lblPrecio->AutoSize = true;
            pnlContenedorScroll->Controls->Add(lblPrecio);

            btnComprar = gcnew Button();
            btnComprar->Text = "AÑADIR AL CARRITO";
            btnComprar->Size = System::Drawing::Size(200, 45);
            btnComprar->Location = System::Drawing::Point(640, 140);
            btnComprar->BackColor = Color::FromArgb(0, 120, 215);
            btnComprar->ForeColor = Color::White;
            btnComprar->FlatStyle = FlatStyle::Flat;
            btnComprar->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            btnComprar->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnComprar_Click);
            pnlContenedorScroll->Controls->Add(btnComprar);

            lblSeccionCalificar = gcnew Label();
            lblSeccionCalificar->Text = "CALIFICAR ESTE JUEGO";
            lblSeccionCalificar->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblSeccionCalificar->ForeColor = Color::FromArgb(102, 192, 244);
            lblSeccionCalificar->Location = System::Drawing::Point(440, 210);
            lblSeccionCalificar->AutoSize = true;
            pnlContenedorScroll->Controls->Add(lblSeccionCalificar);

            cmbPuntuacion = gcnew ComboBox();
            cmbPuntuacion->Items->AddRange(gcnew array<Object^>{ "5 Estrellas", "4 Estrellas", "3 Estrellas", "2 Estrellas", "1 Estrella" });
            cmbPuntuacion->SelectedIndex = 0;
            cmbPuntuacion->Location = System::Drawing::Point(440, 240);
            cmbPuntuacion->Size = System::Drawing::Size(150, 30);
            cmbPuntuacion->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbPuntuacion->BackColor = Color::FromArgb(40, 40, 40);
            cmbPuntuacion->ForeColor = Color::White;               
            cmbPuntuacion->FlatStyle = FlatStyle::Flat;            
            pnlContenedorScroll->Controls->Add(cmbPuntuacion);

            // ¡NUEVO! Calificación que viene de la BD
            lblCalificacionDB = gcnew Label();
            lblCalificacionDB->Location = System::Drawing::Point(600, 243); // Al ladito de la cajita blanca
            lblCalificacionDB->AutoSize = true;
            lblCalificacionDB->ForeColor = Color::Gold;
            lblCalificacionDB->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblCalificacionDB->Text = " 0.0 / 10";
            pnlContenedorScroll->Controls->Add(lblCalificacionDB);

            lblSeccionComentarios = gcnew Label();
            lblSeccionComentarios->Text = "DEJAR UN COMENTARIO";
            lblSeccionComentarios->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblSeccionComentarios->ForeColor = Color::FromArgb(102, 192, 244);
            lblSeccionComentarios->Location = System::Drawing::Point(440, 290);
            lblSeccionComentarios->AutoSize = true;
            pnlContenedorScroll->Controls->Add(lblSeccionComentarios);

            txtComentario = gcnew TextBox();
            txtComentario->Multiline = true;
            txtComentario->Size = System::Drawing::Size(400, 80);
            txtComentario->Location = System::Drawing::Point(440, 320);
            txtComentario->BackColor = Color::FromArgb(40, 40, 40);
            txtComentario->ForeColor = Color::White;
            pnlContenedorScroll->Controls->Add(txtComentario);

            btnEnviarResena = gcnew Button();
            btnEnviarResena->Text = "PUBLICAR COMENTARIO";
            btnEnviarResena->Size = System::Drawing::Size(400, 35);
            btnEnviarResena->Location = System::Drawing::Point(440, 410);
            btnEnviarResena->BackColor = Color::MediumSeaGreen;
            btnEnviarResena->FlatStyle = FlatStyle::Flat;
            btnEnviarResena->ForeColor = Color::White;
            btnEnviarResena->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnEnviar_Click);
            pnlContenedorScroll->Controls->Add(btnEnviarResena);
        }

        void CargarDatosReales() {
            lblTituloJuego->Text = titulo_juego;
            lblPrecio->Text = precio_juego;

            // ¡MAGIA! Le pedimos los datos reales a la base de datos
            DataTable^ dtJuego = Epsteam::ConexionBD::ObtenerDetalleJuego(id_juego_actual);

            if (dtJuego->Rows->Count > 0) {
                DataRow^ fila = dtJuego->Rows[0];

                // 1. Sinopsis
                if (fila["descripcion"] != DBNull::Value)
                    lblSinopsis->Text = fila["descripcion"]->ToString();

                // 2. Desarrolladores y Editores
                String^ des = (fila["desarrolladores"] != DBNull::Value) ? fila["desarrolladores"]->ToString() : "Varios";
                String^ edi = (fila["editores"] != DBNull::Value) ? fila["editores"]->ToString() : "Varios";
                lblDesarrollador->Text = "Desarrollador: " + des + " | Editor: " + edi;

                // 3. Detalles Extra (Fecha, Jugadores, Clasificación)
                String^ fecha = (fila["fecha_lanzamiento"] != DBNull::Value) ? Convert::ToDateTime(fila["fecha_lanzamiento"]).ToString("dd/MM/yyyy") : "N/D";
                String^ jugadores = (fila["jugadores_activos"] != DBNull::Value) ? fila["jugadores_activos"]->ToString() : "0";
                String^ clasificacion = (fila["clasificacion_texto"] != DBNull::Value) ? fila["clasificacion_texto"]->ToString() : "N/D";

                lblDetallesExtra->Text = "INFORMACIÓN ADICIONAL:\n- Fecha de Lanzamiento: " + fecha + "\n- Jugadores Activos: " + jugadores + "\n- Clasificación: " + clasificacion;

                // 4. Calificación General
                String^ calif = (fila["calificacion"] != DBNull::Value) ? fila["calificacion"]->ToString() : "0.0";
                lblCalificacionDB->Text = "" + calif + " / 10";
            }

            // CARGAR LA IMAGEN LOCAL
            String^ nombreLimpio = titulo_juego->Trim()->ToLower();
            nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
            String^ rutaImagen = "../assets/img/" + nombreLimpio + ".jpg";

            try {
                if (System::IO::File::Exists(rutaImagen)) {
                    if (picPortada->Image != nullptr) delete picPortada->Image;
                    picPortada->Image = Image::FromFile(rutaImagen);
                }
                else {
                    picPortada->BackColor = Color::DimGray;
                }
            }
            catch (...) {
                picPortada->BackColor = Color::DimGray;
            }

            // REVISAR SI YA ESTÁ EN EL CARRITO
            for (int i = 0; i < carrito_global->Count; i++) {
                if (carrito_global[i][0] == id_juego_actual.ToString()) {
                    btnComprar->Text = "AGREGADO";
                    btnComprar->BackColor = Color::MediumSeaGreen;
                    break;
                }
            }
        }

        void btnCerrar_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }

        void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
            bool yaEnCarrito = false;
            for (int i = 0; i < carrito_global->Count; i++) {
                if (carrito_global[i][0] == id_juego_actual.ToString()) {
                    yaEnCarrito = true;
                    break;
                }
            }

            if (yaEnCarrito) {
                MessageBox::Show("Ya agregaste este juego al carrito.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                cli::array<System::String^>^ datos = gcnew cli::array<System::String^>{ id_juego_actual.ToString(), titulo_juego, precio_juego };
                carrito_global->Add(datos);

                btnComprar->Text = "AGREGADO";
                btnComprar->BackColor = Color::MediumSeaGreen;
                MessageBox::Show("¡Juego añadido al carrito de la tienda!", "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnEnviar_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("Reseña publicada.", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
            txtComentario->Clear();
        }
    };
}