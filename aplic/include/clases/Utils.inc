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

# Variables de conexión con el servidor de correo.
define('MAIL_HOST',"");
define('MAIL_USUARIO',"");
define('MAIL_CLAVE',"");
define('MAIL_PORT',7);
define('MAIL_REMITENTE',"");

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

         try 
			{$result = self::$dbase->db->Execute($query);
			} 
		catch (Exception $e) 
			{self::$dbase->db_error($e->getMessage(),$file,$line,$query);
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

    }


?>