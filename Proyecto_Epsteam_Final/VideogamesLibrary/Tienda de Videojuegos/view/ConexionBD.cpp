#include "ConexionBD.h"

using namespace Epsteam;
using namespace System::Windows::Forms;

// 1. Conectar a la base de datos
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

// 2. Revisar si el usuario y contraseña son correctos
int ConexionBD::ValidarLogin(String^ usuario, String^ password) {
    int idUsuario = -1;
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "SELECT id_usuario FROM usuario WHERE nickname = @usu AND password_hash = @pass";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@usu", usuario);
            cmd->Parameters->AddWithValue("@pass", password);

            Object^ resultado = cmd->ExecuteScalar();

            if (resultado != nullptr) {
                idUsuario = Convert::ToInt32(resultado);
                idUsuarioActual = idUsuario;
            }
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

// 3.1. Cargar las opciones de las listas desplegables (Géneros, Categorías, etc.)
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

// 3.2. Buscar juegos dependiendo de lo que el usuario seleccionó o escribió
DataTable^ ConexionBD::ObtenerCatalogoFiltrado(String^ textoBusqueda, List<int>^ idsGeneros, List<int>^ idsCategorias, List<int>^ idsEtiquetas, List<int>^ idsDesarrolladores, List<int>^ idsEditores, int precioMaximo) {
    DataTable^ tablaResultados = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "SELECT DISTINCT v.id_juego, v.titulo, v.precio_base FROM videojuego v ";

            // Unir las tablas intermedias si el usuario marcó alguna casilla
            if (idsGeneros != nullptr && idsGeneros->Count > 0) query += "JOIN juego_genero jg ON v.id_juego = jg.id_juego ";
            if (idsCategorias != nullptr && idsCategorias->Count > 0) query += "JOIN juego_categoria jc ON v.id_juego = jc.id_juego ";
            if (idsEtiquetas != nullptr && idsEtiquetas->Count > 0) query += "JOIN juego_etiqueta je ON v.id_juego = je.id_juego ";
            if (idsDesarrolladores != nullptr && idsDesarrolladores->Count > 0) query += "JOIN juego_desarrollador jd ON v.id_juego = jd.id_juego ";
            if (idsEditores != nullptr && idsEditores->Count > 0) query += "JOIN juego_editor jed ON v.id_juego = jed.id_juego ";

            // Filtro del precio de la barra
            query += "WHERE v.precio_base <= @precioMax ";

            // Filtrar por las casillas que están marcadas
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

            // Filtrar por el texto que escribió el usuario
            if (!String::IsNullOrWhiteSpace(textoBusqueda)) {
                query += "AND v.titulo LIKE @busqueda ";
                // Ordenar para que el juego que empiece con esa letra salga primero
                query += "ORDER BY CASE WHEN v.titulo LIKE @ordenExacto THEN 1 ELSE 2 END, v.titulo ASC";
            }
            else {
                query += "ORDER BY v.titulo ASC"; // Orden alfabético normal si no escribió nada
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

// 4. Guardar la compra en las tablas correspondientes
bool ConexionBD::RegistrarCompra(int id_usuario, int id_juego, String^ metodo_pago) {
    bool exito = false;
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        MySqlTransaction^ transaccion = con->BeginTransaction();
        try {
            String^ queryPrecio = "SELECT precio_base FROM videojuego WHERE id_juego = @idJuego";
            MySqlCommand^ cmdPrecio = gcnew MySqlCommand(queryPrecio, con, transaccion);
            cmdPrecio->Parameters->AddWithValue("@idJuego", id_juego);
            double precioJuego = Convert::ToDouble(cmdPrecio->ExecuteScalar());

            String^ queryMaxCompra = "SELECT COALESCE(MAX(id_compra), 0) + 1 FROM compra";
            MySqlCommand^ cmdMaxCompra = gcnew MySqlCommand(queryMaxCompra, con, transaccion);
            int nuevoIdCompra = Convert::ToInt32(cmdMaxCompra->ExecuteScalar());

            String^ queryCompra = "INSERT INTO compra (id_compra, fecha_compra, total_pagado, id_usuario) VALUES (@nuevoIdCompra, NOW(), @precio, @idUsu)";
            MySqlCommand^ cmdCompra = gcnew MySqlCommand(queryCompra, con, transaccion);
            cmdCompra->Parameters->AddWithValue("@nuevoIdCompra", nuevoIdCompra);
            cmdCompra->Parameters->AddWithValue("@precio", precioJuego);
            cmdCompra->Parameters->AddWithValue("@idUsu", id_usuario);
            cmdCompra->ExecuteNonQuery();

            String^ queryMaxDetalle = "SELECT COALESCE(MAX(id_detalle), 0) + 1 FROM detalle_compra";
            MySqlCommand^ cmdMaxDetalle = gcnew MySqlCommand(queryMaxDetalle, con, transaccion);
            int nuevoIdDetalle = Convert::ToInt32(cmdMaxDetalle->ExecuteScalar());

            String^ queryDetalle = "INSERT INTO detalle_compra (id_detalle, id_compra, id_juego, precio_unitario) VALUES (@nuevoIdDetalle, @nuevoIdCompra, @idJuego, @precio)";
            MySqlCommand^ cmdDetalle = gcnew MySqlCommand(queryDetalle, con, transaccion);
            cmdDetalle->Parameters->AddWithValue("@nuevoIdDetalle", nuevoIdDetalle);
            cmdDetalle->Parameters->AddWithValue("@nuevoIdCompra", nuevoIdCompra);
            cmdDetalle->Parameters->AddWithValue("@idJuego", id_juego);
            cmdDetalle->Parameters->AddWithValue("@precio", precioJuego);
            cmdDetalle->ExecuteNonQuery();

            String^ queryMaxBiblio = "SELECT COALESCE(MAX(id_biblioteca), 0) + 1 FROM biblioteca";
            MySqlCommand^ cmdMaxBiblio = gcnew MySqlCommand(queryMaxBiblio, con, transaccion);
            int nuevoIdBiblio = Convert::ToInt32(cmdMaxBiblio->ExecuteScalar());

            String^ queryBiblio = "INSERT INTO biblioteca (id_biblioteca, id_usuario, id_juego, id_detalle, fecha_adquisicion, tiempo_jugado_minutos) VALUES (@idBiblio, @idUsu, @idJuego, @nuevoIdDetalle, NOW(), 0)";
            MySqlCommand^ cmdBiblio = gcnew MySqlCommand(queryBiblio, con, transaccion);
            cmdBiblio->Parameters->AddWithValue("@idBiblio", nuevoIdBiblio);
            cmdBiblio->Parameters->AddWithValue("@idUsu", id_usuario);
            cmdBiblio->Parameters->AddWithValue("@idJuego", id_juego);
            cmdBiblio->Parameters->AddWithValue("@nuevoIdDetalle", nuevoIdDetalle);
            cmdBiblio->ExecuteNonQuery();

            transaccion->Commit();
            exito = true;
        }
        catch (Exception^ ex) {
            transaccion->Rollback();
            MessageBox::Show("Error al procesar el pago: " + ex->Message);
        }
        finally {
            con->Close();
        }
    }
    return exito;
}

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