#pragma once

using namespace System;
using namespace System::Data;
// Usamos la nueva librería que acabas de instalar
using namespace MySql::Data::MySqlClient;

namespace Epsteam {

    public ref class ConexionBD
    {
    private:
        // ESTA ES LA CLAVE PARA XAMPP: 
        // Por defecto, XAMPP usa el usuario "root" y NO tiene contraseña (por eso Pwd está vacío).
        static String^ cadenaConexion = "Server=localhost;Database=epsteam;Uid=root;Pwd=;";

    public:
        static MySqlConnection^ Conectar(); // Cambió a MySqlConnection
        static int ValidarLogin(String^ usuario, String^ password);
        static DataTable^ ObtenerCatalogoJuegos();
        static bool RegistrarCompra(int id_usuario, int id_juego, String^ metodo_pago);
    };
}