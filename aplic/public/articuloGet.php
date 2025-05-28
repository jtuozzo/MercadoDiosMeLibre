<?php
/*
    Nombre: articuloGet.php
    Autor: Julio Tuozzo.
    Función: Ver / Editar un artículo.
    Fecha de creación: 28/05/2025.
    Ultima modificación: 28/05/2025.
*/

session_start();

// Inicializo GETS y POSTS

foreach($_GET as $clave=>$valor)
    {$$clave = $valor;
    }

foreach($_POST as $clave=>$valor)
    {$$clave = $valor;
    }

if(!isset($articulo_id))
    {// No hay artículo
     header("Location: index.php");
     exit;
    }

require("Utils.inc");
require("Articulo.inc");

$articulo = new Articulo;

if(isset($modificar))
    {// Armo los array de fotos
    $fotos_actuales = array();
    $fotos_nuevas = array();
    for($i=1; $i<=MAX_FOTOS; $i++)
        {$aux="articulo_foto_id_{$i}";
         if(isset($$aux))
            {$fotos_actuales[]=$$aux;
            }
         elseif(isset($_FILES["foto_$i"]))
            {$fotos_nuevas[]= $_FILES["foto_$i"]; 
            }
        }

        
     if(!modifArticulo($articulo_id, $articulo->titulo, $articulo->descripcion, $articulo->moneda, $articulo->precio, $fotos_actuales, $fotos_nuevas))
            {$mensaje="<script language='javascript'>
                        Swal.fire({
                        icon:'success',
                        title:'Artículo modificado',
                        confirmButtonColor: '#63676c',
                        confirmButtonText: 'Continuar'
                        })
                       .then(function() {
        	                window.parent.location = reload();
                            window.close();
                    });
                     </script>";
            }
        else
            {$mensaje=Utils::msgError();
            }
    }
else
    {// Trae los datos del artículo

    if (!$articulo->getArticulo($articulo_id))
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
else    
    {// Lo puede ver y comprar
     
    }

?>