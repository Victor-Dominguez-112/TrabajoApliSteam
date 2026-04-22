#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

namespace Epsteam {

    public ref class ConexionBD
    {
    private:
        static String^ cadenaConexion = "Server=localhost;Database=epsteam;Uid=root;Pwd=;";

    public:
        static int idUsuarioActual = -1;
        static String^ nicknameActual = "";
        static String^ avatarActual = "";
        static int temaActual = 0;

        // --- FUNCIONES ---
        static MySqlConnection^ Conectar();
        static int ValidarLogin(String^ usuario, String^ password);
        static int ValidarPagoEmail(String^ email, String^ password);
        static bool GuardarPreferencias(int idUsu, String^ avatar, int tema);
        static DataTable^ ObtenerCatalogoJuegos();

        static DataTable^ ObtenerListaFiltros(String^ tipoFiltro);

        static DataTable^ ObtenerCatalogoFiltrado(String^ textoBusqueda,
            List<int>^ idsGeneros,
            List<int>^ idsCategorias,
            List<int>^ idsEtiquetas,
            List<int>^ idsDesarrolladores,
            List<int>^ idsEditores,
            int precioMaximo);

        static DataTable^ ObtenerMisJuegos(int id_usuario);

        static void AvanzarTiempoJuego(int id_usuario);

        static bool RegistrarCompra(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, int idMetodo, double totalPagado);

        static bool RegistrarUsuario(String^ nickname, String^ email, String^ password);

        static DataTable^ ObtenerDetalleJuego(int id_juego);
    };
}