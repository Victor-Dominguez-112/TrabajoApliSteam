#pragma once
#include "ConexionBD.h"
#include "ThemeManager.h"

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /**
     * @class frmBiblioteca
     * @brief Formulario que representa la interfaz de la "Biblioteca de Juegos" del usuario.
     * @details Esta ventana se encarga de leer la base de datos para extraer los juegos que
     * el usuario logueado ha comprado, generando dinámicamente una cuadrícula visual ("tarjetas")
     * con la portada del juego, su título, el tiempo jugado y un botón para iniciar la simulación del juego.
     */
    public ref class frmBiblioteca : public System::Windows::Forms::Form
    {
    public:
        /**
         * @brief Constructor por defecto de frmBiblioteca.
         * @details Llama a la inicialización de componentes básicos, configura el diseño visual
         * y ejecuta la carga dinámica de los juegos del usuario desde la base de datos.
         */
        frmBiblioteca()
        {
            InitializeComponent();
            ConfigurarInterfaz();
            CargarBiblioteca();
        }

    protected:
        /**
         * @brief Destructor de la clase.
         * @details Libera los recursos y componentes visuales administrados por la ventana.
         */
        ~frmBiblioteca() { if (components) { delete components; } }

    private:
        /** @brief Contenedor principal de componentes de Windows Forms. */
        System::ComponentModel::Container^ components;
        /** @brief Panel superior que funciona como barra de navegación o encabezado. */
        Panel^ pnlTop;
        /** @brief Etiqueta que muestra el título de la ventana ("MI BIBLIOTECA DE JUEGOS"). */
        Label^ lblTitulo;
        /** @brief Botón para cerrar la biblioteca y regresar a la interfaz de la tienda. */
        Button^ btnVolver;
        /** @brief Panel de flujo dinámico donde se inyectan y ordenan las tarjetas de los videojuegos. */
        FlowLayoutPanel^ flowJuegos;

        /**
         * @brief Método autogenerado por el Diseñador de Windows Forms.
         * @details Inicializa los componentes básicos del formulario.
         */
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmBiblioteca::typeid));
            this->SuspendLayout();
            // 
            // frmBiblioteca
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(282, 253);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"frmBiblioteca";
            this->Load += gcnew System::EventHandler(this, &frmBiblioteca::frmBiblioteca_Load);
            this->ResumeLayout(false);

        }

        /**
         * @brief Configura las propiedades de diseño y controles UI generados manualmente.
         * @details Establece los colores, tamaños, posiciones y estilos flat de los botones,
         * encabezados y el panel contenedor de la cuadrícula de juegos.
         */
        void ConfigurarInterfaz() {
            this->Size = System::Drawing::Size(900, 600);
            this->BackColor = Color::FromArgb(27, 40, 56);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterParent;

            pnlTop = gcnew Panel();
            pnlTop->Dock = DockStyle::Top;
            pnlTop->Height = 60;
            pnlTop->BackColor = Color::FromArgb(23, 26, 33);
            this->Controls->Add(pnlTop);

            lblTitulo = gcnew Label();
            lblTitulo->Text = "MI BIBLIOTECA DE JUEGOS";
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Location = System::Drawing::Point(20, 15);
            lblTitulo->AutoSize = true;
            pnlTop->Controls->Add(lblTitulo);

            btnVolver = gcnew Button();
            btnVolver->Text = "VOLVER A LA TIENDA";
            btnVolver->BackColor = Color::FromArgb(60, 60, 60);
            btnVolver->ForeColor = Color::White;
            btnVolver->FlatStyle = FlatStyle::Flat;
            btnVolver->Size = System::Drawing::Size(150, 35);
            btnVolver->Location = System::Drawing::Point(720, 12);
            btnVolver->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnVolver_Click);
            pnlTop->Controls->Add(btnVolver);

            flowJuegos = gcnew FlowLayoutPanel();
            flowJuegos->Dock = DockStyle::Fill;
            flowJuegos->AutoScroll = true;
            flowJuegos->Padding = System::Windows::Forms::Padding(20);
            this->Controls->Add(flowJuegos);
            flowJuegos->BringToFront();
        }

        /**
         * @brief Carga y dibuja el inventario de juegos del usuario.
         * @details Llama a ConexionBD::ObtenerMisJuegos() y por cada registro devuelto,
         * genera un Panel visual (tarjeta) con PictureBox (portada), Labels (título y tiempo) y un Button (Jugar).
         * Si el usuario no tiene juegos, muestra un mensaje invitándolo a la tienda.
         */
        void CargarBiblioteca() {
            flowJuegos->Controls->Clear();
            flowJuegos->ResumeLayout();
            ThemeManager::Aplicar(this);

            // Traemos TUS juegos directamente desde la Base de Datos
            DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(Epsteam::ConexionBD::idUsuarioActual);

            if (misJuegos != nullptr && misJuegos->Rows->Count > 0) {
                for (int i = 0; i < misJuegos->Rows->Count; i++) {
                    DataRow^ fila = misJuegos->Rows[i];
                    String^ titulo = fila["titulo"]->ToString();
                    String^ tiempoStr = fila["tiempo_jugado_minutos"]->ToString();

                    Panel^ card = gcnew Panel();
                    card->Size = System::Drawing::Size(200, 250);
                    card->BackColor = Color::FromArgb(45, 45, 45);
                    card->Margin = System::Windows::Forms::Padding(15);

                    PictureBox^ picPortada = gcnew PictureBox();
                    picPortada->Dock = DockStyle::Fill;
                    picPortada->SizeMode = PictureBoxSizeMode::Zoom;

                    // Buscamos la imagen del juego
                    String^ nombreLimpio = titulo->Trim()->ToLower()->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
                    String^ rutaImagen = "../assets/img/" + nombreLimpio + ".jpg";
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

                    Label^ lblTiempo = gcnew Label();
                    lblTiempo->Text = "Tiempo: " + tiempoStr + " min";
                    lblTiempo->ForeColor = Color::MediumSeaGreen;
                    lblTiempo->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
                    lblTiempo->Dock = DockStyle::Bottom;
                    lblTiempo->TextAlign = ContentAlignment::MiddleCenter;
                    lblTiempo->Height = 30;

                    Button^ btnJugar = gcnew Button();
                    btnJugar->Text = "JUGAR";
                    btnJugar->FlatStyle = FlatStyle::Flat;
                    btnJugar->ForeColor = Color::White;
                    btnJugar->BackColor = Color::FromArgb(0, 120, 215);
                    btnJugar->Dock = DockStyle::Bottom;
                    btnJugar->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnJugar_Click);

                    card->Controls->Add(picPortada);
                    card->Controls->Add(lblTitulo);
                    card->Controls->Add(btnJugar);
                    card->Controls->Add(lblTiempo);
                    picPortada->SendToBack();

                    flowJuegos->Controls->Add(card);
                }
            }
            else {
                Label^ lblVacio = gcnew Label();
                lblVacio->Text = "Aún no tienes juegos en tu biblioteca.\n¡Ve a la tienda a comprar algunos!";
                lblVacio->ForeColor = Color::White;
                lblVacio->AutoSize = true;
                lblVacio->Font = gcnew System::Drawing::Font("Arial", 14);
                flowJuegos->Controls->Add(lblVacio);
            }
        }

        /**
         * @brief Evento disparado al hacer clic en el botón "VOLVER A LA TIENDA".
         * @param sender Objeto que dispara el evento.
         * @param e Argumentos del evento.
         */
        System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close(); // Cierra la biblioteca y regresa a la tienda
        }

        /**
         * @brief Evento disparado al hacer clic en el botón "JUGAR" de cualquier tarjeta.
         * @details Simula el inicio del videojuego seleccionado mediante un mensaje en pantalla.
         * @param sender Objeto que dispara el evento.
         * @param e Argumentos del evento.
         */
        System::Void btnJugar_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("¡Iniciando juego! Preparando motores gráficos...", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        /**
         * @brief Evento de carga inicial del formulario (vacío por defecto).
         * @param sender Objeto que dispara el evento.
         * @param e Argumentos del evento.
         */
    private: System::Void frmBiblioteca_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}