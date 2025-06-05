<?php
/*
    Nombre: seguir.php
    Autor: Julio Tuozzo.
    Función: Controlador de seguimiento de publicaciones de otro usuario.
    Fecha de creación: 04/06/2025.
    Ultima modificación: 05/06/2025.
*/

session_start();

require("Utils.inc");
require("User.inc");

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
if(!isset($seguir))
     {require("seguir_vista.inc");
      exit;
     }

// Actualizo el seguimiento

if($usuario->seguirA($token))
     {$mensaje="<script language='javascript'>
                          Swal.fire({
                          icon:'success',
                          title:'Siguiendo a {$usuario->nombres}.',
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
require("seguir_vista.inc");