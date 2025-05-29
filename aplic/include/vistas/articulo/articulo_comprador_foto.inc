<?php
/*
    Nombre: articulo_comprador_foto.inc
    Autor: Julio Tuozzo.
    Función: Vista de las fotos de un artículo, desde el punto de vista del comprador.
    Fecha de creación: 29/05/2025.
    Ultima modificación: 29/05/2025.
*/


if(isset($articulo->las_fotos[1]))
        {$img_ppal="<img src='getFoto.php?id={$articulo->las_fotos[1]}' alt='SIN FOTO'>"; 
        }
else    
        {$img_ppal="<img src='./images/sin_foto.jpgos[$1]} alt='SIN FOTO'>"; 
        }

echo "<div id='foto'>
        $img_ppal
      </div>



        <div id='hay_fotos'>";

        for($i=1; $i<=count($articulo->las_fotos); $i++)
            {if(strlen($articulo->las_fotos[$i])>0)
                    {$articulo_foto_id="articulo_foto_id_{$i}";
                    echo "<div id='id_articulo_foto_$i' class='hay_una_foto'>
                                <input type='hidden' name='{$articulo_foto_id}' id='{$articulo_foto_id}' value='{$articulo->las_fotos[$i]}' />
                                <input class='del_foto' type='button' onclick='delHayFoto($i)' title='Elimina foto'> <img src='getFoto.php?id={$articulo->las_fotos[$i]} alt='SIN FOTO'> 
                        </div> ";
                    $ppal="";
                    }
            }

        if ($i>MAX_FOTOS)
            {$style="style='display:none'";
            }
        else 
            {$style="";
            }

        echo "</div>
        <label>
            <input id='nueva_foto' type='button' onclick='addFoto(".MAX_FOTOS.")' title='Agregar fotos' $style>
            <strong>Fotos</strong> 
            <span class='nota'> (Máximo ".MAX_FOTOS." fotos) </span>
        </label>";
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
