<?php
/*
    Nombre: articulo_comprar.php
    Autor: Julio Tuozzo.
    Función: Compra un artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 01/06/2025.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\Compra;

$compra = new Compra();

// Inicializo GETS y POSTS y verifico el acceso al artículo

if(isset($_GET['id']) and isset($_GET['key']))
    {foreach($_GET as $clave => $valor)
        {$$clave=$valor;
        }
    }

foreach($_POST as $clave => $valor)
     {if(isset($compra->$clave))
          {$compra->$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
      else     
          {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
     }

$compra->articulo_id = $compra->validoID($id,$key);

if(!$compra->getArticulo($compra->articulo_id))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

if(!isset($_POST['compro']))    
    {$mensaje = "";
     require (__DIR__ . "/../resources/views/articulo/articulo_comprar_vista.php");
     exit;
    }

if($compra->crearCompra())
    {$mensaje="<div class='has_comprado'>
                    <h1>Excelente!!</h1>
                    <h2>Solicitaste comprar: <em>{$compra->titulo}</em>.</h2>";
     if($compra->registrado)
        {$mensaje.="<h2>El vendedor deberá contactarse para concretar tu compra.</h2>";
        }
     else
        {$mensaje.="<h2>Te hemos enviado un correo a <em>{$compra->email}</em></h2>
                    <h2>Verificá tu casilla de correo para terminar el proceso.</h2>
                    <h2>Si no llegó el mail, revisá la casilla de correo basura.</h2>
                    <h2>En el futuro si querés saltear este paso de verificación, podés crear tu usuario aquí: <a href='usuario.php' target='_blank'>Crear Usuario</a></h2>
          </div>";

        }

     $mensaje.="
          <div class='volver'>
                <a href='articuloGet.php?id={$compra->articulo_id}&key={$key}' title='Volver al artículo'>Volver al artículo</a>
          </div>

            <script type='text/javascript'>ocultoID('form');ocultoID('titulo');</script>
         </div>";
    }
else
    {// No se pudo procesar la compra
    if(!$compra->salio_email)
        {$mensaje=Utils::msgError("Error de conexión","Intente en unos minutos");
        }
    elseif($compra->repetida)
        {$mensaje=Utils::msgError("Ya solicitaste esa compra","Aguardá a que te contacte el vendedor");
        }
    else
        {$mensaje=Utils::msgError();
        }
     
    }

require (__DIR__ . "/../resources/views/articulo/articulo_comprar_vista.php");
?>