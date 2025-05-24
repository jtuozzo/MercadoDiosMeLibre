<?php
/*
    Nombre: login_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del login.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 24/05/2025.
*/

$css_local = "login.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/login.js'></script>

<div id='login'>
    <h1>Ingresar</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post'>
        <div>
            <label for='email'>  E-mail: </label>
            <input type='email' name='email' id='email' value='$email' size='40' maxlength='64' $st_email> $email_err 
        </div>

        <div>
            <label for='clave'> Clave: </label>
            <input type='password' name='clave' id='clave' size='20' maxlength='20' $st_clave> $clave_err 
            <div class='verifique'>(Verifique no tener activada la tecla \"BLOQ MAYUS\" al ingresar la clave)</div>
        </div>

        <div>

        <label for='recordarme'><input type='checkbox' name='recordarme' id='recordarme' value='S'> Recordarme en este dispositivo </label>
        </div>


        <input class='boton' type='submit' name='ingresar' value='Iniciar sesión'/>

   </form>

   <p id='me_olvide'> 
        <a href='me_olvide.php'><img src='./images/el_grito_negro.png' align='middle' /> Me olvidé la clave</a>
    </p>

</div>
$mensaje
";
require_once('foot.inc');
?>
