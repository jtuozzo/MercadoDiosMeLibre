<?php
/*
    Nombre: articulo_list.php
    Autor: Julio Tuozzo.
    Función: Listadode de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 27/05/2025.
*/

session_start();

require("Utils.inc");
require("Articulo.inc");
require("User.inc");

// Acá accede con la sesión del usuario o con el link de invitado

if((!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2) and (!isset($_GET['id'])))
     {// No tiene permisos para listar los artículos
      header("Location: index.php");
      exit;
     }

// Guardo los datos en variables

foreach($_GET as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$articulo = new Articulo();
$usuario = new User();

if(isset($id))
     {$token = $id;
     }
else
     {$token = $_SESSION['DML_TOKEN'];
     }

if(!$usuario->tokenValido($token))
     {// El token no es válido
      header("Location: index.php");
      exit;
     }    

$result = Utils::selectLimit($query, $desde,__FILE__, __LINE__);

require("articulo_list.inc");
?>