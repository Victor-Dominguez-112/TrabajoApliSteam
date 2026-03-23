#pragma once
#include "ConexionBD.h"
#include "frmTicket.h" // ¡Conectamos tu nueva vista!

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class frmPago : public System::Windows::Forms::Form
    {
    private:
        int idUsuario;
        // FIRMA BLINDADA PARA EVITAR ERRORES E1767
        System::Collections::Generic::List<cli::array<System::String^>^>^ carritoPago;
        double totalPago;

        Label^ lblTitulo;
        Label^ lblResumen;
        RadioButton^ rbTarjeta;
        RadioButton^ rbEfectivo;
        RadioButton^ rbCartera;
        Panel^ pnlOpciones;
        Label^ lblDinamico;
        Button^ btnPagar;
        Button^ btnCancelar;

    public:
        // FIRMA BLINDADA EN EL CONSTRUCTOR
        frmPago(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, double total)
        {
            idUsuario = idUsu;
            carritoPago = carrito;
            totalPago = total;

            InitializeComponent();
            ConfigurarDiseño();
        }

    protected:
        ~frmPago() { if (components) { delete components; } }

    private:
        System::ComponentModel::Container^ components;
        void InitializeComponent(void) { this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font; }

        void ConfigurarDiseño() {
            this->BackColor = Color::FromArgb(27, 40, 56);
            this->Size = System::Drawing::Size(450, 520);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;

            lblTitulo = gcnew Label();
            lblTitulo->Text = "MÉTODO DE PAGO";
            lblTitulo->ForeColor = Color::FromArgb(102, 192, 244);
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
            lblTitulo->Location = System::Drawing::Point(20, 20);
            lblTitulo->AutoSize = true;
            this->Controls->Add(lblTitulo);

            lblResumen = gcnew Label();
            lblResumen->Text = "Llevas: " + Convert::ToString(carritoPago->Count) + " juego(s) en el carrito\nTotal a pagar: $" + totalPago.ToString("0.00") + " MXN";
            lblResumen->ForeColor = Color::White;
            lblResumen->Font = gcnew System::Drawing::Font("Arial", 11);
            lblResumen->Location = System::Drawing::Point(20, 60);
            lblResumen->AutoSize = true;
            this->Controls->Add(lblResumen);

            rbTarjeta = gcnew RadioButton();
            rbTarjeta->Text = "Tarjeta de Crédito/Débito";
            rbTarjeta->ForeColor = Color::White;
            rbTarjeta->Font = gcnew System::Drawing::Font("Arial", 11);
            rbTarjeta->Location = System::Drawing::Point(40, 110);
            rbTarjeta->Size = System::Drawing::Size(300, 30);
            rbTarjeta->CheckedChanged += gcnew System::EventHandler(this, &frmPago::CambiarMetodoPago);
            this->Controls->Add(rbTarjeta);

            rbEfectivo = gcnew RadioButton();
            rbEfectivo->Text = "Pago en Efectivo (OXXO/Banco)";
            rbEfectivo->ForeColor = Color::White;
            rbEfectivo->Font = gcnew System::Drawing::Font("Arial", 11);
            rbEfectivo->Location = System::Drawing::Point(40, 150);
            rbEfectivo->Size = System::Drawing::Size(300, 30);
            rbEfectivo->CheckedChanged += gcnew System::EventHandler(this, &frmPago::CambiarMetodoPago);
            this->Controls->Add(rbEfectivo);

            rbCartera = gcnew RadioButton();
            rbCartera->Text = "Mi Cartera Epsteam";
            rbCartera->ForeColor = Color::White;
            rbCartera->Font = gcnew System::Drawing::Font("Arial", 11);
            rbCartera->Location = System::Drawing::Point(40, 190);
            rbCartera->Size = System::Drawing::Size(300, 30);
            rbCartera->CheckedChanged += gcnew System::EventHandler(this, &frmPago::CambiarMetodoPago);
            this->Controls->Add(rbCartera);

            pnlOpciones = gcnew Panel();
            pnlOpciones->Location = System::Drawing::Point(40, 240);
            pnlOpciones->Size = System::Drawing::Size(370, 100);
            pnlOpciones->BackColor = Color::FromArgb(45, 45, 45);
            this->Controls->Add(pnlOpciones);

            lblDinamico = gcnew Label();
            lblDinamico->Text = "Selecciona un método de pago arriba.";
            lblDinamico->ForeColor = Color::LightGray;
            lblDinamico->Font = gcnew System::Drawing::Font("Arial", 10);
            lblDinamico->Dock = DockStyle::Fill;
            lblDinamico->TextAlign = ContentAlignment::MiddleCenter;
            pnlOpciones->Controls->Add(lblDinamico);

            btnCancelar = gcnew Button();
            btnCancelar->Text = "CANCELAR";
            btnCancelar->BackColor = Color::FromArgb(60, 60, 60);
            btnCancelar->ForeColor = Color::White;
            btnCancelar->FlatStyle = FlatStyle::Flat;
            btnCancelar->Location = System::Drawing::Point(40, 450);
            btnCancelar->Size = System::Drawing::Size(120, 40);
            btnCancelar->Click += gcnew System::EventHandler(this, &frmPago::btnCancelar_Click);
            this->Controls->Add(btnCancelar);

            btnPagar = gcnew Button();
            btnPagar->Text = "CONFIRMAR PAGO";
            btnPagar->BackColor = Color::FromArgb(0, 120, 215);
            btnPagar->ForeColor = Color::White;
            btnPagar->FlatStyle = FlatStyle::Flat;
            btnPagar->Location = System::Drawing::Point(180, 450);
            btnPagar->Size = System::Drawing::Size(230, 40);
            btnPagar->Enabled = false;
            btnPagar->Click += gcnew System::EventHandler(this, &frmPago::btnPagar_Click);
            this->Controls->Add(btnPagar);
        }

    private: System::Void btnCancelar_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }

    private: System::Void CambiarMetodoPago(System::Object^ sender, System::EventArgs^ e) {
        btnPagar->Enabled = true;
        pnlOpciones->Controls->Clear();

        if (rbTarjeta->Checked) {
            Label^ lblNum = gcnew Label();
            lblNum->Text = "Número de Tarjeta (16 dígitos):";
            lblNum->ForeColor = Color::LightGray;
            lblNum->Font = gcnew System::Drawing::Font("Arial", 9);
            lblNum->Location = System::Drawing::Point(15, 15);
            lblNum->AutoSize = true;

            TextBox^ txtNum = gcnew TextBox();
            txtNum->Location = System::Drawing::Point(15, 35);
            txtNum->Size = System::Drawing::Size(200, 25);
            txtNum->Font = gcnew System::Drawing::Font("Arial", 11);
            txtNum->MaxLength = 16;

            Label^ lblVenc = gcnew Label();
            lblVenc->Text = "Vencimiento:";
            lblVenc->ForeColor = Color::LightGray;
            lblVenc->Font = gcnew System::Drawing::Font("Arial", 9);
            lblVenc->Location = System::Drawing::Point(230, 15);
            lblVenc->AutoSize = true;

            TextBox^ txtVenc = gcnew TextBox();
            txtVenc->Location = System::Drawing::Point(230, 35);
            txtVenc->Size = System::Drawing::Size(60, 25);
            txtVenc->Font = gcnew System::Drawing::Font("Arial", 11);
            txtVenc->MaxLength = 5;
            txtVenc->Text = "MM/AA";
            txtVenc->ForeColor = Color::Gray;
            txtVenc->GotFocus += gcnew System::EventHandler(this, &frmPago::txtVenc_GotFocus);
            txtVenc->LostFocus += gcnew System::EventHandler(this, &frmPago::txtVenc_LostFocus);

            Label^ lblCVV = gcnew Label();
            lblCVV->Text = "CVV:";
            lblCVV->ForeColor = Color::LightGray;
            lblCVV->Font = gcnew System::Drawing::Font("Arial", 9);
            lblCVV->Location = System::Drawing::Point(310, 15);
            lblCVV->AutoSize = true;

            TextBox^ txtCVV = gcnew TextBox();
            txtCVV->Location = System::Drawing::Point(310, 35);
            txtCVV->Size = System::Drawing::Size(45, 25);
            txtCVV->Font = gcnew System::Drawing::Font("Arial", 11);
            txtCVV->MaxLength = 3;
            txtCVV->PasswordChar = '*';

            pnlOpciones->Controls->Add(lblNum);
            pnlOpciones->Controls->Add(txtNum);
            pnlOpciones->Controls->Add(lblVenc);
            pnlOpciones->Controls->Add(txtVenc);
            pnlOpciones->Controls->Add(lblCVV);
            pnlOpciones->Controls->Add(txtCVV);
        }
        else if (rbEfectivo->Checked) {
            Random^ rnd = gcnew Random();
            long long codigoNum = rnd->Next(10000000, 99999999);
            String^ codigoTexto = "EPSTEAM - " + codigoNum.ToString() + rnd->Next(1000, 9999).ToString();

            Label^ lblInstrucciones = gcnew Label();
            lblInstrucciones->Text = "Dicta este código al cajero:\n" + codigoTexto;
            lblInstrucciones->ForeColor = Color::White;
            lblInstrucciones->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
            lblInstrucciones->Dock = DockStyle::Top;
            lblInstrucciones->TextAlign = ContentAlignment::MiddleCenter;
            pnlOpciones->Controls->Add(lblInstrucciones);

            PictureBox^ picCodigo = gcnew PictureBox();
            picCodigo->Size = System::Drawing::Size(300, 60);
            picCodigo->Location = System::Drawing::Point(35, 35);
            picCodigo->BackColor = Color::White;

            Bitmap^ lienzo = gcnew Bitmap(300, 60);
            Graphics^ pincel = Graphics::FromImage(lienzo);
            pincel->Clear(Color::White);

            int posicionX = 10;
            while (posicionX < 290) {
                int grosorLinea = rnd->Next(1, 5);
                int espacio = rnd->Next(1, 4);
                pincel->FillRectangle(Brushes::Black, posicionX, 5, grosorLinea, 50);
                posicionX += grosorLinea + espacio;
            }
            picCodigo->Image = lienzo;
            pnlOpciones->Controls->Add(picCodigo);
        }
        else if (rbCartera->Checked) {
            Label^ lblCartera = gcnew Label();
            lblCartera->Text = "Se descontará de tu Cartera Epsteam.";
            lblCartera->ForeColor = Color::LightGreen;
            lblCartera->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
            lblCartera->Dock = DockStyle::Fill;
            lblCartera->TextAlign = ContentAlignment::MiddleCenter;
            pnlOpciones->Controls->Add(lblCartera);
        }
    }

    private: System::Void txtVenc_GotFocus(System::Object^ sender, System::EventArgs^ e) {
        TextBox^ txt = (TextBox^)sender;
        if (txt->Text == "MM/AA") {
            txt->Text = "";
            txt->ForeColor = Color::Black;
        }
    }
    private: System::Void txtVenc_LostFocus(System::Object^ sender, System::EventArgs^ e) {
        TextBox^ txt = (TextBox^)sender;
        if (String::IsNullOrWhiteSpace(txt->Text)) {
            txt->Text = "MM/AA";
            txt->ForeColor = Color::Gray;
        }
    }

    private: System::Void btnPagar_Click(System::Object^ sender, System::EventArgs^ e) {

        // --- 1. EL CADENERO DE SEGURIDAD ---
        if (rbTarjeta->Checked) {
            bool faltanDatos = false;
            for each (Control ^ c in pnlOpciones->Controls) {
                if (c->GetType() == TextBox::typeid) {
                    if (String::IsNullOrWhiteSpace(c->Text) || c->Text == "MM/AA") {
                        faltanDatos = true;
                        break;
                    }
                }
            }
            if (faltanDatos) {
                MessageBox::Show("¡Oye! No puedes llevarte los juegos gratis. Llena todos los datos de tu tarjeta.", "Aviso de Seguridad", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return; // ¡Abortar misión!
            }
        }

        // --- 2. PREPARAR DATOS DE LA COMPRA ---
        int metodoSeleccionado = 1;
        String^ nombreMetodo = "Tarjeta de Crédito/Débito";
        if (rbEfectivo->Checked) { metodoSeleccionado = 2; nombreMetodo = "Efectivo"; }
        else if (rbCartera->Checked) { metodoSeleccionado = 3; nombreMetodo = "Cartera Epsteam"; }

        // --- 3. GUARDAR EN LA BASE DE DATOS ---
        bool exito = Epsteam::ConexionBD::RegistrarCompra(idUsuario, carritoPago, metodoSeleccionado, totalPago);

        if (exito) {
            // --- 4. ABRIR EL TICKET VISUAL POP-UP (NUEVO) ---
            frmTicket^ ticketVisual = gcnew frmTicket(nombreMetodo, carritoPago, totalPago);
            ticketVisual->ShowDialog();

            // --- 5. GENERAR EL TICKET TXT CON TU NICKNAME ---
            try {
                if (!System::IO::Directory::Exists("Tickets")) {
                    System::IO::Directory::CreateDirectory("Tickets");
                }
                DateTime fecha = DateTime::Now;
                String^ nombreArchivo = "Tickets/Recibo_" + Epsteam::ConexionBD::nicknameActual + "_" + fecha.ToString("HH_mm_ss") + ".txt";

                System::IO::StreamWriter^ recibo = gcnew System::IO::StreamWriter(nombreArchivo);
                recibo->WriteLine("========================================");
                recibo->WriteLine("          RECIBO DE EPSTEAM             ");
                recibo->WriteLine("========================================");
                recibo->WriteLine("Fecha: " + fecha.ToString("dd/MM/yyyy HH:mm:ss"));
                recibo->WriteLine("Cliente: " + Epsteam::ConexionBD::nicknameActual);
                recibo->WriteLine("Método de Pago: " + nombreMetodo);
                recibo->WriteLine("----------------------------------------");
                recibo->WriteLine("ARTÍCULOS COMPRADOS:");

                for (int i = 0; i < carritoPago->Count; i++) {
                    cli::array<System::String^>^ datos = carritoPago[i];
                    recibo->WriteLine("- " + datos[1] + " (" + datos[2] + ")");
                }

                recibo->WriteLine("----------------------------------------");
                recibo->WriteLine("TOTAL PAGADO: $" + totalPago.ToString("0.00") + " MXN");
                recibo->WriteLine("========================================");
                recibo->WriteLine("¡Los juegos ya están en tu Biblioteca!");
                recibo->Close();
            }
            catch (...) {}

            // --- 6. CERRAR EL CARRITO ---
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    }
    };
}