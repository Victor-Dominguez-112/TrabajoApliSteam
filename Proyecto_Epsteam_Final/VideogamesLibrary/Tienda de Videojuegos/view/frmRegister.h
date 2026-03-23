#pragma once
#include "ConexionBD.h" // <--- ¡CONECTADO A LA BASE DE DATOS!

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class frmRegister : public System::Windows::Forms::Form
    {
    public:
        frmRegister(void)
        {
            InitializeComponent();
        }

    protected:
        ~frmRegister()
        {
            if (components) { delete components; }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::TextBox^ txtEmail;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::TextBox^ txtConfirmPass;
    private: System::Windows::Forms::Button^ btnCreate;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::Windows::Forms::Label^ lblUser;
    private: System::Windows::Forms::Label^ lblEmail;
    private: System::Windows::Forms::Label^ lblPass;
    private: System::Windows::Forms::Label^ lblConfirmPass;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->txtEmail = (gcnew System::Windows::Forms::TextBox());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->txtConfirmPass = (gcnew System::Windows::Forms::TextBox());
            this->btnCreate = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->lblUser = (gcnew System::Windows::Forms::Label());
            this->lblEmail = (gcnew System::Windows::Forms::Label());
            this->lblPass = (gcnew System::Windows::Forms::Label());
            this->lblConfirmPass = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(111, 25);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(219, 37);
            this->lblTitle->TabIndex = 10;
            this->lblTitle->Text = L"Crear Cuenta";

            this->txtUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtUsername->Location = System::Drawing::Point(64, 105);
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(300, 35);
            this->txtUsername->TabIndex = 8;

            this->txtEmail->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtEmail->Location = System::Drawing::Point(64, 175);
            this->txtEmail->Name = L"txtEmail";
            this->txtEmail->Size = System::Drawing::Size(300, 35);
            this->txtEmail->TabIndex = 6;

            this->txtPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtPassword->Location = System::Drawing::Point(64, 245);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->PasswordChar = '*';
            this->txtPassword->Size = System::Drawing::Size(300, 35);
            this->txtPassword->TabIndex = 4;

            this->txtConfirmPass->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtConfirmPass->Location = System::Drawing::Point(64, 315);
            this->txtConfirmPass->Name = L"txtConfirmPass";
            this->txtConfirmPass->PasswordChar = '*';
            this->txtConfirmPass->Size = System::Drawing::Size(300, 35);
            this->txtConfirmPass->TabIndex = 2;

            this->btnCreate->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
                static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnCreate->FlatAppearance->BorderSize = 0;
            this->btnCreate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCreate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->btnCreate->ForeColor = System::Drawing::Color::White;
            this->btnCreate->Location = System::Drawing::Point(135, 380);
            this->btnCreate->Name = L"btnCreate";
            this->btnCreate->Size = System::Drawing::Size(160, 45);
            this->btnCreate->TabIndex = 1;
            this->btnCreate->Text = L"Registrarse";
            this->btnCreate->UseVisualStyleBackColor = false;
            this->btnCreate->Click += gcnew System::EventHandler(this, &frmRegister::btnCreate_Click);

            this->btnCancel->FlatAppearance->BorderSize = 0;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->btnCancel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
                static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnCancel->Location = System::Drawing::Point(135, 435);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(160, 40);
            this->btnCancel->TabIndex = 0;
            this->btnCancel->Text = L"Cancelar";
            this->btnCancel->UseVisualStyleBackColor = true;
            this->btnCancel->Click += gcnew System::EventHandler(this, &frmRegister::btnCancel_Click);

            this->lblUser->AutoSize = true;
            this->lblUser->ForeColor = System::Drawing::Color::LightGray;
            this->lblUser->Location = System::Drawing::Point(60, 80);
            this->lblUser->Name = L"lblUser";
            this->lblUser->Size = System::Drawing::Size(68, 20);
            this->lblUser->TabIndex = 9;
            this->lblUser->Text = L"Usuario:";

            this->lblEmail->AutoSize = true;
            this->lblEmail->ForeColor = System::Drawing::Color::LightGray;
            this->lblEmail->Location = System::Drawing::Point(60, 150);
            this->lblEmail->Name = L"lblEmail";
            this->lblEmail->Size = System::Drawing::Size(142, 20);
            this->lblEmail->TabIndex = 7;
            this->lblEmail->Text = L"Correo electrónico:";

            this->lblPass->AutoSize = true;
            this->lblPass->ForeColor = System::Drawing::Color::LightGray;
            this->lblPass->Location = System::Drawing::Point(60, 220);
            this->lblPass->Name = L"lblPass";
            this->lblPass->Size = System::Drawing::Size(96, 20);
            this->lblPass->TabIndex = 5;
            this->lblPass->Text = L"Contraseña:";

            this->lblConfirmPass->AutoSize = true;
            this->lblConfirmPass->ForeColor = System::Drawing::Color::LightGray;
            this->lblConfirmPass->Location = System::Drawing::Point(60, 290);
            this->lblConfirmPass->Name = L"lblConfirmPass";
            this->lblConfirmPass->Size = System::Drawing::Size(169, 20);
            this->lblConfirmPass->TabIndex = 3;
            this->lblConfirmPass->Text = L"Confirmar Contraseña:";

            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
                static_cast<System::Int32>(static_cast<System::Byte>(36)));
            this->ClientSize = System::Drawing::Size(430, 520);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnCreate);
            this->Controls->Add(this->txtConfirmPass);
            this->Controls->Add(this->lblConfirmPass);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lblPass);
            this->Controls->Add(this->txtEmail);
            this->Controls->Add(this->lblEmail);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblUser);
            this->Controls->Add(this->lblTitle);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Name = L"frmRegister";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Registro - Epsteam";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close(); // Regresa al login
    }

    private: System::Void btnCreate_Click(System::Object^ sender, System::EventArgs^ e) {
        // Validaciones básicas de seguridad
        if (String::IsNullOrWhiteSpace(txtUsername->Text) || String::IsNullOrWhiteSpace(txtEmail->Text) || String::IsNullOrWhiteSpace(txtPassword->Text)) {
            MessageBox::Show("Por favor, llena todos los campos.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (txtPassword->Text != txtConfirmPass->Text) {
            MessageBox::Show("Las contraseñas no coinciden. Inténtalo de nuevo.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // --- MAGIA CON LA BASE DE DATOS ---
        bool exito = Epsteam::ConexionBD::RegistrarUsuario(txtUsername->Text, txtEmail->Text, txtPassword->Text);

        if (exito) {
            MessageBox::Show("¡Cuenta creada exitosamente! Ahora puedes iniciar sesión en Epsteam.", "Registro", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }
    }
    };
}