<?php
/*
    Nombre: Utils.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos estáticos de uso global.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 23/05/2025.
*/

// Datos de la instalación

/* Conexión con las bases de datos

define('DB_HOST', '');
define('DB_USER', '');
define('DB_PASS', '');
define('DB_BASE', '');

# Carpeta de logs

define('LOGS', '../carpeta/');

*/

require("config_data.inc");

// Seteo zona horaria
date_default_timezone_set('America/Argentina/Buenos_Aires');


require("DBConecto.inc");

class Utils 
    {static private $dbase;


      // Funcióm que ejecuta una consulta SQL y devuelve el resultado.

     static public function execute($query, $file, $line)
        {if(!isset(self::$dbase))
            {self::$dbase = new DBConecto();
            }
         if (!$result = self::$dbase->db->Execute($query))
                {self::$dbase->db_error(self::$dbase->db->ErrorMsg(),$file,$line,$query);
                 return false;
                }
         return $result;
        }

     static public function msgError($mensaje="Corrija los errores")
        {return "<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'{$mensaje}',
                    confirmButtonColor: '#D22518',
                    })
                 </script>";
        }

     static public function getUser($email, $clave)
        {$query = "SELECT user_id, apellidos, nombres, email, nivel, clave, token 
              FROM user 
              WHERE email='$email' 
              AND clave='$clave'";

        $result = self::execute($query, __FILE__, __LINE__);

        if($result->recordCount() == 0)
            {return false;
            }

        // Inicializo las variables de sesión del usuario

        foreach($result->fields as $key => $valor)
            {$_SESSION["DML_".strtoupper($key)]=$valor;
            }
        
         // Guardo la última sesión

         $query = "UPDATE user 
                   SET last_login=NOW() 
                   WHERE email='$email'";

         $update = self::execute($query, __FILE__, __LINE__);
        }
    }


?>