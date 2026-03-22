#pragma once
#include "ConexionBD.h"

namespace Epsteam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmBiblioteca : public System::Windows::Forms::Form
	{
	public:
		frmBiblioteca(void)
		{
			InitializeComponent();
			CargarMisJuegos(); // <--- PÉGALO AQUÍ ADENTRO
		}

	protected:
		~frmBiblioteca()
		{
			if (components) { delete components; }
		}

	private: System::Windows::Forms::Label^ lblTitulo;
	private: System::Windows::Forms::Button^ btnVolver;
	private: System::Windows::Forms::FlowLayoutPanel^ flowBiblioteca;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->lblTitulo = (gcnew System::Windows::Forms::Label());
			   this->btnVolver = (gcnew System::Windows::Forms::Button());
			   this->flowBiblioteca = (gcnew System::Windows::Forms::FlowLayoutPanel());
			   this->SuspendLayout();

			   this->BackColor = System::Drawing::Color::FromArgb(27, 40, 56);
			   this->ClientSize = System::Drawing::Size(800, 600);
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Mi Biblioteca - Epsteam";

			   this->lblTitulo->AutoSize = true;
			   this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Arial", 20, System::Drawing::FontStyle::Bold));
			   this->lblTitulo->ForeColor = System::Drawing::Color::White;
			   this->lblTitulo->Location = System::Drawing::Point(30, 20);
			   this->lblTitulo->Text = L"MI BIBLIOTECA DE JUEGOS";

			   this->btnVolver->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
			   this->btnVolver->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnVolver->ForeColor = System::Drawing::Color::White;
			   this->btnVolver->Location = System::Drawing::Point(620, 20);
			   this->btnVolver->Size = System::Drawing::Size(130, 35);
			   this->btnVolver->Text = L"Volver a la Tienda";
			   this->btnVolver->Click += gcnew System::EventHandler(this, &frmBiblioteca::btnVolver_Click);

			   this->flowBiblioteca->AutoScroll = true;
			   this->flowBiblioteca->Location = System::Drawing::Point(30, 80);
			   this->flowBiblioteca->Size = System::Drawing::Size(720, 480);
			   this->flowBiblioteca->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);

			   this->Controls->Add(this->btnVolver);
			   this->Controls->Add(this->flowBiblioteca);
			   this->Controls->Add(this->lblTitulo);
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

		   void CargarMisJuegos() {
			   this->flowBiblioteca->Controls->Clear();

			   // Llamamos a la BD usando el ID de la sesión actual guardada en ConexionBD
			   DataTable^ misJuegos = Epsteam::ConexionBD::ObtenerMisJuegos(Epsteam::ConexionBD::idUsuarioActual);

			   if (misJuegos != nullptr && misJuegos->Rows->Count > 0) {
				   for (int i = 0; i < misJuegos->Rows->Count; i++) {
					   DataRow^ fila = misJuegos->Rows[i]; // <--- EXTRAEMOS LA FILA PARA QUE C++ NO LLORE
					   String^ juego = fila["titulo"]->ToString();

					   int tiempoJugado = Convert::ToInt32(fila["tiempo_jugado_minutos"]);
					   String^ textoTiempo = (tiempoJugado >= 120) ? " [+2hrs jugadas]" : " [" + tiempoJugado + " min jugados]";

					   Label^ lbl = gcnew Label(); // <--- UNA SOLA ETIQUETA
					   lbl->Text =juego + textoTiempo;

					   lbl->ForeColor = Color::White;
					   lbl->BackColor = Color::FromArgb(45, 45, 45);
					   lbl->Size = System::Drawing::Size(300, 45);
					   lbl->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
					   lbl->TextAlign = ContentAlignment::MiddleLeft;
					   lbl->Margin = System::Windows::Forms::Padding(10);

					   this->flowBiblioteca->Controls->Add(lbl);
				   }
			   }
			   else {
				   Label^ lblVacio = gcnew Label();
				   lblVacio->Text = "Aún no tienes juegos. ¡Ve a la tienda!";
				   lblVacio->ForeColor = Color::LightGray;
				   lblVacio->AutoSize = true;
				   lblVacio->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Italic);
				   this->flowBiblioteca->Controls->Add(lblVacio);
			   }
		   }

	private: System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	};
}