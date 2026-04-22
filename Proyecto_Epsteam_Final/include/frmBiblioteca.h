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
        PictureBox^ picVolver; // Ahora usamos un PictureBox para volver
        FlowLayoutPanel^ flowJuegos;

        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmBiblioteca::typeid));
            this->SuspendLayout();
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1000, 700);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"frmBiblioteca";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterParent;
            this->ResumeLayout(false);
        }

        void ConfigurarInterfaz() {
            this->Size = System::Drawing::Size(1000, 700);

            // Aplicamos el tema (esto pondrá fondo blanco y letras negras si así lo configuramos)
            ThemeManager::Aplicar(this);

            pnlTop = gcnew Panel();
            pnlTop->Dock = DockStyle::Top;
            pnlTop->Height = 60;
            pnlTop->BackColor = Color::FromArgb(23, 26, 33);
            this->Controls->Add(pnlTop);

            lblTitulo = gcnew Label();
            lblTitulo->Text = "MI BIBLIOTECA";
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Location = System::Drawing::Point(20, 15);
            lblTitulo->AutoSize = true;
            pnlTop->Controls->Add(lblTitulo);

            // --- BOTÓN VOLVER (Como imagen) ---
            picVolver = gcnew PictureBox();
            picVolver->Size = System::Drawing::Size(40, 40);
            picVolver->Location = System::Drawing::Point(930, 10);
            picVolver->SizeMode = PictureBoxSizeMode::Zoom;
            picVolver->Cursor = Cursors::Hand;

            try {
                String^ rutaExe = AppDomain::CurrentDomain->BaseDirectory;
                // Usamos la misma lógica de ruta limpia que en la tienda
                picVolver->Image = Image::FromFile(System::IO::Path::GetFullPath(rutaExe + "../../../assets/img/volver.png"));
            }
            catch (...) {
                
            }

            picVolver->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnVolver_Click);
            pnlTop->Controls->Add(picVolver);

            flowJuegos = gcnew FlowLayoutPanel();
            flowJuegos->Dock = DockStyle::Fill;
            flowJuegos->AutoScroll = true;
            flowJuegos->Padding = System::Windows::Forms::Padding(20, 20, 20, 20);
            this->Controls->Add(flowJuegos);
            flowJuegos->BringToFront();
        }

        void CargarBiblioteca() {
            flowJuegos->Controls->Clear();

            // Obtenemos los juegos de la BD
            DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(Epsteam::ConexionBD::idUsuarioActual);

            if (misJuegos != nullptr && misJuegos->Rows->Count > 0) {
                for (int i = 0; i < misJuegos->Rows->Count; i++) {
                    DataRow^ fila = misJuegos->Rows[i];
                    String^ titulo = fila["titulo"]->ToString();
                    String^ tiempoStr = fila["tiempo_jugado_minutos"]->ToString();

                    Panel^ card = gcnew Panel();
                    card->Size = System::Drawing::Size(200, 310); // MISMO TAMAÑO QUE LA TIENDA
                    card->BackColor = Color::FromArgb(45, 45, 45);
                    card->Margin = System::Windows::Forms::Padding(15);

                    PictureBox^ picPortada = gcnew PictureBox();
                    picPortada->Dock = DockStyle::Fill;
                    picPortada->SizeMode = PictureBoxSizeMode::StretchImage;

                    // Ruta de la imagen del juego
                    String^ nombreLimpio = titulo->Trim()->ToLower()->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
                    String^ rutaImagen = "../assets/img/" + nombreLimpio + ".jpg";

                    if (System::IO::File::Exists(rutaImagen)) {
                        picPortada->Image = Image::FromFile(rutaImagen);
                    }
                    else {
                        picPortada->BackColor = Color::DimGray;
                    }

                    Label^ lblT = gcnew Label();
                    lblT->Text = titulo;
                    lblT->ForeColor = Color::White;
                    lblT->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
                    lblT->Dock = DockStyle::Top;
                    lblT->TextAlign = ContentAlignment::MiddleCenter;
                    lblT->Height = 35;

                    Label^ lblTi = gcnew Label();
                    lblTi->Text = "Jugado: " + tiempoStr + " min";
                    lblTi->ForeColor = Color::MediumSeaGreen;
                    lblTi->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
                    lblTi->Dock = DockStyle::Bottom;
                    lblTi->TextAlign = ContentAlignment::MiddleCenter;
                    lblTi->Height = 25;

                    Button^ btnJugar = gcnew Button();
                    btnJugar->Text = "JUGAR";
                    btnJugar->FlatStyle = FlatStyle::Flat;
                    btnJugar->ForeColor = Color::White;
                    // ¡USAMOS EL COLOR DEL TEMA!
                    btnJugar->BackColor = ThemeManager::ColorBotones;
                    btnJugar->Dock = DockStyle::Bottom;
                    btnJugar->Height = 35;
                    btnJugar->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnJugar_Click);

                    card->Controls->Add(picPortada);
                    card->Controls->Add(lblT);
                    card->Controls->Add(btnJugar);
                    card->Controls->Add(lblTi);
                    picPortada->SendToBack();

                    flowJuegos->Controls->Add(card);
                }
            }
            else {
                Label^ lblVacio = gcnew Label();
                lblVacio->Text = "Tu biblioteca está vacía.";
                lblVacio->ForeColor = ThemeManager::ColorTexto;
                lblVacio->Font = gcnew System::Drawing::Font("Arial", 14);
                lblVacio->AutoSize = true;
                flowJuegos->Controls->Add(lblVacio);
            }
        }

        System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void btnJugar_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("¡Iniciando el juego!", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    };
}