#pragma once

namespace Epsteam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmTicket : public System::Windows::Forms::Form
	{
	public:
		// ¡El recibidor! Exige saber qué juego vas a comprar y su precio
		frmTicket(String^ nombreJuego, String^ precioJuego)
		{
			InitializeComponent();

			// Asignamos los valores que nos mande la tienda
			lblJuegoComprado->Text = nombreJuego;
			lblPrecioTotal->Text = "Total a pagar: " + precioJuego;
		}

	protected:
		~frmTicket()
		{
			if (components) { delete components; }
		}

	private: System::Windows::Forms::Label^ lblTitulo;
	private: System::Windows::Forms::Label^ lblJuegoComprado;
	private: System::Windows::Forms::Label^ lblPrecioTotal;
	private: System::Windows::Forms::Button^ btnConfirmar;
	private: System::Windows::Forms::Button^ btnCancelar;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->lblTitulo = (gcnew System::Windows::Forms::Label());
			   this->lblJuegoComprado = (gcnew System::Windows::Forms::Label());
			   this->lblPrecioTotal = (gcnew System::Windows::Forms::Label());
			   this->btnConfirmar = (gcnew System::Windows::Forms::Button());
			   this->btnCancelar = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();

			   // Configuración de la ventana (estilo recibo Epsteam)
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			   this->ClientSize = System::Drawing::Size(400, 300);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Recibo de Compra - Epsteam";

			   // lblTitulo
			   this->lblTitulo->AutoSize = true;
			   this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
			   this->lblTitulo->ForeColor = System::Drawing::Color::White;
			   this->lblTitulo->Location = System::Drawing::Point(90, 20);
			   this->lblTitulo->Text = L"Resumen de Pedido";

			   // lblJuegoComprado
			   this->lblJuegoComprado->AutoSize = true;
			   this->lblJuegoComprado->Font = (gcnew System::Drawing::Font(L"Arial", 14));
			   this->lblJuegoComprado->ForeColor = System::Drawing::Color::FromArgb(102, 192, 244);
			   this->lblJuegoComprado->Location = System::Drawing::Point(40, 80);
			   this->lblJuegoComprado->Text = L"[Nombre del Juego]";

			   // lblPrecioTotal
			   this->lblPrecioTotal->AutoSize = true;
			   this->lblPrecioTotal->Font = (gcnew System::Drawing::Font(L"Arial", 12));
			   this->lblPrecioTotal->ForeColor = System::Drawing::Color::LightGreen;
			   this->lblPrecioTotal->Location = System::Drawing::Point(40, 130);
			   this->lblPrecioTotal->Text = L"Total a pagar: $0.00";

			   // btnConfirmar
			   this->btnConfirmar->BackColor = System::Drawing::Color::FromArgb(0, 120, 215);
			   this->btnConfirmar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnConfirmar->ForeColor = System::Drawing::Color::White;
			   this->btnConfirmar->Location = System::Drawing::Point(220, 220);
			   this->btnConfirmar->Size = System::Drawing::Size(120, 40);
			   this->btnConfirmar->Text = L"Confirmar Compra";
			   this->btnConfirmar->Click += gcnew System::EventHandler(this, &frmTicket::btnConfirmar_Click);

			   // btnCancelar
			   this->btnCancelar->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
			   this->btnCancelar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnCancelar->ForeColor = System::Drawing::Color::White;
			   this->btnCancelar->Location = System::Drawing::Point(60, 220);
			   this->btnCancelar->Size = System::Drawing::Size(120, 40);
			   this->btnCancelar->Text = L"Cancelar";
			   this->btnCancelar->Click += gcnew System::EventHandler(this, &frmTicket::btnCancelar_Click);

			   // Agregar todo a la ventana
			   this->Controls->Add(this->btnCancelar);
			   this->Controls->Add(this->btnConfirmar);
			   this->Controls->Add(this->lblPrecioTotal);
			   this->Controls->Add(this->lblJuegoComprado);
			   this->Controls->Add(this->lblTitulo);
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

	private: System::Void btnConfirmar_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			// Usamos el nuevo nombre de archivo
			System::IO::StreamWriter^ archivo = gcnew System::IO::StreamWriter("../mis_compras_reales.txt", true);
			archivo->WriteLine(lblJuegoComprado->Text);
			archivo->Close();

			MessageBox::Show("¡Pago exitoso! El juego se ha añadido a tu Biblioteca.", "Epsteam");
			this->Close();
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error al guardar: " + ex->Message);
		}
	} // <-- Esta cierra btnConfirmar_Click

	private: System::Void btnCancelar_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	} // <-- Esta cierra btnCancelar_Click

	}; // <-- Esta cierra la clase frmTicket (línea 127 aprox)
}