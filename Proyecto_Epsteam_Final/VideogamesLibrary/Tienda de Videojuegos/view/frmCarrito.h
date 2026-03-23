#pragma once
#include "frmPago.h"

namespace Epsteam {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /**
     * @class frmCarrito
     * @brief Formulario que representa el Carrito de Compras del usuario.
     * @details Muestra dinámicamente los videojuegos que el usuario ha seleccionado para comprar.
     * Calcula el subtotal, permite eliminar ítems individualmente de la lista en memoria y
     * redirige a la pasarela de pago (frmPago) para concluir la transacción.
     */
    public ref class frmCarrito : public System::Windows::Forms::Form
    {
    private:
        /** @brief Almacena el ID del usuario logueado para pasarlo a la ventana de pago. */
        int idUsuario;

        // FIRMA BLINDADA
        /** * @brief Referencia directa a la lista del carrito creada en la tienda.
         * @details Almacena arreglos de strings donde índice 0 es ID, índice 1 es Título y índice 2 es Precio.
         */
        System::Collections::Generic::List<cli::array<System::String^>^>^ carritoReferencia;

        /** @brief Panel superior de la ventana. */
        Panel^ pnlTop;
        /** @brief Etiqueta principal con el título del carrito. */
        Label^ lblTitulo;
        /** @brief Contenedor dinámico donde se dibujan los ítems del carrito. */
        FlowLayoutPanel^ flowItems;
        /** @brief Panel inferior que contiene los totales y botones de acción. */
        Panel^ pnlBottom;
        /** @brief Etiqueta que muestra el monto total acumulado. */
        Label^ lblTotal;
        /** @brief Botón para proceder al cobro. */
        Button^ btnPagar;
        /** @brief Botón para regresar a la tienda sin perder el carrito. */
        Button^ btnCerrar;

    public:
        // FIRMA BLINDADA EN EL CONSTRUCTOR
        /**
         * @brief Constructor principal del Carrito.
         * @param idUsu ID del usuario actualmente conectado.
         * @param carritoReal Referencia a la lista genérica con los artículos seleccionados en frmTienda.
         */
        frmCarrito(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carritoReal)
        {
            idUsuario = idUsu;
            carritoReferencia = carritoReal;
            InitializeComponent();
            ConfigurarInterfaz();
            DibujarJuegos();
        }

    protected:
        /**
         * @brief Destructor de la clase.
         * @details Libera los recursos y componentes visuales administrados por la ventana.
         */
        ~frmCarrito() { if (components) { delete components; } }

    private:
        /** @brief Contenedor principal de componentes de Windows Forms. */
        System::ComponentModel::Container^ components;

        /**
         * @brief Configuración básica del formulario.
         */
        void InitializeComponent(void) { this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font; this->Text = L"Carrito de Compras"; }

        /**
         * @brief Construye la interfaz visual dinámica del carrito.
         * @details Asigna colores, tamaños y posiciones a los paneles, etiquetas y botones generales.
         */
        void ConfigurarInterfaz() {
            this->Size = System::Drawing::Size(580, 600);
            this->BackColor = Color::FromArgb(27, 40, 56);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterParent;

            pnlTop = gcnew Panel();
            pnlTop->Dock = DockStyle::Top;
            pnlTop->Height = 60;
            pnlTop->BackColor = Color::FromArgb(23, 26, 33);
            this->Controls->Add(pnlTop);

            lblTitulo = gcnew Label();
            lblTitulo->Text = "MI CARRITO DE COMPRAS";
            lblTitulo->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->Location = System::Drawing::Point(20, 15);
            lblTitulo->AutoSize = true;
            pnlTop->Controls->Add(lblTitulo);

            pnlBottom = gcnew Panel();
            pnlBottom->Dock = DockStyle::Bottom;
            pnlBottom->Height = 80;
            pnlBottom->BackColor = Color::FromArgb(32, 45, 60);
            this->Controls->Add(pnlBottom);

            lblTotal = gcnew Label();
            lblTotal->Text = "Total: $0.00 MXN";
            lblTotal->Font = gcnew System::Drawing::Font("Arial", 13, FontStyle::Bold);
            lblTotal->ForeColor = Color::FromArgb(102, 192, 244);
            lblTotal->Location = System::Drawing::Point(20, 25);
            lblTotal->AutoSize = true;
            pnlBottom->Controls->Add(lblTotal);

            btnCerrar = gcnew Button();
            btnCerrar->Text = "SEGUIR COMPRANDO";
            btnCerrar->BackColor = Color::FromArgb(60, 60, 60);
            btnCerrar->ForeColor = Color::White;
            btnCerrar->FlatStyle = FlatStyle::Flat;
            btnCerrar->Size = System::Drawing::Size(150, 40);
            btnCerrar->Location = System::Drawing::Point(410, 20);
            btnCerrar->Click += gcnew System::EventHandler(this, &frmCarrito::btnCerrar_Click);
            pnlBottom->Controls->Add(btnCerrar);

            btnPagar = gcnew Button();
            btnPagar->Text = "IR A PAGAR";
            btnPagar->BackColor = Color::MediumSeaGreen;
            btnPagar->ForeColor = Color::White;
            btnPagar->FlatStyle = FlatStyle::Flat;
            btnPagar->Size = System::Drawing::Size(120, 40);
            btnPagar->Location = System::Drawing::Point(280, 20);
            btnPagar->Click += gcnew System::EventHandler(this, &frmCarrito::btnPagar_Click);
            pnlBottom->Controls->Add(btnPagar);

            flowItems = gcnew FlowLayoutPanel();
            flowItems->Dock = DockStyle::Fill;
            flowItems->AutoScroll = true;
            flowItems->Padding = System::Windows::Forms::Padding(10);
            this->Controls->Add(flowItems);
            flowItems->BringToFront();
        }

        /**
         * @brief Renderiza visualmente cada ítem contenido en el carritoReferencia.
         * @details Itera sobre la lista del carrito. Por cada juego, crea un panel con su nombre,
         * su precio parseado numéricamente (para ir sumando al total) y un botón de eliminación (X).
         * Si el carrito está vacío, muestra un mensaje y deshabilita el botón de pago.
         */
        void DibujarJuegos() {
            flowItems->Controls->Clear();
            double total = 0;

            if (carritoReferencia->Count == 0) {
                Label^ lblVacio = gcnew Label();
                lblVacio->Text = "Tu carrito está vacío. ¡Ve a agregar unos juegos!";
                lblVacio->ForeColor = Color::Gray;
                lblVacio->Font = gcnew System::Drawing::Font("Arial", 12);
                lblVacio->AutoSize = true;
                flowItems->Controls->Add(lblVacio);
                btnPagar->Enabled = false;
                btnPagar->BackColor = Color::DimGray;
            }
            else {
                btnPagar->Enabled = true;
                btnPagar->BackColor = Color::MediumSeaGreen;
            }

            for (int i = 0; i < carritoReferencia->Count; i++) {
                // FIRMA BLINDADA
                cli::array<System::String^>^ datos = carritoReferencia[i];
                String^ nombre = datos[1];
                String^ precioTexto = datos[2];

                String^ precioLimpio = precioTexto->Replace("$", "")->Replace(" MXN", "")->Replace(",", "");
                double precioNum = 0;
                Double::TryParse(precioLimpio, precioNum);
                total += precioNum;

                Panel^ pnlItem = gcnew Panel();
                pnlItem->Width = 520;
                pnlItem->Height = 50;
                pnlItem->BackColor = Color::FromArgb(45, 45, 45);
                pnlItem->Margin = System::Windows::Forms::Padding(5);

                Label^ lblNombre = gcnew Label();
                lblNombre->Text = nombre;
                lblNombre->ForeColor = Color::White;
                lblNombre->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
                lblNombre->Location = System::Drawing::Point(10, 15);
                lblNombre->AutoSize = true;
                pnlItem->Controls->Add(lblNombre);

                Label^ lblPrecio = gcnew Label();
                lblPrecio->Text = precioTexto;
                lblPrecio->ForeColor = Color::LightGray;
                lblPrecio->Font = gcnew System::Drawing::Font("Arial", 10);
                lblPrecio->Location = System::Drawing::Point(250, 15);
                lblPrecio->AutoSize = true;
                pnlItem->Controls->Add(lblPrecio);

                Button^ btnEliminar = gcnew Button();
                btnEliminar->Text = "X";
                btnEliminar->BackColor = Color::Crimson;
                btnEliminar->ForeColor = Color::White;
                btnEliminar->FlatStyle = FlatStyle::Flat;
                btnEliminar->Size = System::Drawing::Size(30, 30);
                btnEliminar->Location = System::Drawing::Point(470, 10);
                btnEliminar->Tag = i;
                btnEliminar->Click += gcnew System::EventHandler(this, &frmCarrito::btnEliminar_Click);
                pnlItem->Controls->Add(btnEliminar);

                flowItems->Controls->Add(pnlItem);
            }
            lblTotal->Text = "Total a pagar: $" + total.ToString("0.00") + " MXN";
        }

        /**
         * @brief Evento que elimina un juego específico de la lista del carrito.
         * @details Utiliza la propiedad Tag del botón clickeado para obtener el índice del arreglo,
         * lo elimina de carritoReferencia y vuelve a invocar DibujarJuegos() para actualizar la interfaz.
         * @param sender Botón "X" que fue clickeado.
         * @param e Argumentos del evento.
         */
    private: System::Void btnEliminar_Click(System::Object^ sender, System::EventArgs^ e) {
        Button^ btn = (Button^)sender;
        int indice = Convert::ToInt32(btn->Tag);
        carritoReferencia->RemoveAt(indice);
        DibujarJuegos();
    }

           /**
            * @brief Cierra el formulario del carrito para regresar a la tienda principal.
            * @param sender Botón "SEGUIR COMPRANDO".
            * @param e Argumentos del evento.
            */
    private: System::Void btnCerrar_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

           /**
            * @brief Abre la pasarela de pago para liquidar los artículos del carrito.
            * @details Vuelve a calcular el total asegurándose de que el precio esté limpio.
            * Instancia 'frmPago' pasando el ID, el carrito y el total. Si el pago es exitoso (DialogResult::OK),
            * vacía la lista del carrito y cierra la ventana.
            * @param sender Botón "IR A PAGAR".
            * @param e Argumentos del evento.
            */
    private: System::Void btnPagar_Click(System::Object^ sender, System::EventArgs^ e) {
        double total = 0;
        for (int i = 0; i < carritoReferencia->Count; i++) {
            String^ precioLimpio = carritoReferencia[i][2]->Replace("$", "")->Replace(" MXN", "")->Replace(",", "");
            double precioNum = 0;
            Double::TryParse(precioLimpio, precioNum);
            total += precioNum;
        }

        frmPago^ pasarela = gcnew frmPago(this->idUsuario, carritoReferencia, total);

        if (pasarela->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            carritoReferencia->Clear();
            this->Close();
        }
    }
    };
}