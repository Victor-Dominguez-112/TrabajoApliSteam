#pragma once
#include "ConexionBD.h"

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /**
     * @class frmTicket
     * @brief Formulario que presenta el recibo de compra digital en pantalla.
     * @details Dibuja un comprobante de compra con un estilo de ticket de caja clásico (ASCII).
     * Utiliza una fuente monoespaciada (Courier New) para alinear perfectamente los nombres
     * de los videojuegos y sus precios, logrando un diseño cuadrado ideal para capturas de pantalla.
     */
    public ref class frmTicket : public System::Windows::Forms::Form
    {
    private:
        /** @brief Etiqueta principal que contiene todo el texto formateado (Magia ASCII) del ticket. */
        Label^ lblASCII;

    public:
        // FIRMA BLINDADA
        /**
         * @brief Constructor de la ventana del Ticket.
         * @details Recibe los datos consolidados de la compra para plasmarlos inmediatamente en el recibo.
         * @param metodo Nombre del método de pago utilizado (ej. "Cartera Epsteam").
         * @param carrito Lista genérica blindada con los detalles (ID, Título, Precio) de cada juego comprado.
         * @param total Monto total pagado.
         */
        frmTicket(String^ metodo, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, double total)
        {
            InitializeComponent();
            ConfigurarInterfaz(metodo, carrito, total);
        }

    protected:
        /**
         * @brief Destructor de la clase.
         * @details Libera la memoria de los componentes visuales de Windows Forms.
         */
        ~frmTicket() { if (components) { delete components; } }

    private:
        /** @brief Contenedor principal de los componentes visuales. */
        System::ComponentModel::Container^ components;

        /**
         * @brief Método autogenerado por el Diseñador de Windows Forms.
         * @details Inicializa los componentes básicos y carga el ícono de la ventana.
         */
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
            this->Load += gcnew System::EventHandler(this, &frmTicket::frmTicket_Load);
            this->ResumeLayout(false);

        }

        /**
         * @brief Construye el diseño del ticket y concatena la información de compra.
         * @details Configura la ventana como un bloque fijo (FixedSingle). Crea una cadena
         * de texto extensa aplicando truncamiento a los títulos muy largos e inyectando formato
         * estilo C++ (String::Format) para alinear a la derecha los precios monetarios.
         * @param metodo Cadena de texto con el método de pago.
         * @param carrito Referencia a los artículos comprados.
         * @param total Monto final cobrado.
         */
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

        /**
         * @brief Evento que cierra la ventana del ticket emergente.
         * @param sender Botón "CERRAR".
         * @param e Argumentos del evento.
         */
        System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        /**
         * @brief Evento disparado al cargar el formulario (actualmente vacío).
         * @param sender Formulario frmTicket.
         * @param e Argumentos del evento.
         */
    private: System::Void frmTicket_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}