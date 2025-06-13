<?php
/*
    Nombre: login.php
    Autor: Julio Tuozzo.
    Función: Controlador del login del usuario.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 13/06/2025.
*/

session_start();

require("Utils.inc");
require("User.inc");

$user = new User;

// Vacío las variables de sesión y las cookies donde están los datos del usuario

Utils::logout();

if (!isset($_POST['ingresar']))
     {$email=$st_email=$email_err=$st_clave=$clave_err=$mensaje="";
      require("login_vista.inc");
      exit;
     }

// Guardo los datos posteados en variables

foreach($_POST as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

// Validaciones del usuario

if(strlen($email)==0)
     {$st_email="class='st_error'";
      $email_err="<br/><span class='error'>Ingrese e-mail</span>";
      $mensaje=Utils::msgError();
     }

if(strlen($clave)==0)
     {$st_clave="class='st_error'";
      $clave_err="<br/><span class='error'>Ingrese clave</span>";
      $mensaje=Utils::msgError();
     }


if(!isset($mensaje)) // Hasta acá no hubo errores, valido el usuario y la clave
     {$clave = hash("sha512", $clave);

      $hay_usuario=$user->getUser($email, $clave, true);

     if(!$hay_usuario)
        {$st_email="class='st_error'";
        $st_clave="class='st_error'";
        $email_err="<br/><span class='error'>Usuario o clave incorrectos</span>";
        $clave_err="";
        $mensaje=Utils::msgError();
        }

     }

if (isset($mensaje))
     {require("login_vista.inc");
      exit;
     }

// Veo si quería que lo recuerde

if (isset($_POST['recordarme']))
     {setcookie("DML_EMAIL", $email, time()+60*60*24*30);
      setcookie("DML_CLAVE", $clave, time()+60*60*24*30);
     }
else
     {setcookie("DML_EMAIL", "", time()-3600);
      setcookie("DML_CLAVE", "", time()-3600);
     }

// Voy a la página de inicio
header("Location: index.php");
?>