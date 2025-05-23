<?php
/*
    Nombre: me_olvide_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de me olvidé la clave.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 23/05/2025.
*/

$css_local = "me_olvide.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/me_olvide.js'></script>
<div id='me_olvide'>
    <h1>Me olvidé la clave!</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
        <div>
            <label for='email'>  E-mail: </label>
            <input type='email' name='email' id='email' size='40' maxlength='64' $st_email> $email_err 
        </div>
        <p>
        Ingrese su e-mail. Si se encuentra registrado recibirá un correo con las instrucciones para generar su nueva clave. <br/>
        Si está registrado y no lo recibe, no olvide de mirar en su correo basura.
        </p>
        <input class='boton' type='submit' name='enviar' value='Enviar nueva clave' onclick=\"this.value='Aguarde . . .'\">
    </form>    
        $mensaje
</div>

";
require_once('foot.inc');
?>
