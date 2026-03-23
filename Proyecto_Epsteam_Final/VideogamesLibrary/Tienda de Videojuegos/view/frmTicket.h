#pragma once
#include "ConexionBD.h"

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class frmTicket : public System::Windows::Forms::Form
    {
    private:
        Label^ lblASCII;

    public:
        // FIRMA BLINDADA
        frmTicket(String^ metodo, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, double total)
        {
            InitializeComponent();
            ConfigurarInterfaz(metodo, carrito, total);
        }

    protected:
        ~frmTicket() { if (components) { delete components; } }

    private:
        System::ComponentModel::Container^ components;
        void InitializeComponent(void) {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmTicket::typeid));
            this->SuspendLayout();
            // 
            // frmTicket
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(282, 253);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Name = L"frmTicket";
            this->Text = L"Tu Recibo Digital";
            this->ResumeLayout(false);

        }

        void ConfigurarInterfaz(String^ metodo, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, double total) {
            this->BackColor = Color::FromArgb(27, 40, 56);
            this->Size = System::Drawing::Size(450, 550);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterParent;
            this->MaximizeBox = false;

            lblASCII = gcnew Label();
            lblASCII->Location = System::Drawing::Point(15, 15);
            lblASCII->Size = System::Drawing::Size(420, 500);
            lblASCII->ForeColor = Color::White;
            lblASCII->Padding = System::Windows::Forms::Padding(5);
            lblASCII->Font = gcnew System::Drawing::Font("Courier New", 11); // Magia ASCII

            DateTime fecha = DateTime::Now;
            String^ ticketTexto = "";
            ticketTexto += "========================================\n";
            ticketTexto += "          RECIBO DE EPSTEAM             \n";
            ticketTexto += "========================================\n\n";
            ticketTexto += "Fecha: " + fecha.ToString("dd/MM/yyyy HH:mm:ss") + "\n";
            ticketTexto += "ID Cliente: " + Epsteam::ConexionBD::nicknameActual + "\n";
            ticketTexto += "Método Pago: " + metodo + "\n";
            ticketTexto += "----------------------------------------\n";
            ticketTexto += "ARTÍCULOS COMPRADOS:\n\n";

            for (int i = 0; i < carrito->Count; i++) {
                // BLINDAJE AL SACAR LOS DATOS
                cli::array<System::String^>^ datos = carrito[i];
                String^ titulo = datos[1];
                if (titulo->Length > 25) titulo = titulo->Substring(0, 22) + "...";

                String^ precioTexto = datos[2]->Replace(" MXN", "");

                ticketTexto += "- " + String::Format("{0,-28} {1,10}\n", titulo, precioTexto);
            }
            ticketTexto += "\n----------------------------------------\n";
            ticketTexto += String::Format("{0,-28} {1,10}\n", "TOTAL PAGADO:", "$" + total.ToString("0.00"));
            ticketTexto += "========================================\n\n";
            ticketTexto += "¡Los juegos ya están en tu Biblioteca!\n";
            ticketTexto += "      ¡Gracias por tu compra!       \n";

            lblASCII->Text = ticketTexto;
            this->Controls->Add(lblASCII);

            Button^ btnOK = gcnew Button();
            btnOK->Text = "CERRAR";
            btnOK->Size = System::Drawing::Size(100, 30);
            btnOK->Location = System::Drawing::Point(175, 390);
            btnOK->BackColor = Color::FromArgb(0, 120, 215);
            btnOK->ForeColor = Color::White;
            btnOK->FlatStyle = FlatStyle::Flat;
            btnOK->Click += gcnew System::EventHandler(this, &frmTicket::btnOK_Click);
            this->Controls->Add(btnOK);

            btnOK->BringToFront();
        }

        System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}