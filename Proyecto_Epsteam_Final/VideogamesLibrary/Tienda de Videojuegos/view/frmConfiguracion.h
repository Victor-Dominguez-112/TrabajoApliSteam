#pragma once
#include "ThemeManager.h"

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class frmConfiguracion : public System::Windows::Forms::Form
    {
    public:
        frmConfiguracion(void)
        {
            InitializeComponent();
            ConfigurarInterfaz();

            // Leemos el cerebro central para que el ComboBox muestre el tema correcto (0, 1 o 2)
            cmbTema->SelectedIndex = ThemeManager::TemaActual;

            // Y nos pintamos de ese color al nacer
            ThemeManager::Aplicar(this);
        }

    protected:
        ~frmConfiguracion() { if (components) { delete components; } }

    private:
        System::ComponentModel::Container^ components;

        // Controles de la interfaz
        Panel^ pnlTop;
        Label^ lblTitulo;
        Button^ btnVolver;

        PictureBox^ picAvatar;
        Button^ btnCambiarAvatar;

        Label^ lblBio;
        TextBox^ txtBio;

        Label^ lblTema;
        ComboBox^ cmbTema;

        Button^ btnGuardar;

        void InitializeComponent(void) {
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->Text = L"Configuración de Perfil";
        }

        void ConfigurarInterfaz() {
            // Diseño base de la ventana
            this->Size = System::Drawing::Size(500, 600);
            this->BackColor = Color::FromArgb(27, 40, 56); // Tema oscuro por defecto
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterParent;

            // --- BARRA SUPERIOR ---
            pnlTop = gcnew Panel();
            pnlTop->Dock = DockStyle::Top;
            pnlTop->Height = 60;
            pnlTop->BackColor = Color::FromArgb(23, 26, 33);
            this->Controls->Add(pnlTop);

            lblTitulo = gcnew Label();
            lblTitulo->Text = "MI PERFIL Y AJUSTES";
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Location = System::Drawing::Point(20, 15);
            lblTitulo->AutoSize = true;
            pnlTop->Controls->Add(lblTitulo);

            btnVolver = gcnew Button();
            btnVolver->Text = "VOLVER";
            btnVolver->BackColor = Color::FromArgb(60, 60, 60);
            btnVolver->ForeColor = Color::White;
            btnVolver->FlatStyle = FlatStyle::Flat;
            btnVolver->Location = System::Drawing::Point(370, 15);
            btnVolver->Size = System::Drawing::Size(100, 30);
            btnVolver->Click += gcnew System::EventHandler(this, &frmConfiguracion::btnVolver_Click);
            pnlTop->Controls->Add(btnVolver);

            // --- SECCIÓN IMAGEN DE PERFIL ---
            picAvatar = gcnew PictureBox();
            picAvatar->Size = System::Drawing::Size(150, 150);
            picAvatar->Location = System::Drawing::Point(175, 80);
            picAvatar->BackColor = Color::DimGray;
            picAvatar->SizeMode = PictureBoxSizeMode::Zoom;
            picAvatar->BorderStyle = BorderStyle::FixedSingle;
            this->Controls->Add(picAvatar);

            btnCambiarAvatar = gcnew Button();
            btnCambiarAvatar->Text = "Cambiar Imagen";
            btnCambiarAvatar->BackColor = Color::FromArgb(45, 45, 45);
            btnCambiarAvatar->ForeColor = Color::White;
            btnCambiarAvatar->FlatStyle = FlatStyle::Flat;
            btnCambiarAvatar->Location = System::Drawing::Point(175, 240);
            btnCambiarAvatar->Size = System::Drawing::Size(150, 30);
            btnCambiarAvatar->Click += gcnew System::EventHandler(this, &frmConfiguracion::btnCambiarAvatar_Click);
            this->Controls->Add(btnCambiarAvatar);

            // --- SECCIÓN BIOGRAFÍA ---
            lblBio = gcnew Label();
            lblBio->Text = "Sobre mí (Biografía):";
            lblBio->ForeColor = Color::LightGray;
            lblBio->Location = System::Drawing::Point(50, 290);
            lblBio->AutoSize = true;
            lblBio->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(lblBio);

            txtBio = gcnew TextBox();
            txtBio->Multiline = true;
            txtBio->Location = System::Drawing::Point(50, 315);
            txtBio->Size = System::Drawing::Size(400, 80);
            txtBio->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(txtBio);

            // --- SECCIÓN TEMAS VISUALES ---
            lblTema = gcnew Label();
            lblTema->Text = "Tema de la Interfaz:";
            lblTema->ForeColor = Color::LightGray;
            lblTema->Location = System::Drawing::Point(50, 420);
            lblTema->AutoSize = true;
            lblTema->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(lblTema);

            cmbTema = gcnew ComboBox();
            cmbTema->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbTema->Location = System::Drawing::Point(50, 445);
            cmbTema->Size = System::Drawing::Size(400, 30);
            cmbTema->Font = gcnew System::Drawing::Font("Arial", 11);
            cmbTema->Items->Add("Tema Oscuro (Clásico Epsteam)");
            cmbTema->Items->Add("Tema Claro (Light Mode)");
            cmbTema->Items->Add("Tema Cyberpunk (Neón)");
            cmbTema->SelectedIndex = 0; // Selecciona el oscuro por defecto
            cmbTema->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfiguracion::cmbTema_SelectedIndexChanged);
            this->Controls->Add(cmbTema);

            // --- BOTÓN GUARDAR ---
            btnGuardar = gcnew Button();
            btnGuardar->Text = "GUARDAR CAMBIOS";
            btnGuardar->BackColor = Color::MediumSeaGreen;
            btnGuardar->ForeColor = Color::White;
            btnGuardar->FlatStyle = FlatStyle::Flat;
            btnGuardar->Location = System::Drawing::Point(150, 520);
            btnGuardar->Size = System::Drawing::Size(200, 40);
            btnGuardar->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            btnGuardar->Click += gcnew System::EventHandler(this, &frmConfiguracion::btnGuardar_Click);
            this->Controls->Add(btnGuardar);
        }

        // --- LÓGICA DE EVENTOS ---

        System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close(); // Cierra la ventana de perfil
        }

        // 1. Abrir explorador de Windows para buscar una foto
        System::Void btnCambiarAvatar_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Filter = "Archivos de Imagen (*.jpg; *.jpeg; *.png)|*.jpg;*.jpeg;*.png";
            ofd->Title = "Selecciona tu nueva imagen de perfil";

            if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                // Carga la imagen seleccionada en el PictureBox
                picAvatar->Image = Image::FromFile(ofd->FileName);
                // NOTA FUTURA: Aquí guardaremos la ruta (ofd->FileName) en una variable para la BD
            }
        }

        // 2. Previsualización del Tema (La Magia Recursiva)
        System::Void cmbTema_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            // 1. Actualizamos el cerebro global
            ThemeManager::EstablecerTema(cmbTema->SelectedIndex);

            // 2. Aplicamos a la ventana actual para previsualizar
            ThemeManager::Aplicar(this);
        }

        // 3. Simular Guardado
        System::Void btnGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
            // Como ignoramos la BD por ahora, solo simulamos que funciona
            MessageBox::Show("¡Perfil actualizado con éxito!\n\nBiografía y tema guardados localmente.", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // --- EL MOTOR DE TEMAS (FUNCIÓN RECURSIVA) ---
        // Cambia el color de TODOS los elementos de la ventana automáticamente
        void AplicarTemaVisual(Control^ contenedor, Color colorFondo, Color colorTexto, Color colorBoton) {
            contenedor->BackColor = colorFondo;

            // Si el control es un Label o texto, le cambiamos la letra
            if (contenedor->GetType() == Label::typeid || contenedor->GetType() == TextBox::typeid) {
                contenedor->ForeColor = colorTexto;
            }

            // Si es un botón, le pintamos el fondo del color especial de botones
            if (contenedor->GetType() == Button::typeid) {
                contenedor->BackColor = colorBoton;
                contenedor->ForeColor = colorTexto;
            }

            // Si este control tiene más controles adentro (ej. un Panel), nos metemos y hacemos lo mismo
            for each (Control ^ c in contenedor->Controls) {
                AplicarTemaVisual(c, colorFondo, colorTexto, colorBoton);
            }
        }
    };
}