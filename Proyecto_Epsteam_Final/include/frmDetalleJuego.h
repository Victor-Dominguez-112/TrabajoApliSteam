#pragma once
#include "ThemeManager.h"

namespace Epsteam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class frmDetalleJuego : public System::Windows::Forms::Form
	{
	private:
		int id_juego_actual;
		String^ titulo_juego;
		String^ precio_juego;

		Panel^ pnlHeader;
		Panel^ pnlContenedorScroll;

		Label^ lblTituloJuego;
		Label^ lblDesarrollador;
		Button^ btnCerrar;
		PictureBox^ picPortada;
		Label^ lblSinopsis;
		Label^ lblRequisitos;
		Label^ lblPrecio;
		Button^ btnComprar;

		Label^ lblSeccionCalificar;
		ComboBox^ cmbPuntuacion;
		Label^ lblSeccionComentarios;
		TextBox^ txtComentario;
		Button^ btnEnviarResena;

	public:
		// AHORA RECIBE EL TÍTULO Y PRECIO DESDE LA TIENDA
		frmDetalleJuego(int idJuego, String^ titulo, String^ precio)
		{
			id_juego_actual = idJuego;
			titulo_juego = titulo;
			precio_juego = precio;

			InitializeComponent();
			ConfigurarDiseno();
			ThemeManager::Aplicar(this);
			CargarDatosSimulados();
		}

	protected:
		~frmDetalleJuego() { if (components) { delete components; } }

	private:
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Text = L"Epsteam - Detalle de Juego";
			this->Size = System::Drawing::Size(900, 600);
			this->MinimumSize = System::Drawing::Size(900, 600);
			this->BackColor = Color::FromArgb(27, 40, 56);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->StartPosition = FormStartPosition::CenterScreen;
		}

		void ConfigurarDiseno() {
			pnlHeader = gcnew Panel();
			pnlHeader->Dock = DockStyle::Top;
			pnlHeader->Height = 80;
			pnlHeader->BackColor = Color::FromArgb(23, 26, 33);
			this->Controls->Add(pnlHeader);

			lblTituloJuego = gcnew Label();
			lblTituloJuego->Text = "Cargando...";
			lblTituloJuego->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
			lblTituloJuego->ForeColor = Color::White;
			lblTituloJuego->Location = System::Drawing::Point(20, 15);
			lblTituloJuego->AutoSize = true;
			pnlHeader->Controls->Add(lblTituloJuego);

			lblDesarrollador = gcnew Label();
			lblDesarrollador->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Italic);
			lblDesarrollador->ForeColor = Color::FromArgb(102, 192, 244);
			lblDesarrollador->Location = System::Drawing::Point(25, 50);
			lblDesarrollador->AutoSize = true;
			pnlHeader->Controls->Add(lblDesarrollador);

			btnCerrar = gcnew Button();
			btnCerrar->Text = "X";
			btnCerrar->FlatStyle = FlatStyle::Flat;
			btnCerrar->ForeColor = Color::White;
			btnCerrar->BackColor = Color::Crimson;
			btnCerrar->Size = System::Drawing::Size(35, 35);
			btnCerrar->Location = System::Drawing::Point(850, 20);
			btnCerrar->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnCerrar_Click);
			pnlHeader->Controls->Add(btnCerrar);

			pnlContenedorScroll = gcnew Panel();
			pnlContenedorScroll->Location = System::Drawing::Point(0, 80);
			pnlContenedorScroll->Size = System::Drawing::Size(900, 520);
			pnlContenedorScroll->AutoScroll = true;
			this->Controls->Add(pnlContenedorScroll);

			picPortada = gcnew PictureBox();
			picPortada->Location = System::Drawing::Point(30, 20);
			picPortada->Size = System::Drawing::Size(380, 450);
			picPortada->BackColor = Color::FromArgb(40, 40, 40);
			picPortada->SizeMode = PictureBoxSizeMode::StretchImage;
			pnlContenedorScroll->Controls->Add(picPortada);

			lblRequisitos = gcnew Label();
			lblRequisitos->Location = System::Drawing::Point(30, 480);
			lblRequisitos->Size = System::Drawing::Size(380, 150);
			lblRequisitos->ForeColor = Color::LightGray;
			lblRequisitos->Font = gcnew System::Drawing::Font("Consolas", 9);
			pnlContenedorScroll->Controls->Add(lblRequisitos);

			Label^ lblSinopTitulo = gcnew Label();
			lblSinopTitulo->Text = "SINOPSIS";
			lblSinopTitulo->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblSinopTitulo->ForeColor = Color::FromArgb(102, 192, 244);
			lblSinopTitulo->Location = System::Drawing::Point(440, 20);
			lblSinopTitulo->AutoSize = true;
			pnlContenedorScroll->Controls->Add(lblSinopTitulo);

			lblSinopsis = gcnew Label();
			lblSinopsis->Location = System::Drawing::Point(440, 50);
			lblSinopsis->Size = System::Drawing::Size(420, 90);
			lblSinopsis->AutoSize = false;
			lblSinopsis->ForeColor = Color::White;
			lblSinopsis->Font = gcnew System::Drawing::Font("Arial", 10);
			pnlContenedorScroll->Controls->Add(lblSinopsis);

			lblPrecio = gcnew Label();
			lblPrecio->Font = gcnew System::Drawing::Font("Arial", 22, FontStyle::Bold);
			lblPrecio->ForeColor = Color::LightGreen;
			lblPrecio->Location = System::Drawing::Point(440, 150);
			lblPrecio->AutoSize = true;
			pnlContenedorScroll->Controls->Add(lblPrecio);

			btnComprar = gcnew Button();
			btnComprar->Text = "AÑADIR AL CARRITO";
			btnComprar->Size = System::Drawing::Size(200, 45);
			btnComprar->Location = System::Drawing::Point(640, 140);
			btnComprar->BackColor = Color::FromArgb(0, 120, 215);
			btnComprar->ForeColor = Color::White;
			btnComprar->FlatStyle = FlatStyle::Flat;
			btnComprar->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
			btnComprar->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnComprar_Click);
			pnlContenedorScroll->Controls->Add(btnComprar);

			lblSeccionCalificar = gcnew Label();
			lblSeccionCalificar->Text = "CALIFICAR ESTE JUEGO";
			lblSeccionCalificar->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblSeccionCalificar->ForeColor = Color::FromArgb(102, 192, 244);
			lblSeccionCalificar->Location = System::Drawing::Point(440, 210);
			lblSeccionCalificar->AutoSize = true;
			pnlContenedorScroll->Controls->Add(lblSeccionCalificar);

			cmbPuntuacion = gcnew ComboBox();
			cmbPuntuacion->Items->AddRange(gcnew array<Object^>{ "5 Estrellas", "4 Estrellas", "3 Estrellas", "2 Estrellas", "1 Estrella" });
			cmbPuntuacion->SelectedIndex = 0;
			cmbPuntuacion->Location = System::Drawing::Point(440, 240);
			cmbPuntuacion->Size = System::Drawing::Size(150, 30);
			cmbPuntuacion->DropDownStyle = ComboBoxStyle::DropDownList;
			pnlContenedorScroll->Controls->Add(cmbPuntuacion);

			lblSeccionComentarios = gcnew Label();
			lblSeccionComentarios->Text = "DEJAR UN COMENTARIO";
			lblSeccionComentarios->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblSeccionComentarios->ForeColor = Color::FromArgb(102, 192, 244);
			lblSeccionComentarios->Location = System::Drawing::Point(440, 290);
			lblSeccionComentarios->AutoSize = true;
			pnlContenedorScroll->Controls->Add(lblSeccionComentarios);

			txtComentario = gcnew TextBox();
			txtComentario->Multiline = true;
			txtComentario->Size = System::Drawing::Size(400, 80);
			txtComentario->Location = System::Drawing::Point(440, 320);
			txtComentario->BackColor = Color::FromArgb(40, 40, 40);
			txtComentario->ForeColor = Color::White;
			pnlContenedorScroll->Controls->Add(txtComentario);

			btnEnviarResena = gcnew Button();
			btnEnviarResena->Text = "PUBLICAR COMENTARIO";
			btnEnviarResena->Size = System::Drawing::Size(400, 35);
			btnEnviarResena->Location = System::Drawing::Point(440, 410);
			btnEnviarResena->BackColor = Color::MediumSeaGreen;
			btnEnviarResena->FlatStyle = FlatStyle::Flat;
			btnEnviarResena->ForeColor = Color::White;
			btnEnviarResena->Click += gcnew System::EventHandler(this, &frmDetalleJuego::btnEnviar_Click);
			pnlContenedorScroll->Controls->Add(btnEnviarResena);
		}

		void CargarDatosSimulados() {
			// USAMOS LOS DATOS QUE MANDÓ LA TIENDA
			lblTituloJuego->Text = titulo_juego;
			lblPrecio->Text = precio_juego;

			// Textos genéricos para llenar el espacio visual
			lblSinopsis->Text = "Explora mundos increíbles y vive aventuras épicas. Información detallada temporalmente no disponible por mantenimiento de servidores.";
			lblDesarrollador->Text = "Desarrollador: Epsteam Partners | Editor: Global Publishing";
			lblRequisitos->Text = "REQUISITOS MÍNIMOS:\n- SO: Windows 10 64-bit\n- Procesador: Intel Core i5\n- Memoria: 8 GB RAM\n- Gráficos: NVIDIA GTX Series\n- Espacio: 50 GB disponible";

			// CARGA DE IMAGEN DESDE ../assets/img/
			String^ nombreLimpio = titulo_juego->Trim()->ToLower();
			nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");
			String^ rutaImagen = "../assets/img/" + nombreLimpio + ".jpg";

			try {
				if (System::IO::File::Exists(rutaImagen)) {
					if (picPortada->Image != nullptr) delete picPortada->Image;
					picPortada->Image = Image::FromFile(rutaImagen);
				}
				else {
					picPortada->BackColor = Color::DimGray;
				}
			}
			catch (...) {
				picPortada->BackColor = Color::DimGray;
			}
		}

		void btnCerrar_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }

		void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show("Juego añadido al carrito.", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		void btnEnviar_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show("Reseña publicada.", "Epsteam", MessageBoxButtons::OK, MessageBoxIcon::Information);
			txtComentario->Clear();
		}
	};
}