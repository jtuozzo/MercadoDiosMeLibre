<?php
/*
    Nombre: articulo_comprador_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo, desde el punto de vista del comprador.
    Fecha de creación: 29/05/2025.
    Ultima modificación: 29/05/2025.
*/

$css_local = "articulo.css";
$precio = number_format((float)$articulo->precio,2,",",".");
$descripcion = nl2br($articulo->descripcion);

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    <div id='encabezado'><h3>{$articulo->titulo}</h3> &nbsp; <h3>{$articulo->moneda} {$precio}</h3></div>
    <p>{$descripcion}</p>";


if(isset($articulo->las_fotos[1]))
        {$img_ppal="<img src='getFoto.php?id={$articulo->las_fotos[1]}&key={$key}' alt='SIN FOTO'  id='fotoPpal'>"; 
        }
else    
        {$img_ppal="<img src='./images/sin_foto.jpg' alt='SIN FOTO'>"; 
        }

echo "<div id='foto_comprador'>
        $img_ppal
      </div>

       <div class='select_foto'>";

        for($i=1; $i<=count($articulo->las_fotos); $i++)
            {if(strlen($articulo->las_fotos[$i])>0)
                    {$articulo_foto_id="articulo_foto_id_{$i}";
                     echo "<img src='getFoto.php?id={$articulo->las_fotos[$i]}&key={$key}' alt='SIN FOTO' onClick=setFotoPpal({$articulo->las_fotos[$i]},'{$key}')>";
                    }
            }

echo "</div>";

echo       "<form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
            <input type='hidden' name='id' value='{$articulo->articulo_id}' />
            <input type='hidden' name='key' value='$key' />
<div class='botonera'>
            <div></div>
            <input class='boton' type='submit' name='comprar' id='comprar' value='Quiero comprarlo' />
            <input type='button' class='boton' value='Cerrar' onClick='window.close()' />
         </div> 

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
