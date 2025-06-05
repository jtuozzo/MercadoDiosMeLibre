<?php
/*
    Nombre: seguir_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista de la opción para seguir las publicaciones de un usuario.
    Fecha de creación: 05/06/2025.
    Ultima modificación: 05/06/2025.
*/

// Determino el texto en función si el usuario está logueado o no. Si no está logueado no puede seguir artículos.

if(!isset($_SESSION['DML_USER_ID']))
    {$cuerpo ="<h2>Para seguir las publicaciones nuevas de {$usuario->nombres} tenés que tener usuario.</h2>
        <h3>Si ya tenés usuario ingresá a: <a href='login.php'>Ingresar</a></h3>
        <h3>Si no, podés crearlo acá: <a href='usuario.php'>Crear Usuario</a></h3>";

    }
elseif(empty($mensaje))
    {$cuerpo = "<h2>Seguir nuevas publicaciones de {$usuario->nombres}</h2>
        <script language='javascript'>
                        Swal.fire({
                                 text: 'Querés seguir las nuevas publicaciones de {$usuario->nombres}??',
                                 icon: 'question',
                                 showCancelButton: true,
                                 confirmButtonColor: '#1b998b',
                                 cancelButtonColor: '#d7263d',
                                 cancelButtonText: 'No',
                                 confirmButtonText: 'Si',
                                 focusConfirm: true
                                })
                    .then((result) => {
                                    if (result.isConfirmed) {
                                        window.location='seguir.php?id=$token&seguir=SI';
                                        }
                                    else
                                        {window.location='articulo_list.php?id=$token';
                                        }
                                }
                                )
                     </script>";
    }
else    
    {$cuerpo = $mensaje;
    }


$css_local = "seguir.css";

require_once('head.inc');
echo "
<script type='text/javascript' src='./js/seguir.js'></script>

<div id='seguir'>
    {$cuerpo}
</div>";

require("foot.inc");