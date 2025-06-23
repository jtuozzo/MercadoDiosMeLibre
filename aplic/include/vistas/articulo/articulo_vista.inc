<?php
/*
    Nombre: articulo_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 23/06/2025.
*/

$css_local = "articulo.css";

// Partes variables del formulario en función de la vista

switch ($articulo->vista)
    {case "A": // Alta
        $encabezado = "<h1>Crear Articulo</h1>";
        $guardar="<input class='boton' type='submit' name='crear' id='crear' value='Crear artículo' />";
        $cerrar="<div></div>";
        break;
     case "M": // Modifica
        $link=$_SERVER['REQUEST_SCHEME']."://".$_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']."?id={$articulo->articulo_id}&key=".$_SESSION['DML_TOKEN'];
        $encabezado = "<h1>Modificar Articulo</h1>
                <div class='link' onClick=copyClipp('{$link}')><img src='./images/copy.png' />  Copiar link del artículo</div>";

                $cerrar="<input type='button' class='boton' value='Cerrar' onClick='window.close()' />";
        $guardar="<input class='boton' type='submit' name='modificar' id='crear' value='Guardar' />";
        break;
    }


require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    $encabezado
    <form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
        <input type='hidden' name='articulo_id' value='{$articulo->articulo_id}'/>
        <input type='hidden' name='user_id' value='{$articulo->user_id}'/>
        <input type='hidden' name='key' value='$key'/>

        <div class='linea_1'>
            <div>
                <label for='titulo'>  Título: </label>
                <input type='text' name='titulo' id='titulo' value='{$articulo->titulo}' size='40' maxlength='64' {$articulo->st_titulo} required='required'> {$articulo->titulo_err} 
            </div>

            <div>
                <label for='precio'>  Precio: </label>

                <select name='moneda' id='moneda' >";

                foreach (Utils::$moneda as $clave => $value) 
                    {$selected = ($articulo->moneda == $clave) ? "selected='selected'" : "";
                     echo "<option value='{$clave}' {$selected}>{$value}</option>";
                    }
echo "          </select> 

                <input type='number' name='precio' id='precio' value='{$articulo->precio}' size='10' maxlength='16' {$articulo->st_precio} required='required'> {$articulo->precio_err}
            </div>
            <div>
                <label for='vendido' class='checks'><input type='checkbox' name='vendido' id='vendido' value='S' {$articulo->chk_vendido} /> Vendido </label>
            </div>
            <div>
                <label for='oculto' class='checks'><input type='checkbox' name='oculto' id='oculto' value='S' {$articulo->chk_oculto} /> Oculto </label>
            </div>
            <div>
                <label for='orden'>Orden: </label>
                <input type='number' name='orden' id='orden' value='{$articulo->orden}' size='3' maxlength='3' {$articulo->st_orden} /> {$articulo->orden_err} 
                <br/><em>Indica en que orden aparecen los artículos en el listado.</em>
            </div>
        </div>   
        
        <div class='linea_2'>
            <label for='descripcion'> Descripción: </label>
            <textarea name='descripcion' id='descripcion' rows='5'  {$articulo->st_descripcion} required='required'>{$articulo->descripcion}</textarea> {$articulo->descripcion_err}
        </div>";

require("articulo_foto_vista.inc");

echo       " <div class='botonera'>
            <div></div>
            {$guardar}
            {$cerrar}
         </div> 

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
