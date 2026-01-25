<?php
/*
    Nombre: articuloGet.php
    Autor: Julio Tuozzo.
    Función: Ver / Editar un artículo.
    Fecha de creación: 28/05/2025.
    Ultima modificación: 25/01/2026.
*/

session_start();

require("Utils.inc");
require("Articulo.inc");

$articulo = new Articulo;

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


if(isset($modificar))
    {// Armo los array de fotos
    $fotos_actuales = array();
    $fotos_nuevas = array();
    for($i=1; $i<=Utils::$max_fotos; $i++)
        {$aux="articulo_foto_id_{$i}";
         if(isset($$aux))
            {$fotos_actuales[$i]=$$aux;
            }
         elseif(isset($_FILES["foto_$i"]))
            {$fotos_nuevas[$i]= $_FILES["foto_$i"]; 
            }
         else
            {$fotos_actuales[$i]="";
            }
        }

     if($articulo->modifArticulo($fotos_actuales, $fotos_nuevas))
            {$mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Artículo modificado',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                       .then(function() {
        	                window.opener.location.reload();
                            window.close();
                    });
                     </script>";
            }
        else
            {$articulo->las_fotos = $fotos_actuales;
             $mensaje=Utils::msgError();
            }
    }
elseif(isset($comprar))
    {header("Location: articulo_comprar.php?id={$id}&key={$key}");
    }
else
    {// Trae los datos del artículo

    if (!$articulo->getArticulo($articulo->articulo_id))
        {header("Location: index.php");
         exit;
        }
    $mensaje="";
    }

// Defino el tipo de vista del artículo

if(isset($_SESSION['DML_USER_ID']) and $_SESSION['DML_USER_ID']==$articulo->user_id)
    {// El artículo es del usuario, es una vista de edición y lo puede modificar
     $articulo->vista="M";
     require("articulo_vista.inc");
    }
elseif($articulo->oculto=="N" and $articulo->vendido=="N")
    {// Lo puede ver y comprar
     require("articulo_comprador_vista.inc");
    }
else
    {// El artículo no está disponible
     require("articulo_no_disponible_vista.inc");
    }

?>