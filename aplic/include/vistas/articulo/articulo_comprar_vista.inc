<?php
/*
    Nombre: articulo_comprar_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista para la compra de un artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 31/05/2025.
*/

$css_local = "comprar.css";
$precio = number_format($articulo->precio,2,",",".");
$descripcion = nl2br($articulo->descripcion);

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo_comprar.js'></script>

<div id='comprar'>
    <h2>Vas a solicitar comprar: {$articulo->titulo} por {$articulo->moneda} {$precio}</h2>";

if(isset($articulo->las_fotos[1]))
        {$img_ppal="<img src='getFoto.php?id={$articulo->las_fotos[1]}&key={$key}' alt='SIN FOTO'  id='fotoPpal'>"; 
        }
else    
        {$img_ppal="<img src='./images/sin_foto.jpg' alt='SIN FOTO'>"; 
        }

echo       "<div class='contenedor'>
                <div class='foto'>
                        $img_ppal
                </div>
                <div class ='formulario'>
                   <form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>
                        <input type='hidden' name='id' value='{$articulo->articulo_id}' />
                        <input type='hidden' name='key' value='$key' />

            </div>
            
            <div class='botonera'>
                <input class='boton' type='submit' name='comprar' id='comprar' value='Comprar' />
            </div> 

   </form>
   
$mensaje
</div>
";
require_once('foot.inc');
?>
