<?php
/*
    Nombre: articulo_comprador.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo, desde el punto de vista del comprador.
    Fecha de creación: 29/05/2025.
    Ultima modificación: 29/05/2025.
*/

$css_local = "articulo.css";
$precio = number_format($articulo->precio,2,",",".");
$descripcion = nl2br($articulo->descripcion);

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    <div id='encabezado'><h3>{$articulo->titulo}</h3> &nbsp; <h3>{$articulo->moneda} {$precio}</h3></div>
    <p>{$descripcion}</p>";

require("articulo_comprador_foto.inc");

echo       "<form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
<div class='botonera'>
            <div></div>
            <input class='boton' type='submit' name='comprar' id='comprar' value='Comprar artículo' />
            <input type='button' class='boton' value='Cerrar' onClick='window.close()' />
         </div> 

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
