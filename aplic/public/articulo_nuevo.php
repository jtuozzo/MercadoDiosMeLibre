<?php
/*
    Nombre: articulo_nuevo.php
    Autor: Julio Tuozzo.
    Función: Creación de artículo.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 26/05/2025.
*/

session_start();

if(!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2)
     {// No tiene permisos para crear artículos
      header("Location: index.php");
      exit;
     }

require("Utils.inc");
require("Articulo.inc");

// Guardo los datos posteados en variables

foreach($_POST as $key => $valor)
     {$$key=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$articulo = new Articulo();

if(!isset($_POST['crear']))
     {// No se ha enviado el formulario, muestro la vista
      $titulo=$descripcion=$precio=$mensaje="";
      require("articulo_vista.inc");
      exit;
     }

// Armo el array de fotos
$fotos = array();
for($i=1; $i<=MAX_FOTOS; $i++)
     {$fotos[$i] = $_FILES["foto_$i"];
     }

if(!$articulo->crearArticulo($titulo, $descripcion, $moneda, $precio, $fotos))
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
                     </script>";
        foreach($_POST as $key => $valor)
            {$$key="";
            }
        }
     
require("articulo_vista.inc");
?>