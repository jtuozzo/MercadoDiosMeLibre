<?php
/*
    Nombre: usuario.php
    Autor: Julio Tuozzo.
    Función: Controlador del usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 13/06/2025.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;

$user = new User();

// Defino la vista del usuario como Alta
$user->vista="A";

foreach($_POST as $key => $valor)
     {if(isset($user->$key))
          {$user->$key = trim(htmlentities($valor,ENT_QUOTES,"UTF-8"));
          }
      else
          {$$key=trim(htmlentities($valor,ENT_QUOTES,"UTF-8"));
          }
     }


if(!isset($_POST['crear']))
     {$mensaje="";
      require(__DIR__ . '/../resources/views/usuario_vista.php');
      exit;
     }

if($user->crearUsuario($clave, $reingresa ))
          {// Se pudo crear el usuario
          $mensaje="<div class='creado'>Nuevo usuario creado.<br/> <br/>Verificá tu casilla de correo <em>{$user->email}</em> para terminar el proceso.<br/> <br/>Si no llegó el mail, revisá la casilla de correo basura.</div>
          <script type='text/javascript'>ocultoID('form');</script>";
          }
     else
          {// No se pudo crear el usuario
          if(strlen($user->send_mail_err)>0)
               {$mensaje=Utils::msgError($user->send_mail_err, "Intente más tarde.");
               }
          else 
               {$mensaje=Utils::msgError();
               }
          
          }

require(__DIR__ . '/../resources/views/usuario_vista.php');
?>