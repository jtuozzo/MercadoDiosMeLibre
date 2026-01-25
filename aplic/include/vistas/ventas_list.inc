<?php
/*
    Nombre: ventas_list.inc
    Autor: Julio Tuozzo.
    Función: Vista del listado de artículos vendidos.
    Fecha de creación: 02/06/2025.
    Ultima modificación: 25/01/2026.
*/

$css_local = "ventas_list.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/ventas_list.js'></script>
<div class='encabezado'>
    <h2 class='encabezado_h2'>Mis posibles Ventas</h2>
    <h2>Quieren comprarlo</h2>
</div>
<div id='list_ventas'>";

if($result->recordCount()==0)
    {echo "<div class='sin'>
                    <img src='./images/estanteria.png' />
                    <h1>Sin artículos vendidos</h1>
          </div>
          <script type='text/javascript'>ocultarEncabezado()</script>";
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

             $fecha = substr(Utils::fecha_format($insert_datetime),0,-3);       
             if(empty($confirmado))
                  {$confirmado_class="no_confirmado";
                   $confirmado_label="<div><strong>(Sin confirmar)</strong></div>";
                  }
             else
                  {$confirmado_class=$confirmado_label="";
                  }

             echo "<div class='renglon_comprador'>
                    <div class='elimina_comprador' onClick=\"compraDelete($articulo_compra_id, '{$compradores->fields['nombres']}', '{$compradores->fields['apellidos']}')\"><img src='./images/eliminar_36.png'/></div>  
                    <div class = 'un_comprador $confirmado_class'>
                            $confirmado_label
                            <div><strong>$fecha</strong></div> 
                            <div>$nombres $apellidos</div> 
                            <div>$email</div> 
                            <div>$whatsapp</div> 
                            <div>$comentarios</div>
                    </div>
                  
                  </div>
                  ";
             $compradores->moveNext();
            }
                       
echo                    "</div>
            </div>";

     $result->moveNext();
    }

echo "</div>";
echo Utils::paginador($pagina,$q_registros,$el_orden,$sentido,0);
require('foot.inc');
?>
