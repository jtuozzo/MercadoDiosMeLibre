<?php
/*
    Nombre: no_seguir.php
    Autor: Julio Tuozzo.
    Función: Controlador para dejar de seguir publicaciones de otro usuario.
    Fecha de creación: 05/06/2025.
    Ultima modificación: 06/06/2025.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;

if(!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL']<2)
     {// No está sesionado, se va
      header("Location: index.php");
      exit;
     }




// Veo si hay token y si es válido

foreach($_GET as $clave => $valor)
     {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$usuario = new User;
$token = $id;

if(!isset($id) or !$usuario->tokenValido($token))
     {// El token no vino o no es válido
      header("Location: index.php");
      exit;
     }        
$mensaje="";

if(!isset($no_seguir))
     {require(__DIR__ . '/../resources/views/no_seguir_vista.php');
      exit;
     }

// Actualizo el seguimiento

if($usuario->noSeguirA($token))
     {$mensaje="<script language='javascript'>
                          Swal.fire({
                          icon:'success',
                          text:'Ya no estás siguiendo las nuevas publicaciones de {$usuario->nombres}.',
                          confirmButtonColor: '#63676c',
                          })
                      .then(function() {
                                  window.location = 'articulo_list.php?id=$token';
                              });
                       </script>";
     }
else 
     {$mensaje="<script language='javascript'>
                          Swal.fire({
                          icon:'error',
                          title:'Oooppsss!!',
                          text: 'Hubo un error, intentá más tarde'
                          confirmButtonColor: '#D22518',
                          })
                      .then(function() {
                                  window.location = 'articulo_list.php?id=$token';
                              });
                       </script>";
     }
require(__DIR__ . '/../resources/views/no_seguir_vista.php');