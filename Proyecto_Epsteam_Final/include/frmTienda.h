#pragma once
#include "frmTicket.h"
#include "frmBiblioteca.h"
#include "ConexionBD.h" 
#include "frmPago.h"
#include "frmCarrito.h"
#include "frmConfiguracion.h"
#include "ThemeManager.h"
#include "frmDetalleJuego.h" 

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class GestorImagenes {
    public:
        static String^ ObtenerRuta(String^ nombreJuego) {
            String^ nombreLimpio = nombreJuego->Trim()->ToLower();
            nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
            return "../assets/img/" + nombreLimpio + ".jpg";
        }
    };

    public ref class frmTienda : public System::Windows::Forms::Form
    {
    public:
        frmTienda(int idLogueado)
        {
            idUsuarioActual = idLogueado;
            InitializeComponent();
            ThemeManager::Aplicar(this);
            ignorarBusqueda = false;

            // --- BOTÓN MI BIBLIOTECA ---
            Button^ btnBiblioteca = gcnew Button();
            btnBiblioteca->Text = "MI BIBLIOTECA";
            btnBiblioteca->BackColor = Color::FromArgb(45, 45, 45);
            btnBiblioteca->ForeColor = Color::White;
            btnBiblioteca->FlatStyle = FlatStyle::Flat;
            btnBiblioteca->Size = System::Drawing::Size(130, 35);
            btnBiblioteca->Location = System::Drawing::Point(450, 15);
            btnBiblioteca->Click += gcnew System::EventHandler(this, &frmTienda::btnBiblioteca_Click);
            pnlNav->Controls->Add(btnBiblioteca);

            // --- BOTÓN CARRITO ---
            carritoCompras = gcnew System::Collections::Generic::List<cli::array<System::String^>^>();
            btnCarrito = gcnew Button();
            btnCarrito->Text = "CARRITO (0)";
            btnCarrito->BackColor = Color::FromArgb(45, 45, 45);
            btnCarrito->ForeColor = Color::White;
            btnCarrito->FlatStyle = FlatStyle::Flat;
            btnCarrito->Size = System::Drawing::Size(130, 35);
            btnCarrito->Location = System::Drawing::Point(600, 15);
            btnCarrito->Click += gcnew System::EventHandler(this, &frmTienda::btnCarrito_Click);
            pnlNav->Controls->Add(btnCarrito);

            // --- BOTÓN MI PERFIL (AHORA ES UNA VARIABLE GLOBAL) ---
            btnPerfil = gcnew Button();
            btnPerfil->Text = "MI PERFIL";
            btnPerfil->BackColor = Color::FromArgb(45, 45, 45);
            btnPerfil->ForeColor = Color::White;
            btnPerfil->FlatStyle = FlatStyle::Flat;
            btnPerfil->Size = System::Drawing::Size(100, 35);
            btnPerfil->Location = System::Drawing::Point(750, 15);
            // IMPORTANTE: Al hacer clic en el texto, muestra el menú en lugar de abrir directo la ventana
            btnPerfil->Click += gcnew System::EventHandler(this, &frmTienda::MostrarMenuPerfil);
            pnlNav->Controls->Add(btnPerfil);

            // --- CREACIÓN DEL MENÚ DESPLEGABLE ---
            menuPerfil = gcnew System::Windows::Forms::ContextMenuStrip();
            menuPerfil->ShowImageMargin = false; // Quita la barra gris de la izquierda
            menuPerfil->ShowCheckMargin = false; // Quita espacio de checkbox
            menuPerfil->BackColor = Color::FromArgb(45, 45, 45);
            menuPerfil->ForeColor = Color::White;
            menuPerfil->Items->Add("Editar Perfil", nullptr, gcnew EventHandler(this, &frmTienda::AbrirConfiguracion));
            menuPerfil->Items->Add("-"); // Línea separadora
            menuPerfil->Items->Add("Cerrar Sesión", nullptr, gcnew EventHandler(this, &frmTienda::btnCerrarSesion_Click));

            // --- CREACIÓN DE LA FOTO (BOTÓN DINÁMICO) ---
            picPerfilBoton = gcnew System::Windows::Forms::PictureBox();
            picPerfilBoton->Size = System::Drawing::Size(40, 40);
            picPerfilBoton->Location = System::Drawing::Point(750, 12);
            picPerfilBoton->SizeMode = PictureBoxSizeMode::Zoom;
            picPerfilBoton->Cursor = Cursors::Hand;
            picPerfilBoton->Visible = false;

            // 👇 AQUÍ ES DONDE PEGAS EL CÓDIGO NUEVO 👇
            try {
                String^ rutaExe = AppDomain::CurrentDomain->BaseDirectory;
                String^ rutaSucia = rutaExe + "../../../assets/avatares/avatar1.png"; // Cambiado a .png

                // Limpiamos la ruta
                String^ rutaLimpia = System::IO::Path::GetFullPath(rutaSucia);
                picPerfilBoton->Image = Image::FromFile(rutaLimpia);
            }
            catch (...) {
                // SI FALLA, QUE NO MUESTRE NINGÚN MENSAJE, SOLO QUE SE PONGA GRIS
                picPerfilBoton->BackColor = Color::DimGray;
            }
            // 👆 HASTA AQUÍ EL CÓDIGO NUEVO 👆

            picPerfilBoton->Click += gcnew System::EventHandler(this, &frmTienda::MostrarMenuPerfil);
            pnlNav->Controls->Add(picPerfilBoton);

            // Ocultamos el viejo botón de cerrar sesión porque ya está en el menú
            btnCerrarSesion->Visible = false;

            // --- BUSCADOR Y TIMERS ---
            timerBusqueda = gcnew System::Windows::Forms::Timer();
            timerBusqueda->Interval = 400;
            timerBusqueda->Tick += gcnew System::EventHandler(this, &frmTienda::timerBusqueda_Tick);

            ConstruirInterfazBuscador();

            ticksGracia = 0;
            timerFarmeo = gcnew System::Windows::Forms::Timer();
            timerFarmeo->Interval = 1200;
            timerFarmeo->Tick += gcnew System::EventHandler(this, &frmTienda::timerFarmeo_Tick);
            timerFarmeo->Start();

            CargarJuegosTienda(Epsteam::ConexionBD::ObtenerCatalogoJuegos());
        }

    protected:
        ~frmTienda() { if (components) { delete components; } }

    private:
        bool ignorarBusqueda;
        System::Windows::Forms::Timer^ timerFarmeo;
        System::Windows::Forms::Timer^ timerBusqueda;
        int ticksGracia;
        int idUsuarioActual;

        // ¡AQUÍ ESTÁN LAS VARIABLES GLOBALES DE LOS BOTONES NUEVOS!
        System::Windows::Forms::Button^ btnPerfil;
        System::Windows::Forms::ContextMenuStrip^ menuPerfil;
        System::Windows::Forms::PictureBox^ picPerfilBoton;

        System::Windows::Forms::Panel^ pnlNav;
        System::Windows::Forms::Label^ lblLogo;
        System::Windows::Forms::FlowLayoutPanel^ flowTienda;
        System::Windows::Forms::Button^ btnCerrarSesion;
        System::ComponentModel::Container^ components;
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

        System::Collections::Generic::List<cli::array<System::String^>^>^ carritoCompras;
        System::Windows::Forms::Button^ btnCarrito;

        void ConstruirInterfazBuscador() {
            pnlBuscador = gcnew Panel();
            pnlBuscador->Dock = DockStyle::Top;
            pnlBuscador->Height = 140;
            pnlBuscador->BackColor = Color::FromArgb(32, 45, 60);
            pnlBuscador->BorderStyle = BorderStyle::None; // Adiós a la línea blanca

            this->Controls->Add(pnlBuscador);
            pnlBuscador->BringToFront();

            txtBusqueda = gcnew TextBox();
            txtBusqueda->Location = System::Drawing::Point(35, 25);
            txtBusqueda->Size = System::Drawing::Size(300, 30);
            txtBusqueda->Font = gcnew System::Drawing::Font("Arial", 12);
            txtBusqueda->ForeColor = Color::Gray;
            txtBusqueda->Text = "Buscar juego o etiqueta...";
            txtBusqueda->GotFocus += gcnew System::EventHandler(this, &frmTienda::txtBusqueda_GotFocus);
            txtBusqueda->LostFocus += gcnew System::EventHandler(this, &frmTienda::txtBusqueda_LostFocus);
            txtBusqueda->TextChanged += gcnew System::EventHandler(this, &frmTienda::IniciarTimerBusqueda);
            txtBusqueda->KeyDown += gcnew KeyEventHandler(this, &frmTienda::txtBusqueda_KeyDown);
            txtBusqueda->KeyPress += gcnew KeyPressEventHandler(this, &frmTienda::txtBusqueda_KeyPress);
            pnlBuscador->Controls->Add(txtBusqueda);

            lstSugerencias = gcnew ListBox();
            lstSugerencias->Location = System::Drawing::Point(35, 140);
            lstSugerencias->Size = System::Drawing::Size(300, 100);
            lstSugerencias->Visible = false;
            lstSugerencias->MouseClick += gcnew MouseEventHandler(this, &frmTienda::lstSugerencias_MouseClick);
            this->Controls->Add(lstSugerencias);
            lstSugerencias->BringToFront();

            tbPrecio = gcnew TrackBar();
            tbPrecio->Location = System::Drawing::Point(720, 20);
            tbPrecio->Size = System::Drawing::Size(220, 45);
            tbPrecio->Minimum = 0;
            tbPrecio->Maximum = 2000;
            tbPrecio->Value = 2000;
            tbPrecio->TickFrequency = 200;
            tbPrecio->Scroll += gcnew System::EventHandler(this, &frmTienda::ActualizarLabelPrecio);
            pnlBuscador->Controls->Add(tbPrecio);

            lblPrecio = gcnew Label();
            lblPrecio->Text = "Precio Máx: $2000 MXN";
            lblPrecio->ForeColor = Color::White;
            lblPrecio->Location = System::Drawing::Point(730, 65);
            lblPrecio->AutoSize = true;
            lblPrecio->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            pnlBuscador->Controls->Add(lblPrecio);

            CrearBotonFiltro("Géneros", 35, 80, pnlFiltroGeneros, clbGeneros, "genero");
            CrearBotonFiltro("Categorías", 165, 80, pnlFiltroCategorias, clbCategorias, "categoria");
            CrearBotonFiltro("Etiquetas", 295, 80, pnlFiltroEtiquetas, clbEtiquetas, "etiqueta");
            CrearBotonFiltro("Desarrollador", 425, 80, pnlFiltroDesarrolladores, clbDesarrolladores, "desarrollador");
            CrearBotonFiltro("Editor", 555, 80, pnlFiltroEditores, clbEditores, "editor");
        }

        void CrearBotonFiltro(String^ texto, int posX, int posY, Panel^% panelOut, CheckedListBox^% clbOut, String^ tipoFiltroBD) {
            Button^ btn = gcnew Button();
            btn->Text = texto;
            btn->Location = System::Drawing::Point(posX, posY);
            btn->Size = System::Drawing::Size(120, 35);
            btn->BackColor = Color::FromArgb(45, 45, 45);
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            pnlBuscador->Controls->Add(btn);

            panelOut = gcnew Panel();
            panelOut->Location = System::Drawing::Point(posX, 140);
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

    private: System::Void txtBusqueda_GotFocus(System::Object^ sender, System::EventArgs^ e) {
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") {
            ignorarBusqueda = true;
            txtBusqueda->Text = "";
            txtBusqueda->ForeColor = Color::Black;
            ignorarBusqueda = false;
        }
    }

    private: System::Void txtBusqueda_LostFocus(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrWhiteSpace(txtBusqueda->Text)) {
            ignorarBusqueda = true;
            txtBusqueda->Text = "Buscar juego o etiqueta...";
            txtBusqueda->ForeColor = Color::Gray;
            ignorarBusqueda = false;
        }
    }

    private: System::Void txtBusqueda_KeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
        if (e->KeyChar == (char)13 || e->KeyChar == (char)27) e->Handled = true;
    }

    private: System::Void txtBusqueda_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
        if (e->KeyCode == Keys::Escape) {
            lstSugerencias->Visible = false;
            e->Handled = true; e->SuppressKeyPress = true; this->Focus();
        }
        if (e->KeyCode == Keys::Enter) {
            lstSugerencias->Visible = false;
            EjecutarBusquedaEnBD();
            e->Handled = true; e->SuppressKeyPress = true; this->Focus();
        }
    }

    private: System::Void ClicFueraDeFiltros(System::Object^ sender, MouseEventArgs^ e) {
        pnlFiltroGeneros->Visible = false;
        pnlFiltroCategorias->Visible = false;
        pnlFiltroEtiquetas->Visible = false;
        pnlFiltroDesarrolladores->Visible = false;
        pnlFiltroEditores->Visible = false;
        lstSugerencias->Visible = false;
    }

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

    private: System::Void ActualizarLabelPrecio(System::Object^ sender, System::EventArgs^ e) {
        lblPrecio->Text = "Precio Máx: $" + tbPrecio->Value + " MXN";
        IniciarTimerBusqueda(sender, e);
    }

    private: System::Void IniciarTimerBusqueda(System::Object^ sender, System::EventArgs^ e) {
        if (ignorarBusqueda) return;
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") return;
        timerBusqueda->Stop(); timerBusqueda->Start();
    }

    private: System::Void timerBusqueda_Tick(System::Object^ sender, System::EventArgs^ e) {
        timerBusqueda->Stop(); EjecutarBusquedaEnBD();
    }

    private: System::Void FiltroCasilla_Modificada(System::Object^ sender, ItemCheckEventArgs^ e) {
        this->BeginInvoke(gcnew MethodInvoker(this, &frmTienda::EjecutarBusquedaEnBD));
    }

    private: System::Void EjecutarBusquedaEnBD() {
        String^ busqueda = txtBusqueda->Text;
        if (busqueda == "Buscar juego o etiqueta...") busqueda = "";

        bool esSmartText = false;
        for (int i = 0; i < clbGeneros->Items->Count; i++) {
            DataRowView^ fila = (DataRowView^)clbGeneros->Items[i];
            if (fila["nombre"]->ToString()->ToLower() == busqueda->ToLower()) {
                clbGeneros->SetItemChecked(i, true);
                ignorarBusqueda = true; txtBusqueda->Text = ""; ignorarBusqueda = false;
                esSmartText = true; break;
            }
        }
        if (esSmartText) return;

        List<int>^ idsGeneros = gcnew List<int>();
        for (int i = 0; i < clbGeneros->CheckedItems->Count; i++) idsGeneros->Add(Convert::ToInt32(((DataRowView^)clbGeneros->CheckedItems[i])["id"]));

        List<int>^ idsCategorias = gcnew List<int>();
        for (int i = 0; i < clbCategorias->CheckedItems->Count; i++) idsCategorias->Add(Convert::ToInt32(((DataRowView^)clbCategorias->CheckedItems[i])["id"]));

        List<int>^ idsEtiquetas = gcnew List<int>();
        for (int i = 0; i < clbEtiquetas->CheckedItems->Count; i++) idsEtiquetas->Add(Convert::ToInt32(((DataRowView^)clbEtiquetas->CheckedItems[i])["id"]));

        List<int>^ idsDesarrolladores = gcnew List<int>();
        for (int i = 0; i < clbDesarrolladores->CheckedItems->Count; i++) idsDesarrolladores->Add(Convert::ToInt32(((DataRowView^)clbDesarrolladores->CheckedItems[i])["id"]));

        List<int>^ idsEditores = gcnew List<int>();
        for (int i = 0; i < clbEditores->CheckedItems->Count; i++) idsEditores->Add(Convert::ToInt32(((DataRowView^)clbEditores->CheckedItems[i])["id"]));

        DataTable^ resultados = Epsteam::ConexionBD::ObtenerCatalogoFiltrado(busqueda, idsGeneros, idsCategorias, idsEtiquetas, idsDesarrolladores, idsEditores, tbPrecio->Value);
        CargarJuegosTienda(resultados);

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

    private: System::Void lstSugerencias_MouseClick(System::Object^ sender, MouseEventArgs^ e) {
        if (lstSugerencias->SelectedItem != nullptr) {
            ignorarBusqueda = true;
            txtBusqueda->Text = lstSugerencias->SelectedItem->ToString();
            lstSugerencias->Visible = false;
            ignorarBusqueda = false;
            EjecutarBusquedaEnBD();
        }
    }

           void CargarJuegosTienda(DataTable^ juegosTabla) {
               flowTienda->SuspendLayout();
               flowTienda->Controls->Clear();

               if (juegosTabla != nullptr && juegosTabla->Rows->Count > 0) {
                   for (int i = 0; i < juegosTabla->Rows->Count; i++) {
                       DataRow^ fila = juegosTabla->Rows[i];
                       int id_juego = Convert::ToInt32(fila["id_juego"]);
                       String^ titulo = fila["titulo"]->ToString();
                       String^ precio = "$" + fila["precio_base"]->ToString() + " MXN";
                       AgregarJuego(id_juego, titulo, precio);
                   }
               }
               else {
                   Label^ lblVacio = gcnew Label();
                   lblVacio->Text = "No se encontraron juegos";
                   lblVacio->ForeColor = Color::White;
                   lblVacio->AutoSize = true;
                   lblVacio->Font = gcnew System::Drawing::Font("Arial", 14);
                   flowTienda->Controls->Add(lblVacio);
               }
               flowTienda->ResumeLayout();
           }

           void AgregarJuego(int id_juego, String^ titulo, String^ precio) {
               Panel^ card = gcnew Panel();
               card->Size = System::Drawing::Size(200, 310);
               card->BackColor = Color::FromArgb(45, 45, 45);
               card->Margin = System::Windows::Forms::Padding(10, 15, 10, 15);

               PictureBox^ picPortada = gcnew PictureBox();
               picPortada->Dock = DockStyle::Fill;
               picPortada->SizeMode = PictureBoxSizeMode::StretchImage;
               String^ rutaImagen = GestorImagenes::ObtenerRuta(titulo);

               if (System::IO::File::Exists(rutaImagen)) {
                   picPortada->Image = Image::FromFile(rutaImagen);
               }
               else {
                   picPortada->BackColor = Color::DimGray;
               }

               cli::array<System::String^>^ datosJuego = gcnew cli::array<System::String^>{ id_juego.ToString(), titulo, precio };

               picPortada->Cursor = Cursors::Hand;
               picPortada->Tag = datosJuego;
               picPortada->Click += gcnew System::EventHandler(this, &frmTienda::AbrirDetalle_Click);

               Label^ lblTitulo = gcnew Label();
               lblTitulo->Text = titulo;
               lblTitulo->ForeColor = Color::White;
               lblTitulo->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
               lblTitulo->Dock = DockStyle::Top;
               lblTitulo->TextAlign = ContentAlignment::MiddleCenter;
               lblTitulo->Height = 35;

               lblTitulo->Cursor = Cursors::Hand;
               lblTitulo->Tag = datosJuego;
               lblTitulo->Click += gcnew System::EventHandler(this, &frmTienda::AbrirDetalle_Click);

               Label^ lblPrecio = gcnew Label();
               lblPrecio->Text = precio;
               lblPrecio->ForeColor = Color::LightGreen;
               lblPrecio->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
               lblPrecio->Dock = DockStyle::Bottom;
               lblPrecio->TextAlign = ContentAlignment::MiddleCenter;
               lblPrecio->Height = 25;

               Button^ btnComprar = gcnew Button();
               btnComprar->Text = "AGREGAR AL CARRO";
               btnComprar->FlatStyle = FlatStyle::Flat;
               btnComprar->ForeColor = Color::White;
               btnComprar->BackColor = Color::FromArgb(0, 120, 215);
               btnComprar->Dock = DockStyle::Bottom;
               btnComprar->Height = 35;
               btnComprar->Tag = datosJuego;
               btnComprar->Click += gcnew System::EventHandler(this, &frmTienda::btnComprar_Click);

               card->Controls->Add(picPortada);
               card->Controls->Add(lblTitulo);
               card->Controls->Add(btnComprar);
               card->Controls->Add(lblPrecio);
               picPortada->SendToBack();

               flowTienda->Controls->Add(card);
           }

    private: System::Void AbrirDetalle_Click(System::Object^ sender, System::EventArgs^ e) {
        Control^ controlClicado = (Control^)sender;

        cli::array<System::String^>^ datos = (cli::array<System::String^>^)controlClicado->Tag;
        int idJuegoClicado = Convert::ToInt32(datos[0]);
        String^ tituloClicado = datos[1];
        String^ precioClicado = datos[2];

        frmDetalleJuego^ ventanaDetalles = gcnew frmDetalleJuego(idJuegoClicado, tituloClicado, precioClicado, carritoCompras);
        ventanaDetalles->ShowDialog();

        btnCarrito->Text = "CARRITO (" + Convert::ToString(carritoCompras->Count) + ")";

        for each (Control ^ card in flowTienda->Controls) {
            for each (Control ^ c in card->Controls) {
                if (c->GetType() == Button::typeid) {
                    Button^ btn = (Button^)c;
                    cli::array<System::String^>^ datosBtn = (cli::array<System::String^>^)btn->Tag;
                    bool sigueEnCarrito = false;
                    for (int i = 0; i < carritoCompras->Count; i++) {
                        if (carritoCompras[i][0] == datosBtn[0]) { sigueEnCarrito = true; break; }
                    }
                    if (sigueEnCarrito) {
                        btn->Text = "AGREGADO";
                        btn->BackColor = Color::MediumSeaGreen;
                    }
                }
            }
        }
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

               // Botón falso de diseño visual, se oculta por código luego
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
               this->flowTienda->Padding = System::Windows::Forms::Padding(20, 150, 20, 20);
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
        ThemeManager::EstablecerTema(0);
        this->Close();
    }

    private: System::Void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btnCliquado = (Button^)sender;
        cli::array<System::String^>^ datos = (cli::array<System::String^>^)btnCliquado->Tag;

        String^ idJuegoStr = datos[0];
        String^ nombreJuego = datos[1];
        String^ precioReal = datos[2];

        bool yaLoTiene = false;

        try {
            DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(idUsuarioActual);
            if (misJuegos != nullptr) {
                for (int i = 0; i < misJuegos->Rows->Count; i++) {
                    if (misJuegos->Rows[i]["titulo"]->ToString() == nombreJuego) {
                        yaLoTiene = true;
                        break;
                    }
                }
            }
        }
        catch (...) {}

        if (yaLoTiene) {
            MessageBox::Show("¡Ya tienes '" + nombreJuego + "' en tu biblioteca!", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        bool yaEnCarrito = false;
        for (int i = 0; i < carritoCompras->Count; i++) {
            if (carritoCompras[i][0] == idJuegoStr) { yaEnCarrito = true; break; }
        }

        if (yaEnCarrito) {
            MessageBox::Show("Ya agregaste este juego al carrito.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        else {
            carritoCompras->Add(datos);
            btnCarrito->Text = "CARRITO (" + Convert::ToString(carritoCompras->Count) + ")";
            btnCliquado->Text = "AGREGADO";
            btnCliquado->BackColor = Color::MediumSeaGreen;
        }
    }

    private: System::Void btnCarrito_Click(System::Object^ sender, System::EventArgs^ e) {
        if (carritoCompras->Count == 0) {
            MessageBox::Show("Tu carrito está vacío.");
            return;
        }

        frmCarrito^ ventanaCarrito = gcnew frmCarrito(idUsuarioActual, carritoCompras);
        ventanaCarrito->ShowDialog();
        btnCarrito->Text = "CARRITO (" + Convert::ToString(carritoCompras->Count) + ")";

        for each (Control ^ card in flowTienda->Controls) {
            for each (Control ^ c in card->Controls) {
                if (c->GetType() == Button::typeid) {
                    Button^ btn = (Button^)c;
                    cli::array<System::String^>^ datos = (cli::array<System::String^>^)btn->Tag;
                    String^ idJuego = datos[0];
                    bool sigueEnCarrito = false;
                    for (int i = 0; i < carritoCompras->Count; i++) {
                        if (carritoCompras[i][0] == idJuego) { sigueEnCarrito = true; break; }
                    }
                    if (sigueEnCarrito) {
                        btn->Text = "AGREGADO";
                        btn->BackColor = Color::MediumSeaGreen;
                    }
                    else {
                        btn->Text = "AGREGAR AL CARRO";
                        btn->BackColor = Color::FromArgb(0, 120, 215);
                    }
                }
            }
        }
    }

    private: System::Void btnBiblioteca_Click(System::Object^ sender, System::EventArgs^ e) {
        frmBiblioteca^ biblioteca = gcnew frmBiblioteca();
        this->Hide();
        biblioteca->ShowDialog();
        this->Show();
    }

    private: System::Void MostrarMenuPerfil(System::Object^ sender, System::EventArgs^ e) {
        Control^ controlClickeado = (Control^)sender;
        menuPerfil->Show(controlClickeado, System::Drawing::Point(0, controlClickeado->Height));
    }

    private: System::Void AbrirConfiguracion(System::Object^ sender, System::EventArgs^ e) {
        frmConfiguracion^ ventanaPerfil = gcnew frmConfiguracion();
        this->Hide();
        ventanaPerfil->ShowDialog();
        this->Show();
        ThemeManager::Aplicar(this);

        // Al regresar, revisamos qué foto eligió el usuario
        String^ fotoElegida = ventanaPerfil->avatarElegido;

        // Si no está vacío o no es el default, intentamos cargarla
        if (!String::IsNullOrEmpty(fotoElegida)) {

            // 1. ¡Declaramos rutaFinal AQUÍ AFUERA para que el catch la pueda ver!
            String^ rutaFinal = fotoElegida;

            try {
                // Si la ruta NO tiene "C:\" o "D:\" significa que es un avatar de assets
                if (!fotoElegida->Contains(":\\")) {
                    String^ rutaExe = AppDomain::CurrentDomain->BaseDirectory;
                    String^ rutaSucia = rutaExe + "../../../assets/avatares/" + fotoElegida;

                    // ¡AQUÍ ESTÁ LA MAGIA! Limpiamos la ruta para que Windows la lea perfectamente
                    rutaFinal = System::IO::Path::GetFullPath(rutaSucia);
                }

                // Intentamos cargar la foto con la ruta ya limpia
                picPerfilBoton->Image = Image::FromFile(rutaFinal);

                // Ocultamos el botón de texto y mostramos la foto
                btnPerfil->Visible = false;
                picPerfilBoton->Visible = true;

            }
            catch (Exception^ ex) {
            }
        }
    }

    private: System::Void timerFarmeo_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (ticksGracia < 25) ticksGracia++;
        else Epsteam::ConexionBD::AvanzarTiempoJuego(idUsuarioActual);
    }
    };
}