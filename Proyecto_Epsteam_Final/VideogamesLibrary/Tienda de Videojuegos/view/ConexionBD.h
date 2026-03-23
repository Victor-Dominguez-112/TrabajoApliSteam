#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

namespace Epsteam {

    /**
     * @class ConexionBD
     * @brief Gestiona la conexión y todas las operaciones con la base de datos MySQL (XAMPP).
     * * Esta clase contiene métodos estáticos para realizar consultas, inserciones y
     * validaciones necesarias para el funcionamiento de la tienda Epsteam, incluyendo
     * el inicio de sesión, el catálogo, los filtros, el registro de compras y de usuarios nuevos.
     */
    public ref class ConexionBD
    {
    private:
        /**
         * @brief Cadena de conexión estática para conectar con la base de datos MySQL local.
         */
        static String^ cadenaConexion = "Server=localhost;Database=epsteam;Uid=root;Pwd=;";

    public:
        /**
         * @brief Almacena el ID del usuario actualmente logueado en la aplicación.
         */
        static int idUsuarioActual = -1;

        /**
         * @brief Almacena el nombre de usuario (nickname) actualmente logueado para mostrarlo en los recibos y ventanas.
         */
        static String^ nicknameActual = "";

        /**
         * @brief Establece y abre una conexión con la base de datos.
         * @return Un objeto MySqlConnection configurado y abierto, o nullptr si hay un error de conexión.
         */
        static MySqlConnection^ Conectar();

        /**
         * @brief Valida las credenciales de inicio de sesión de un usuario.
         * @param usuario Nombre de usuario (nickname) introducido.
         * @param password Contraseña introducida.
         * @return El ID del usuario si las credenciales son correctas, de lo contrario devuelve -1.
         */
        static int ValidarLogin(String^ usuario, String^ password);

        /**
         * @brief Obtiene el catálogo completo de videojuegos sin aplicar ningún filtro.
         * @return DataTable con la información básica (ID, título, precio) de todos los juegos disponibles.
         */
        static DataTable^ ObtenerCatalogoJuegos();

        /**
         * @brief Obtiene una lista de opciones desde la BD para llenar los filtros desplegables.
         * @param tipoFiltro Cadena de texto indicando la tabla de filtro a buscar (ej. "genero", "categoria").
         * @return DataTable con los IDs y nombres de los filtros correspondientes para poblar los CheckedListBox.
         */
        static DataTable^ ObtenerListaFiltros(String^ tipoFiltro);

        /**
         * @brief Busca y filtra juegos en el catálogo basándose en múltiples criterios ingresados por el usuario.
         * @param textoBusqueda Texto introducido en la barra de búsqueda principal.
         * @param idsGeneros Lista de IDs de los géneros seleccionados en el panel de filtros.
         * @param idsCategorias Lista de IDs de las categorías seleccionadas.
         * @param idsEtiquetas Lista de IDs de las etiquetas seleccionadas.
         * @param idsDesarrolladores Lista de IDs de los desarrolladores seleccionados.
         * @param idsEditores Lista de IDs de los editores seleccionados.
         * @param precioMaximo Valor máximo de precio establecido en la barra deslizante.
         * @return DataTable con los resultados de los juegos que cumplen estrictamente con los filtros aplicados.
         */
        static DataTable^ ObtenerCatalogoFiltrado(String^ textoBusqueda,
            List<int>^ idsGeneros,
            List<int>^ idsCategorias,
            List<int>^ idsEtiquetas,
            List<int>^ idsDesarrolladores,
            List<int>^ idsEditores,
            int precioMaximo);

        /**
         * @brief Extrae los juegos que un usuario en específico ha comprado para mostrarlos en su biblioteca.
         * @param id_usuario El ID del usuario del cual se quiere cargar la biblioteca.
         * @return DataTable con los títulos de los juegos y el tiempo jugado registrado.
         */
        static DataTable^ ObtenerMisJuegos(int id_usuario);

        /**
         * @brief Incrementa gradualmente el tiempo de juego registrado en la biblioteca de un usuario.
         * @param id_usuario El ID del usuario activo cuyo tiempo de juego se va a simular.
         */
        static void AvanzarTiempoJuego(int id_usuario);

        // ¡EL SECRETO! Aquí usamos "String^" a secas para que sea 100% compatible con tus ventanas
        /**
         * @brief Ejecuta la transacción SQL completa para registrar una nueva compra.
         * Registra los datos en las tablas: 'compra', 'detalle_compra' y finalmente otorga el juego en 'biblioteca'.
         * @param idUsu ID del usuario que está realizando el pago.
         * @param carrito Lista genérica que contiene los arreglos de strings con los detalles de los juegos en el carrito.
         * @param idMetodo Número entero representativo del método de pago elegido (ej. 1 para Tarjeta).
         * @param totalPagado El monto monetario final cobrado al usuario.
         * @return true si la transacción completa (Commit) fue exitosa, false si ocurrió algún error y se hizo Rollback.
         */
        static bool RegistrarCompra(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, int idMetodo, double totalPagado);

        // Nueva función para registrar usuarios en la Base de Datos
        /**
         * @brief Guarda un nuevo usuario en la base de datos validando que el nombre no esté repetido.
         * @param nickname El nombre de usuario que se desea registrar.
         * @param email El correo electrónico del usuario.
         * @param password La contraseña introducida.
         * @return true si la cuenta se creó y guardó correctamente, false si hubo un error o el usuario ya existe.
         */
        static bool RegistrarUsuario(String^ nickname, String^ email, String^ password);
    };
}