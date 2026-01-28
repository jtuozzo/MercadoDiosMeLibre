<?php
/*
    Nombre: usuario_mod.php
    Autor: Julio Tuozzo.
    Función: Controlador de modificación de datos de usuario.
    Fecha de creación: 13/06/2025.
    Ultima modificación: 13/06/2025.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;

$user = new User();

if(!$user->getUser($_SESSION['DML_EMAIL'],$_SESSION['DML_CLAVE']))
     {header("Location: login.php");
      exit;
     }

// Defino la vista del usuario como Modificación
$user->vista="M";

foreach($_POST as $key => $valor)
     {if(isset($user->$key))
          {$user->$key = trim(htmlentities($valor,ENT_QUOTES,"UTF-8"));
          }
      else
          {$$key=trim(htmlentities($valor,ENT_QUOTES,"UTF-8"));
          }
     }

if(!isset($_POST['guardar']))
     {$mensaje="";
      require(__DIR__ . '/../resources/views/usuario_vista.php');
      exit;
     }

if($user->modifUsuario($clave))
          {// Se pudo modificar el usuario
          $mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Usuario modificado',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                       .then(function() {
        	                window.location='index.php';
                    });
                     </script>";
          }
     else
          {// No se pudo modificar el usuario
           $mensaje=Utils::msgError();
          }
          
require(__DIR__ . '/../resources/views/usuario_vista.php');
?>