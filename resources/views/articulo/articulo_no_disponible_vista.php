<?php
/*
    Nombre: articulo_no_disponible_vista.php
    Autor: Julio Tuozzo.
    Función: Vista de un artículo que ya no está a la venta.
    Fecha de creación: 25/01/2026.
    Ultima modificación: 28/01/2026.
*/

$css_local = "articulo.css";
$precio = number_format((float)$articulo->precio,2,",",".");
$descripcion = nl2br($articulo->descripcion);

require(__DIR__ . '/../layouts/header.php');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    <div id='encabezado'><h3>{$articulo->titulo}</h3> <div class='no_disponible'>UPSSS!! Ya no está disponible!!</div> </div>
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
      
<div class='botonera'>
            <div></div>
            <div></div>
            <input type='button' class='boton' value='Inicio' id='salir' onClick='cierroArticulo()' />
</div> 

$mensaje
</div>
";
require(__DIR__ . '/../layouts/footer.php');
?>
