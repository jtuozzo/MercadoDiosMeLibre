<?php
/*
    Nombre: me_olvide_vista.php
    Autor: Julio Tuozzo.
    Función: Vista de me olvidé la clave.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 23/05/2025.
*/

$css_local = "me_olvide.css";

require(__DIR__ . '/layouts/header.php');
echo "
<script type='text/javascript' src='./js/me_olvide.js'></script>
<div id='me_olvide'>
    <h1>Me olvidé la clave!</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
        <div>
            <label for='email'>  E-mail: </label>
            <input type='text' name='email' id='email' size='40' maxlength='64' value='$email' $st_email> $email_err 
        </div>
        <p>
        Ingresá tu e-mail. Si se encuentra registrado recibirás un correo con las instrucciones para generar tu nueva clave. <br/>
        Si estás registrado y no la recibís, no olvides mirar en tu correo basura.
        </p>
        <input class='boton' type='submit' name='enviar' value='Enviar nueva clave' onclick=\"this.value='Aguarde . . .'\">
    </form>    
        $mensaje
</div>

";
require(__DIR__ . '/layouts/footer.php');
?>
