<?php
/*
    Nombre: getFoto.php
    Autor: Julio Tuozzo.
    Función: Trae una foto de artículo de la base de datos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 29/05/2025.
*/
require("Utils.inc");
require("Articulo.inc");

$articulo = new Articulo;

if($articulo->getFoto($_GET['id'], $_GET['key']))
    {
     header("Content-Type: {$articulo->foto_tipo_file}");
     echo $articulo->foto;
    }
else    
    {header("Content-Type: image/jpeg");
     $fp = fopen("./images/sin_foto.jpg", "rb");
     $foto = fread($fp, filesize("./images/sin_foto.jpg"));
     echo $foto;
    }


?>