<?php
/*
    Nombre: articulo_foto_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de las fotos de un artículo.
    Fecha de creación: 28/05/2025.
    Ultima modificación: 28/05/2025.
*/

$ppal = "<div class='ppal_side'>Foto principal</div>";

echo "<div id='foto'>
        <div class='hay_fotos'>";

        for($i=1; $i<=count($articulo->las_fotos); $i++)
            {$articulo_foto_id="articulo_foto_id_{$i}";
             echo "<div id='id_foto_$i' class='hay_foto'>
                        <input type='hidden' name='{$articulo_foto_id}' value={$articulo->las_fotos[$i]} />
                        <input class='del_foto' type='button' onclick='delHayFoto($i)' title='Elimina foto'> <img src='getFoto.php?id={$articulo->las_fotos[$i]} alt='SIN FOTO'> 
                  $ppal </div> ";
             $ppal="";
            }
        echo "</div>
        <label>
            <input id='nueva_foto' type='button' onclick='addFoto(".MAX_FOTOS.")' title='Agregar fotos'>
            <strong>Fotos</strong> 
            <span class='nota'> (Máximo ".MAX_FOTOS." fotos) </span>
        </label>
";
        for($i = $i; $i <= MAX_FOTOS; $i++)
            {$foto = "foto_$i";
             $foto_err = "foto_err_{$i}";
             $st_foto = "st_foto_$i";
            
             echo "<div id='id_foto_$i' class='foto'>
                        <input class='del_foto' type='button' onclick='delFoto($i)' title='Elimina foto'> <input type='file' name='$foto' id='$foto' accept='image/*' {$articulo->$st_foto}> {$articulo->$foto_err}
                  $ppal </div> ";

             $ppal="";
            }
    echo "</div>";

?>
