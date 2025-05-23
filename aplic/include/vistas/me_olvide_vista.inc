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
<div id='me_olvide'>
    <h1>Me olvidé la clave!</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post'>
        <div>
            <label for='email'>  E-mail: </label>
            <input type='email' name='email' id='email' value='$email' size='40' maxlength='64' $st_email> $email_err 
        </div>
        <p>
        Ingrese su e-mail. Si se encuentra registrado recibirá un correo con las instrucciones para generar su nueva clave. <br/>
        Si está registrado y no lo recibe, no olvide de mirar en su correo basura.
        </p>
        <input class='boton' type='submit' name='enviar' value='Enviar nueva clave'/>

</div>
$mensaje
";
require_once('foot.inc');
?>
