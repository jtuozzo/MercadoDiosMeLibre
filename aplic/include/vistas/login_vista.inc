<?php
/*
    Nombre: login_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del login.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 20/05/2025.
*/

$css_local = "login.css";

require_once('head.inc');
echo "
<div id='login'>
    <h1>Iniciar sesión</h1>
    <form action='login.php' method='post'>
        <label for='usuario'>Usuario:</label>
        <input type='text' name='usuario' id='usuario' required>
        <label for='password'>Contraseña:</label>
        <input type='password' name='password' id='password' required>
        <button type='submit'>Iniciar sesión</button>
    </form>
    <p><a href='recuperar_password.php'>¿Olvidaste tu contraseña?</a></p>
</div>
";
require_once('foot.inc');
?>
