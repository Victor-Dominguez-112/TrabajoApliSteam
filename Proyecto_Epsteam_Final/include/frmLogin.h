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

    /**
     * @class frmLogin
     * @brief Formulario inicial que gestiona el acceso y autenticación de usuarios.
     * @details Esta ventana solicita credenciales (usuario y contraseña) y las valida contra
     * la base de datos MySQL mediante la clase ConexionBD. También provee acceso a la ventana
     * de creación de nuevas cuentas (frmRegister).
     */
    public ref class frmLogin : public System::Windows::Forms::Form
    {
    public:
        /**
         * @brief Constructor por defecto de frmLogin.
         * @details Inicializa todos los componentes visuales de la ventana de inicio de sesión.
         */
        frmLogin(void)
        {
            InitializeComponent();
        }

    protected:
        /**
         * @brief Destructor de la clase.
         * @details Libera la memoria de los componentes visuales administrados cuando se cierra la aplicación.
         */
        ~frmLogin()
        {
            if (components)
            {
                delete components;
            }
        }

        // Declaración de los elementos de tu diseño
    private:
        /** @brief Etiqueta principal con el título de bienvenida. */
        System::Windows::Forms::Label^ lblTitle;
        /** @brief Campo de texto para que el usuario ingrese su nickname. */
        System::Windows::Forms::TextBox^ txtUsername;
        /** @brief Campo de texto oculto para que el usuario ingrese su contraseña. */
        System::Windows::Forms::TextBox^ txtPassword;
        /** @brief Botón que desencadena el proceso de validación y acceso. */
        System::Windows::Forms::Button^ btnLogin;
        /** @brief Botón que abre la ventana de registro de nuevos usuarios. */
        System::Windows::Forms::Button^ btnRegister;

    private:
        /** @brief Contenedor principal de componentes de Windows Forms. */
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /**
         * @brief Método autogenerado por el Diseñador de Windows Forms.
         * @details Inicializa, posiciona y da estilo a todos los controles UI de la ventana de login.
         */
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(frmLogin::typeid));
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
            this->lblTitle->Location = System::Drawing::Point(108, 30);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(163, 32);
            this->lblTitle->TabIndex = 4;
            this->lblTitle->Text = L"Bienvenido";
            // 
            // txtUsername
            // 
            this->txtUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtUsername->Location = System::Drawing::Point(65, 90);
            this->txtUsername->MaxLength = 20;
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(250, 30);
            this->txtUsername->TabIndex = 3;
            // 
            // txtPassword
            // 
            this->txtPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->txtPassword->Location = System::Drawing::Point(65, 140);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->PasswordChar = '*';
            this->txtPassword->Size = System::Drawing::Size(250, 30);
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
            this->btnLogin->Location = System::Drawing::Point(115, 200);
            this->btnLogin->Name = L"btnLogin";
            this->btnLogin->Size = System::Drawing::Size(150, 40);
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
            this->btnRegister->Location = System::Drawing::Point(115, 250);
            this->btnRegister->Name = L"btnRegister";
            this->btnRegister->Size = System::Drawing::Size(150, 40);
            this->btnRegister->TabIndex = 0;
            this->btnRegister->Text = L"Crear Cuenta";
            this->btnRegister->UseVisualStyleBackColor = true;
            this->btnRegister->Click += gcnew System::EventHandler(this, &frmLogin::btnRegister_Click);
            // 
            // frmLogin
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
                static_cast<System::Int32>(static_cast<System::Byte>(36)));
            this->ClientSize = System::Drawing::Size(384, 311);
            this->Controls->Add(this->btnRegister);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblTitle);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
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
        /**
         * @brief Evento que valida las credenciales introducidas y otorga el acceso.
         * @details Revisa que los campos no estén vacíos. Llama a ConexionBD::ValidarLogin()
         * y, si recibe un ID válido, oculta el login, muestra un saludo personalizado y abre la Tienda (frmTienda).
         * Al cerrar la tienda, vuelve a mostrar el login.
         * @param sender Botón "Entrar" que disparó el evento.
         * @param e Argumentos del evento.
         */
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
            MessageBox::Show("¡Bienvenido de vuelta, " + Epsteam::ConexionBD::nicknameActual + "!", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // --- EL CAMBIO ESTÁ AQUÍ ---
            // Le pasamos el 'idLogueado' adentro de los paréntesis de frmTienda
            frmTienda^ tienda = gcnew frmTienda(idLogueado);
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
           /**
            * @brief Evento que se ejecuta al cargar y dibujar el formulario por primera vez.
            * @details Realiza una prueba temprana de conexión a la base de datos MySQL (ConexionBD::Conectar)
            * para asegurar que los servicios de XAMPP estén encendidos y disponibles antes de que el usuario intente loguearse.
            * @param sender El propio formulario frmLogin.
            * @param e Argumentos del evento.
            */
    private: System::Void frmLogin_Load(System::Object^ sender, System::EventArgs^ e) {
        // Intentamos abrir la puerta de la BD nada más arrancar
        MySql::Data::MySqlClient::MySqlConnection^ prueba = Epsteam::ConexionBD::Conectar();
    }


           // ---------------------------------------------------------------------
           // 3. EL TEXTO AZUL DE CREAR CUENTA
           // ---------------------------------------------------------------------
           /**
            * @brief Evento que redirige al usuario a la ventana de registro de cuentas.
            * @details Oculta temporalmente la ventana de login (Hide) y muestra la ventana modal frmRegister.
            * Cuando el registro finaliza o se cancela, el login vuelve a aparecer (Show).
            * @param sender Botón "Crear Cuenta" que disparó el evento.
            * @param e Argumentos del evento.
            */
    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
        frmRegister^ ventanaRegistro = gcnew frmRegister();
        this->Hide();
        ventanaRegistro->ShowDialog();
        this->Show();
    } // <--- LLAVE 3: CIERRA EL BOTÓN DE REGISTRO

    }; // <--- LLAVE 4: CIERRA LA CLASE frmLogin (¡Esta es la que tiene el punto y coma!)
} // <--- LLAVE 5: CIERRA EL NAMESPACE Epsteam