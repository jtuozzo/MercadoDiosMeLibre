<?php
/*
    Nombre: usuario_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del nuevo usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 13/06/2025.
*/

$css_local = "usuario.css";

switch ($user->vista) {
    case "A":
        $titulo="Crear usuario";
        $email = "<div>
                     <label for='email'>  E-mail: </label>
                     <input type='text'  class='usuario' name='email' id='email' value='{$user->email}'  maxlength='64' {$user->st_email}> {$user->email_err} 
                  </div>";
        $sub_tips="Debe tener como mínimo 8 dígitos. Pueden ser letras, números o símbolos.";
        $top_tips="";
        $reingresa = " <div>
            <label for='reingresa'> Reingresá la clave: </label>
            <input type='password' name='reingresa' id='reingresa' size='20' maxlength='20' {$user->st_reingresa}> {$user->reingresa_err} 
        </div>";

        $boton = "<input class='boton' type='submit' name='crear' value='Crear usuario' onClick=\"this.value='Aguarde . . .'\"/>";
        break;
    case "M":
        $titulo="Mis perfil";
        $top_tips="Debe ingresar su clave para modificar los datos del perfil.";
        $email ="";
        $sub_tips="";
        $reingresa = "<p id='cambiar_clave'> 
                        <a href='cambiar_clave.php'><img src='./images/llave.png' align='middle' /> Cambiar la clave </a>
                      </p>";
        $boton = "<input class='boton' type='submit' name='guardar' value='Modificar datos' onClick=\"this.value='Aguarde . . .'\"/>";

}

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/usuario.js'></script>

<div id='usuario'>
    <h1>$titulo</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

        <div>
            <label for='nombres'>  Nombre/s: </label>
            <input class='usuario' type='text' name='nombres' id='nombres' value='{$user->nombres}'  maxlength='64' {$user->st_nombres}> {$user->nombres_err} 
        </div>

        <div>
            <label for='apellidos'>  Apellido/s: </label>
            <input type='text'  class='usuario' name='apellidos' id='apellidos' value='{$user->apellidos}'  maxlength='64' {$user->st_apellidos}> {$user->apellidos_err} 
        </div>

        $email

        <div>
            <div class='tips top_tips'>$top_tips</div>    
            <label for='clave'> Clave: </label>
            <input type='password' name='clave' id='clave' size='20' maxlength='20' {$user->st_clave}> <span onClick='changeClave()' id='ver_clave'><img src='./images/ver.png' id='ver_clave_img'></span>{$user->clave_err} 
            <div class='tips'>$sub_tips</div>
            <div class='verifique'>(Verifique no tener activada la tecla \"BLOQ MAYUS\" al ingresar la clave)</div>
        </div>

        $reingresa

        $boton

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
