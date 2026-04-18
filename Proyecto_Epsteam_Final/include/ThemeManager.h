#pragma once
namespace Epsteam {
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class ThemeManager {
    public:
        // El cerebro recuerda cuál fue el último índice seleccionado
        static int TemaActual = 0;

        static Color ColorFondo = Color::FromArgb(27, 40, 56);
        static Color ColorTexto = Color::White;
        static Color ColorBotones = Color::FromArgb(45, 45, 45);

        static void Aplicar(Control^ contenedor) {
            contenedor->BackColor = ColorFondo;

            if (contenedor->GetType() == Label::typeid || contenedor->GetType() == TextBox::typeid) {
                contenedor->ForeColor = ColorTexto;
            }

            if (contenedor->GetType() == Button::typeid) {
                contenedor->BackColor = ColorBotones;
                contenedor->ForeColor = ColorTexto;
            }

            for each (Control ^ c in contenedor->Controls) {
                Aplicar(c);
            }
        }

        static void EstablecerTema(int tipo) {
            TemaActual = tipo; // Guardamos el número

            if (tipo == 0) { // Oscuro
                ColorFondo = Color::FromArgb(27, 40, 56);
                ColorTexto = Color::White;
                ColorBotones = Color::FromArgb(45, 45, 45);
            }
            else if (tipo == 1) { // Claro
                ColorFondo = Color::WhiteSmoke;
                ColorTexto = Color::Black;
                ColorBotones = Color::ForestGreen;
            }
            else if (tipo == 2) { // Cyberpunk
                ColorFondo = Color::FromArgb(15, 10, 30);
                ColorTexto = Color::Cyan;
                ColorBotones = Color::DeepPink;
            }
        }
    };
}