<?php
/*
    Nombre: confirmar_compra.php
    Autor: Julio Tuozzo.
    Función: Controlador de la confirmación de una compra.
    Fecha de creación: 01/06/2025.
    Ultima modificación: 01/06/2025.
*/

require("Utils.inc");
require("Articulo.inc");


foreach($_GET as $key => $valor)
     {$$key=trim($valor);
     }

$compra = new Compra();

if(isset($id) and isset($key) and isset($email)) // Llegaron los datos, confirmo la compra
     {if($compra->confirmarCompra($id, $key, $email))
          {// Compra confirmada
           $mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Compra confirmada',
                        text:'Hemos enviado un e-mail a $email para que puedas hacer el seguimiento.',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                     .then(function() {
        	                window.location = 'index.php';
                     });
                     </script>";
           
          }
      else
          {// Se pudo confirmar la compra
           $mensaje="<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'Ooops!!',
                    text:'Error en el link de confirmación de compra',
                    confirmButtonColor: '#D22518',
                    })
               	  .then(function() {
        	                window.location = 'index.php';
                    });
                 </script>";
          }
     }
else // Si no se enviaron los parámetros va al index
     {header("Location: index.php");
      exit();
     }

require("articulo_comprar_vista.inc");
?>