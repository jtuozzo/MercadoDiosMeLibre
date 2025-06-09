<?php
/*
    Nombre: usuario.php
    Autor: Julio Tuozzo.
    Función: Controlador del usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 08/06/2025.
*/

session_start();

require("Utils.inc");
require("User.inc");

$user = new User();


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
      require("usuario_vista.inc");
      exit;
     }

if(!isset($_SESSION['DML_USER_ID']))
     {// No hay usuario sesionado, es un nuevo usuario
     if($user->crearUsuario($clave, $reingresa ))
          {// Se pudo crear el usuario
          $mensaje="<div class='creado'>Nuevo usuario creado.<br/> Verificá tu casilla la correo de <em>$email</em> para terminar el proceso.<br/> <br/>Si no llegó el mail, revisá la casilla de correo basura.</div>
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

     }
elseif(!isset($_SESSION['DML_USER_PASS']))
     {// Está sesionado, vuelvo a validar la password

      $mensaje="";
      

     }
else 
     {// Hay usuario sesionado y validado, proceso la modificación modificación
      if($user->modifUsuario($clave, $reingresa))
          {$mensaje = "TODO OK";
           unset($_SESSION['DML_USER_PASS']);
          }
      else
          {$mensaje=Utils::msgError();
          }

     }

require("usuario_vista.inc");
?>