<?php
/*
    Nombre: articulo_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 26/05/2025.
*/

$css_local = "articulo.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    <h1>Crear Articulo</h1>
      
    <form action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

        <div class='linea_1'>
            <div>
                <label for='titulo'>  Título: </label>
                <input type='text' name='titulo' id='titulo' value='$titulo' size='40' maxlength='64' {$articulo->st_titulo}> {$articulo->titulo_err} 
            </div>

            <div>
                <label for='precio'>  Precio: </label>

                <select name='moneda' id='moneda' >
                    <option value='ARS' {$articulo->sel_ARS}>ARS - Pesos</option>
                    <option value='USD' {$articulo->sel_USD}>USD - Dólares</option>
                </select> 

                <input type='text' name='precio' id='precio' value='$precio' size='10' maxlength='16' {$articulo->st_precio}> {$articulo->precio_err}
            </div>
        </div>   
        
        <div class='linea_2'>
            <label for='descripcion'> Descripción: </label>
            <textarea name='descripcion' id='descripcion' rows='5'  {$articulo->st_descripcion}>$descripcion</textarea> {$articulo->descripcion_err}
        </div>

        <div id='foto'>
        <label>
            <strong>Fotos</strong> 
            <input id='nueva_foto' type='button' onclick='addFoto(".MAX_FOTOS.")' title='Agregar fotos'>
            <span class='nota'> (Máximo ".MAX_FOTOS." fotos) </span>
        </label>";

        for($i = 1; $i <= MAX_FOTOS; $i++)
            {$foto = "foto_$i";
             $foto_err = "foto_err_{$i}";
             $st_foto = "st_foto_$i";
            
             echo "<div id='id_foto_$i' class='foto'>";

                if($i==1)
                    {$ppal = "<div class='ppal_side'><strong >Foto principal</strong></div>";
                    }

                else
                    {$ppal = "";
                    }

echo "    $ppal_title
      <input class='del_foto' type='button' onclick='delFoto($i)' title='Elimina foto'> <input type='file' name='$foto' id='$foto' accept='image/*' {$articulo->$st_foto}> {$articulo->$foto_err}
                  $ppal </div> ";
            }
    echo "</div>
          <input class='boton' type='submit' name='crear' value='Crear artículo' onClick=\"this.value='Aguarde . . .'\"/>

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
