<?php
/*
    Nombre: confirmar_compra.php
    Autor: Julio Tuozzo.
    Función: Controlador de la confirmación de una compra.
    Fecha de creación: 01/06/2025.
    Ultima modificación: 01/06/2025.
*/






require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\Compra;

foreach($_GET as $clave => $valor)
     {$$clave=trim($valor);
     }

$compra = new Compra();

if(isset($id) and isset($key) and isset($email)) // Llegaron los datos, confirmo la compra
     {if($compra->confirmarCompra($id, $key, $email))
          {// Compra confirmada
           $mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Compra confirmada',
                        text:'Ahora tenés que esperar a que el vendedor te contacte.',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                     .then(function() {
        	                window.location = 'index.php';
                     });
                     </script>";
           
          }
      else
          {// No se pudo confirmar la compra
           $mensaje="<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'Ooops!!',
                    text:'Error en el link de confirmación de compra.',
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
require("head.php");
     echo $mensaje;
require("foot.php");
?>