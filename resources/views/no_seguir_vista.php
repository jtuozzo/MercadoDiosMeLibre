<?php
/*
    Nombre: no_seguir_vista.php
    Autor: Julio Tuozzo.
    Función: Vista de la opción para dejar de seguir las publicaciones de un usuario.
    Fecha de creación: 06/06/2025.
    Ultima modificación: 06/06/2025.
*/

if(empty($mensaje))
    {$cuerpo = "<h2>Seguir nuevas publicaciones de {$usuario->nombres}</h2>
        <script language='javascript'>
                        Swal.fire({
                                 text: 'Querés dejar de seguir las nuevas publicaciones de {$usuario->nombres}??',
                                 icon: 'question',
                                 showCancelButton: true,
                                 confirmButtonColor: '#1b998b',
                                 cancelButtonColor: '#d7263d',
                                 cancelButtonText: 'No',
                                 confirmButtonText: 'Si',
                                 focusCancel: true
                                })
                    .then((result) => {
                                    if (result.isConfirmed) {
                                        window.location='no_seguir.php?id=$token&no_seguir=SI';
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

require(__DIR__ . '/layouts/header.php');
echo "
<script type='text/javascript' src='./js/seguir.js'></script>

<div id='seguir'>
    {$cuerpo}
</div>";

require(__DIR__ . '/layouts/footer.php');