#include "ConexionBD.h"

using namespace Epsteam;
using namespace System::Windows::Forms;

// 1. Conectar a la base de datos
MySqlConnection^ ConexionBD::Conectar() 
{
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

int Epsteam::ConexionBD::ValidarLogin(String^ usuario, String^ password) {
    int idUsuario = -1;
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            // Limpiamos memoria antes de empezar
            avatarActual = "";
            temaActual = 0;

            String^ query = "CALL SP_ValidarLogin(@usu, @pass)";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@usu", usuario);
            cmd->Parameters->AddWithValue("@pass", password);

            MySqlDataReader^ reader = cmd->ExecuteReader();

            if (reader->Read()) {
                idUsuario = Convert::ToInt32(reader["id_usuario"]);
                idUsuarioActual = idUsuario;
                nicknameActual = reader["nickname"]->ToString();

                // 1. Leemos la foto (Si es la de defecto, la ignoramos para mostrar el BOTON)
                if (!reader->IsDBNull(reader->GetOrdinal("avatar_ruta"))) {
                    String^ fotoBD = reader["avatar_ruta"]->ToString();
                    if (fotoBD != "avatar1.png" && fotoBD != "") {
                        avatarActual = fotoBD;
                    }
                }

                // 2. ¡AQUÍ ESTÁ LA CLAVE! Leemos el tema guardado
                if (!reader->IsDBNull(reader->GetOrdinal("tema_elegido"))) {
                    temaActual = Convert::ToInt32(reader["tema_elegido"]);
                }
            }
            reader->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Error en Base de Datos: " + ex->Message);
        }
        finally { con->Close(); }
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

// 3.1. Cargar las opciones de las listas desplegables (AHORA USANDO CALL)
DataTable^ ConexionBD::ObtenerListaFiltros(String^ tipoFiltro) {
    DataTable^ tablaFiltros = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            // El procedimiento decide internamente a qué tabla hacerle el SELECT
            String^ query = "CALL SP_ObtenerListaFiltros(@tipo)";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@tipo", tipoFiltro);

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

// 3.2. Buscar juegos (Se queda igual porque la consulta es 100% dinámica)
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

// 4. Guardar la compra en las tablas correspondientes
bool ConexionBD::RegistrarCompra(int idUsu, System::Collections::Generic::List<cli::array<System::String^>^>^ carrito, int idMetodo, double totalPagado) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        MySqlTransaction^ transaccion = con->BeginTransaction();
        try {
            String^ queryCompra = "INSERT INTO compra (`fecha_compra`, `total_pagado`, `id_usuario`) "
                "VALUES (NOW(), @total, @idUsu); "
                "SELECT LAST_INSERT_ID();";

            MySqlCommand^ cmd1 = gcnew MySqlCommand(queryCompra, con, transaccion);
            cmd1->Parameters->AddWithValue("@total", totalPagado);
            cmd1->Parameters->AddWithValue("@idUsu", idUsu);

            int idCompra = Convert::ToInt32(cmd1->ExecuteScalar());

            String^ queryDetalle = "INSERT INTO detalle_compra (id_compra, id_juego, precio_unitario) VALUES (@idCompra, @idJuego, @precioPagado); SELECT LAST_INSERT_ID();";
            MySqlCommand^ cmd2 = gcnew MySqlCommand(queryDetalle, con, transaccion);

            String^ queryBiblio = "INSERT INTO biblioteca (id_usuario, id_juego, id_detalle, fecha_adquisicion, tiempo_jugado_minutos) "
                "VALUES (@idUsu, @idJuego, @idDetalle, NOW(), 0)";
            MySqlCommand^ cmd3 = gcnew MySqlCommand(queryBiblio, con, transaccion);

            for (int i = 0; i < carrito->Count; i++) {
                cmd2->Parameters->Clear();
                cmd2->Parameters->AddWithValue("@idCompra", idCompra);
                cmd2->Parameters->AddWithValue("@idJuego", Convert::ToInt32(carrito[i][0]));

                String^ precioStr = carrito[i][2]->Replace("$", "")->Replace(" MXN", "")->Replace(",", "");
                cmd2->Parameters->AddWithValue("@precioPagado", Convert::ToDouble(precioStr));

                int idDetalle = Convert::ToInt32(cmd2->ExecuteScalar());

                cmd3->Parameters->Clear();
                cmd3->Parameters->AddWithValue("@idUsu", idUsu);
                cmd3->Parameters->AddWithValue("@idJuego", Convert::ToInt32(carrito[i][0]));
                cmd3->Parameters->AddWithValue("@idDetalle", idDetalle);

                cmd3->ExecuteNonQuery();
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

// 5. Cargar los juegos que el usuario ya compró (AHORA USANDO CALL)
DataTable^ ConexionBD::ObtenerMisJuegos(int id_usuario) {
    DataTable^ tablaMisJuegos = gcnew DataTable();
    MySqlConnection^ con = Conectar();

    if (con != nullptr) {
        try {
            String^ query = "CALL SP_ObtenerMisJuegos(@idUsu)";
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

// 6. Sumar tiempo jugado a la biblioteca (AHORA USANDO CALL)
void ConexionBD::AvanzarTiempoJuego(int id_usuario) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            String^ query = "CALL SP_AvanzarTiempoJuego(@idUsu)";
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

// 8. Guardar las preferencias visuales del usuario
bool ConexionBD::GuardarPreferencias(int idUsu, String^ avatar, int tema) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            String^ query = "UPDATE usuario SET avatar_ruta = @avatar, tema_elegido = @tema WHERE id_usuario = @id";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@avatar", avatar);
            cmd->Parameters->AddWithValue("@tema", tema);
            cmd->Parameters->AddWithValue("@id", idUsu);
            cmd->ExecuteNonQuery();

            // Actualizamos la memoria del programa
            avatarActual = avatar;
            temaActual = tema;
            return true;
        }
        catch (...) { return false; }
        finally { con->Close(); }
    }
    return false;
}

// 9. Validar pagos usando el Correo Electrónico (Para PayPal)
int ConexionBD::ValidarPagoEmail(String^ email, String^ password) {
    int idEncontrado = -1;
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            String^ query = "SELECT id_usuario FROM usuario WHERE email = @mail AND password_hash = @pass";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@mail", email);
            cmd->Parameters->AddWithValue("@pass", password);

            Object^ resultado = cmd->ExecuteScalar();
            if (resultado != nullptr) {
                idEncontrado = Convert::ToInt32(resultado);
            }
        }
        catch (...) {}
        finally { con->Close(); }
    }
    return idEncontrado;
}

// 10. Traer la Ficha Técnica de un solo juego para frmDetalleJuego
DataTable^ ConexionBD::ObtenerDetalleJuego(int id_juego) {
    DataTable^ tabla = gcnew DataTable();
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            String^ query = "CALL SP_ObtenerFichaTecnicaJuego(@id)";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@id", id_juego);
            MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
            adapter->Fill(tabla);
        }
        catch (...) {}
        finally { con->Close(); }
    }
    return tabla;
}

// 7. Registrar un usuario nuevo en la Base de Datos (AHORA USANDO CALL)
bool ConexionBD::RegistrarUsuario(String^ nickname, String^ email, String^ password) {
    MySqlConnection^ con = Conectar();
    if (con != nullptr) {
        try {
            // El Procedimiento Almacenado revisa si existe y si no, lo inserta calculando el ID.
            String^ query = "CALL SP_RegistrarUsuario(@nick, @email, @pass)";
            MySqlCommand^ cmd = gcnew MySqlCommand(query, con);
            cmd->Parameters->AddWithValue("@nick", nickname);
            cmd->Parameters->AddWithValue("@email", email);
            cmd->Parameters->AddWithValue("@pass", password);

            // ExecuteScalar atrapa el "SELECT 1" o "SELECT 0" que arroja el Procedimiento
            int resultado = Convert::ToInt32(cmd->ExecuteScalar());

            if (resultado == 0) {
                MessageBox::Show("Ese nombre de usuario ya está ocupado. ¡Elige otro!", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }

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