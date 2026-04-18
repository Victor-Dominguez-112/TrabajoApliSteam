/**
 * @file frmlogin.cpp
 * @brief Punto de entrada principal de la aplicación Epsteam.
 * @details Este archivo contiene la función main que arranca el entorno de Windows Forms,
 * aplica los estilos visuales del sistema operativo y lanza el formulario de inicio de sesión (frmLogin).
 */

#include "frmLogin.h"

using namespace System;
using namespace System::Windows::Forms;

/**
 * @brief Función principal (Entry Point) del programa.
 * @details Configura el hilo de ejecución para que sea compatible con componentes COM (STAThread),
 * habilita los estilos visuales modernos de Windows y ejecuta el bucle de mensajes de la
 * aplicación mostrando la ventana frmLogin como la ventana principal.
 * @param args Arreglo de cadenas de texto con los argumentos pasados por línea de comandos (no se utilizan en este proyecto).
 * @return Un valor entero que representa el código de salida del programa (0 indica una ejecución y cierre exitosos).
 */
[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Epsteam::frmLogin form;
    Application::Run(% form);
    return 0;
}