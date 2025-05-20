<?php
/*
    Nombre: login.php
    Autor: Julio Tuozzo.
    Función: Controlador del login del usuario.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 20/05/2025.
*/

session_start();

require("Utils.inc");

// Vacío las variables de sesión donde están los datos del usuario

foreach($_SESSION as $clave => $valor)
     {if(strpos($clave,"DML_")!== false)
            {unset($_SESSION[$clave]);
            }
     }

if (!isset($_POST['ingresar']))
     {require("login_vista.inc");
      exit;
     }

// Guardo los datos posteados en variables

foreach($_POST as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,'ISO-8859-1'));
     }

// Validaciones del usuario

if(strlen($email)==0)
     {$st_email="class='st_error'";
      $email_err="<span class='error'>Ingrese e-mail</span>";
      $mensaje=Utils::msgError();
     }

if(strlen($clave)==0)
     {$st_clave="class='st_error'";
      $clave_err="<span class='error'>Ingrese clave</span>";
      $mensaje=Utils::msgError();
     }

$clave = hash("sha512", $clave);

$query = "SELECT user_id, apellidos, nombres, email, nivel, clave, token 
          FROM user 
          WHERE email='$email' 
          AND clave='$clave'";

$result = Utils::execute($query, __FILE__, __LINE__);

if($result->recordCount() == 0)
     {$st_email="class='st_error'";
      $st_clave="class='st_error'";
      $email_err="<span class='error'>Usuario o clave incorrectos</span>";
      $mensaje=Utils::msgError();
     }

if (isset($mensaje))
     {require("login_vista.inc");
      exit;
     }

// Todo OK, guardo el último login del usuario

$query = "UPDATE user 
          SET last_login=NOW() 
          WHERE email='$email'";

$update = Utils::execute($query, __FILE__, __LINE__);

// Guardo los datos del usuario en la sesión

foreach($result->fields as $key => $valor)
     {$_SESSION["DML_".$key]=$valor;
     }

// Voy a la página de inicio
header("Location: index.php");
?>