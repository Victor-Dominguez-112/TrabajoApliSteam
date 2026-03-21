📦 Model (Modelo)

📌 Descripción

El modelo se encarga de la gestión de datos y la interacción con la base de datos MySQL. Representa las entidades del sistema y ejecuta operaciones CRUD.


🧠 Responsabilidades

* Conexión a la base de datos
* Inserción de datos
* Consulta de registros
* Actualización de información
* Eliminación de datos



🧩 Clases principales

* `ConexionBD` → Maneja la conexión con MySQL
* `Usuario` → Representa a los usuarios
* `Videojuego` → Representa los juegos
* `Compra` → Registra las compras



🗄️ Base de datos

Tablas utilizadas:

* usuarios
* videojuegos
* compras



🔄 Ejemplo de funciones

* `guardarUsuario()`
* `obtenerVideojuegos()`
* `registrarCompra()`



📌 Notas

* No contiene lógica de interfaz
* No interactúa directamente con el usuario
