<?php
/*
    Nombre: cambiar_clave_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del cambio de clave.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 03/06/2025.
*/

$css_local = "cambiar_clave.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/cambiar_clave.js'></script>

<div id='cambiar_clave'>
    <h1>Cambiar clave</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post'>

        <div>
            <label for='clave'> Clave: </label>
            <input type='password' name='clave' id='clave' size='20' maxlength='20' {$user->st_clave}> <span onClick='changeClave()' id='ver_clave'><img src='./images/ver.png' id='ver_clave_img'></span>{$user->clave_err} 


            <label for='nueva_clave'>Nueva clave: </label>
            <input type='password' name='nueva_clave' id='nueva_clave' size='20' maxlength='20' {$user->st_nueva_clave}> <span onClick='changeNuevaClave()' id='ver_nueva_clave'><img src='./images/ver.png' id='ver_nueva_clave_img'> {$user->nueva_clave_err} 
            <div id='tips' >Debe tener como mínimo 8 dígitos. Pueden ser letras, números o símbolos.</div>

            <label for='reingresa'>Reingresá la nueva clave: </label>
            <input type='password' name='reingresa' id='reingresa' size='20' maxlength='20' {$user->st_reingresa}> {$user->reingresa_err} 


            <div class='verifique'>(Verifique no tener activada la tecla \"BLOQ MAYUS\" al ingresar la clave)</div>
        </div>



        <input class='boton' type='submit' name='cambiar' value='Cambiar clave'/>

   </form>


</div>
$mensaje
";
require_once('foot.inc');
?>
