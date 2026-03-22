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

        static MySqlConnection^ Conectar();
        static int ValidarLogin(String^ usuario, String^ password);
        static DataTable^ ObtenerCatalogoJuegos();

        // =========================================================================
        static DataTable^ ObtenerListaFiltros(String^ tipoFiltro);

        // ¡ACTUALIZADO! Ahora recibe Desarrolladores y Editores
        static DataTable^ ObtenerCatalogoFiltrado(String^ textoBusqueda,
            List<int>^ idsGeneros,
            List<int>^ idsCategorias,
            List<int>^ idsEtiquetas,
            List<int>^ idsDesarrolladores,
            List<int>^ idsEditores,
            int precioMaximo);
        // =========================================================================

        static DataTable^ ObtenerMisJuegos(int id_usuario);
        static bool RegistrarCompra(int id_usuario, int id_juego, String^ metodo_pago);
        static void AvanzarTiempoJuego(int id_usuario);
    };
}