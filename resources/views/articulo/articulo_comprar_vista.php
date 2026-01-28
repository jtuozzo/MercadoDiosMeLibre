<?php
/*
    Nombre: articulo_comprar_vista.php
    Autor: Julio Tuozzo.
    Función: Vista para la compra de un artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 31/05/2025.
*/

$css_local = "comprar.css";
$precio = number_format($compra->precio,2,",",".");
$descripcion = nl2br($compra->descripcion);

require(__DIR__ . '/../layouts/header.php');
echo "
<script type='text/javascript' src='./js/articulo_comprar.js'></script>

<div id='comprar'>
    <a href='articuloGet.php?id={$compra->articulo_id}&key={$key}' title='Volver al artículo' id='titulo'><h2>Vas a solicitar comprar: {$compra->titulo} por {$compra->moneda} {$precio}</h2></a>";

if(isset($compra->las_fotos[1]))
        {$img_ppal="<img src='getFoto.php?id={$compra->las_fotos[1]}&key={$key}' alt='SIN FOTO' />"; 
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
                        <input type='hidden' name='id' value='{$compra->articulo_id}' />
                        <input type='hidden' name='key' value='$key' />
                        <h3>Tus datos para que el vendedor te contacte</h3>";

if(!$compra->registrado)
        {echo "<div>
                    <label for='nombres'>Nombre/s: </label> 
                    <input type='text' name='nombres' id='nombres' value='{$compra->nombres}' size='40' maxlength='64' {$compra->st_nombres} required='required'> {$compra->nombres_err}
               </div>

               <div>
                    <label for='apellidos'>Apellido/s: </label> 
                    <input type='text' name='apellidos' id='apellidos' value='{$compra->apellidos}' size='40' maxlength='64' {$compra->st_apellidos} required='required'> {$compra->apellidos_err}
               </div>

               <div>
                    <label for='email'>  E-mail: </label>
                    <input type='email' name='email' id='email' value='{$compra->email}' size='40' maxlength='64' {$compra->st_email} required='required'> {$compra->email_err} 
              </div>";
        }

echo "         <div>
                    <label for='whatsapp'>  Telefono / Whatsapp: </label>
                    <input type='whatsapp' name='whatsapp' id='whatsapp' value='{$compra->whatsapp}' size='14' maxlength='14' {$compra->st_whatsapp} > {$compra->whatsapp_err} 
              </div>

              <div class='comentarios'>
                        <label for='comentarios' {$compra->st_comentarios}> Comentarios: </label>
                        <textarea name='comentarios' id='comentarios' rows='6' placeholder='Colocá aquí datos adicionales.\nTambién podes hacer preguntas acerca del artículo, ya que esto es una solicitud de compra.\nLa compra la acordás luego directamente con el vendedor.'>{$compra->comentarios}</textarea>{$compra->comentarios_err}
              </div>
                                
           </div>
         </div>

            <input class='boton' type='submit' name='compro' id='compro' value='Comprar' />

            </form>
$mensaje
</div>
";
require(__DIR__ . '/../layouts/footer.php');
?>
