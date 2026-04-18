#include "ConexionBD.h"
// ¡Cero includes de ventanas aquí! Adiós al bucle infinito.

using namespace Epsteam;
using namespace System::Windows::Forms;

/**
 * @brief Implementación de la conexión a la base de datos MySQL.
 * @details Utiliza la cadena de conexión definida en el archivo de cabecera.
 * Si la conexión falla, captura la excepción y muestra un MessageBox con el error.
 * @return Un objeto MySqlConnection abierto, o nullptr si falla.
 */
 // 1. Conectar a la base de datos (Se queda igual)
MySqlConnection^ ConexionBD::Conectar() {
    try {
        MySqlConnection^ conexion = gcnew MySqlConnection(cadenaConexion);
        conexion->Open();
        return conexion;
    }
    catch (Exception^ ex) {
        MessageBox::Show("Error al conectar con MySQL: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return nullptr;
    }
}

/**
 * @brief Implementación de la validación del inicio de sesión.
 * @details Realiza una consulta SELECT buscando coincidencias exactas del nickname y el hash de la contraseña.
 * Además de verificar el acceso, guarda el ID y el nickname en variables estáticas globales para uso futuro.
 * @param usuario El nickname introducido en el login.
 * @param password La contraseña introducida en el login.
 * @return El ID del usuario (>0) en caso de éxito, o -1 en caso de error o credenciales incorrectas.
 */
 // 2. CORREGIMOS ESTA FUNCIÓN PARA ATRAPAR EL NOMBRE DE USUARIO
int ConexionBD::ValidarLogin(String^ usuario, String^ password) {
    int idUsuario = -1;
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            // ¡EL SECRETO! Ahora también traemos el nickname de la tabla
            String^ query = "SELECT id_usuario, nickname FROM usuario WHERE nickname = @usu AND password_hash = @pass";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@usu", usuario);
            cmd->Parameters->AddWithValue("@pass", password);

            MySqlDataReader^ reader = cmd->ExecuteReader();

            if (reader->Read()) {
                // Atrapamos el ID
                idUsuario = Convert::ToInt32(reader["id_usuario"]);
                idUsuarioActual = idUsuario;

                // ¡LA CORONA! Atrapamos el nombre de usuario y lo guardamos
                nicknameActual = reader["nickname"]->ToString();
            }
            reader->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error en el Login: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return idUsuario;
}
// (El resto del archivo se queda igualito como lo tienes)

/**
 * @brief Implementación de la obtención del catálogo completo.
 * @details Ejecuta un SELECT básico sobre la tabla 'videojuego' para extraer ID, título y precio base.
 * Rellena un DataTable a través de un MySqlDataAdapter.
 * @return DataTable instanciado con todos los juegos disponibles en la base de datos.
 */
 // 3. Traer todos los juegos al abrir la tienda por primera vez
DataTable^ ConexionBD::ObtenerCatalogoJuegos() {
    DataTable^ tablaJuegos = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "SELECT id_juego, titulo, precio_base FROM videojuego";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(tablaJuegos);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al traer los juegos: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return tablaJuegos;
}

/**
 * @brief Implementación para cargar catálogos secundarios (filtros).
 * @details Utiliza condicionales para determinar qué tabla consultar (genero, categoria, etiqueta, etc.).
 * Estandariza la salida para que las columnas siempre se llamen 'id' y 'nombre', facilitando su uso en la interfaz.
 * @param tipoFiltro String que define la tabla objetivo.
 * @return DataTable estructurado con columnas estandarizadas.
 */
 // 3.1. Cargar las opciones de las listas desplegables
DataTable^ ConexionBD::ObtenerListaFiltros(String^ tipoFiltro) {
    DataTable^ tablaFiltros = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "";
            if (tipoFiltro == "genero") query = "SELECT id_genero AS id, nombre_genero AS nombre FROM genero ORDER BY nombre ASC";
            else if (tipoFiltro == "categoria") query = "SELECT id_categoria AS id, nombre_categoria AS nombre FROM categoria ORDER BY nombre ASC";
            else if (tipoFiltro == "etiqueta") query = "SELECT id_etiqueta AS id, nombre_etiqueta AS nombre FROM etiqueta ORDER BY nombre ASC";
            else if (tipoFiltro == "desarrollador") query = "SELECT id_desarrollador AS id, nombre_empresa AS nombre FROM desarrollador ORDER BY nombre ASC";
            else if (tipoFiltro == "editor") query = "SELECT id_editor AS id, nombre_editor AS nombre FROM editor ORDER BY nombre ASC";

            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(tablaFiltros);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al cargar los filtros: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return tablaFiltros;
}

/**
 * @brief Implementación de la búsqueda dinámica de juegos.
 * @details Construye una consulta SQL dinámica agregando bloques JOIN y WHERE dependiendo
 * de qué listas (Lists) vienen con datos. Aplica cláusulas IN para los filtros y LIKE para la búsqueda por texto.
 * @param textoBusqueda Texto ingresado por el usuario (filtro LIKE).
 * @param idsGeneros Lista de enteros de los géneros marcados.
 * @param idsCategorias Lista de enteros de las categorías marcadas.
 * @param idsEtiquetas Lista de enteros de las etiquetas marcadas.
 * @param idsDesarrolladores Lista de enteros de desarrolladores marcados.
 * @param idsEditores Lista de enteros de editores marcados.
 * @param precioMaximo Tope de precio base.
 * @return DataTable filtrado con los juegos coincidentes.
 */
 // 3.2. Buscar juegos
DataTable^ ConexionBD::ObtenerCatalogoFiltrado(String^ textoBusqueda, List<int>^ idsGeneros, List<int>^ idsCategorias, List<int>^ idsEtiquetas, List<int>^ idsDesarrolladores, List<int>^ idsEditores, int precioMaximo) {
    DataTable^ tablaResultados = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "SELECT DISTINCT v.id_juego, v.titulo, v.precio_base FROM videojuego v ";

            if (idsGeneros != nullptr && idsGeneros->Count > 0) query += "JOIN juego_genero jg ON v.id_juego = jg.id_juego ";
            if (idsCategorias != nullptr && idsCategorias->Count > 0) query += "JOIN juego_categoria jc ON v.id_juego = jc.id_juego ";
            if (idsEtiquetas != nullptr && idsEtiquetas->Count > 0) query += "JOIN juego_etiqueta je ON v.id_juego = je.id_juego ";
            if (idsDesarrolladores != nullptr && idsDesarrolladores->Count > 0) query += "JOIN juego_desarrollador jd ON v.id_juego = jd.id_juego ";
            if (idsEditores != nullptr && idsEditores->Count > 0) query += "JOIN juego_editor jed ON v.id_juego = jed.id_juego ";

            query += "WHERE v.precio_base <= @precioMax ";

            if (idsGeneros != nullptr && idsGeneros->Count > 0) {
                String^ inClause = String::Join(",", idsGeneros);
                query += "AND jg.id_genero IN (" + inClause + ") ";
            }
            if (idsCategorias != nullptr && idsCategorias->Count > 0) {
                String^ inClause = String::Join(",", idsCategorias);
                query += "AND jc.id_categoria IN (" + inClause + ") ";
            }
            if (idsEtiquetas != nullptr && idsEtiquetas->Count > 0) {
                String^ inClause = String::Join(",", idsEtiquetas);
                query += "AND je.id_etiqueta IN (" + inClause + ") ";
            }
            if (idsDesarrolladores != nullptr && idsDesarrolladores->Count > 0) {
                String^ inClause = String::Join(",", idsDesarrolladores);
                query += "AND jd.id_desarrollador IN (" + inClause + ") ";
            }
            if (idsEditores != nullptr && idsEditores->Count > 0) {
                String^ inClause = String::Join(",", idsEditores);
                query += "AND jed.id_editor IN (" + inClause + ") ";
            }

            if (!String::IsNullOrWhiteSpace(textoBusqueda)) {
                query += "AND v.titulo LIKE @busqueda ";
                query += "ORDER BY CASE WHEN v.titulo LIKE @ordenExacto THEN 1 ELSE 2 END, v.titulo ASC";
            }
            else {
                query += "ORDER BY v.titulo ASC";
            }

            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@precioMax", precioMaximo);

            if (!String::IsNullOrWhiteSpace(textoBusqueda)) {
                cmd->Parameters->AddWithValue("@busqueda", "%" + textoBusqueda->Trim() + "%");
                cmd->Parameters->AddWithValue("@ordenExacto", textoBusqueda->Trim() + "%");
            }

            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(tablaResultados);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al buscar juegos: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return tablaResultados;
}

/**
 * @brief Implementación de la transacción de compra maestra.
 * @details Este es el método central de transacciones en la tienda.
 * Abre una transacción SQL (BeginTransaction) y realiza tres inserciones dependientes:
 * 1. Inserta el recibo global en 'compra' y recupera el LAST_INSERT_ID().
 * 2. Itera sobre el carrito para insertar cada ítem en 'detalle_compra'.
 * 3. Inmediatamente inserta el registro del juego en 'biblioteca' a nombre del usuario.
 * Si algo falla, aplica Rollback. Si todo es correcto, hace Commit.
 * @param idUsu ID del cliente.
 * @param carrito Lista de los juegos y sus precios a insertar.
 * @param idMetodo ID del método de pago.
 * @param totalPagado Gran total de la venta.
 * @return booleano indicando el éxito del bloque de transacciones.
 */
 // 4. Guardar la compra en las tablas correspondientes
bool ConexionBD::RegistrarCompra(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, int idMetodo, double totalPagado) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        MySqlTransaction^ transaccion = con->BeginTransaction();
        try {
            // 1. Guardar el ticket principal
            String^ queryCompra = "INSERT INTO compra (`fecha_compra`, `total_pagado`, `id_usuario`) "
                "VALUES (NOW(), @total, @idUsu); "
                "SELECT LAST_INSERT_ID();";

            MySqlCommand^ cmd1 = gcnew MySqlCommand(queryCompra, con, transaccion);
            cmd1->Parameters->AddWithValue("@total", totalPagado);
            cmd1->Parameters->AddWithValue("@idUsu", idUsu);

            int idCompra = Convert::ToInt32(cmd1->ExecuteScalar());

            // 2. Guardar el detalle de la compra (Le agregamos SELECT LAST_INSERT_ID para saber qué número de detalle fue)
            String^ queryDetalle = "INSERT INTO detalle_compra (id_compra, id_juego, precio_unitario) VALUES (@idCompra, @idJuego, @precioPagado); SELECT LAST_INSERT_ID();";
            MySqlCommand^ cmd2 = gcnew MySqlCommand(queryDetalle, con, transaccion);

            // 3. ¡LA NOVEDAD! Preparar la inserción a la biblioteca
            String^ queryBiblio = "INSERT INTO biblioteca (id_usuario, id_juego, id_detalle, fecha_adquisicion, tiempo_jugado_minutos) "
                "VALUES (@idUsu, @idJuego, @idDetalle, NOW(), 0)";
            MySqlCommand^ cmd3 = gcnew MySqlCommand(queryBiblio, con, transaccion);

            for (int i = 0; i < carrito->Count; i++) {
                // A) Insertar en detalle_compra
                cmd2->Parameters->Clear();
                cmd2->Parameters->AddWithValue("@idCompra", idCompra);
                cmd2->Parameters->AddWithValue("@idJuego", Convert::ToInt32(carrito[i][0]));

                String^ precioStr = carrito[i][2]->Replace("$", "")->Replace(" MXN", "")->Replace(",", "");
                cmd2->Parameters->AddWithValue("@precioPagado", Convert::ToDouble(precioStr));

                // Usamos ExecuteScalar para atrapar el ID del detalle recién creado
                int idDetalle = Convert::ToInt32(cmd2->ExecuteScalar());

                // B) ¡ENTREGAR EL JUEGO A LA BIBLIOTECA!
                cmd3->Parameters->Clear();
                cmd3->Parameters->AddWithValue("@idUsu", idUsu);
                cmd3->Parameters->AddWithValue("@idJuego", Convert::ToInt32(carrito[i][0]));
                cmd3->Parameters->AddWithValue("@idDetalle", idDetalle);

                cmd3->ExecuteNonQuery(); // Guardamos el juego en la repisa
            }

            transaccion->Commit();
            return true;
        }
        catch (Exception^ ex) {
            transaccion->Rollback();
            MessageBox::Show("Error al registrar la compra: " + ex->Message);
            return false;
        }
        finally {
            con->Close();
        }
    }
    return false;
}

/**
 * @brief Implementación de la carga de inventario de usuario.
 * @details Realiza un JOIN cuádruple entre 'compra', 'detalle_compra', 'videojuego' y 'biblioteca'
 * para garantizar la pertenencia del juego y extraer sus minutos jugados de manera segura.
 * @param id_usuario ID del cliente activo.
 * @return DataTable resultante de la consulta compleja de biblioteca.
 */
 // 5. Cargar los juegos que el usuario ya compró
DataTable^ ConexionBD::ObtenerMisJuegos(int id_usuario) {
    DataTable^ tablaMisJuegos = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "SELECT v.id_juego, v.titulo, b.tiempo_jugado_minutos FROM compra c JOIN detalle_compra d ON c.id_compra = d.id_compra JOIN videojuego v ON d.id_juego = v.id_juego JOIN biblioteca b ON d.id_detalle = b.id_detalle WHERE c.id_usuario = @idUsu";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@idUsu", id_usuario);
            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(tablaMisJuegos);
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al cargar biblioteca: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return tablaMisJuegos;
}

/**
 * @brief Función invisible para simular el avance del tiempo de juego.
 * @details Realiza un UPDATE sumando 1 al campo de tiempo_jugado_minutos de todos los juegos del usuario.
 * Se incluyó una restricción WHERE para que el contador de horas no sobrepase las 2 horas (121 minutos) como demo.
 * @param id_usuario El ID del cliente logueado actualmente.
 */
 // 6. Sumar tiempo jugado a la biblioteca
void ConexionBD::AvanzarTiempoJuego(int id_usuario) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            String^ query = "UPDATE biblioteca SET tiempo_jugado_minutos = tiempo_jugado_minutos + 1 WHERE id_usuario = @idUsu AND tiempo_jugado_minutos < 121";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@idUsu", id_usuario);
            cmd->ExecuteNonQuery();
        }
        catch (...) {}
        finally {
            con->Close();
        }
    }
}

/**
 * @brief Registro seguro de nuevos clientes.
 * @details Evita la inserción si el nickname ya existe mediante un COUNT().
 * Adicionalmente, implementa una lógica de auto-resolución (bypass) de IDs, calculando el máximo + 1
 * para eludir posibles restricciones de llave foránea (FK) impuestas en la tabla por la base de datos.
 * @param nickname Elegido por el cliente.
 * @param email Correo electrónico de registro.
 * @param password Contraseña de acceso a Epsteam.
 * @return True si se inserta el usuario burlando restricciones con el nuevo ID generado, False de lo contrario.
 */
 // 7. Registrar un usuario nuevo en la Base de Datos
bool ConexionBD::RegistrarUsuario(String^ nickname, String^ email, String^ password) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            // A) Revisar si el usuario ya existe para no tener duplicados
            String^ queryCheck = "SELECT COUNT(*) FROM usuario WHERE nickname = @nick";
            MySqlCommand^ cmdCheck = gcnew MySqlCommand(queryCheck, con);
            cmdCheck->Parameters->AddWithValue("@nick", nickname);

            int existe = Convert::ToInt32(cmdCheck->ExecuteScalar());
            if (existe > 0) {
                MessageBox::Show("Ese nombre de usuario ya está ocupado. ¡Elige otro!", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

            // B) ¡EL TRUCO MAESTRO! Le ganamos a MySQL calculando el ID nosotros mismos
            // Buscamos el ID más alto y le sumamos 1. Si está vacía, le pone el 1.
            String^ queryMax = "SELECT IFNULL(MAX(id_usuario), 0) + 1 FROM usuario";
            MySqlCommand^ cmdMax = gcnew MySqlCommand(queryMax, con);
            int nuevoId = Convert::ToInt32(cmdMax->ExecuteScalar());

            // C) Guardamos mandándole nuestro propio ID a la fuerza (id_usuario)
            String^ query = "INSERT INTO usuario (id_usuario, nickname, email, password_hash, fecha_nacimiento, saldo_cartera, id_pais) "
                "VALUES (@id, @nick, @email, @pass, '2000-01-01', 0.00, 1)";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@id", nuevoId); // Metemos el ID calculado
            cmd->Parameters->AddWithValue("@nick", nickname);
            cmd->Parameters->AddWithValue("@email", email);
            cmd->Parameters->AddWithValue("@pass", password);

            cmd->ExecuteNonQuery();
            return true;
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error al crear cuenta: " + ex->Message);
            return false;
        }
        finally {
            con->Close();
        }
    }
    return false;
}