#pragma once

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class frmSimulacionXsolla : public System::Windows::Forms::Form
    {
    public:
        frmSimulacionXsolla(void)
        {
            ConfigurarVentana();
        }

    protected:
        ~frmSimulacionXsolla() {}

    private:
        Panel^ pnlFondoBarcode;
        PictureBox^ picBarcode;
        Label^ lblInstrucciones;
        Label^ lblCodigoNumerico;
        Button^ btnCerrar;

        void ConfigurarVentana() {
            this->Size = System::Drawing::Size(450, 400);
            this->BackColor = Color::FromArgb(30, 30, 30); // Gris oscuro casi negro
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Text = "Xsolla PayStation - Efectivo";

            // Título/Instrucciones
            lblInstrucciones = gcnew Label();
            lblInstrucciones->Text = "Muestra este código de barras en tu tienda física más cercana para completar el pago.";
            lblInstrucciones->ForeColor = Color::White;
            lblInstrucciones->Font = gcnew System::Drawing::Font("Arial", 11);
            lblInstrucciones->TextAlign = ContentAlignment::MiddleCenter;
            lblInstrucciones->Size = System::Drawing::Size(400, 50);
            lblInstrucciones->Location = System::Drawing::Point(15, 20);
            this->Controls->Add(lblInstrucciones);

            // Contenedor blanco para el código de barras
            pnlFondoBarcode = gcnew Panel();
            pnlFondoBarcode->BackColor = Color::White;
            pnlFondoBarcode->Size = System::Drawing::Size(360, 160);
            pnlFondoBarcode->Location = System::Drawing::Point(35, 90);
            this->Controls->Add(pnlFondoBarcode);

            // Área donde se pintará el código de barras
            picBarcode = gcnew PictureBox();
            picBarcode->Size = System::Drawing::Size(340, 100);
            picBarcode->Location = System::Drawing::Point(10, 15);
            picBarcode->BackColor = Color::White;
            picBarcode->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &frmSimulacionXsolla::DibujarCodigoBarras);
            pnlFondoBarcode->Controls->Add(picBarcode);

            // Código numérico debajo de las barras
            Random^ rnd = gcnew Random();
            lblCodigoNumerico = gcnew Label();
            lblCodigoNumerico->Text = "XSOLLA - " + rnd->Next(1000, 9999) + " - " + rnd->Next(10000, 99999);
            lblCodigoNumerico->ForeColor = Color::Black;
            lblCodigoNumerico->Font = gcnew System::Drawing::Font("Consolas", 14, FontStyle::Bold);
            lblCodigoNumerico->TextAlign = ContentAlignment::MiddleCenter;
            lblCodigoNumerico->Size = System::Drawing::Size(340, 30);
            lblCodigoNumerico->Location = System::Drawing::Point(10, 120);
            pnlFondoBarcode->Controls->Add(lblCodigoNumerico);

            // Botón para finalizar/cerrar
            btnCerrar = gcnew Button();
            btnCerrar->Text = "HE GUARDADO EL CÓDIGO";
            btnCerrar->BackColor = Color::FromArgb(255, 100, 0); // Color naranja tipo Xsolla
            btnCerrar->ForeColor = Color::White;
            btnCerrar->FlatStyle = FlatStyle::Flat;
            btnCerrar->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            btnCerrar->Size = System::Drawing::Size(250, 45);
            btnCerrar->Location = System::Drawing::Point(90, 280);
            btnCerrar->Click += gcnew System::EventHandler(this, &frmSimulacionXsolla::btnCerrar_Click);
            this->Controls->Add(btnCerrar);
        }

        // --- Codigo de barras ---
        System::Void DibujarCodigoBarras(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
            Graphics^ g = e->Graphics;
            Random^ rnd = gcnew Random(12345); 

            int xPos = 10;
            while (xPos < picBarcode->Width - 20) {
                int grosorBarra = rnd->Next(2, 6); 
                int espacioBlanco = rnd->Next(2, 5); 

                g->FillRectangle(Brushes::Black, xPos, 0, grosorBarra, picBarcode->Height);
                xPos += (grosorBarra + espacioBlanco);
            }
        }

        System::Void btnCerrar_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close(); 
        }
    private: System::Void InitializeComponent() {
        this->SuspendLayout();
        this->ClientSize = System::Drawing::Size(282, 253);
        this->Name = L"frmSimulacionXsolla";
        this->Load += gcnew System::EventHandler(this, &frmSimulacionXsolla::frmSimulacionXsolla_Load);
        this->ResumeLayout(false);
    }
    private: System::Void frmSimulacionXsolla_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}