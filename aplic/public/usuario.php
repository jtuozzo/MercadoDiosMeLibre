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
     {$$key=trim($valor);
     }

$user = new User();

if(!isset($_POST['crear']))
     {require("usuario_vista.inc");
      exit;
     }

if($user->crearUsuario($email, $clave, $nombres, $apellidos))
     {// Se pudo crear el usuario
      $mensaje="<div class='creado'>Nuevo usuario creado. Verificá tu casilla de correo para terminar el proceso. <br />Si no llegó el mail, revisá la casilla de correo basura.</div>";
     }
else
     {// No se pudo crear el usuario
      $mensaje=Utils::msgError();
     }
require("usuario_vista.inc");
?>