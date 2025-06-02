<?php
/*
    Nombre: articulo_list.inc
    Autor: Julio Tuozzo.
    Función: Vista del listado de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 31/05/2025.
*/

$css_local = "articulo_list.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/articulo_list.js'></script>
$cabecera
<div id='list_articulos'>";

if($result->recordCount()==0)
    {echo "<script type='text/javascript'>sin_articulos()</script>
          <div class='sin'>
                    <img src='./images/estanteria.png' />
                    <h1>Sin artículos a la venta</h1>
          </div>";
    }

while(!$result->EOF)
    {foreach($result->fields as $clave=>$valor)
            {$$clave=$valor; 
            }
     
     $onClick="onCLick=\"window.open('articuloGet.php?id=$articulo_id&key=$token')\"";

     
    if($vendido=="S")
            {$label_vendido="<h2 class='vendido'>VENDIDO</h2>";
             $class_vendido="vendido";
             if(!isset($_SESSION['DML_TOKEN']) or $_SESSION['DML_TOKEN']!==$token)
                {$onClick="";
                }
             else
                {$class_vendido.=" propietario ";
                }
             
            }
      else
            {$label_vendido="";
             $class_vendido="en_venta";
            }

      $precio=number_format($precio,2,",",".");
      echo "<div class='un_articulo $class_vendido' $onClick>
                 $label_vendido
                <img src='getFoto.php?id=$articulo_foto_id&key=$token' alt='$titulo'>

            <div class='titulo'>$titulo</div>
            <div class='precio'>$moneda $precio</div>

            </div>";

     $result->moveNext();
    }

echo "</div>";
echo Utils::paginador($pagina,$q_registros,$orden,$sentido,$id);
require('foot.inc');
?>
