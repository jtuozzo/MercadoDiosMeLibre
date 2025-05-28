<?php
/*
    Nombre: getArticulo.php
    Autor: Julio Tuozzo.
    Función: Ver / Editar un artículo.
    Fecha de creación: 28/05/2025.
    Ultima modificación: 28/05/2025.
*/

session_start();

if(!isset($_GET['id']))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

require("Utils.inc");
require("Articulo.inc");

$articulo = new Articulo;

// Trae los datos del artículo

if (!$articulo->getArticulo($_GET['id']))
    {header("Location: index.php");
     exit;
    }


?>