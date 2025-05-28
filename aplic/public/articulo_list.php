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
      // Como no es el usuario dueño de los artículos, ve los que están solo en venta
      $articulo->solo_en_venta = true;
     }
else
     {$token = $_SESSION['DML_TOKEN'];
      // Es el usuario, ve a todos los artículos
      $articulo->solo_en_venta = false;
     }

if(!$usuario->tokenValido($token))
     {// El token no es válido
      header("Location: index.php");
      exit;
     }    

if(!isset($pagina))
     {// No está paginando, es un query nuevo
      $pagina = 1;
      $sentido ="ASC";
      $orden = "articulo_id";
      $q_registros = $articulo->countArticulos($usuario->id);
     }

$desde = ($pagina - 1) * MAX_ARTICULOS;

// Armo y ejecuto la consulta

$query = $articulo->queryArticulos($usuario->id, $orden, $sentido);

$result = Utils::selectLimit($query, $desde,__FILE__, __LINE__); 


if($sentido=="DESC")
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9660;";
         $_aux_var="sen_$orden";
         $$_aux_var="ASC";
        }
else
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9650;";
         $_aux_var="sen_$orden";
         $$_aux_var="DESC";
        }


require("articulo_list.inc");
?>