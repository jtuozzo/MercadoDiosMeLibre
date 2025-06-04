<?php
/*
    Nombre: seguir.php
    Autor: Julio Tuozzo.
    Función: Controlador de seguimiento de publicaciones de otro usuario.
    Fecha de creación: 04/06/2025.
    Ultima modificación: 04/06/2025.
*/

session_start();

require("Utils.inc");
require("User.inc");

// Veo si hay token y si es válido

foreach($_GET as $clave => $valor)
     {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$usuario = new User;
$token = $id;

if(!isset($id) or !$usuario->tokenValido($token))
     {// El token no vino o no es válido
      header("Location: index.php");
      exit;
     }        

if(!isset($_POST['seguir']))
     {require("seguir.inc");
      exit;
     }
ACÁ QUEDÉ

Hay dos opciones, que el usuario esté sesionado, entonces solo confirma el seguimiento. Si no, crea el usuario o se sesiona y sigue con el seguimiento