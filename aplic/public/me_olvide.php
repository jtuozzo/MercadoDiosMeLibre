<?php
/*
    Nombre: me_olvide.php
    Autor: Julio Tuozzo.
    Función: Controlador que envía el mail para que se resetee una clave.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 23/05/2025.
*/

require("Utils.inc");
require("User.inc");

// Si no se envió el formulario, lo muestro

if(!isset($_POST['enviar']))
     {require("me_olvide_vista.inc");
      exit;
     }

// Guardo los datos posteados en variables
foreach($_POST as $key => $valor)
     {$$key=trim($valor);
     }

// Valido el email
if(strlen($email)==0)
     {$st_email="class='st_error'";
      $email_err="<br/><span class='error'>Ingrese e-mail</span>";
     }
else
     {// Valido el formato del email
      if(!filter_var($email, FILTER_VALIDATE_EMAIL))
         {$st_email="class='st_error'";
          $email_err="<br/><span class='error'>Formato de e-mail incorrecto</span>";
         }
     }

if(strlen($email_err)>0)
     {require("me_olvide_vista.inc");
      exit;
     }

$user = new User();

$mensaje="<script type='text/javascript'>ocultoForm();</script>";

if($user->nuevaClave($email))
     {// Se pudo cambiar la clave y enviar la clave, o el mail no está registrado.
      $mensaje.="<div class='mensaje bien'>Se envió un mail a <em>$email</em> con la nueva clave.</div>";
     }
else
     {// No se pudo eviar la clave, aviso que pruebe en un rato.
      $mensaje.="<div class='mensaje mal'>No se pudo cambiar la clave, intente más tarde.</div>";
     }
require("me_olvide_vista.inc");

?>