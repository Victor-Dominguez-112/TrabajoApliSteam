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

        static void EstablecerTema(int tipo)
        {
            TemaActual = tipo; // Guardamos el número

            if (tipo == 0) { // Oscuro (Clásico Epsteam)
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
            else if (tipo == 3) { // Océano Profundo
                ColorFondo = Color::FromArgb(15, 25, 35);
                ColorTexto = Color::White;
                ColorBotones = Color::FromArgb(0, 153, 204); // Cian oscuro
            }
            else if (tipo == 4) { // Modo Sangriento
                ColorFondo = Color::FromArgb(18, 18, 18);
                ColorTexto = Color::FromArgb(240, 240, 240);
                ColorBotones = Color::FromArgb(180, 20, 20); // Rojo Carmesí
            }
            else if (tipo == 5) { // Neón Synthwave
                ColorFondo = Color::FromArgb(25, 15, 35);
                ColorTexto = Color::White;
                ColorBotones = Color::FromArgb(255, 0, 128); // Rosa Neón
            }
            else if (tipo == 6) { // Hacker Terminal
                ColorFondo = Color::FromArgb(5, 5, 5);
                ColorTexto = Color::FromArgb(0, 255, 0); // Verde clásico de consola
                ColorBotones = Color::FromArgb(25, 25, 25);
            }
            else if (tipo == 7) { // Eclipse Solar
                ColorFondo = Color::FromArgb(30, 30, 35);
                ColorTexto = Color::White;
                ColorBotones = Color::FromArgb(255, 100, 0); // Naranja vibrante
            }
            else if (tipo == 8) { // Bosque Místico
                ColorFondo = Color::FromArgb(15, 30, 20); // Verde muy oscuro
                ColorTexto = Color::White;
                ColorBotones = Color::FromArgb(46, 204, 113); // Esmeralda brillante
            }
            else if (tipo == 9) { // Atardecer Retro
                ColorFondo = Color::FromArgb(40, 20, 35); // Púrpura cálido
                ColorTexto = Color::FromArgb(255, 235, 180); // Amarillo suave (durazno)
                ColorBotones = Color::FromArgb(255, 87, 34); // Naranja atardecer
            }
        }
    };
}