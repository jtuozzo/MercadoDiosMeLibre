<?php
/*
    Nombre: articulo_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de un artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 28/05/2025.
*/

$css_local = "articulo.css";

// Partes variables del formulario en función de la vista

switch ($articulo->vista)
    {case "A": // Alta
        $encabezado = "<h1>Crear Articulo</h1>";
        break;
     case "M": // Modifica
        $encabezado = "<h1>Modificar Articulo</h1>";
        break;
     case "C": // Consulta y compra
        $encabezado = "<h2>{$articulo->titulo}</h2>";
    }


require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo.js'></script>

<div id='articulo'>
    $encabezado
    <form enctype='multipart/form-data' action='{$_SERVER['PHP_SELF']}' method='post' id='form'>

        <div class='linea_1'>
            <div>
                <label for='titulo'>  Título: </label>
                <input type='text' name='titulo' id='titulo' value='{$articulo->titulo}' size='40' maxlength='64' {$articulo->st_titulo} required='required'> {$articulo->titulo_err} 
            </div>

            <div>
                <label for='precio'>  Precio: </label>

                <select name='moneda' id='moneda' >
                    <option value='ARS' {$articulo->sel_ARS}>ARS - Pesos</option>
                    <option value='USD' {$articulo->sel_USD}>USD - Dólares</option>
                </select> 

                <input type='text' name='precio' id='precio' value='{$articulo->precio}' size='10' maxlength='16' {$articulo->st_precio} required='required'> {$articulo->precio_err}
            </div>
        </div>   
        
        <div class='linea_2'>
            <label for='descripcion'> Descripción: </label>
            <textarea name='descripcion' id='descripcion' rows='5'  {$articulo->st_descripcion} required='required'>{$articulo->descripcion}</textarea> {$articulo->descripcion_err}
        </div>

        <div id='foto'>
        <label>
            <input id='nueva_foto' type='button' onclick='addFoto(".MAX_FOTOS.")' title='Agregar fotos'>
            <strong>Fotos</strong> 
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

echo "<input class='del_foto' type='button' onclick='delFoto($i)' title='Elimina foto'> <input type='file' name='$foto' id='$foto' accept='image/*' {$articulo->$st_foto}> {$articulo->$foto_err}
                  $ppal </div> ";
            }
    echo "</div>
          <input class='boton' type='submit' name='crear' id='crear' value='Crear artículo' />

   </form>
$mensaje
</div>
";
require_once('foot.inc');
?>
