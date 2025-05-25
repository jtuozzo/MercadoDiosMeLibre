<?php
/*
    Nombre: usuario.php
    Autor: Julio Tuozzo.
    Función: Controlador del usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 24/05/2025.
*/

require("Utils.inc");
require("User.inc");

foreach($_POST as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,"UTF-8"));
     }

$user = new User();

if(!isset($_POST['crear']))
     {require("usuario_vista.inc");
      exit;
     }

if($user->crearUsuario($nombres, $apellidos, $email, $clave, $reingresa ))
     {// Se pudo crear el usuario
      $mensaje="<div class='creado'>Nuevo usuario creado.<br/> Verificá tu casilla la correo de <em>$email</em> para terminar el proceso.<br/> <br/>Si no llegó el mail, revisá la casilla de correo basura.</div>
      <script type='text/javascript'>ocultoForm();</script>";
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
require("usuario_vista.inc");
?>