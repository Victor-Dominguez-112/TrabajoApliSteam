#pragma once
#include "frmTicket.h"
#include "frmBiblioteca.h"
#include "ConexionBD.h" 
#include "frmPago.h"
#include "frmCarrito.h"
#include "frmConfiguracion.h"
#include "ThemeManager.h"

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /**
     * @class GestorImagenes
     * @brief Clase auxiliar para el manejo de las carátulas de los videojuegos.
     */
    public ref class GestorImagenes {
    public:
        /**
         * @brief Formatea el título de un juego para obtener la ruta de su imagen local.
         * @details Convierte el texto a minúsculas, reemplaza espacios por guiones bajos y elimina caracteres especiales.
         * @param nombreJuego El título del videojuego tal como viene de la base de datos.
         * @return Ruta relativa hacia el archivo de imagen (.jpg).
         */
        static String^ ObtenerRuta(String^ nombreJuego) {
            String^ nombreLimpio = nombreJuego->Trim()->ToLower();
            nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
            return "img/" + nombreLimpio + ".jpg";
        }
    };

    /**
     * @class frmTienda
     * @brief Formulario principal de la aplicación, actúa como el catálogo o "Storefront".
     * @details Permite al usuario visualizar juegos, aplicar filtros dinámicos (género, categoría, etc.),
     * buscar por nombre, ajustar un límite de precio, agregar ítems al carrito y navegar hacia su biblioteca.
     */
    public ref class frmTienda : public System::Windows::Forms::Form
    {
    public:
        /**
         * @brief Constructor de la Tienda principal.
         * @details Configura la interfaz de usuario, inicializa las listas del carrito,
         * arranca los temporizadores de búsqueda y farmeo, y carga el catálogo completo por defecto.
         * @param idLogueado ID del usuario que acaba de iniciar sesión.
         */
        frmTienda(int idLogueado)
        {
            idUsuarioActual = idLogueado;
            InitializeComponent();
            ThemeManager::Aplicar(this);
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

            carritoCompras = gcnew System::Collections::Generic::List<cli::array<System::String^>^>();

            btnCarrito = gcnew Button();
            btnCarrito->Text = "CARRITO (0)";
            btnCarrito->BackColor = Color::FromArgb(45, 45, 45);
            btnCarrito->ForeColor = Color::White;
            btnCarrito->FlatStyle = FlatStyle::Flat;
            btnCarrito->Size = System::Drawing::Size(130, 35);
            btnCarrito->Location = System::Drawing::Point(600, 20);
            btnCarrito->Click += gcnew System::EventHandler(this, &frmTienda::btnCarrito_Click);
            pnlNav->Controls->Add(btnCarrito);

            
            Button^ btnPerfil = gcnew Button();
            btnPerfil->Text = "MI PERFIL";
            btnPerfil->BackColor = Color::FromArgb(45, 45, 45);
            btnPerfil->ForeColor = Color::White;
            btnPerfil->FlatStyle = FlatStyle::Flat;
            btnPerfil->Size = System::Drawing::Size(100, 35);
            btnPerfil->Location = System::Drawing::Point(740, 20); 
            btnPerfil->Click += gcnew System::EventHandler(this, &frmTienda::btnPerfil_Click);
            pnlNav->Controls->Add(btnPerfil);

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
        /**
         * @brief Destructor de la clase.
         * @details Libera la memoria de los componentes de la interfaz gráfica.
         */
        ~frmTienda() { if (components) { delete components; } }

    private:
        /** @brief Bandera para evitar que eventos de texto disparen búsquedas innecesarias. */
        bool ignorarBusqueda;
        /** @brief Temporizador para simular horas de juego en segundo plano. */
        System::Windows::Forms::Timer^ timerFarmeo;
        /** @brief Temporizador (Debounce) para retrasar la búsqueda en base de datos mientras se escribe. */
        System::Windows::Forms::Timer^ timerBusqueda;
        /** @brief Retraso inicial para evitar que el farmeo arranque de golpe al abrir la tienda. */
        int ticksGracia;
        /** @brief ID del cliente activo. */
        int idUsuarioActual;

        /** @brief Panel de navegación superior. */
        System::Windows::Forms::Panel^ pnlNav;
        /** @brief Etiqueta con el Logo de la tienda. */
        System::Windows::Forms::Label^ lblLogo;
        /** @brief Panel de flujo donde se inyectan las tarjetas (cards) de los videojuegos. */
        System::Windows::Forms::FlowLayoutPanel^ flowTienda;
        /** @brief Botón para cerrar sesión y volver al login. */
        System::Windows::Forms::Button^ btnCerrarSesion;
        /** @brief Contenedor de componentes. */
        System::ComponentModel::Container^ components;

        /** @brief Panel secundario que aloja todos los filtros y el buscador. */
        System::Windows::Forms::Panel^ pnlBuscador;
        /** @brief Caja de texto principal para buscar por nombre o etiqueta. */
        System::Windows::Forms::TextBox^ txtBusqueda;
        /** @brief Barra deslizante para ajustar el límite de precio. */
        System::Windows::Forms::TrackBar^ tbPrecio;
        /** @brief Etiqueta que muestra el valor numérico del TrackBar. */
        System::Windows::Forms::Label^ lblPrecio;
        /** @brief Lista flotante de sugerencias de autocompletado de búsqueda. */
        System::Windows::Forms::ListBox^ lstSugerencias;

        /** @brief Lista de casillas de verificación para Géneros. */
        System::Windows::Forms::CheckedListBox^ clbGeneros;
        /** @brief Lista de casillas de verificación para Categorías. */
        System::Windows::Forms::CheckedListBox^ clbCategorias;
        /** @brief Lista de casillas de verificación para Etiquetas. */
        System::Windows::Forms::CheckedListBox^ clbEtiquetas;
        /** @brief Lista de casillas de verificación para Desarrolladores. */
        System::Windows::Forms::CheckedListBox^ clbDesarrolladores;
        /** @brief Lista de casillas de verificación para Editores. */
        System::Windows::Forms::CheckedListBox^ clbEditores;

        // Paneles desplegables que ocultan/muestran las Listas de casillas (CheckedListBox)
        System::Windows::Forms::Panel^ pnlFiltroGeneros;
        System::Windows::Forms::Panel^ pnlFiltroCategorias;
        System::Windows::Forms::Panel^ pnlFiltroEtiquetas;
        System::Windows::Forms::Panel^ pnlFiltroDesarrolladores;
        System::Windows::Forms::Panel^ pnlFiltroEditores;

        /** @brief Lista genérica en memoria que funge como Carrito de Compras. */
        System::Collections::Generic::List<cli::array<System::String^>^>^ carritoCompras;
        /** @brief Botón de acceso al carrito, muestra la cantidad de ítems actual. */
        System::Windows::Forms::Button^ btnCarrito;

        /**
         * @brief Construye e inicializa dinámicamente el área de filtros y barra de búsqueda.
         */
        void ConstruirInterfazBuscador() {
            pnlBuscador = gcnew Panel();
            pnlBuscador->Dock = DockStyle::Top;
            pnlBuscador->Height = 140; // Más espacio para respirar
            pnlBuscador->BackColor = Color::FromArgb(32, 45, 60);
            this->Controls->Add(pnlBuscador);
            pnlBuscador->BringToFront();

            // Buscador alineado arriba a la izquierda
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

            // Sugerencias debajo del buscador
            lstSugerencias = gcnew ListBox();
            lstSugerencias->Location = System::Drawing::Point(35, 140);
            lstSugerencias->Size = System::Drawing::Size(300, 100);
            lstSugerencias->Visible = false;
            lstSugerencias->MouseClick += gcnew MouseEventHandler(this, &frmTienda::lstSugerencias_MouseClick);
            this->Controls->Add(lstSugerencias);
            lstSugerencias->BringToFront();

            // Barra de precio a la derecha
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

            // ¡DISEÑO LIMPIO! Todos los filtros en una sola línea recta
            CrearBotonFiltro("Géneros", 35, 80, pnlFiltroGeneros, clbGeneros, "genero");
            CrearBotonFiltro("Categorías", 165, 80, pnlFiltroCategorias, clbCategorias, "categoria");
            CrearBotonFiltro("Etiquetas", 295, 80, pnlFiltroEtiquetas, clbEtiquetas, "etiqueta");
            CrearBotonFiltro("Desarrollador", 425, 80, pnlFiltroDesarrolladores, clbDesarrolladores, "desarrollador");
            CrearBotonFiltro("Editor", 555, 80, pnlFiltroEditores, clbEditores, "editor");
        }

        /**
         * @brief Crea un botón desplegable y su respectivo panel de casillas de verificación.
         * @param texto Texto visible en el botón del filtro.
         * @param posX Coordenada X del botón.
         * @param posY Coordenada Y del botón.
         * @param panelOut Referencia al panel donde se aloja la lista.
         * @param clbOut Referencia al CheckedListBox generado.
         * @param tipoFiltroBD Nombre de la tabla en base de datos para cargar las opciones.
         */
        void CrearBotonFiltro(String^ texto, int posX, int posY, Panel^% panelOut, CheckedListBox^% clbOut, String^ tipoFiltroBD) {
            Button^ btn = gcnew Button();
            btn->Text = texto;
            btn->Location = System::Drawing::Point(posX, posY);
            btn->Size = System::Drawing::Size(120, 35);
            btn->BackColor = Color::FromArgb(45, 45, 45);
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            pnlBuscador->Controls->Add(btn);

            // El panel desplegable sale EXACTAMENTE debajo de su botón
            panelOut = gcnew Panel();
            panelOut->Location = System::Drawing::Point(posX, 140);
            panelOut->Size = System::Drawing::Size(180, 200); // Más ancho para que no se corten las letras
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

        /** @brief Elimina el texto placeholder de la búsqueda al recibir foco. */
    private: System::Void txtBusqueda_GotFocus(System::Object^ sender, System::EventArgs^ e) {
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") {
            ignorarBusqueda = true;
            txtBusqueda->Text = "";
            txtBusqueda->ForeColor = Color::Black;
            ignorarBusqueda = false;
        }
    }

           /** @brief Restaura el texto placeholder si la caja quedó vacía al perder el foco. */
    private: System::Void txtBusqueda_LostFocus(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrWhiteSpace(txtBusqueda->Text)) {
            ignorarBusqueda = true;
            txtBusqueda->Text = "Buscar juego o etiqueta...";
            txtBusqueda->ForeColor = Color::Gray;
            ignorarBusqueda = false;
        }
    }

           /** @brief Evita ruidos de sistema (Beep) al presionar Enter en el buscador. */
    private: System::Void txtBusqueda_KeyPress(System::Object^ sender, KeyPressEventArgs^ e) {
        if (e->KeyChar == (char)13 || e->KeyChar == (char)27) e->Handled = true;
    }

           /** @brief Permite realizar la búsqueda con Enter o cerrarla con Escape. */
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

           /** @brief Oculta los paneles desplegables de filtros si el usuario da clic fuera de ellos. */
    private: System::Void ClicFueraDeFiltros(System::Object^ sender, MouseEventArgs^ e) {
        pnlFiltroGeneros->Visible = false;
        pnlFiltroCategorias->Visible = false;
        pnlFiltroEtiquetas->Visible = false;
        pnlFiltroDesarrolladores->Visible = false;
        pnlFiltroEditores->Visible = false;
        lstSugerencias->Visible = false;
    }

           /** @brief Alterna la visibilidad (abrir/cerrar) del panel de un filtro específico. */
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

           /** @brief Actualiza la etiqueta visual del precio máximo y dispara una nueva búsqueda. */
    private: System::Void ActualizarLabelPrecio(System::Object^ sender, System::EventArgs^ e) {
        lblPrecio->Text = "Precio Máx: $" + tbPrecio->Value + " MXN";
        IniciarTimerBusqueda(sender, e);
    }

           /** @brief Inicia o reinicia el temporizador de Debounce para no saturar la BD al escribir. */
    private: System::Void IniciarTimerBusqueda(System::Object^ sender, System::EventArgs^ e) {
        if (ignorarBusqueda) return;
        if (txtBusqueda->Text == "Buscar juego o etiqueta...") return;
        timerBusqueda->Stop(); timerBusqueda->Start();
    }

           /** @brief Evento disparado cuando el temporizador de búsqueda alcanza su límite. */
    private: System::Void timerBusqueda_Tick(System::Object^ sender, System::EventArgs^ e) {
        timerBusqueda->Stop(); EjecutarBusquedaEnBD();
    }

           /** @brief Dispara una búsqueda en la BD de forma asíncrona al marcar o desmarcar un filtro. */
    private: System::Void FiltroCasilla_Modificada(System::Object^ sender, ItemCheckEventArgs^ e) {
        this->BeginInvoke(gcnew MethodInvoker(this, &frmTienda::EjecutarBusquedaEnBD));
    }

           /**
            * @brief Concentra toda la lógica de filtrado y búsqueda.
            * @details Extrae los IDs de las casillas seleccionadas de todos los paneles, el límite
            * de precio del TrackBar y el texto del TextBox. Lo envía todo a ConexionBD, que
            * devuelve un DataTable con los resultados. También gestiona las sugerencias de autocompletado.
            */
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

           /** @brief Carga un juego en el buscador principal al hacer clic en una sugerencia de la lista. */
    private: System::Void lstSugerencias_MouseClick(System::Object^ sender, MouseEventArgs^ e) {
        if (lstSugerencias->SelectedItem != nullptr) {
            ignorarBusqueda = true;
            txtBusqueda->Text = lstSugerencias->SelectedItem->ToString();
            lstSugerencias->Visible = false;
            ignorarBusqueda = false;
            EjecutarBusquedaEnBD();
        }
    }

           /**
            * @brief Renderiza masivamente la cuadrícula de juegos en la tienda.
            * @param juegosTabla DataTable resultante de la base de datos con los juegos a mostrar.
            */
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
                   lblVacio->Text = "No se encontraron juegos con esos filtros 😢";
                   lblVacio->ForeColor = Color::White;
                   lblVacio->AutoSize = true;
                   lblVacio->Font = gcnew System::Drawing::Font("Arial", 14);
                   flowTienda->Controls->Add(lblVacio);
               }
               flowTienda->ResumeLayout();
           }

           /**
            * @brief Genera y dibuja una tarjeta visual individual para un videojuego.
            * @param id_juego ID del videojuego.
            * @param titulo Título del videojuego.
            * @param precio Precio base formateado.
            */
           void AgregarJuego(int id_juego, String^ titulo, String^ precio) {
               Panel^ card = gcnew Panel();
               // ¡MAGIA! Tarjetas más altas para acomodar mejor la imagen
               card->Size = System::Drawing::Size(210, 330);
               card->BackColor = Color::FromArgb(45, 45, 45);
               card->Margin = System::Windows::Forms::Padding(15);

               PictureBox^ picPortada = gcnew PictureBox();
               picPortada->Dock = DockStyle::Fill;
               // ¡MAGIA 2! StretchImage para que la portada no deje bordes negros ni se corte raro
               picPortada->SizeMode = PictureBoxSizeMode::StretchImage;
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
               lblTitulo->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
               lblTitulo->Dock = DockStyle::Top;
               lblTitulo->TextAlign = ContentAlignment::MiddleCenter;
               lblTitulo->Height = 35; // Un poco más alto por si el nombre es largo

               Label^ lblPrecio = gcnew Label();
               lblPrecio->Text = precio;
               lblPrecio->ForeColor = Color::LightGreen; // Precio en verde
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

               btnComprar->Tag = gcnew cli::array<System::String^>{ id_juego.ToString(), titulo, precio };
               btnComprar->Click += gcnew System::EventHandler(this, &frmTienda::btnComprar_Click);

               card->Controls->Add(picPortada);
               card->Controls->Add(lblTitulo);
               card->Controls->Add(btnComprar);
               card->Controls->Add(lblPrecio);
               picPortada->SendToBack();

               flowTienda->Controls->Add(card);
           }

#pragma region Windows Form Designer generated code
           /**
            * @brief Método autogenerado por el Diseñador de Windows Forms.
            * @details Inicializa componentes principales y de diseño de ventana general.
            */
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
               // Ajustamos el margen para que los juegos empiecen más abajo de los filtros
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

           /**
            * @brief Cierra sesión, detiene los temporizadores de fondo y cierra la ventana.
            */
    private: System::Void btnCerrarSesion_Click(System::Object^ sender, System::EventArgs^ e) {
        timerFarmeo->Stop(); // Lo que ya tenías

        // ¡NUEVO! Reseteamos el tema global al Oscuro (0) antes de irnos
        ThemeManager::EstablecerTema(0);

        this->Close(); // Regresamos al login
    }

           /**
            * @brief Evento que añade un juego al carrito.
            * @details Comprueba primero en la base de datos si el usuario ya es dueño del juego.
            * Luego comprueba si el juego ya está en el carrito para no duplicarlo. Si pasa las validaciones,
            * lo agrega, incrementa el contador del carrito y cambia el color del botón.
            */
    private: System::Void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btnCliquado = (Button^)sender;
        cli::array<System::String^>^ datos = (cli::array<System::String^>^)btnCliquado->Tag;

        String^ idJuegoStr = datos[0];
        String^ nombreJuego = datos[1];
        String^ precioReal = datos[2];

        bool yaLoTiene = false;
        DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(idUsuarioActual);
        if (misJuegos != nullptr) {
            for (int i = 0; i < misJuegos->Rows->Count; i++) {
                if (misJuegos->Rows[i]["titulo"]->ToString() == nombreJuego) {
                    yaLoTiene = true;
                    break;
                }
            }
        }
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

           /**
            * @brief Abre el formulario de la cesta de la compra.
            * @details Verifica que el carrito no esté vacío. Si el usuario vuelve del carrito,
            * esta función se encarga de re-evaluar qué juegos fueron eliminados de la lista y
            * restablece los botones ("AGREGAR AL CARRO" o "AGREGADO") visualmente en la tienda.
            */
    private: System::Void btnCarrito_Click(System::Object^ sender, System::EventArgs^ e) {
        if (carritoCompras->Count == 0) {
            MessageBox::Show("Tu carrito está vacío.", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
            return;
        }

        frmCarrito^ ventanaCarrito = gcnew frmCarrito(idUsuarioActual, carritoCompras);
        ventanaCarrito->ShowDialog();

        btnCarrito->Text = "CARRITO (" + Convert::ToString(carritoCompras->Count) + ")";

        for each(Control ^ card in flowTienda->Controls) {
            for each(Control ^ c in card->Controls) {
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

           /**
            * @brief Abre el formulario de la Biblioteca de Juegos.
            */
    private: System::Void btnBiblioteca_Click(System::Object^ sender, System::EventArgs^ e) {
        frmBiblioteca^ biblioteca = gcnew frmBiblioteca();
        this->Hide();
        biblioteca->ShowDialog();
        this->Show();
    }

    private: System::Void btnPerfil_Click(System::Object^ sender, System::EventArgs^ e) {
        frmConfiguracion^ ventanaPerfil = gcnew frmConfiguracion();
        this->Hide();
        ventanaPerfil->ShowDialog(); // El programa se pausa en esta línea

        // --- CUANDO LA VENTANA DE PERFIL SE CIERRA, EL CÓDIGO CONTINÚA AQUÍ ---
        this->Show(); // La tienda reaparece
        ThemeManager::Aplicar(this); // ¡CLAVE! Obligamos a la tienda a pintarse con el tema nuevo
    }

           /**
            * @brief Función asíncrona que simula el tiempo de juego ("Farmeo").
            * @details Cuenta un pequeño retraso inicial (ticksGracia) para evitar saturación al cargar,
            * y después invoca a ConexionBD::AvanzarTiempoJuego repetidamente en segundo plano.
            */
    private: System::Void timerFarmeo_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (ticksGracia < 25) ticksGracia++;
        else Epsteam::ConexionBD::AvanzarTiempoJuego(idUsuarioActual);
    }
    };
}