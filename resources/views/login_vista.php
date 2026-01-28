<?php
/*
    Nombre: login_vista.php
    Autor: Julio Tuozzo.
    Función: Vista del login.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 08/06/2025.
*/

$css_local = "login.css";

require(__DIR__ . '/layouts/header.php');
echo "
<script type='text/javascript' src='./js/login.js'></script>

<div id='login'>
    <h1>Ingresar</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post'>
        <div>
            <label for='email'>  E-mail: </label>
            <input type='email' name='email' id='email' value='$email' maxlength='64' $st_email> $email_err 
        </div>

        <div>

            <label for='clave'> Clave: </label>
            <input type='password' name='clave' id='clave' size='20' maxlength='20' {$st_clave}> <span onClick='changeClave()' id='ver_clave'><img src='./images/ver.png' id='ver_clave_img'></span>{$clave_err} 

            <div class='verifique'>(Verifique no tener activada la tecla \"BLOQ MAYUS\" al ingresar la clave)</div>
        </div>

        <div>

        <label for='recordarme'><input type='checkbox' name='recordarme' id='recordarme' value='S'> Recordarme en este dispositivo </label>
        </div>


        <input class='boton' type='submit' name='ingresar' value='Iniciar sesión' onclick=\"this.value='Aguarde . . .'\" />

   </form>

   <p id='me_olvide'> 
        <a href='me_olvide.php'><img src='./images/el_grito_negro.png' align='middle' /> Me olvidé la clave</a>
    </p>

</div>
$mensaje
";
require(__DIR__ . '/layouts/footer.php');
?>
