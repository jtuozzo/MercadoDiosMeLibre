<?php
/*
    Nombre: confirmar_usuario_vista.php
    Autor: Julio Tuozzo.
    Función: Vista de la confirmación del usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 24/05/2025.
*/

$css_local = "usuario.css";

require(__DIR__ . '/layouts/header.php');
echo "
<script type='text/javascript' src='./js/usuario.js'></script>

<div id='usuario'>
    <h1>Confirmación de usuario</h1>
    $mensaje
</div>
";
require(__DIR__ . '/layouts/footer.php');
?>
