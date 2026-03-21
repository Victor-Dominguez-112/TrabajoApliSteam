🎯 Controller (Controlador)

📌 Descripción

El controlador actúa como intermediario entre el modelo y la vista. Procesa las acciones del usuario y coordina el flujo del sistema.



🧠 Responsabilidades

* Recibir datos de la vista
* Validar información
* Ejecutar lógica del sistema
* Llamar al modelo
* Actualizar la vista



🧩 Clases principales

* `UsuarioController`
* `VideojuegoController`
* `CompraController`



🔄 Ejemplo de funciones

* `registrarUsuario()`
* `mostrarCatalogo()`
* `comprarJuego()`



🔁 Flujo de trabajo

1. La vista envía una acción
2. El controlador procesa la solicitud
3. Se comunica con el modelo
4. Devuelve resultados a la vista



📌 Notas

* No maneja directamente la base de datos
* No muestra información directamente (eso es tarea de la vista)
