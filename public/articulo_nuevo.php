<?php
/*
    Nombre: articulo_nuevo.php
    Autor: Julio Tuozzo.
    Función: Creación de artículo.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 06/02/2025.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\Articulo;
use App\Controller\User;

$usuario = new User;
$usuario->setPermisos();


if(!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2)
     {// No tiene permisos para crear artículos
      header("Location: index.php");
      exit;
     }



$articulo = new Articulo();

// Defino la vista del artículo como Alta
$articulo->vista="A";

// Guardo los datos posteados en variables
foreach($_POST as $clave => $valor)
     {if(isset($articulo->$clave))
          {$articulo->$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
      else     
          {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
     }

$key=$_SESSION['DML_TOKEN'];

if(!isset($_POST['crear']))
     {// No se ha enviado el formulario, muestro la vista
      $mensaje="";
      require(__DIR__ . '/../resources/views/articulo/articulo_vista.php');
      exit;
     }

// Armo el array de fotos
$fotos = array();
for($i=1; $i<=Utils::$max_fotos; $i++)
     {$fotos[$i] = $_FILES["foto_$i"]; 
     }

if(!$articulo->crearArticulo($fotos))
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
        
        foreach($_POST as $clave => $valor)
            {if(isset($articulo->$clave))
                    {$articulo->$clave="";
                    }
             else     
                    {$$clave="";
                    }
            }
         $articulo->orden = 0;   
        }

require(__DIR__ . '/../resources/views/articulo/articulo_vista.php');
?>