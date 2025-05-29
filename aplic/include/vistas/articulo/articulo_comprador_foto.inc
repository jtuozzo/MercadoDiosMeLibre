<?php
/*
    Nombre: articulo_comprador_foto.inc
    Autor: Julio Tuozzo.
    Función: Vista de las fotos de un artículo, desde el punto de vista del comprador.
    Fecha de creación: 29/05/2025.
    Ultima modificación: 29/05/2025.
*/


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
                     echo "<img src='getFoto.php?id={$articulo->las_fotos[$i]}&key={$key}' alt='SIN FOTO' onClick=setFotoPpal({$articulo->las_fotos[$i]},{$key})>";
                    }
            }

echo "</div>";
?>
