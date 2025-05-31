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
    <a href='articuloGet.php?id={$articulo->articulo_id}&key={$key}' title='Volver al artículo'><h2>Vas a solicitar comprar: {$articulo->titulo} por {$articulo->moneda} {$precio}</h2></a>";

if(isset($articulo->las_fotos[1]))
        {$img_ppal="<img src='getFoto.php?id={$articulo->las_fotos[1]}&key={$key}' alt='SIN FOTO' />"; 
        }
else    
        {$img_ppal="<img src='./images/sin_foto.jpg' alt='SIN FOTO'>"; 
        }

echo       "<form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

            <div class='contenedor'>
                <div class='foto'>
                        $img_ppal
                </div>
                <div class ='formulario'>
                        <input type='hidden' name='id' value='{$articulo->articulo_id}' />
                        <input type='hidden' name='key' value='$key' />";

if(!$comprador->registrado)
        {echo "<h3>Tus datos para que el vendedor te contacte</h3>
                <div>
                    <label for='nombres'>Nombre/s: </label> 
                    <input type='text' name='nombres' id='nombres' value='{$comprador->nombres}' size='40' maxlength='64' {$comprador->st_nombres} required='required'> {$comprador->nombres_err}
               </div>

               <div>
                    <label for='apellidos'>Apellido/s: </label> 
                    <input type='text' name='apellidos' id='apellidos' value='{$comprador->apellidos}' size='40' maxlength='64' {$comprador->st_apellidos} required='required'> {$comprador->apellidos_err}
               </div>

               <div>
                    <label for='email'>  E-mail: </label>
                    <input type='email' name='email' id='email' value='{$comprador->email}' size='40' maxlength='64' {$comprador->st_email} required='required'> {$comprador->email_err} 
              </div>

              <div>
                    <label for='whatsapp'>  Whatsapp: </label>
                    <input type='whatsapp' name='whatsapp' id='whatsapp' value='{$comprador->whatsapp}' size='14' maxlength='14' {$comprador->st_whatsapp} > {$comprador->whatsapp_err} 
              </div>

              <div class='comentarios'>
                        <label for='comentarios'> Comentarios: </label>
                        <textarea name='comentarios' id='comentarios' rows='5'  required='required'>{$comprador->comentarios}</textarea>
              </div>";

        }

echo "                        
                        
                </div>
            </div>

            <input class='boton' type='submit' name='compro' id='compro' value='Comprar' />

            </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
