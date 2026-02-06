<?php
/*
    Nombre: ventas_list.php
    Autor: Julio Tuozzo.
    Función: Listado de artículos que tienen oferta de compra.
    Fecha de creación: 02/06/2025.
    Ultima modificación: 06/02/2026.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\Ventas;
use App\Controller\User;

$usuario = new User;
$usuario->setPermisos();


// Acá accede con la sesión del usuario

if(!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2)
     {// No tiene permisos para listar los artículos
      header("Location: index.php");
      exit;
     }

// Guardo los datos en variables

foreach($_GET as $clave => $valor)
     {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$ventas = new Ventas();

if(!isset($pagina))
     {// No está paginando, es un query nuevo
      $pagina = 1;
      $sentido ="DESC";
      $el_orden = "articulo_compra_id";
      $q_registros = $ventas->countVentas($_SESSION['DML_USER_ID']);
     }

$desde = ($pagina - 1) * Utils::$max_articulos;

// Armo y ejecuto la consulta

$query = $ventas->queryVentas($_SESSION['DML_USER_ID'], $el_orden, $sentido);

$result = Utils::selectLimit($query, $desde,__FILE__, __LINE__); 

if($sentido=="DESC")
        {$_aux_var="arr_$el_orden";
         $$_aux_var="&nbsp; &#9660;";
         $_aux_var="sen_$el_orden";
         $$_aux_var="ASC";
        }
else
        {$_aux_var="arr_$el_orden";
         $$_aux_var="&nbsp; &#9650;";
         $_aux_var="sen_$el_orden";
         $$_aux_var="DESC";
        }

require(__DIR__ . '/../resources/views/ventas_list.php');
?>