<?php
/*
    Nombre: articulo_list.inc
    Autor: Julio Tuozzo.
    Función: Vista del listado de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 27/05/2025.
*/

$css_local = "articulo_list.css";

require_once('head.inc');
echo "
<div id='list_articulos'>";

while(!$result->EOF)
    {foreach($result->fields as $clave=>$valor)
            {$$clave=$valor; 
            }

      $precio=number_format($precio,2,",",".");
      echo "<a href='getArticulo.php?id=$articulo_id' class='un_articulo'>
                <img src='getFoto.php?id=$articulo_foto_id' alt='$titulo'>

            <div class='titulo'>$titulo</div>
            <div class='precio'>$moneda $precio</div>

            </a>";

     $result->moveNext();
    }

echo "</div>";
require_once('foot.inc');
?>
