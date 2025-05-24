<?php
/*
    Nombre: usuario_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del nuevo usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 24/05/2025.
*/

$css_local = "usuario.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/usuario.js'></script>

<div id='usuario'>
    <h1>Crear usuario</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

        <div>
            <label for='nombres'>  Nombre/s: </label>
            <input type='text' name='nombres' id='nombres' value='$nombres' size='40' maxlength='64' {$user->st_nombres}> {$user->nombres_err} 
        </div>

        <div>
            <label for='apellidos'>  Apellido/s: </label>
            <input type='text' name='apellidos' id='apellidos' value='$apellidos' size='40' maxlength='64' {$user->st_apellidos}> {$user->apellidos_err} 
        </div>

        <div>
            <label for='email'>  E-mail: </label>
            <input type='text' name='email' id='email' value='$email' size='40' maxlength='64' {$user->st_email}> {$user->email_err} 
        </div>

        <div>
            <label for='clave'> Clave: </label>
            <input type='password' name='clave' id='clave' size='20' maxlength='20' {$user->st_clave}> {$user->clave_err} 
            <div id='tips' >Debe tener como mínimo 8 dígitos. Pueden ser letras, números o símbolos.</div>
            <div class='verifique'>(Verifique no tener activada la tecla \"BLOQ MAYUS\" al ingresar la clave)</div>
        </div>

        <div>
            <label for='reingresa'> Reingresá la clave: </label>
            <input type='password' name='reingresa' id='reingresa' size='20' maxlength='20' {$user->st_reingresa}> {$user->reingresa_err} 
        </div>

        <input class='boton' type='submit' name='crear' value='Crear usuario' onClick=\"this.value='Aguarde . . .'\"/>

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
