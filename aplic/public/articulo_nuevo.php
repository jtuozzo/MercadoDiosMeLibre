<?php
/*
    Nombre: articulo_nuevo.php
    Autor: Julio Tuozzo.
    Función: Creación de artículo.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 25/05/2025.
*/

session_start();

require("Utils.inc");
require("Articulo.inc");

// Guardo los datos posteados en variables

foreach($_POST as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$articulo = new Articulo();

if(!isset($_POST['crear']))
     {// No se ha enviado el formulario, muestro la vista
      $mensaje="";
      require("articulo_vista.inc");
      exit;
     }

if(!$articulo->crearArticulo($titulo, $descripcion, $moneda, $precio, $foto))
        {// No se pudo crear el artículo
         $mensaje=Utils::msgError();
        }
    else
        {// Se pudo crear el artículo
        $mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Artículo creado',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                     .then(function() {
        	                window.location = 'index.php';
                     });
                     </script>";
        }

require("articulo_vista.inc");
?>