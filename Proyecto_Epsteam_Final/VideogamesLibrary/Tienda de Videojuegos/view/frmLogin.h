#pragma once
#include "frmTienda.h"
#include "frmRegister.h"
#include "ConexionBD.h" // Nuestra nueva y flamante clase

namespace Epsteam {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class frmLogin : public System::Windows::Forms::Form
    {
    public:
        frmLogin(void)
        {
            InitializeComponent();
        }

    protected:
        ~frmLogin()
        {
            if (components)
            {
                delete components;
            }
        }

        // Declaración de los elementos de tu diseño
    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::Button^ btnLogin;
    private: System::Windows::Forms::Button^ btnRegister;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnRegister = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // lblTitle
            // 
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(122, 38);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(188, 37);
            this->lblTitle->TabIndex = 4;
            this->lblTitle->Text = L"Bienvenido";
            // 
            // txtUsername
            // 
            this->txtUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtUsername->Location = System::Drawing::Point(73, 112);
            this->txtUsername->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->txtUsername->MaxLength = 20;
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(281, 35);
            this->txtUsername->TabIndex = 3;
            // 
            // txtPassword
            // 
            this->txtPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtPassword->Location = System::Drawing::Point(73, 175);
            this->txtPassword->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->PasswordChar = '*';
            this->txtPassword->Size = System::Drawing::Size(281, 35);
            this->txtPassword->TabIndex = 2;
            // 
            // btnLogin
            // 
            this->btnLogin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
                static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnLogin->FlatAppearance->BorderSize = 0;
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->Location = System::Drawing::Point(129, 250);
            this->btnLogin->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnLogin->Name = L"btnLogin";
            this->btnLogin->Size = System::Drawing::Size(169, 50);
            this->btnLogin->TabIndex = 1;
            this->btnLogin->Text = L"Entrar";
            this->btnLogin->UseVisualStyleBackColor = false;
            this->btnLogin->Click += gcnew System::EventHandler(this, &frmLogin::btnLogin_Click);
            // 
            // btnRegister
            // 
            this->btnRegister->FlatAppearance->BorderSize = 0;
            this->btnRegister->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRegister->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold));
            this->btnRegister->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(123)),
                static_cast<System::Int32>(static_cast<System::Byte>(255)));
            this->btnRegister->Location = System::Drawing::Point(129, 312);
            this->btnRegister->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->btnRegister->Name = L"btnRegister";
            this->btnRegister->Size = System::Drawing::Size(169, 50);
            this->btnRegister->TabIndex = 0;
            this->btnRegister->Text = L"Crear Cuenta";
            this->btnRegister->UseVisualStyleBackColor = true;
            this->btnRegister->Click += gcnew System::EventHandler(this, &frmLogin::btnRegister_Click);
            // 
            // frmLogin
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
                static_cast<System::Int32>(static_cast<System::Byte>(36)));
            this->ClientSize = System::Drawing::Size(432, 389);
            this->Controls->Add(this->btnRegister);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblTitle);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
            this->MaximizeBox = false;
            this->Name = L"frmLogin";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Iniciar Sesión";
            this->Load += gcnew System::EventHandler(this, &frmLogin::frmLogin_Load);
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

        // ---------------------------------------------------------------------
            // 1. EL BOTÓN DE ENTRAR (LOGIN)
            // ---------------------------------------------------------------------
    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ usuario = txtUsername->Text;
        String^ password = txtPassword->Text;

        if (usuario == "" || password == "") {
            MessageBox::Show("Escribe tu usuario y contraseña.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // 1. Llamamos a nuestra super clase de Base de Datos
        // Le pasamos los textos tal cual, sin conversiones raras
        int idLogueado = Epsteam::ConexionBD::ValidarLogin(usuario, password);

        // 2. Evaluamos la respuesta (-1 significa que falló)
        if (idLogueado != -1) {

            // ¡ESTO RESPONDE TU PREGUNTA DE CÓMO SABER SI SE CONECTÓ!
            MessageBox::Show("¡Conexión a la BD Exitosa! Bienvenido, tu ID es: " + idLogueado,
                "Éxito", MessageBoxButtons::OK, MessageBoxIcon::Information);

            frmTienda^ tienda = gcnew frmTienda();
            this->Hide();
            tienda->ShowDialog();
            this->Show();
        }
        else {
            MessageBox::Show("Usuario o contraseña incorrectos, o la BD está apagada.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    
    // <--- CIERRA btnLogin_Click // <--- LLAVE 1: CIERRA EL BOTÓN DE ENTRAR


    // ---------------------------------------------------------------------
    // 2. EL LOAD (A veces se crea solo al darle doble clic al fondo)
    // ---------------------------------------------------------------------
    private: System::Void frmLogin_Load(System::Object^ sender, System::EventArgs^ e) {
        // Intentamos abrir la puerta de la BD nada más arrancar
        MySql::Data::MySqlClient::MySqlConnection^ prueba = Epsteam::ConexionBD::Conectar();
    }


    // ---------------------------------------------------------------------
    // 3. EL TEXTO AZUL DE CREAR CUENTA
    // ---------------------------------------------------------------------
    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
        frmRegister^ ventanaRegistro = gcnew frmRegister();
        this->Hide();
        ventanaRegistro->ShowDialog();
        this->Show();
    } // <--- LLAVE 3: CIERRA EL BOTÓN DE REGISTRO

    }; // <--- LLAVE 4: CIERRA LA CLASE frmLogin (¡Esta es la que tiene el punto y coma!)
} // <--- LLAVE 5: CIERRA EL NAMESPACE Epsteam