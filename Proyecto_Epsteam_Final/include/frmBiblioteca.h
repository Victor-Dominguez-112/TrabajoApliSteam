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
     */
    public ref class frmBiblioteca : public System::Windows::Forms::Form
    {
    public:
        frmBiblioteca()
        {
            InitializeComponent();
            ConfigurarInterfaz();
            CargarBiblioteca();
        }

    protected:
        ~frmBiblioteca() { if (components) { delete components; } }

    private:
        System::ComponentModel::Container^ components;
        Panel^ pnlTop;
        Label^ lblTitulo;
        Button^ btnVolver;
        FlowLayoutPanel^ flowJuegos;

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

        void ConfigurarInterfaz() {
            // 1. IGUALAMOS EL TAMAÑO AL DE LA TIENDA
            this->Size = System::Drawing::Size(1000, 700);
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
            btnVolver->Location = System::Drawing::Point(820, 12); // Ajustado a la derecha por el nuevo ancho
            btnVolver->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnVolver_Click);
            pnlTop->Controls->Add(btnVolver);

            flowJuegos = gcnew FlowLayoutPanel();
            flowJuegos->Dock = DockStyle::Fill;
            flowJuegos->AutoScroll = true;
            flowJuegos->Padding = System::Windows::Forms::Padding(20, 20, 20, 20); // Ajuste de padding
            this->Controls->Add(flowJuegos);
            flowJuegos->BringToFront();
        }

        void CargarBiblioteca() {
            flowJuegos->Controls->Clear();
            flowJuegos->ResumeLayout();
            ThemeManager::Aplicar(this);

            DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(Epsteam::ConexionBD::idUsuarioActual);

            if (misJuegos != nullptr && misJuegos->Rows->Count > 0) {
                for (int i = 0; i < misJuegos->Rows->Count; i++) {
                    DataRow^ fila = misJuegos->Rows[i];
                    String^ titulo = fila["titulo"]->ToString();
                    String^ tiempoStr = fila["tiempo_jugado_minutos"]->ToString();

                    Panel^ card = gcnew Panel();
                    // 2. IGUALAMOS EL TAMAÑO DE LA TARJETA AL DE LA TIENDA
                    card->Size = System::Drawing::Size(200, 310);
                    card->BackColor = Color::FromArgb(45, 45, 45);
                    // 3. IGUALAMOS LOS MÁRGENES PARA QUE QUEPAN 4 POR FILA
                    card->Margin = System::Windows::Forms::Padding(10, 15, 10, 15);

                    PictureBox^ picPortada = gcnew PictureBox();
                    picPortada->Dock = DockStyle::Fill;
                    // 4. CAMBIAMOS ZOOM POR STRETCH PARA QUE LLENE IGUAL QUE LA TIENDA
                    picPortada->SizeMode = PictureBoxSizeMode::StretchImage;

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
                    lblTitulo->Height = 35; // Altura fija como en la tienda

                    Label^ lblTiempo = gcnew Label();
                    lblTiempo->Text = "Tiempo: " + tiempoStr + " min";
                    lblTiempo->ForeColor = Color::MediumSeaGreen;
                    lblTiempo->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
                    lblTiempo->Dock = DockStyle::Bottom;
                    lblTiempo->TextAlign = ContentAlignment::MiddleCenter;
                    lblTiempo->Height = 25; // Altura fija

                    Button^ btnJugar = gcnew Button();
                    btnJugar->Text = "JUGAR";
                    btnJugar->FlatStyle = FlatStyle::Flat;
                    btnJugar->ForeColor = Color::White;
                    btnJugar->BackColor = Color::FromArgb(0, 120, 215);
                    btnJugar->Dock = DockStyle::Bottom;
                    btnJugar->Height = 35; // Altura fija como el botón comprar
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

        System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void btnJugar_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("¡Iniciando juego! Preparando motores gráficos...", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

    private: System::Void frmBiblioteca_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}