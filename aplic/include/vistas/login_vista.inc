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
      
    <form action='{$_SERVER['PHP_SELF']}' method='post'>
        <label for='email'>
            E-mail: <input type='text' name='email' id='email' value='$email' size='50' maxlength='64' $st_email> $email_err 
        </label>
        
        <label for='clave'>
            Clave: <input type='password' name='clave' id='clave' size='20' maxlength='20' $st_clave> $clave_err
        </label>
        
        <input type='submit' name='ingresar' value='Iniciar sesión'/>
    </form>
    <p><a href='recuperar_password.php'>¿Olvidaste tu contraseña?</a></p>
</div>
$mensaje
";
require_once('foot.inc');
?>
