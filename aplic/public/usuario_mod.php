<?php
/*
    Nombre: usuario_mod.php
    Autor: Julio Tuozzo.
    Función: Controlador de modificación de datos de usuario.
    Fecha de creación: 13/06/2025.
    Ultima modificación: 13/06/2025.
*/

session_start();

require("Utils.inc");
require("User.inc");

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
      require("usuario_vista.inc");
      exit;
     }

if($user->modifUsuario($clave))
          {// Se pudo modificar el usuario
          $mensaje="<div class='creado'>Nuevo usuario creado.<br/> <br/>Verificá tu casilla de correo <em>{$user->email}</em> para terminar el proceso.<br/> <br/>Si no llegó el mail, revisá la casilla de correo basura.</div>
          <script type='text/javascript'>ocultoID('form');</script>";
          }
     else
          {// No se pudo modificar el usuario
           $mensaje=Utils::msgError();
          }
          
require("usuario_vista.inc");
?>