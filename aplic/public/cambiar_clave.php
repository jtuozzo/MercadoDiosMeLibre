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

// Verifico el llamado al controlador

foreach($_GET as $key => $valor)
     {$$key=trim($valor);
     }

   
if(!isset($id))
     {$mensaje=$mens_error;
     }

// Verifico que exista el usuario y que la clave esté pendiente de generar

$query = "SELECT user_id 
          FROM user
          WHERE email = '$id' AND 
          expira_clace<NOW()";

$result = Utils::execute($query,__FILE__,__LINE__);

if($result->recordCount() == 0)
     {$mensaje=$mens_error;
     }

require("cambiar_clave_vista.inc");

?>