#pragma once

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class frmPasarela : public System::Windows::Forms::Form
    {
    private:
        // Controles Fase 1: Login
        Label^ lblInstruccion;
        TextBox^ txtCorreo;
        TextBox^ txtPassword;
        Button^ btnAvanzar;

        // Controles Fase 2: Procesamiento
        Label^ lblTitulo;
        Label^ lblMonto;
        Label^ lblEstado;
        ProgressBar^ barraProgreso;

        Timer^ timerSimulacion;
        int progresoActual = 0;

    public:
        frmPasarela(String^ proveedor, double montoCobrar)
        {
            InitializeComponent();
            ConfigurarDiseñoExterno(proveedor, montoCobrar);
        }

    protected:
        ~frmPasarela() { if (components) { delete components; } }

    private: System::ComponentModel::Container^ components;

            void InitializeComponent(void) {
                this->components = gcnew System::ComponentModel::Container();
                this->timerSimulacion = gcnew System::Windows::Forms::Timer(this->components);
                this->SuspendLayout();

                this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);

                // ¡LA MAGIA ESTÁ AQUÍ! Cambiamos 'Font' por 'None' para evitar que Windows deforme la ventana
                this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;

                this->ClientSize = System::Drawing::Size(500, 380);

                this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
                this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
                this->Name = L"frmPasarela";
                this->Text = L"Navegador Seguro";
                this->ResumeLayout(false);
            }

            void ConfigurarDiseñoExterno(String^ proveedor, double monto) {
                this->BackColor = Color::White;
             
                // --- TÍTULOS GENERALES ---
                lblTitulo = gcnew Label();
                lblTitulo->Font = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
                lblTitulo->AutoSize = false;
                lblTitulo->Size = System::Drawing::Size(500, 40);
                lblTitulo->Location = System::Drawing::Point(0, 20);
                lblTitulo->TextAlign = ContentAlignment::MiddleCenter;
                this->Controls->Add(lblTitulo);
                 
                lblMonto = gcnew Label();
                lblMonto->Text = "Total a procesar: $" + monto.ToString("0.00") + " MXN";
                lblMonto->Font = gcnew System::Drawing::Font("Arial", 11);
                lblMonto->AutoSize = false;
                lblMonto->Size = System::Drawing::Size(500, 30); // Le dimos más altura por si acaso
                lblMonto->Location = System::Drawing::Point(0, 60);
                lblMonto->TextAlign = ContentAlignment::MiddleCenter;
                this->Controls->Add(lblMonto);

                // --- FASE 1: CONTROLES DE LOGIN ---
                lblInstruccion = gcnew Label();
                lblInstruccion->Text = "Inicia sesión con tu cuenta para continuar.";
                lblInstruccion->Font = gcnew System::Drawing::Font("Arial", 10);
                lblInstruccion->AutoSize = false;
                lblInstruccion->Size = System::Drawing::Size(500, 40); // Aumentamos la altura a 40px para evitar cortes
                lblInstruccion->Location = System::Drawing::Point(0, 100);
                lblInstruccion->TextAlign = ContentAlignment::MiddleCenter;
                this->Controls->Add(lblInstruccion);

                txtCorreo = gcnew TextBox();
                txtCorreo->Font = gcnew System::Drawing::Font("Arial", 12);
                txtCorreo->Location = System::Drawing::Point(100, 140);
                txtCorreo->Size = System::Drawing::Size(300, 30);
                txtCorreo->Text = "correo@ejemplo.com";
                txtCorreo->ForeColor = Color::Gray;
                txtCorreo->GotFocus += gcnew System::EventHandler(this, &frmPasarela::LimpiarTextoCorreo);
                this->Controls->Add(txtCorreo);
 
                txtPassword = gcnew TextBox();
                txtPassword->Font = gcnew System::Drawing::Font("Arial", 12);
                txtPassword->Location = System::Drawing::Point(100, 190);
                txtPassword->Size = System::Drawing::Size(300, 30);
                txtPassword->PasswordChar = '*';
                this->Controls->Add(txtPassword);

                btnAvanzar = gcnew Button();
                btnAvanzar->Text = "Iniciar Sesión";
                btnAvanzar->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
                btnAvanzar->Location = System::Drawing::Point(100, 250);
                btnAvanzar->Size = System::Drawing::Size(300, 45);
                btnAvanzar->FlatStyle = FlatStyle::Flat;
                btnAvanzar->Click += gcnew System::EventHandler(this, &frmPasarela::btnAvanzar_Click);
                this->Controls->Add(btnAvanzar);
 
                // --- FASE 2: CONTROLES DE CARGA ---
                barraProgreso = gcnew ProgressBar();
                barraProgreso->Location = System::Drawing::Point(100, 170);
                barraProgreso->Size = System::Drawing::Size(300, 30);
                barraProgreso->Visible = false;
                this->Controls->Add(barraProgreso);
 
                lblEstado = gcnew Label();
                lblEstado->Text = "Autenticando...";
                lblEstado->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Italic);
                lblEstado->AutoSize = false;
                lblEstado->Size = System::Drawing::Size(500, 30);
                lblEstado->Location = System::Drawing::Point(0, 210);
                lblEstado->TextAlign = ContentAlignment::MiddleCenter;
                lblEstado->Visible = false;
                this->Controls->Add(lblEstado);
 
                if (proveedor == "PayPal") {
                    lblTitulo->Text = "PayPal";
                    lblTitulo->ForeColor = Color::FromArgb(0, 48, 135);
                    btnAvanzar->BackColor = Color::FromArgb(0, 112, 186);
                    btnAvanzar->ForeColor = Color::White;
                    this->Text = L"Autorización de PayPal - Seguro";
                }
                else if (proveedor == "Xsolla") {
                    // Xsolla suele ser más minimalista: solo el logo y el login
                    lblTitulo->Text = "XSOLLA";
                    lblTitulo->ForeColor = Color::Black;
                    lblInstruccion->Text = "Ingresa tu ID de usuario de Xsolla";
                    btnAvanzar->Text = "PAGAR AHORA";
                    btnAvanzar->BackColor = Color::FromArgb(255, 60, 0); // Naranja Xsolla
                    btnAvanzar->ForeColor = Color::White;
                    this->Text = L"Xsolla Global Payment Service";
                }
                else if (proveedor == "MercadoPago") {
                    lblTitulo->Text = "Mercado Pago";
                    lblTitulo->ForeColor = Color::FromArgb(0, 158, 227);
                    btnAvanzar->BackColor = Color::FromArgb(0, 158, 227);
                    btnAvanzar->ForeColor = Color::White;
                    this->Text = L"Mercado Pago Checkout";
                }
                else if (proveedor == "Mi Cartera Epsteam" || proveedor == "Bancario") {
                    // Este es tu diseño "de la casa", usa los colores de tu tienda
                    lblTitulo->Text = "EPSTEAM WALLET";
                    lblTitulo->ForeColor = Color::FromArgb(102, 192, 244); // Azul Steam
                    this->BackColor = Color::FromArgb(23, 26, 33); // Fondo oscuro de tu tienda
                    lblInstruccion->Text = "Confirma tu identidad para usar tu saldo.";
                    lblInstruccion->ForeColor = Color::White;
                    lblMonto->ForeColor = Color::White;
                    btnAvanzar->Text = "AUTORIZAR GASTO";
                    btnAvanzar->BackColor = Color::FromArgb(102, 192, 244);
                    btnAvanzar->ForeColor = Color::Black;
                    this->Text = L"Seguridad de Cartera Epsteam";
                }

                timerSimulacion->Interval = 60;
                timerSimulacion->Tick += gcnew System::EventHandler(this, &frmPasarela::timerSimulacion_Tick);
            }

            // --- EVENTOS ---
            System::Void LimpiarTextoCorreo(System::Object^ sender, System::EventArgs^ e) {
                if (txtCorreo->Text == "correo@ejemplo.com") {
                    txtCorreo->Text = "";
                    txtCorreo->ForeColor = Color::Black;
                }
            }

            System::Void btnAvanzar_Click(System::Object^ sender, System::EventArgs^ e) {
                if (String::IsNullOrWhiteSpace(txtCorreo->Text) || String::IsNullOrWhiteSpace(txtPassword->Text)) {
                    MessageBox::Show("Por favor ingresa un correo y contraseña para simular el pago.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }

                lblInstruccion->Visible = false;
                txtCorreo->Visible = false;
                txtPassword->Visible = false;
                btnAvanzar->Visible = false;
   
                barraProgreso->Visible = true;
                lblEstado->Visible = true;

                timerSimulacion->Start();
            }

            System::Void timerSimulacion_Tick(System::Object^ sender, System::EventArgs^ e) {
                progresoActual += 2;

                if (progresoActual <= 100) {
                    barraProgreso->Value = progresoActual;

                    if (progresoActual == 20) lblEstado->Text = "Verificando token de seguridad...";
                    if (progresoActual == 50) lblEstado->Text = "Aprobando fondos de la cuenta...";
                    if (progresoActual == 85) lblEstado->Text = "Pago exitoso. Redirigiendo a Epsteam...";
                }
                else {
                    timerSimulacion->Stop();
                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
            }
    };
}