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
$articulo = new Articulo();
$comprador = new Comprador();

// Inicializo GETS y POSTS y verifico el acceso al artículo

if(isset($_GET['id']) and isset($_GET['key']))
    {$articulo->articulo_id = $articulo->validoID($_GET['id'],$_GET['key']);
     $key=$_GET['key'];
    }

foreach($_POST as $clave => $valor)
     {if(isset($articulo->$clave))
          {$articulo->$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
      else     
          {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
          }
     }

if(!isset($articulo->articulo_id))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

if(!isset($_POST['comprar']))    
    {require ("articulo_comprar_vista.inc");
     exit;
    }

if($comprador->crearCompra())
    {if($comprador->registrado)
        {

        }
     else
        {$mensaje="<div class='has_comprado'>
                    <h1>Excelente!!</h1>
                    <h2>Te hemos enviado un correo a {$comprador->email}</h2>
                    Verificá tu casilla la correopara terminar el proceso.<br/> <br/>Si no llegó el mail, revisá la casilla de correo basura.<br />
                    Si en el futuro querés saltear este paso de verificación, podés crear tu usuario aquí: <a href='usuario.php'>Crear Usuario</a>
          </div>";

        }

     $mensaje.="<script type='text/javascript'>ocultoForm();</script>
         </div>";
    }
else
    {// No se pudo procesar la compra
     $mensaje=Utils::msgError();
    }

require ("articulo_comprar_vista.inc");
?>