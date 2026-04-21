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
        // Variable para atrapar la decisión del usuario y mandarla a la BD
        String^ avatarElegido = "avatar1.jpg";

        frmConfiguracion(void)
        {
            InitializeComponent();
            ConfigurarInterfaz();

            // Leemos el cerebro central para que el ComboBox muestre el tema correcto (0, 1 o 2)
            cmbTema->SelectedIndex = ThemeManager::TemaActual;

            // Y nos pintamos de ese color al nacer
            ThemeManager::Aplicar(this);
            // Obligamos a la lista de temas a quedarse siempre en blanco y negro para que sea legible
            this->cmbTema->BackColor = Color::White;
            this->cmbTema->ForeColor = Color::Black;        
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

        // --- NUEVOS CONTROLES PARA AVATARES PREDETERMINADOS ---
        Label^ lblEligeAvatar;
        PictureBox^ picPred1;
        PictureBox^ picPred2;
        PictureBox^ picPred3;
        PictureBox^ picPred4;
        PictureBox^ picPred5;

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
            this->Size = System::Drawing::Size(500, 750); // Hice la ventana un poco más alta
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

            // --- SECCIÓN IMAGEN DE PERFIL (PERSONALIZADA) ---
            picAvatar = gcnew PictureBox();
            picAvatar->Size = System::Drawing::Size(150, 150);
            picAvatar->Location = System::Drawing::Point(175, 80);
            picAvatar->BackColor = Color::DimGray;
            picAvatar->SizeMode = PictureBoxSizeMode::Zoom;
            picAvatar->BorderStyle = BorderStyle::FixedSingle;
            this->Controls->Add(picAvatar);

            btnCambiarAvatar = gcnew Button();
            btnCambiarAvatar->Text = "Subir de mi PC";
            btnCambiarAvatar->BackColor = Color::FromArgb(45, 45, 45);
            btnCambiarAvatar->ForeColor = Color::White;
            btnCambiarAvatar->FlatStyle = FlatStyle::Flat;
            btnCambiarAvatar->Location = System::Drawing::Point(175, 240);
            btnCambiarAvatar->Size = System::Drawing::Size(150, 30);
            btnCambiarAvatar->Click += gcnew System::EventHandler(this, &frmConfiguracion::btnCambiarAvatar_Click);
            this->Controls->Add(btnCambiarAvatar);

            // --- NUEVA SECCIÓN: AVATARES PREDETERMINADOS ---
            lblEligeAvatar = gcnew Label();
            lblEligeAvatar->Text = "O elige un avatar clásico:";
            lblEligeAvatar->ForeColor = Color::LightGray;
            lblEligeAvatar->Location = System::Drawing::Point(155, 290);
            lblEligeAvatar->AutoSize = true;
            lblEligeAvatar->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(lblEligeAvatar);

            // Avatar 1
            picPred1 = gcnew PictureBox();
            picPred1->Size = System::Drawing::Size(60, 60);
            picPred1->Location = System::Drawing::Point(50, 320); // Ajustado para que quepan 5
            picPred1->SizeMode = PictureBoxSizeMode::Zoom;
            picPred1->Cursor = Cursors::Hand;
            picPred1->Tag = "avatar1.jpg";
            picPred1->Click += gcnew System::EventHandler(this, &frmConfiguracion::SeleccionAvatar_Click);
            this->Controls->Add(picPred1);

            // Avatar 2
            picPred2 = gcnew PictureBox();
            picPred2->Size = System::Drawing::Size(60, 60);
            picPred2->Location = System::Drawing::Point(135, 320);
            picPred2->SizeMode = PictureBoxSizeMode::Zoom;
            picPred2->Cursor = Cursors::Hand;
            picPred2->Tag = "avatar2.jpg";
            picPred2->Click += gcnew System::EventHandler(this, &frmConfiguracion::SeleccionAvatar_Click);
            this->Controls->Add(picPred2);

            // Avatar 3
            picPred3 = gcnew PictureBox();
            picPred3->Size = System::Drawing::Size(60, 60);
            picPred3->Location = System::Drawing::Point(220, 320);
            picPred3->SizeMode = PictureBoxSizeMode::Zoom;
            picPred3->Cursor = Cursors::Hand;
            picPred3->Tag = "avatar3.jpg";
            picPred3->Click += gcnew System::EventHandler(this, &frmConfiguracion::SeleccionAvatar_Click);
            this->Controls->Add(picPred3);

            // Avatar 4 (¡NUEVO!)
            picPred4 = gcnew PictureBox();
            picPred4->Size = System::Drawing::Size(60, 60);
            picPred4->Location = System::Drawing::Point(305, 320);
            picPred4->SizeMode = PictureBoxSizeMode::Zoom;
            picPred4->Cursor = Cursors::Hand;
            picPred4->Tag = "avatar4.jpg"; // Asegúrate que tu archivo se llame así
            picPred4->Click += gcnew System::EventHandler(this, &frmConfiguracion::SeleccionAvatar_Click);
            this->Controls->Add(picPred4);

            // Avatar 5 (¡NUEVO!)
            picPred5 = gcnew PictureBox();
            picPred5->Size = System::Drawing::Size(60, 60);
            picPred5->Location = System::Drawing::Point(390, 320);
            picPred5->SizeMode = PictureBoxSizeMode::Zoom;
            picPred5->Cursor = Cursors::Hand;
            picPred5->Tag = "avatar5.jpg"; // Asegúrate que tu archivo se llame así
            picPred5->Click += gcnew System::EventHandler(this, &frmConfiguracion::SeleccionAvatar_Click);
            this->Controls->Add(picPred5);

            try {
                String^ rutaExe = AppDomain::CurrentDomain->BaseDirectory;

                String^ rutaFinal = rutaExe + "../../../assets/avatares/";

                picPred1->Image = Image::FromFile(rutaFinal + "avatar1.png");
                picPred2->Image = Image::FromFile(rutaFinal + "avatar2.png");
                picPred3->Image = Image::FromFile(rutaFinal + "avatar3.jpg");
                picPred4->Image = Image::FromFile(rutaFinal + "avatar4.png");
                picPred5->Image = Image::FromFile(rutaFinal + "avatar5.png");

                // Si llega aquí, significa que cargaron. Vamos a quitar los fondos grises.
                picPred1->BackColor = Color::Transparent;
                picPred2->BackColor = Color::Transparent;
                picPred3->BackColor = Color::Transparent;
                picPred4->BackColor = Color::Transparent;
                picPred5->BackColor = Color::Transparent;
            }
            catch (Exception^ ex) {
                // Si falla, el mensaje nos dirá la ruta final calculada
                String^ rutaIntento = AppDomain::CurrentDomain->BaseDirectory + "../../../assets/avatares/avatar1.jpg";
                MessageBox::Show("No se encontró en: " + rutaIntento, "Error de Ruta");
            }

            // --- SECCIÓN BIOGRAFÍA ---
            lblBio = gcnew Label();
            lblBio->Text = "Sobre mí (Biografía):";
            lblBio->ForeColor = Color::LightGray;
            lblBio->Location = System::Drawing::Point(50, 410); // Lo bajé un poco
            lblBio->AutoSize = true;
            lblBio->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(lblBio);

            txtBio = gcnew TextBox();
            txtBio->Multiline = true;
            txtBio->Location = System::Drawing::Point(50, 435);
            txtBio->Size = System::Drawing::Size(400, 80);
            txtBio->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(txtBio);

            // --- SECCIÓN TEMAS VISUALES ---
            lblTema = gcnew Label();
            lblTema->Text = "Tema de la Interfaz:";
            lblTema->ForeColor = Color::LightGray;
            lblTema->Location = System::Drawing::Point(50, 540); // Lo bajé un poco
            lblTema->AutoSize = true;
            lblTema->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(lblTema);

            cmbTema = gcnew ComboBox();
            cmbTema->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbTema->Location = System::Drawing::Point(50, 565);
            cmbTema->Size = System::Drawing::Size(400, 30);
            cmbTema->Font = gcnew System::Drawing::Font("Arial", 11);
            cmbTema->Items->Add("Tema Oscuro (Clásico Epsteam)");
            cmbTema->Items->Add("Tema Claro (Light Mode)");
            cmbTema->Items->Add("Tema Cyberpunk (Neón)");
            cmbTema->Items->Add("Tema Oceano Profundo");
            cmbTema->Items->Add("Tema Modo Sangriento");
            cmbTema->Items->Add("Tema Neón Synthwave");
            cmbTema->Items->Add("Tema Hacker Terminal");
            cmbTema->Items->Add("Tema Eclipse Solar");
            cmbTema->Items->Add("Tema Bosque Místico");
            cmbTema->Items->Add("Tema Atardecer Retro");
            cmbTema->SelectedIndex = 0; // Selecciona el oscuro por defecto
            cmbTema->SelectedIndexChanged += gcnew System::EventHandler(this, &frmConfiguracion::cmbTema_SelectedIndexChanged);
            this->Controls->Add(cmbTema);

            // --- BOTÓN GUARDAR ---
            btnGuardar = gcnew Button();
            btnGuardar->Text = "GUARDAR CAMBIOS";
            btnGuardar->BackColor = Color::MediumSeaGreen;
            btnGuardar->ForeColor = Color::White;
            btnGuardar->FlatStyle = FlatStyle::Flat;
            btnGuardar->Location = System::Drawing::Point(150, 640); // Lo bajé un poco
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
                picAvatar->Image = Image::FromFile(ofd->FileName);
                // Si sube una foto de su PC, guardamos la ruta completa (ofd->FileName) en la variable
                avatarElegido = ofd->FileName;
            }
        }

        // --- NUEVO: EVENTO DE CLIC EN AVATARES PREDETERMINADOS ---
        System::Void SeleccionAvatar_Click(System::Object^ sender, System::EventArgs^ e) {

            // 1. Limpiamos los fondos de todos los avatares para apagar selecciones anteriores
            picPred1->BackColor = Color::Transparent;
            picPred2->BackColor = Color::Transparent;
            picPred3->BackColor = Color::Transparent;
            picPred4->BackColor = Color::Transparent;
            picPred5->BackColor = Color::Transparent;

            // 2. Averiguamos a cuál le dieron clic
            PictureBox^ picClickeado = safe_cast<PictureBox^>(sender);

            // 3. Lo iluminamos poniéndole fondo azul
            picClickeado->BackColor = Color::DeepSkyBlue;

            // 4. Copiamos la foto al PictureBox grande de arriba para que el usuario la vea
            picAvatar->Image = picClickeado->Image;

            // 5. Atrapamos el texto oculto (Tag) y lo preparamos para la Base de Datos
            if (picClickeado->Tag != nullptr) {
                avatarElegido = picClickeado->Tag->ToString();
            }
        }

        // 2. Previsualización del Tema (La Magia Recursiva)
        System::Void cmbTema_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            ThemeManager::EstablecerTema(cmbTema->SelectedIndex);
            ThemeManager::Aplicar(this);
        }

        // 3. Simular Guardado
        System::Void btnGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ mensaje = "¡Perfil actualizado con éxito!";
            MessageBox::Show(mensaje, "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // --- EL MOTOR DE TEMAS (FUNCIÓN RECURSIVA) ---
        void AplicarTemaVisual(Control^ contenedor, Color colorFondo, Color colorTexto, Color colorBoton) {
            contenedor->BackColor = colorFondo;

            if (contenedor->GetType() == Label::typeid || contenedor->GetType() == TextBox::typeid) {
                contenedor->ForeColor = colorTexto;
            }

            if (contenedor->GetType() == Button::typeid) {
                contenedor->BackColor = colorBoton;
                contenedor->ForeColor = colorTexto;
            }

            for each (Control ^ c in contenedor->Controls) {
                AplicarTemaVisual(c, colorFondo, colorTexto, colorBoton);
            }
        }
    };
}