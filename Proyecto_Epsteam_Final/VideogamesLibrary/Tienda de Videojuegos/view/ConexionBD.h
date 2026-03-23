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

        // ¡EL SECRETO! Aquí usamos "String^" a secas para que sea 100% compatible con tus ventanas
        static bool RegistrarCompra(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, int idMetodo, double totalPagado);
    };
}