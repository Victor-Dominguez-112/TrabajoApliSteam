#pragma once
#include "frmTicket.h"
#include "frmBiblioteca.h"
#include "ConexionBD.h" 

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    // Clase para acomodar los nombres de las imágenes
    public ref class GestorImagenes {
    public:
        static String^ ObtenerRuta(String^ nombreJuego) {
            String^ nombreLimpio = nombreJuego->Trim()->ToLower();
            nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
            return "img/" + nombreLimpio + ".jpg";
        }
    };

    public ref class frmTienda : public System::Windows::Forms::Form
    {
    public:
        frmTienda(void)
        {
            InitializeComponent();

            // Candado para que la búsqueda no se vuelva loca al dar clic
            ignorarBusqueda = false;

            Button^ btnBiblioteca = gcnew Button();
            btnBiblioteca->Text = "MI BIBLIOTECA";
            btnBiblioteca->BackColor = Color::FromArgb(45, 45, 45);
            btnBiblioteca->ForeColor = Color::White;
            btnBiblioteca->FlatStyle = FlatStyle::Flat;
            btnBiblioteca->Size = System::Drawing::Size(130, 35);
            btnBiblioteca->Location = System::Drawing::Point(450, 20);
            btnBiblioteca->Click += gcnew System::EventHandler(this, &frmTienda::btnBiblioteca_Click);
            pnlNav->Controls->Add(btnBiblioteca);

            // Timer para que no busque letras a lo loco (evita el lag)
            timerBusqueda = gcnew System::Windows::Forms::Timer();
            timerBusqueda->Interval = 400;
            timerBusqueda->Tick += gcnew System::EventHandler(this, &frmTienda::timerBusqueda_Tick);

            ConstruirInterfazBuscador();

            ticksGracia = 0;
            timerFarmeo = gcnew System::Windows::Forms::Timer();
            timerFarmeo->Interval = 1200;
            timerFarmeo->Tick += gcnew System::EventHandler(this, &frmTienda::timerFarmeo_Tick);
            timerFarmeo->Start();

            // Cargar juegos al abrir la ventana
            CargarJuegosTienda(Epsteam::ConexionBD::ObtenerCatalogoJuegos());
        }

    protected:
        ~frmTienda()
        {
            if (components) { delete components; }
        }

    private:
        bool ignorarBusqueda;
        System::Windows::Forms::Timer^ timerFarmeo;
        System::Windows::Forms::Timer^ timerBusqueda;
        int ticksGracia;

        System::Windows::Forms::Panel^ pnlNav;
        System::Windows::Forms::Label^ lblLogo;
        System::Windows::Forms::FlowLayoutPanel^ flowTienda;
        System::Windows::Forms::Button^ btnCerrarSesion;
        System::ComponentModel::Container^ components;

        // Variables de la barra de búsqueda y filtros
        System::Windows::Forms::Panel^ pnlBuscador;
        System::Windows::Forms::TextBox^ txtBusqueda;
        System::Windows::Forms::TrackBar^ tbPrecio;
        System::Windows::Forms::Label^ lblPrecio;
        System::Windows::Forms::ListBox^ lstSugerencias;

        System::Windows::Forms::CheckedListBox^ clbGeneros;
        System::Windows::Forms::CheckedListBox^ clbCategorias;
        System::Windows::Forms::CheckedListBox^ clbEtiquetas;
        System::Windows::Forms::CheckedListBox^ clbDesarrolladores;
        System::Windows::Forms::CheckedListBox^ clbEditores;

        System::Windows::Forms::Panel^ pnlFiltroGeneros;
        System::Windows::Forms::Panel^ pnlFiltroCategorias;
        System::Windows::Forms::Panel^ pnlFiltroEtiquetas;
        System::Windows::Forms::Panel^ pnlFiltroDesarrolladores;
        System::Windows::Forms::Panel^ pnlFiltroEditores;

        // --- Armar el área del buscador visualmente ---
        void ConstruirInterfazBuscador() {
            pnlBuscador = gcnew Panel();
            pnlBuscador->Dock = DockStyle::Top;
            pnlBuscador->Height = 130; // Más grande para las dos filas
            pnlBuscador->BackColor = Color::FromArgb(32, 45, 60);
            this->Controls->Add(pnlBuscador);
            pnlBuscador->BringToFront();

            // Caja de texto para buscar
            txtBusqueda = gcnew TextBox();
            txtBusqueda->Location = System::Drawing::Point(35, 50);
            txtBusqueda->Size = System::Drawing::Size(280, 30);
            txtBusqueda->Font = gcnew System::Drawing::Font("Arial", 12);
            txtBusqueda->ForeColor = Color::Gray;
            txtBusqueda->Text = "Buscar juego o etiqueta...";
            txtBusqueda->GotFocus += gcnew System::EventHandler(this, &frmTienda::txtBusqueda_GotFocus);
            txtBusqueda->LostFocus += gcnew System::EventHandler(this, &frmTienda::txtBusqueda_LostFocus);
            txtBusqueda->TextChanged += gcnew System::EventHandler(this, &frmTienda::IniciarTimerBusqueda);
            txtBusqueda->KeyDown += gcnew KeyEventHandler(this, &frmTienda::txtBusqueda_KeyDown);
            txtBusqueda->KeyPress += gcnew KeyPressEventHandler(this, &frmTienda::txtBusqueda_KeyPress);
            pnlBuscador->Controls->Add(txtBusqueda);

            // Lista desplegable para autocompletar
            lstSugerencias = gcnew ListBox();
            lstSugerencias->Location = System::Drawing::Point(35, 190);
            lstSugerencias->Size = System::Drawing::Size(280, 100);
            lstSugerencias->Visible = false;
            lstSugerencias->MouseClick += gcnew MouseEventHandler(this, &frmTienda::lstSugerencias_MouseClick);
            this->Controls->Add(lstSugerencias);
            lstSugerencias->BringToFront();

            // Barra para escoger el precio
            tbPrecio = gcnew TrackBar();
            tbPrecio->Location = System::Drawing::Point(750, 30);
            tbPrecio->Size = System::Drawing::Size(200, 45);
            tbPrecio->Minimum = 0;
            tbPrecio->Maximum = 2000;
            tbPrecio->Value = 2000;
            tbPrecio->TickFrequency = 200;
            tbPrecio->Scroll += gcnew System::EventHandler(this, &frmTienda::ActualizarLabelPrecio);
            pnlBuscador->Controls->Add(tbPrecio);

            lblPrecio = gcnew Label();
            lblPrecio->Text = "Precio Máx: $2000 MXN";
            lblPrecio->ForeColor = Color::White;
            lblPrecio->Location = System::Drawing::Point(760, 75);
            lblPrecio->AutoSize = true;
            lblPrecio->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            pnlBuscador->Controls->Add(lblPrecio);

            // Primera fila de botones (Arriba)
            CrearBotonFiltro("Géneros", 340, 20, pnlFiltroGeneros, clbGeneros, "genero");
            CrearBotonFiltro("Categorías", 470, 20, pnlFiltroCategorias, clbCategorias, "categoria");
            CrearBotonFiltro("Etiquetas", 600, 20, pnlFiltroEtiquetas, clbEtiquetas, "etiqueta");

            // Segunda fila de botones (Abajo)
            CrearBotonFiltro("Desarrollador", 340, 70, pnlFiltroDesarrolladores, clbDesarrolladores, "desarrollador");
            CrearBotonFiltro("Editor", 470, 70, pnlFiltroEditores, clbEditores, "editor");
        }

        // Crear los botones de filtros y sus listas ocultas
        void CrearBotonFiltro(String^ texto, int posX, int posY, Panel^% panelOut, CheckedListBox^% clbOut, String^ tipoFiltroBD) {
            Button^ btn = gcnew Button();
            btn->Text = texto + " v";
            btn->Location = System::Drawing::Point(posX, posY);
            btn->Size = System::Drawing::Size(120, 35);
            btn->BackColor = Color::FromArgb(45, 45, 45);
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            pnlBuscador->Controls->Add(btn);

            panelOut = gcnew Panel();
            panelOut->Location = System::Drawing::Point(posX, 190);
            panelOut->Size = System::Drawing::Size(180, 200);
            panelOut->Visible = false;
            panelOut->BackColor = Color::FromArgb(45, 45, 45);
            panelOut->BorderStyle = BorderStyle::FixedSingle;
            this->Controls->Add(panelOut);
            panelOut->BringToFront();

            clbOut = gcnew CheckedListBox();
            clbOut->Dock = DockStyle::Fill;
            clbOut->BackColor = Color::FromArgb(45, 45, 45);
            clbOut->ForeColor = Color::White;
            clbOut->CheckOnClick = true;

            DataTable^ datos = Epsteam::ConexionBD::ObtenerListaFiltros(tipoFiltroBD);
            clbOut->DataSource = datos;
            clbOut->DisplayMember = "nombre";
            clbOut->ValueMember = "id";
            clbOut->ItemCheck += gcnew ItemCheckEventHandler(this, &frmTienda::FiltroCasilla_Modificada);

            panelOut->Controls->Add(clbOut);

            btn->Click += gcnew System::EventHandler(this, &frmTienda::TogglePanelFiltro);
            btn->Tag = panelOut;
        }

        // --- Eventos del Buscador ---

        // Quitar el texto gris al hacer clic
    private: System::Void txtBusqueda_GotFocus(System::Object^ sender, System::EventArgs^ e) {
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") {
            ignorarBusqueda = true;
            txtBusqueda->Text = "";
            txtBusqueda->ForeColor = Color::Black;
            ignorarBusqueda = false;
        }
    }

           // Poner el texto gris si lo dejan vacío
    private: System::Void txtBusqueda_LostFocus(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrWhiteSpace(txtBusqueda->Text)) {
            ignorarBusqueda = true;
            txtBusqueda->Text = "Buscar juego o etiqueta...";
            txtBusqueda->ForeColor = Color::Gray;
            ignorarBusqueda = false;
        }
    }

           // Evitar que Windows haga "Beep" al presionar Enter o Esc
    private: System::Void txtBusqueda_KeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
        if (e->KeyChar == (char)13 || e->KeyChar == (char)27) {
            e->Handled = true;
        }
    }

           // Que el Enter busque y el Esc cierre la lista
    private: System::Void txtBusqueda_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
        if (e->KeyCode == Keys::Escape) {
            lstSugerencias->Visible = false;
            e->Handled = true;
            e->SuppressKeyPress = true;
            this->Focus();
        }
        if (e->KeyCode == Keys::Enter) {
            lstSugerencias->Visible = false;
            EjecutarBusquedaEnBD();
            e->Handled = true;
            e->SuppressKeyPress = true;
            this->Focus();
        }
    }

           // Si dan clic en el fondo, ocultar todos los menús
    private: System::Void ClicFueraDeFiltros(System::Object^ sender, MouseEventArgs^ e) {
        pnlFiltroGeneros->Visible = false;
        pnlFiltroCategorias->Visible = false;
        pnlFiltroEtiquetas->Visible = false;
        pnlFiltroDesarrolladores->Visible = false;
        pnlFiltroEditores->Visible = false;
        lstSugerencias->Visible = false;
    }

           // Mostrar solo la lista del botón que se presionó
    private: System::Void TogglePanelFiltro(System::Object^ sender, System::EventArgs^ e) {
        Button^ btn = (Button^)sender;
        Panel^ panelAsociado = (Panel^)btn->Tag;
        bool estabaVisible = panelAsociado->Visible;

        pnlFiltroGeneros->Visible = false;
        pnlFiltroCategorias->Visible = false;
        pnlFiltroEtiquetas->Visible = false;
        pnlFiltroDesarrolladores->Visible = false;
        pnlFiltroEditores->Visible = false;

        if (!estabaVisible) {
            panelAsociado->Visible = true;
            panelAsociado->BringToFront();
        }
    }

           // Cambiar el texto del precio al mover la barra
    private: System::Void ActualizarLabelPrecio(System::Object^ sender, System::EventArgs^ e) {
        lblPrecio->Text = "Precio Máx: $" + tbPrecio->Value + " MXN";
        IniciarTimerBusqueda(sender, e);
    }

           // Esperar un ratito antes de buscar para no trabar la compu
    private: System::Void IniciarTimerBusqueda(System::Object^ sender, System::EventArgs^ e) {
        if (ignorarBusqueda) return;
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") return;

        timerBusqueda->Stop();
        timerBusqueda->Start();
    }

    private: System::Void timerBusqueda_Tick(System::Object^ sender, System::EventArgs^ e) {
        timerBusqueda->Stop();
        EjecutarBusquedaEnBD();
    }

           // Buscar inmediatamente si marcan una casilla
    private: System::Void FiltroCasilla_Modificada(System::Object^ sender, ItemCheckEventArgs^ e) {
        this->BeginInvoke(gcnew MethodInvoker(this, &frmTienda::EjecutarBusquedaEnBD));
    }

           // Función principal para mandar a llamar a la BD
    private: System::Void EjecutarBusquedaEnBD() {
        String^ busqueda = txtBusqueda->Text;
        if (busqueda == "Buscar juego o etiqueta...") busqueda = "";

        // Marcar casilla automáticamente si el texto coincide con un género
        bool esSmartText = false;
        for (int i = 0; i < clbGeneros->Items->Count; i++) {
            DataRowView^ fila = (DataRowView^)clbGeneros->Items[i];
            if (fila["nombre"]->ToString()->ToLower() == busqueda->ToLower()) {
                clbGeneros->SetItemChecked(i, true);

                ignorarBusqueda = true;
                txtBusqueda->Text = "";
                ignorarBusqueda = false;

                esSmartText = true;
                break;
            }
        }
        if (esSmartText) return;

        // Recoger todos los IDs seleccionados
        List<int>^ idsGeneros = gcnew List<int>();
        for (int i = 0; i < clbGeneros->CheckedItems->Count; i++) {
            idsGeneros->Add(Convert::ToInt32(((DataRowView^)clbGeneros->CheckedItems[i])["id"]));
        }

        List<int>^ idsCategorias = gcnew List<int>();
        for (int i = 0; i < clbCategorias->CheckedItems->Count; i++) {
            idsCategorias->Add(Convert::ToInt32(((DataRowView^)clbCategorias->CheckedItems[i])["id"]));
        }

        List<int>^ idsEtiquetas = gcnew List<int>();
        for (int i = 0; i < clbEtiquetas->CheckedItems->Count; i++) {
            idsEtiquetas->Add(Convert::ToInt32(((DataRowView^)clbEtiquetas->CheckedItems[i])["id"]));
        }

        List<int>^ idsDesarrolladores = gcnew List<int>();
        for (int i = 0; i < clbDesarrolladores->CheckedItems->Count; i++) {
            idsDesarrolladores->Add(Convert::ToInt32(((DataRowView^)clbDesarrolladores->CheckedItems[i])["id"]));
        }

        List<int>^ idsEditores = gcnew List<int>();
        for (int i = 0; i < clbEditores->CheckedItems->Count; i++) {
            idsEditores->Add(Convert::ToInt32(((DataRowView^)clbEditores->CheckedItems[i])["id"]));
        }

        // Ejecutar la búsqueda en SQL
        DataTable^ resultados = Epsteam::ConexionBD::ObtenerCatalogoFiltrado(busqueda, idsGeneros, idsCategorias, idsEtiquetas, idsDesarrolladores, idsEditores, tbPrecio->Value);

        CargarJuegosTienda(resultados);

        // Rellenar la lista de sugerencias
        if (busqueda->Length > 0 && resultados->Rows->Count > 0) {
            lstSugerencias->Items->Clear();
            for (int i = 0; i < resultados->Rows->Count && i < 5; i++) {
                lstSugerencias->Items->Add(resultados->Rows[i]["titulo"]->ToString());
            }
            lstSugerencias->Visible = true;
        }
        else {
            lstSugerencias->Visible = false;
        }
    }

           // Completar el texto si el usuario da clic en una sugerencia
    private: System::Void lstSugerencias_MouseClick(System::Object^ sender, MouseEventArgs^ e) {
        if (lstSugerencias->SelectedItem != nullptr) {
            ignorarBusqueda = true; // Activar candado
            txtBusqueda->Text = lstSugerencias->SelectedItem->ToString();
            lstSugerencias->Visible = false;
            ignorarBusqueda = false; // Desactivar candado

            EjecutarBusquedaEnBD();
        }
    }

           // --- Mostrar los juegos en pantalla ---
           void CargarJuegosTienda(DataTable^ juegosTabla) {
               // Congelar la interfaz para que no parpadee al dibujar
               flowTienda->SuspendLayout();
               flowTienda->Controls->Clear();

               if (juegosTabla != nullptr && juegosTabla->Rows->Count > 0) {
                   for (int i = 0; i < juegosTabla->Rows->Count; i++) {
                       DataRow^ fila = juegosTabla->Rows[i];
                       String^ id_juego = fila["id_juego"]->ToString();
                       String^ titulo = fila["titulo"]->ToString();
                       String^ precio = "$" + fila["precio_base"]->ToString() + " MXN";
                       AgregarJuego(id_juego, titulo, precio);
                   }
               }
               else {
                   Label^ lblVacio = gcnew Label();
                   lblVacio->Text = "No se encontraron juegos con esos filtros 😢";
                   lblVacio->ForeColor = Color::White;
                   lblVacio->AutoSize = true;
                   lblVacio->Font = gcnew System::Drawing::Font("Arial", 14);
                   flowTienda->Controls->Add(lblVacio);
               }
               flowTienda->ResumeLayout();
           }

           void AgregarJuego(String^ id_juego, String^ titulo, String^ precio) {
               Panel^ card = gcnew Panel();
               card->Size = System::Drawing::Size(200, 250);
               card->BackColor = Color::FromArgb(45, 45, 45);
               card->Margin = System::Windows::Forms::Padding(15);

               PictureBox^ picPortada = gcnew PictureBox();
               picPortada->Dock = DockStyle::Fill;
               picPortada->SizeMode = PictureBoxSizeMode::Zoom;
               String^ rutaImagen = GestorImagenes::ObtenerRuta(titulo);

               if (System::IO::File::Exists(rutaImagen)) {
                   picPortada->Image = Image::FromFile(rutaImagen);
               }
               else {
                   picPortada->BackColor = Color::DimGray;
               }

               Label^ lblTitulo = gcnew Label();
               lblTitulo->Text = titulo;
               lblTitulo->ForeColor = Color::White;
               lblTitulo->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
               lblTitulo->Dock = DockStyle::Top;
               lblTitulo->TextAlign = ContentAlignment::MiddleCenter;

               Label^ lblPrecio = gcnew Label();
               lblPrecio->Text = precio;
               lblPrecio->ForeColor = Color::LightGray;
               lblPrecio->Dock = DockStyle::Bottom;
               lblPrecio->TextAlign = ContentAlignment::MiddleCenter;

               Button^ btnComprar = gcnew Button();
               btnComprar->Text = "COMPRAR";
               btnComprar->FlatStyle = FlatStyle::Flat;
               btnComprar->ForeColor = Color::White;
               btnComprar->BackColor = Color::FromArgb(0, 120, 215);
               btnComprar->Dock = DockStyle::Bottom;

               btnComprar->Tag = gcnew array<String^>{id_juego, titulo, precio};
               btnComprar->Click += gcnew System::EventHandler(this, &frmTienda::btnComprar_Click);

               card->Controls->Add(picPortada);
               card->Controls->Add(lblTitulo);
               card->Controls->Add(btnComprar);
               card->Controls->Add(lblPrecio);
               picPortada->SendToBack();

               flowTienda->Controls->Add(card);
           }

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->pnlNav = (gcnew System::Windows::Forms::Panel());
               this->lblLogo = (gcnew System::Windows::Forms::Label());
               this->btnCerrarSesion = (gcnew System::Windows::Forms::Button());
               this->flowTienda = (gcnew System::Windows::Forms::FlowLayoutPanel());
               this->pnlNav->SuspendLayout();
               this->SuspendLayout();

               this->pnlNav->BackColor = System::Drawing::Color::FromArgb(23, 26, 33);
               this->pnlNav->Controls->Add(this->btnCerrarSesion);
               this->pnlNav->Controls->Add(this->lblLogo);
               this->pnlNav->Dock = System::Windows::Forms::DockStyle::Top;
               this->pnlNav->Location = System::Drawing::Point(0, 0);
               this->pnlNav->Name = L"pnlNav";
               this->pnlNav->Size = System::Drawing::Size(1000, 60);

               this->lblLogo->AutoSize = true;
               this->lblLogo->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold));
               this->lblLogo->ForeColor = System::Drawing::Color::FromArgb(102, 192, 244);
               this->lblLogo->Location = System::Drawing::Point(20, 15);
               this->lblLogo->Text = L"EPSTEAM - TIENDA";

               this->btnCerrarSesion->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
               this->btnCerrarSesion->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnCerrarSesion->ForeColor = System::Drawing::Color::White;
               this->btnCerrarSesion->Location = System::Drawing::Point(850, 15);
               this->btnCerrarSesion->Size = System::Drawing::Size(120, 30);
               this->btnCerrarSesion->Text = L"Cerrar Sesión";
               this->btnCerrarSesion->Click += gcnew System::EventHandler(this, &frmTienda::btnCerrarSesion_Click);

               this->flowTienda->AutoScroll = true;
               this->flowTienda->BackColor = System::Drawing::Color::FromArgb(27, 40, 56);
               this->flowTienda->Dock = System::Windows::Forms::DockStyle::Fill;
               this->flowTienda->Location = System::Drawing::Point(0, 60);
               this->flowTienda->Name = L"flowTienda";
               this->flowTienda->Padding = System::Windows::Forms::Padding(20);
               this->flowTienda->Size = System::Drawing::Size(1000, 640);
               this->flowTienda->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &frmTienda::ClicFueraDeFiltros);

               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(1000, 700);
               this->Controls->Add(this->flowTienda);
               this->Controls->Add(this->pnlNav);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Tienda Epsteam";
               this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &frmTienda::ClicFueraDeFiltros);
               this->pnlNav->ResumeLayout(false);
               this->pnlNav->PerformLayout();
               this->ResumeLayout(false);
           }
#pragma endregion

    private: System::Void btnCerrarSesion_Click(System::Object^ sender, System::EventArgs^ e) {
        timerFarmeo->Stop();
        this->Close();
    }

    private: System::Void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btnCliquado = (Button^)sender;
        array<String^>^ datos = (array<String^>^)btnCliquado->Tag;
        String^ idJuegoStr = datos[0];
        String^ nombreJuego = datos[1];
        String^ precioReal = datos[2];

        bool yaLoTiene = false;
        DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(Epsteam::ConexionBD::idUsuarioActual);

        if (misJuegos != nullptr) {
            for (int i = 0; i < misJuegos->Rows->Count; i++) {
                DataRow^ fila = misJuegos->Rows[i];
                if (fila["titulo"]->ToString() == nombreJuego) {
                    yaLoTiene = true;
                    break;
                }
            }
        }

        if (yaLoTiene) {
            MessageBox::Show("¡El registro indica que ya tienes '" + nombreJuego + "'!", "Juego Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
        else {
            frmTicket^ ticket = gcnew frmTicket(idJuegoStr, nombreJuego, precioReal);
            ticket->ShowDialog();
        }
    }

    private: System::Void btnBiblioteca_Click(System::Object^ sender, System::EventArgs^ e) {
        frmBiblioteca^ biblioteca = gcnew frmBiblioteca();
        this->Hide();
        biblioteca->ShowDialog();
        this->Show();
    }

    private: System::Void timerFarmeo_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (ticksGracia < 25) {
            ticksGracia++;
        }
        else {
            Epsteam::ConexionBD::AvanzarTiempoJuego(Epsteam::ConexionBD::idUsuarioActual);
        }
    }
    };
}