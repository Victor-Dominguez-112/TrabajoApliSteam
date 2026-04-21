#pragma once
#include "ConexionBD.h"

namespace Epsteam {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class frmFirmaElectronica : public System::Windows::Forms::Form {
    private:
        int idUsuarioActivo;
        String^ carteraSeleccionada;
        TextBox^ txtUsuario;
        TextBox^ txtPassword;

    public:
        // Ahora recibimos el ID y el NOMBRE de la pasarela
        frmFirmaElectronica(int idUsu, String^ nombreCartera) {
            idUsuarioActivo = idUsu;
            carteraSeleccionada = nombreCartera;
            ConfigurarVentana();
        }

    private:
        void ConfigurarVentana() {
            this->Size = System::Drawing::Size(350, 280);
            this->BackColor = Color::FromArgb(30, 30, 35);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
            this->Text = "Pasarela Segura - " + carteraSeleccionada;

            Label^ lblTitulo = gcnew Label();
            lblTitulo->Text = "Iniciar sesión en\n" + carteraSeleccionada;
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            lblTitulo->TextAlign = ContentAlignment::MiddleCenter;
            lblTitulo->Dock = DockStyle::Top;
            lblTitulo->Height = 60;
            this->Controls->Add(lblTitulo);

            Label^ lblSubtitulo = gcnew Label();
            lblSubtitulo->Text = "(Usa tus credenciales de Epsteam)";
            lblSubtitulo->ForeColor = Color::LightGray;
            lblSubtitulo->Font = gcnew System::Drawing::Font("Arial", 9);
            lblSubtitulo->Location = Point(0, 60);
            lblSubtitulo->Width = 350;
            lblSubtitulo->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(lblSubtitulo);

            txtUsuario = gcnew TextBox();
            txtUsuario->Location = Point(50, 100);
            txtUsuario->Size = System::Drawing::Size(230, 25);
            txtUsuario->Font = gcnew System::Drawing::Font("Arial", 11);
            this->Controls->Add(txtUsuario);

            txtPassword = gcnew TextBox();
            txtPassword->Location = Point(50, 140);
            txtPassword->Size = System::Drawing::Size(230, 25);
            txtPassword->Font = gcnew System::Drawing::Font("Arial", 11);
            txtPassword->PasswordChar = '*';
            this->Controls->Add(txtPassword);

            Button^ btnConfirmar = gcnew Button();
            btnConfirmar->Text = "PAGAR AHORA";
            btnConfirmar->BackColor = Color::FromArgb(0, 120, 215);
            btnConfirmar->ForeColor = Color::White;
            btnConfirmar->FlatStyle = FlatStyle::Flat;
            btnConfirmar->Location = Point(90, 190);
            btnConfirmar->Size = System::Drawing::Size(150, 35);
            btnConfirmar->Click += gcnew EventHandler(this, &frmFirmaElectronica::ValidarCredenciales);
            this->Controls->Add(btnConfirmar);
        }

        void ValidarCredenciales(Object^ sender, EventArgs^ e) {
            if (txtUsuario->Text != Epsteam::ConexionBD::nicknameActual) {
                MessageBox::Show("Solo puedes autorizar pagos con la cuenta que tiene la sesión activa.", "Alerta de Seguridad", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try {
                // 🛑 ¡AQUÍ ESTÁ EL CULPABLE DEL TIMEOUT! 🛑
                // BORRA ESTA CADENA Y PON LA QUE USAS EN ConexionBD.h
                String^ cadenaConexion = "Server = localhost; Database = epsteam; Uid = root; Pwd = ;";

                SqlConnection^ sqlCon = gcnew SqlConnection(cadenaConexion);

                SqlCommand^ cmd = gcnew SqlCommand("sp_AutenticarTransaccionInterna", sqlCon);
                cmd->CommandType = Data::CommandType::StoredProcedure;

                cmd->Parameters->AddWithValue("@IdSesionActiva", idUsuarioActivo);
                cmd->Parameters->AddWithValue("@UsuarioIngresado", txtUsuario->Text);
                cmd->Parameters->AddWithValue("@Password", txtPassword->Text);

                sqlCon->Open();
                int resultado = Convert::ToInt32(cmd->ExecuteScalar());
                sqlCon->Close();

                if (resultado > 0) {
                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
                else {
                    MessageBox::Show("Contraseña incorrecta para el usuario " + txtUsuario->Text, "Fallo de Autorización", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (SqlException^ ex) {
                // Ahora te dirá exactamente por qué falla SQL (ej. "No se encontró el servidor")
                MessageBox::Show("Fallo de conexión a la Base de Datos.\nError: " + ex->Message, "Error Crítico SQL", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}