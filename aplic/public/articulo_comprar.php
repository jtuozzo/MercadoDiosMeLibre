<?php
/*
    Nombre: articulo_comprar.php
    Autor: Julio Tuozzo.
    Función: Compra un artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 31/05/2025.
*/

session_start();


require("Utils.inc");
require("Articulo.inc");
require("Compra.inc");
$articulo = new Articulo();
$compra = new Compra();

// Inicializo GETS y POSTS y verifico el acceso al artículo

if(isset($_GET['id']) and isset($_GET['key']))
    {$articulo->articulo_id = $articulo->validoID($_GET['id'],$_GET['key']);
     $key=$_GET['key'];
    }

foreach($_POST as $clave => $valor)
     {if(isset($compra->$clave))
          {$compra->$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
      else     
          {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
      if(isset($id))
          {$articulo->articulo_id=$id;
          }
     }

if(!$articulo->getArticulo($articulo->articulo_id))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

if(!isset($_POST['compro']))    
    {$mensaje = "";
     require ("articulo_comprar_vista.inc");
     exit;
    }

if($compra->crearCompra($articulo->articulo_id))
    {$mensaje="<div class='has_comprado'>
                    <h1>Excelente!!</h1>
                    <h2>Solicitaste comprar: <em>{$articulo->titulo}</em>.</h2>";
     if($compra->registrado)
        {$mensaje.="<h2>El vendedor deberá contactarse para concretar tu compra.</h2>";
        }
     else
        {$mensaje.="<h2>Te hemos enviado un correo a {$compra->email}</h2>
                    <h2>Verificá tu casilla la correo para terminar el proceso.</h2>
                    <h2>Si no llegó el mail, revisá la casilla de correo basura.</h2>
                    <h2>En el futuro si querés saltear este paso de verificación, podés crear tu usuario aquí: <a href='usuario.php' target='_blank'>Crear Usuario</a></h2>
          </div>";

        }

     $mensaje.="
          <div class='volver'>
                <a href='articuloGet.php?id={$articulo->articulo_id}&key={$key}' title='Volver al artículo'>Volver al artículo</a>
          </div>

            <script type='text/javascript'>ocultoID('form');ocultoID('titulo');</script>
         </div>";
    }
else
    {// No se pudo procesar la compra
     $mensaje=Utils::msgError();
    }

require ("articulo_comprar_vista.inc");
?>