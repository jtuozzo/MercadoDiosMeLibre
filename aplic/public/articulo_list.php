<?php
/*
    Nombre: articulo_list.php
    Autor: Julio Tuozzo.
    Función: Listado de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 17/06/2025.
*/

session_start();

require("Utils.inc");
require("Articulo.inc");
require("User.inc");

// Acá accede con la sesión del usuario o con el link de invitado

if((!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2) and (!isset($_GET['id'])))
     {// No tiene permisos para listar los artículos
      header("Location: index.php");
      exit;
     }

// Guardo los datos en variables
$id="";

foreach($_GET as $clave => $valor)
     {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$articulo = new Articulo();
$usuario = new User();

if(strlen($id)>0)
     {$token = $id;
     }
else
     {$token = $_SESSION['DML_TOKEN'];
     }

if(!$usuario->tokenValido($token))
     {// El token no es válido
      header("Location: index.php");
      exit;
     }    

if(!isset($pagina))
     {// No está paginando, es un query nuevo
      $pagina = 1;
      $sentido ="ASC";
      $orden = "orden";
      $q_registros = $articulo->countArticulos($usuario->user_id);
     }

$desde = ($pagina - 1) * MAX_ARTICULOS;

// Armo y ejecuto la consulta

$query = $articulo->queryArticulos($usuario->user_id, $orden, $sentido);

$result = Utils::selectLimit($query, $desde,__FILE__, __LINE__); 


if($sentido=="DESC")
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9660;";
         $_aux_var="sen_$orden";
         $$_aux_var="ASC";
        }
else
        {$_aux_var="arr_$orden";
         $$_aux_var="&nbsp; &#9650;";
         $_aux_var="sen_$orden";
         $$_aux_var="DESC";
        }

if(!isset($_SESSION['DML_TOKEN']) or $_SESSION['DML_TOKEN']!=$token)
     {$cabecera="<div class='cabecera'>
                         <h2>Artículos de {$usuario->nombres}</h2>";

      if($usuario->siguiendo($token))
               {$cabecera.="<input type='button' class='boton seguir' value='Dejar de seguir' onClick=\"window.location='no_seguir.php?id=$token'\"/>";
               }
      else
               {$cabecera.="<input type='button' class='boton seguir' value='Seguir publicaciones' onClick=\"window.location='seguir.php?id=$token'\"/>";

               }
                         
      $cabecera.="</div>";
     }
else 
     {$link=$_SERVER['REQUEST_SCHEME']."://".$_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']."?id=".$_SESSION['DML_TOKEN'];
      $cabecera="<div class='link' onClick=copyClipp('{$link}')><img src='./images/copy.png' />  Copiar link del listado</div>";
     }

require("articulo_list.inc");
?>