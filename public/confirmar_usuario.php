<?php
/*
    Nombre: confirmar_usuario.php
    Autor: Julio Tuozzo.
    Función: Controlador de la confirmación del usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 24/05/2025.
*/






require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;

foreach($_GET as $key => $valor)
     {$$key=trim($valor);
     }

$user = new User();

if(isset($id)) // Hay ID trato de confirmar el usuario
     {if(!$user->confirmarUsuario($id))
          {// No se pudo confirmar el usuario
           $mensaje="<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'Ooops!!',
                    text:'{$user->msg_error}',
                    confirmButtonColor: '#D22518',
                    })
               	  .then(function() {
        	                window.location = 'index.php';
                    });
                 </script>";
          }
      else
          {// Se pudo confirmar el usuario
           $mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Usuario confirmado',
                        text:'El usuario ha sido confirmado correctamente.',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                     .then(function() {
        	                window.location = 'index.php';
                     });
                     </script>";
          }
     }
else // Si no se envió ni el id va a index
     {header("Location: index.php");
      exit();
     }

require(__DIR__ . '/../resources/views/confirmar_usuario_vista.php');
?>