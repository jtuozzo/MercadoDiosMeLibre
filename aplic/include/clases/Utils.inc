<?php
/*
    Nombre: Utils.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos estáticos de uso global.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 28/05/2025.
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

# Carpeta de archivos temporales
define('TMP', '../tmp/');

# Cantidad máxima de fotos por artículo
define('MAX_FOTOS', 10);

# Cantidad máxima de artículos por página
define('MAX_ARTICULOS', 20);

*/

require("config_data.inc");

// Seteo zona horaria
date_default_timezone_set('America/Argentina/Buenos_Aires');
ini_set('default_charset', 'utf-8');


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

     // Función que ejecuta una consulta SQL en un rango de registros y devuelve el resultado.
     static public function selectLimit($query, $desde, $file, $line)
        {if(!isset(self::$dbase))
            {self::$dbase = new DBConecto();
            }

         try 
            {$result = self::$dbase->db->selectLimit($query, MAX_ARTICULOS, $desde);
            } 
         catch (Exception $e) 
            {self::$dbase->db_error($e->getMessage(),$file,$line,$query);
             return false;
            }
         return $result;
        }


      // Función que inicia una transacción 
      static public function startTrans($file, $line)
         {if(!isset(self::$dbase))
               {self::$dbase = new DBConecto();
               }

            try
               {self::$dbase->db->StartTrans();
               }
            catch (Exception $e)
               {self::$dbase->db_error($e->getMessage(),$file,$line);
               }
         }

      // Función que completa una transacción
      static public function completeTrans($file, $line)
         {if(!isset(self::$dbase))
               {self::$dbase = new DBConecto();
               }

            try
               {self::$dbase->db->CompleteTrans();
               }
            catch (Exception $e)
               {self::$dbase->db_error($e->getMessage(),$file,$line);
               }
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
                  {if (isset($_SERVER["HTTP_X_FORWARDED_FOR"]) and $_SERVER["HTTP_X_FORWARDED_FOR"] )
                     {$realip = $_SERVER["HTTP_X_FORWARDED_FOR"];
                     }
                  elseif (isset($_SERVER["HTTP_CLIENT_IP"]) and  $_SERVER["HTTP_CLIENT_IP"] )
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


     static function paginador($pagina,$q_registros,$orden,$sentido)
         {# $pagina: Página que estoy mostrando.
          # $q_registros: cantidad de registros de la consulta.
          # $orden: orden de los registros.
          # $sentido: Sentido ascendente o descendente.

         if($q_registros<=MAX_ARTICULOS)
            {return "";
            }

         $paginador = "\n <div class='paginado'>";

         if ($pagina>1)
            { $pag=$pagina-1;
               $paginador.= "<strong><a href='{$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&orden=$orden&sentido=$sentido'>
               <img src='./images/go-first.png' alt='<<||' border='0' /></a> &nbsp;
               <a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido'>
               <img src='./images/go-previous.png' alt='< Ant.|' border='0' /></strong></a>";
            }

         if(isset($q_registros) and $q_registros>0)
            {$paginador.= "<strong>  &nbsp; Pag. &nbsp; </strong>";
            }

         if ($pagina>7)
            {$pag_desde=$pagina-6;
            $paginador.= "......";
            }
         else
            {$pag_desde=1;
            }

         for ($I=MAX_ARTICULOS*($pag_desde-1), $pag=$pag_desde ; $I<$q_registros; $I=$I+MAX_ARTICULOS, $pag++)
            { if ($pag==$pagina)
                     {$paginador.= "<strong>&nbsp;<big> $pag </big>&nbsp;</strong>";
                     }
               else
                     {$paginador.= "<a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido'> $pag </a> &nbsp; \n";
                     }

               if ($pag-$pag_desde>14)
                     {$paginador.= "......";
                     break;
                     }

            }


         if ($pagina<($q_registros/MAX_ARTICULOS))
            {$pag=$pagina+1;
             $ultima=intval(($q_registros-1)/MAX_ARTICULOS)+1;
             $paginador.= "&nbsp;
                  <a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&orden=$orden&sentido=$sentido'><strong>
                  <img src='./images/go-next.png' alt='|Sig.>' border='0' /></a> &nbsp;
                  <a href='{$_SERVER['PHP_SELF']}?pagina=$ultima&q_registros=$q_registros&orden=$orden&sentido=$sentido'>
                  <img src='./images/go-last.png' alt='||>>' border='0' /></strong></a>";
            }

         $paginador.= "</div> \n";

         return $paginador;


         }
         
    }


?>