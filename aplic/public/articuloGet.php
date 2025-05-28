<?php
/*
    Nombre: articuloGet.php
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

// Defino el tipo de vista del artículo

if(isset($_SESSION['DML_USER_ID']) and $_SESSION['DML_USER_ID']==$articulo->user_id)
    {// El artículo es del usuario, es una vista de edición y lo puede modificar
     $articulo->vista="M";
    }
else    
    {// Lo puede ver y comprar
     $articulo->vista="C";
    }
// Traigo la vista con los datos del artículo
$mensaje="";
require("articulo_vista.inc");

?>