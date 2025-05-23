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

$user = new User();

if($user->setClave($email))
     {// Se pudo cambiar la clave y enviar la clave, o el mail no está registrado.
      $mensaje="Si el e-mail está registrado, se envió un mail a $email con la nueva clave.";
     }
else
     {// No se pudo eviar la clave, aviso que pruebe en un rato.
      $mensaje=Utils::msgError("No se pudo cambiar la clave, intente más tarde.");
     }
     
?>