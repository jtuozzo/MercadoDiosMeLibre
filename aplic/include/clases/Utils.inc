<?php
/*
    Nombre: Utils.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos estáticos de uso global.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 25/05/2025.
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

# Cantidad máxima de fotos por artículo
define('MAX_FOTOS', 10);

*/

require("config_data.inc");

// Seteo zona horaria
date_default_timezone_set('America/Argentina/Buenos_Aires');


require("DBConecto.inc");

class Utils 
    {static public $dbase;


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

     static public function msgError($mensaje="Corrija los errores", $sub = null)
        {if(isset($sub))
            {$sub="text: '$sub',";
            }
         
         return "<script language='javascript'>
                    Swal.fire({
                    icon:'error',
                    title:'{$mensaje}',
                    $sub
                    confirmButtonColor: '#D22518',
                    })
                 </script>";
        }

      static public function getIP()
            {if ($_SERVER)
                  {if ( $_SERVER["HTTP_X_FORWARDED_FOR"] )
                     {$realip = $_SERVER["HTTP_X_FORWARDED_FOR"];
                     }
                  elseif ( $_SERVER["HTTP_CLIENT_IP"] )
                     {$realip = $_SERVER["HTTP_CLIENT_IP"];
                     }
                  else
                     {$realip = $_SERVER["REMOTE_ADDR"];
                     }
                  }
             else
                  {if ( getenv( "HTTP_X_FORWARDED_FOR" ) )
                     {$realip = getenv( "HTTP_X_FORWARDED_FOR" );
                     }
                  elseif ( getenv( "HTTP_CLIENT_IP" ) )
                     {$realip = getenv( "HTTP_CLIENT_IP" );
                     }
                  else {$realip = getenv( "REMOTE_ADDR" );
                        }
                  }
            return $realip;
            }

     static public function logout()
         {// Destruyo la sesión del usuario y las cookies asociadas

            foreach($_SESSION as $clave => $valor)
                  {if(strpos($clave,"DML_")!== false)
                           {unset($_SESSION[$clave]);
                           }
                  }

            setcookie("DML_EMAIL", "", time()-3600);
            setcookie("DML_CLAVE", "", time()-3600);
         }
    }


?>