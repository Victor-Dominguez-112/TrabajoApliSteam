#pragma once
#include "frmTicket.h"
#include "frmBiblioteca.h"
#include "ConexionBD.h" 

namespace Epsteam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data; 
	using namespace System::Drawing;

	// =========================================================================
	// INICIO DEL GESTOR DE IMÁGENES (VERSIÓN DINÁMICA Y OPTIMIZADA)
	// =========================================================================
	public ref class GestorImagenes {
	public:
		static String^ ObtenerRuta(String^ nombreJuego) {

			// 1. Le quitamos los espacios fantasma al inicio/final con Trim()
			String^ nombreLimpio = nombreJuego->Trim()->ToLower();

			// 2. Aplicamos la regla de tu compañero: cambiamos espacios y borramos símbolos
			nombreLimpio = nombreLimpio->Replace(" ", "_")->Replace(":", "")->Replace("!", "")->Replace("'", "");

			// 3. Armamos la ruta final
			return "img/" + nombreLimpio + ".jpg";
		}
	};
	// =========================================================================
	// FIN DEL GESTOR DE IMÁGENES
	// =========================================================================

	public ref class frmTienda : public System::Windows::Forms::Form
	{
	public:
		frmTienda(void)
		{
			InitializeComponent();

			Button^ btnBiblioteca = gcnew Button();
			btnBiblioteca->Text = "MI BIBLIOTECA";
			btnBiblioteca->BackColor = Color::FromArgb(45, 45, 45);
			btnBiblioteca->ForeColor = Color::White;
			btnBiblioteca->FlatStyle = FlatStyle::Flat;
			btnBiblioteca->Size = System::Drawing::Size(130, 35);
			btnBiblioteca->Location = System::Drawing::Point(450, 20);
			btnBiblioteca->Click += gcnew System::EventHandler(this, &frmTienda::btnBiblioteca_Click);

			pnlNav->Controls->Add(btnBiblioteca);

			// ==========================================================
			// --- AQUÍ CONECTAMOS TU BASE DE DATOS CON LAS IMÁGENES ---
			// ==========================================================

			// 1. Traemos los 150 juegos de tu XAMPP
			DataTable^ misJuegosReales = Epsteam::ConexionBD::ObtenerCatalogoJuegos();

			// 2. Verificamos que la BD haya devuelto información
			if (misJuegosReales != nullptr && misJuegosReales->Rows->Count > 0) {

				// 3. Recorremos fila por fila
				for (int i = 0; i < misJuegosReales->Rows->Count; i++) {

					DataRow^ fila = misJuegosReales->Rows[i];
					String^ titulo = fila["titulo"]->ToString();
					String^ precio = "$" + fila["precio_base"]->ToString() + " MXN";

					// 4. Se lo mandamos a la función de tu compañero.
					// OJO: Solo pasamos 2 datos, la imagen se pondrá sola gracias a su GestorImagenes.
					AgregarJuego(titulo, precio);
				}
			}
			else {
				MessageBox::Show("No se encontraron juegos en la BD.", "Aviso");
			}
			// ==========================================================
		}
	

	protected:
		~frmTienda()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ pnlNav;
		System::Windows::Forms::Label^ lblLogo;
		System::Windows::Forms::FlowLayoutPanel^ flowTienda;
		System::Windows::Forms::Button^ btnCerrarSesion;
		System::ComponentModel::Container^ components;

		// Función mágica para crear cuadritos de juegos automáticamente
		// Función mágica para crear cuadritos con IMÁGENES
		void AgregarJuego(String^ titulo, String^ precio) {
			Panel^ card = gcnew Panel();
			card->Size = System::Drawing::Size(200, 250);
			card->BackColor = Color::FromArgb(45, 45, 45);
			card->Margin = System::Windows::Forms::Padding(15);

			// --- AQUÍ SUCEDE LA MAGIA DE LA IMAGEN ---
			PictureBox^ picPortada = gcnew PictureBox();
			picPortada->Dock = DockStyle::Fill;
			picPortada->SizeMode = PictureBoxSizeMode::Zoom;

			// Usamos nuestro Gestor para armar la ruta correcta (ej. "img/valorant.jpg")
			String^ rutaImagen = GestorImagenes::ObtenerRuta(titulo);
			
			// Verificamos si la imagen existe en tu carpeta 'img'
			if (System::IO::File::Exists(rutaImagen)) {
				picPortada->Image = Image::FromFile(rutaImagen);
			}
			else {
				picPortada->BackColor = Color::DimGray; // Si no la encuentra, pinta gris
			}
			// ------------------------------------------

			Label^ lblTitulo = gcnew Label();
			lblTitulo->Text = titulo;
			lblTitulo->ForeColor = Color::White;
			lblTitulo->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblTitulo->Dock = DockStyle::Top;
			lblTitulo->TextAlign = ContentAlignment::MiddleCenter;

			Label^ lblPrecio = gcnew Label();
			lblPrecio->Text = precio;
			lblPrecio->ForeColor = Color::LightGray;
			lblPrecio->Dock = DockStyle::Bottom;
			lblPrecio->TextAlign = ContentAlignment::MiddleCenter;

			Button^ btnComprar = gcnew Button();
			btnComprar->Text = "COMPRAR";
			btnComprar->FlatStyle = FlatStyle::Flat;
			btnComprar->ForeColor = Color::White;
			btnComprar->BackColor = Color::FromArgb(0, 120, 215);
			btnComprar->Dock = DockStyle::Bottom;

			btnComprar->Tag = gcnew array<String^>{titulo, precio};
			btnComprar->Click += gcnew System::EventHandler(this, &frmTienda::btnComprar_Click);

			// Agregamos todo a la tarjeta (¡La imagen entra aquí!)
			card->Controls->Add(picPortada);
			card->Controls->Add(lblTitulo);
			card->Controls->Add(btnComprar);
			card->Controls->Add(lblPrecio);

			// Mandamos la imagen al fondo para que el título y el botón queden por encima
			picPortada->SendToBack();

			flowTienda->Controls->Add(card);
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pnlNav = (gcnew System::Windows::Forms::Panel());
			this->lblLogo = (gcnew System::Windows::Forms::Label());
			this->btnCerrarSesion = (gcnew System::Windows::Forms::Button());
			this->flowTienda = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pnlNav->SuspendLayout();
			this->SuspendLayout();

			// Panel de Navegación (Arriba)
			this->pnlNav->BackColor = System::Drawing::Color::FromArgb(23, 26, 33);
			this->pnlNav->Controls->Add(this->btnCerrarSesion);
			this->pnlNav->Controls->Add(this->lblLogo);
			this->pnlNav->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnlNav->Location = System::Drawing::Point(0, 0);
			this->pnlNav->Name = L"pnlNav";
			this->pnlNav->Size = System::Drawing::Size(1000, 60);

			// Logo Epsteam
			this->lblLogo->AutoSize = true;
			this->lblLogo->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold));
			this->lblLogo->ForeColor = System::Drawing::Color::FromArgb(102, 192, 244);
			this->lblLogo->Location = System::Drawing::Point(20, 15);
			this->lblLogo->Text = L"EPSTEAM - TIENDA";

			// Botón Cerrar Sesión
			this->btnCerrarSesion->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
			this->btnCerrarSesion->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCerrarSesion->ForeColor = System::Drawing::Color::White;
			this->btnCerrarSesion->Location = System::Drawing::Point(850, 15);
			this->btnCerrarSesion->Size = System::Drawing::Size(120, 30);
			this->btnCerrarSesion->Text = L"Cerrar Sesión";
			this->btnCerrarSesion->Click += gcnew System::EventHandler(this, &frmTienda::btnCerrarSesion_Click);

			// FlowLayoutPanel (Donde caen los juegos)
			this->flowTienda->AutoScroll = true;
			this->flowTienda->BackColor = System::Drawing::Color::FromArgb(27, 40, 56);
			this->flowTienda->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowTienda->Location = System::Drawing::Point(0, 60);
			this->flowTienda->Name = L"flowTienda";
			this->flowTienda->Padding = System::Windows::Forms::Padding(20);
			this->flowTienda->Size = System::Drawing::Size(1000, 640);

			// frmTienda Config
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 700);
			this->Controls->Add(this->flowTienda);
			this->Controls->Add(this->pnlNav);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None; // Sin bordes feos
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tienda Epsteam";
			this->pnlNav->ResumeLayout(false);
			this->pnlNav->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

private: System::Void btnCerrarSesion_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close(); // Cierra la tienda y te regresa a la pantalla de inicio
	}

private: System::Void btnComprar_Click(System::Object^ sender, System::EventArgs^ e) {
	// 1. Agarramos el nombre del juego del botón que presionaste
	Button^ btnCliquado = (Button^)sender;
	Panel^ pnlPadre = (Panel^)btnCliquado->Parent;
	String^ nombreJuego = "";

	// Buscamos el Label que tiene el título en ese cuadrito
	for each (Control ^ c in pnlPadre->Controls) {
		if (c->GetType() == Label::typeid && c->Dock == DockStyle::Top) {
			nombreJuego = c->Text;
			break;
		}
	}

	// --- EL CANDADO AQUÍ ---
	bool yaLoTiene = false;
	if (System::IO::File::Exists("../mis_compras_reales.txt")) {
		System::IO::StreamReader^ lector = gcnew System::IO::StreamReader("../mis_compras_reales.txt");
		String^ linea;
		while ((linea = lector->ReadLine()) != nullptr) {
			if (linea == nombreJuego) { // <--- Aquí es donde bloquea la compra
				yaLoTiene = true;
				break;
			}
		}
		lector->Close();
	}

	if (yaLoTiene) {
		MessageBox::Show("¡Ya tienes '" + nombreJuego + "' en tu biblioteca!", "Juego Duplicado", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else {
		// Si no lo tiene, abrimos el ticket normal
		String^ precio = ""; // Aquí deberías jalar el precio como ya lo hacías
		frmTicket^ ticket = gcnew frmTicket(nombreJuego, precio);
		ticket->ShowDialog();
	}
}
	   private: System::Void btnBiblioteca_Click(System::Object^ sender, System::EventArgs^ e) {
		   // Esta es la función que Visual Studio no encuentra (Error 29)
		   frmBiblioteca^ biblioteca = gcnew frmBiblioteca();
		   this->Hide();
		   biblioteca->ShowDialog();
		   this->Show();
	   }
	};
}