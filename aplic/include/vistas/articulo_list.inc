<?php
/*
    Nombre: articulo_list.inc
    Autor: Julio Tuozzo.
    Función: Vista del listado de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 27/05/2025.
*/

$css_local = "articulo.css";

require_once('head.inc');
echo "
<div id='list_articulos'>";

while(!$result->EOF)
    {foreach($result->fields as $clave=>$valor)
            {$$clave=$valor; 
            }

      echo "<div class='un_articulo'>
                <img src='getFoto.php?id=$articulo_foto_id' alt='$titulo'>
        </div>";

     $result->moveNext();
    }

echo "</div>";
require_once('foot.inc');
?>
