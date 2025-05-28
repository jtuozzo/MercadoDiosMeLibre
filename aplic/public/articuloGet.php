<?php
/*
    Nombre: articuloGet.php
    Autor: Julio Tuozzo.
    Función: Ver / Editar un artículo.
    Fecha de creación: 28/05/2025.
    Ultima modificación: 28/05/2025.
*/

session_start();

// Inicializo GETS y POSTS

foreach($_GET as $clave=>$valor)
    {$$clave = $valor;
    }

foreach($_POST as $clave=>$valor)
    {$$clave = $valor;
    }

if(!isset($articulo_id))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

require("Utils.inc");
require("Articulo.inc");

$articulo = new Articulo;

// Trae los datos del artículo

if (!$articulo->getArticulo($articulo_id))
    {header("Location: index.php");
     exit;
    }

// Defino el tipo de vista del artículo

if(isset($_SESSION['DML_USER_ID']) and $_SESSION['DML_USER_ID']==$articulo->user_id)
    {// El artículo es del usuario, es una vista de edición y lo puede modificar
     $articulo->vista="M";
     $mensaje="";
     require("articulo_vista.inc");
    }
else    
    {// Lo puede ver y comprar
     
    }

?>