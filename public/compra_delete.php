<?php
/*
    Nombre: compra_delete.php
    Autor: Julio Tuozzo.
    Función: Elimina una solicitud de compra.
    Fecha de creación: 25/01/2026.
    Ultima modificación: 25/01/2026.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\Articulo;
use App\Controller\Ventas;

// Acá accede con la sesión del usuario

if(!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2) 
     {// No tiene permisos para eliminar compras      
      Utils::error_log("No tiene acceso para eliminar una compra",__FILE__,__LINE__);
     }

foreach($_GET as $clave => $valor)
     {$$clave=trim($valor);
     }

$venta = new Ventas();

if(!empty($articulo_compra_id))
     {$venta->deleteComprador($articulo_compra_id);
     }
else
     {Utils::error_log("El articulo_compra_id está vacío",__FILE__,__LINE__);
     }

?>