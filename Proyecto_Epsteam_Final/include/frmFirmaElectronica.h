#pragma once
#include "ConexionBD.h"

namespace Epsteam {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class frmFirmaElectronica : public System::Windows::Forms::Form {
    private:
        int idUsuarioActivo;
        String^ carteraSeleccionada;
        double totalCobro;

        TextBox^ txtUsuario;
        TextBox^ txtPassword;
        Button^ btnConfirmar;

    public:
        // Añadimos el total a cobrar al constructor
        frmFirmaElectronica(int idUsu, String^ nombreCartera, double total) {
            idUsuarioActivo = idUsu;
            carteraSeleccionada = nombreCartera;
            totalCobro = total;
            ConfigurarVentana();
        }

    private:
        void ConfigurarVentana() {
            // Diseño estilo PayPal (Fondo Blanco, estilo limpio)
            this->Size = System::Drawing::Size(400, 420);
            this->BackColor = Color::White;
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
            this->Text = "Autorización de " + carteraSeleccionada + " - Seguro";

            // Logo simulado / Nombre de la plataforma
            Label^ lblLogo = gcnew Label();
            lblLogo->Text = carteraSeleccionada;
            lblLogo->ForeColor = Color::FromArgb(0, 48, 135); // Azul oscuro clásico de PayPal
            lblLogo->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
            lblLogo->TextAlign = ContentAlignment::MiddleCenter;
            lblLogo->Location = Point(0, 30);
            lblLogo->Width = 400;
            this->Controls->Add(lblLogo);

            // Total a procesar
            Label^ lblTotal = gcnew Label();
            lblTotal->Text = "Total a procesar: $" + totalCobro.ToString("0.00") + " MXN";
            lblTotal->ForeColor = Color::Black;
            lblTotal->Font = gcnew System::Drawing::Font("Arial", 12);
            lblTotal->TextAlign = ContentAlignment::MiddleCenter;
            lblTotal->Location = Point(0, 80);
            lblTotal->Width = 400;
            this->Controls->Add(lblTotal);

            // Instrucciones
            // Instrucciones claras
            Label^ lblInstrucciones = gcnew Label();
            lblInstrucciones->Text = "Ingresa tu correo y contraseña de Epsteam.";
            lblInstrucciones->ForeColor = Color::FromArgb(50, 50, 50);
            lblInstrucciones->Font = gcnew System::Drawing::Font("Arial", 10);
            lblInstrucciones->TextAlign = ContentAlignment::MiddleCenter;
            lblInstrucciones->Location = Point(0, 130);
            lblInstrucciones->Width = 400;
            this->Controls->Add(lblInstrucciones);

            // Input de Usuario
            // Input de Correo (Antes era de usuario)
            txtUsuario = gcnew TextBox();
            txtUsuario->Location = Point(50, 170);
            txtUsuario->Size = System::Drawing::Size(300, 30);
            txtUsuario->Font = gcnew System::Drawing::Font("Arial", 12);
            txtUsuario->Text = ""; // Lo dejamos vacío para que el usuario escriba
            txtUsuario->Enabled = true; // Lo desbloqueamos

            // Le ponemos un texto gris de fondo (opcional) o simplemente lo dejamos en blanco
            this->Controls->Add(txtUsuario);

            // Input de Contraseña
            txtPassword = gcnew TextBox();
            txtPassword->Location = Point(50, 220);
            txtPassword->Size = System::Drawing::Size(300, 30);
            txtPassword->Font = gcnew System::Drawing::Font("Arial", 12);
            txtPassword->PasswordChar = '*';
            this->Controls->Add(txtPassword);

            // Botón de Iniciar Sesión (Azul brillante)
            btnConfirmar = gcnew Button();
            btnConfirmar->Text = "Iniciar Sesión";
            btnConfirmar->BackColor = Color::FromArgb(0, 112, 186); // Azul PayPal
            btnConfirmar->ForeColor = Color::White;
            btnConfirmar->FlatStyle = FlatStyle::Flat;
            btnConfirmar->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
            btnConfirmar->Location = Point(50, 280);
            btnConfirmar->Size = System::Drawing::Size(300, 45);
            btnConfirmar->Cursor = Cursors::Hand;
            btnConfirmar->Click += gcnew EventHandler(this, &frmFirmaElectronica::ValidarCredenciales);
            this->Controls->Add(btnConfirmar);
        }

        void ValidarCredenciales(Object^ sender, EventArgs^ e) {
            // ¡MAGIA! Ahora validamos usando el CORREO ELECTRÓNICO
            int idValidado = Epsteam::ConexionBD::ValidarPagoEmail(txtUsuario->Text, txtPassword->Text);

            if (idValidado == idUsuarioActivo) {
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Correo o contraseña incorrectos. Intenta de nuevo.", "Error de Autorización", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}