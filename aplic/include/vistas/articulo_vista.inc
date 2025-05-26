<?php
/*
    Nombre: articulo_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 26/05/2025.
*/

$css_local = "articulo.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    <h1>Crear Articulo</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

        <div>
            <label for='titulo'>  Título: </label>
            <input type='text' name='titulo' id='titulo' value='$titulo' size='40' maxlength='64' {$user->st_titulo}> {$user->titulo_err} 
        </div>

        <div>
            <label for='precio'>  Precio: </label>

            <select name='moneda' id='moneda' {$user->st_moneda}>
                <option value='ARS' {$user->sel_ARS}>ARS - Pesos</option>
                <option value='USD' {$user->sel_USD}>USD - Dólares</option>
            </select> {$user->moneda_err}

            <input type='text' name='precio' id='precio' value='$precio' size='10' maxlength='16' {$user->st_precio}> {$user->precio_err}
        </div>

        <div>
            <label for='clave'> Descripción: </label>
            <textarea name='descripcion' id='descripcion' rows='5'  {$user->st_descripcion}>$descripcion</textarea> {$user->descripcion_err}
        </div>

        <div>
            
        </div>

        <input class='boton' type='submit' name='crear' value='Crear artículo' onClick=\"this.value='Aguarde . . .'\"/>

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
