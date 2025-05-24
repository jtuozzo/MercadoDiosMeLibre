<?php
/*
    Nombre: cambiar_clave.php
    Autor: Julio Tuozzo.
    Función: Controlador cambia la clave.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 24/05/2025.
*/

require("Utils.inc");
require("User.inc");

$mens_error = "<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'Ooops!!',
                    text:'No se pudo cambiar la clave, intente nuevamente.',
                    confirmButtonColor: '#D22518',
                    })
               	  .then(function() {
        	                window.location = 'index.php';
                    });
                 </script>";


foreach($_GET as $key => $valor)
     {$$key=trim($valor);
     }

foreach($_POST as $key => $valor)
     {$$key=trim($valor);
     }
$user = new User();

if(isset($id)) // Si se envió el id por GET, lo valido
     {if(!filter_var($id, FILTER_VALIDATE_EMAIL))
         {$mensaje=$mens_error;
         }

     // Verifico que exista el usuario y que la clave esté pendiente de generar

      $query = "SELECT user_id 
                FROM user
                WHERE email = '$id' AND 
                expira_clave<NOW()";

      $result = Utils::execute($query,__FILE__,__LINE__);

      if($result->recordCount() == 0)
            {$mensaje=$mens_error;
            }
       
     }
elseif(isset($clave)) // Se envió la clave por POST, llamo al método de User para cambiar la clave
     {

      if($user->cambiarClave($clave, $nueva_clave, $reingresa))
            {// Se pudo cambiar la clave
             $mensaje="<script language='javascript'>
                          Swal.fire({
                          icon:'success',
                          text:'La clave se cambió correctamente.',
                          confirmButtonColor: '#63676c',
                          })
                      .then(function() {
                                  window.location = 'index.php';
                              });
                       </script>";
            }
      else
            {// No se pudo cambiar la clave
             $mensaje=Utils::msgError();
            }
     }
else // Si no se envió ni el id ni la clave, va a index
     {header("Location: index.php");
      exit();
     }

require("cambiar_clave_vista.inc");

?>