<?php
/*
    Nombre: articulo_list.php
    Autor: Julio Tuozzo.
    Función: Listado de artículos.
    Fecha de creación: 27/05/2025.
    Ultima modificación: 28/01/2026.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;
use App\Controller\Articulo;

$usuario = new User;
$usuario->setPermisos();

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

if(strlen($id)>0)
     {$token = $id;
     }
elseif(isset($_SESSION['DML_TOKEN']))
     {$token = $_SESSION['DML_TOKEN'];
     }
else
     {// No hay token
      header("Location: index.php");
      exit;
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
      $el_orden = "orden";
      $q_registros = $articulo->countArticulos($usuario->user_id);
     }

$desde = ($pagina - 1) * Utils::$max_articulos;

// Armo y ejecuto la consulta

$query = $articulo->queryArticulos($usuario->user_id, $el_orden, $sentido);

$result = Utils::selectLimit($query, $desde,__FILE__, __LINE__); 


if($sentido=="DESC")
        {$_aux_var="arr_$el_orden";
         $$_aux_var="&nbsp; &#9660;";
         $_aux_var="sen_$el_orden";
         $$_aux_var="ASC";
        }
else
        {$_aux_var="arr_$el_orden";
         $$_aux_var="&nbsp; &#9650;";
         $_aux_var="sen_$el_orden";
         $$_aux_var="DESC";
        }

if($q_registros>0)
     {$buscar_box = "<div class='buscar'> <input type='text' id='articulo' placeholder='Buscar' autocomplete='off'>
                     <input type='hidden' id='token' value='$token' />
                     <div id='resultados' class='autocomplete-result d-none'></div>
                    </div>
                    ";
     }
else
     {$buscar_box = "";
     }

$cabecera="<div class='cabecera'>";

if(!isset($_SESSION['DML_TOKEN']) or $_SESSION['DML_TOKEN']!=$token)
     {$cabecera.="<h2>Artículos de {$usuario->nombres}</h2>
                  $buscar_box";

      if($usuario->siguiendo($token))
               {$cabecera.="<input type='button' class='boton seguir' value='Dejar de seguir' onClick=\"window.location='no_seguir.php?id=$token'\"/>";
               }
      else
               {$cabecera.="<div><input type='button' class='boton seguir' value='Seguir publicaciones' onClick=\"window.location='seguir.php?id=$token'\"/></div>";

               }
                         
      
     }
else 
     {$link=$_SERVER['REQUEST_SCHEME']."://".$_SERVER['SERVER_NAME'].$_SERVER['PHP_SELF']."?id=".$_SESSION['DML_TOKEN'];
      $cabecera.="<div class='link' onClick=copyClipp('{$link}')><img src='./images/copy.png' />  Copiar link del listado</div>
      $buscar_box";
     }

$cabecera.="</div>";

require(__DIR__ . '/../resources/views/articulo/articulo_list_vista.php');
?>