<?php
/*
    Nombre: ventas_list.inc
    Autor: Julio Tuozzo.
    Función: Vista del listado de artículos vendidos.
    Fecha de creación: 02/06/2025.
    Ultima modificación: 02/06/2025.
*/

$css_local = "ventas_list.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/ventas_list.js'></script>
<h2>Mis Ventas</h2>
<div id='list_ventas'>";

if($result->recordCount()==0)
    {echo "<div class='sin'>
                    <img src='./images/estanteria.png' />
                    <h1>Sin artículos vendidos</h1>
          </div>";
    }

while(!$result->EOF)
    {foreach($result->fields as $clave=>$valor)
            {$$clave=nl2br(htmlentities($valor,ENT_QUOTES,'UTF-8'));
            }
     
    if($vendido=="S")
            {$label_vendido="<h2 class='vendido'>VENDIDO</h2>";
             $class_vendido="vendido";
            }
      else
            {$label_vendido="";
             $class_vendido="en_venta";
            }

      $precio=number_format($precio,2,",",".");
      echo "<div class='renglon'>
                    <div class='articulo $class_vendido' onCLick=\"window.open('articuloGet.php?id=$articulo_id&key={$_SESSION['DML_TOKEN']}')\">
                        $label_vendido
                        <img src='getFoto.php?id=$articulo_foto_id&key={$_SESSION['DML_TOKEN']}' alt='$titulo'>

                    <div class='titulo'>$titulo</div>
                    <div class='precio'>$moneda $precio</div>
                    </div>
                    <div class='comprador'>";
       $compradores = $ventas->getCompradores($articulo_id);

       while(!$compradores->EOF)
            {foreach($compradores->fields as $clave=>$valor)
                    {$$clave=nl2br(htmlentities($valor,ENT_QUOTES,'UTF-8'));
                    }
             echo "<div>$nombres $apellidos $email $whatsapp $comentarios</div>";
             $compradores->moveNext();
            }
                       
echo                    "</div>
            </div>";

     $result->moveNext();
    }

echo "</div>";
echo Utils::paginador($pagina,$q_registros,$orden,$sentido,0);
require('foot.inc');
?>
