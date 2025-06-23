<?php
/*
    Nombre: Utils.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos estáticos de uso global.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 23/06/2025.
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

*/

require("config_data.inc");

// Seteos varios
date_default_timezone_set('America/Argentina/Buenos_Aires');
ini_set('default_charset', 'utf-8');
error_reporting(E_ALL & ~E_NOTICE & ~E_DEPRECATED);



require("Mail.inc");
require("DBConecto.inc");

class Utils 
    {static public $dbase;
     static public $max_fotos = 10; // Cantidad máxima de fotos por artículo.
     static public $max_articulos = 8; // Cantidad máxima de artículos por página.
     static public $moneda = array("ARS" => "ARS Pesos", "USD" => "USD Dólares", "EUR" => "Euros"); // Monedas. Si se modifica este array hay que cambiar la estructura de articulo.moneda en la base de datos.


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
            {$result = self::$dbase->db->selectLimit($query, Utils::$max_articulos, $desde);
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


     static function paginador($pagina,$q_registros,$el_orden,$sentido,$id)
         {# $pagina: Página que estoy mostrando.
          # $q_registros: cantidad de registros de la consulta.
          # $el_orden: orden de los registros.
          # $sentido: Sentido ascendente o descendente.
          # $id: ID del llamador.

         if($q_registros<=Utils::$max_articulos)
            {return "";
            }

         $paginador = "\n <div class='paginado'>";

         if ($pagina>1)
            { $pag=$pagina-1;
               $paginador.= "<strong><a href='{$_SERVER['PHP_SELF']}?pagina=1&q_registros=$q_registros&el_orden=$el_orden&sentido=$sentido&id=$id'>
               <img src='./images/go-first.png' alt='<<||' border='0' /></a> &nbsp;
               <a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&el_orden=$el_orden&sentido=$sentido&id=$id'>
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

         for ($I=Utils::$max_articulos*($pag_desde-1), $pag=$pag_desde ; $I<$q_registros; $I=$I+Utils::$max_articulos, $pag++)
            { if ($pag==$pagina)
                     {$paginador.= "<strong>&nbsp;<big> $pag </big>&nbsp;</strong>";
                     }
               else
                     {$paginador.= "<a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&el_orden=$el_orden&sentido=$sentido&id=$id'> $pag </a> &nbsp; \n";
                     }

               if ($pag-$pag_desde>14)
                     {$paginador.= "......";
                     break;
                     }

            }


         if ($pagina<($q_registros/Utils::$max_articulos))
            {$pag=$pagina+1;
             $ultima=intval(($q_registros-1)/Utils::$max_articulos)+1;
             $paginador.= "&nbsp;
                  <a href='{$_SERVER['PHP_SELF']}?pagina=$pag&q_registros=$q_registros&el_orden=$el_orden&sentido=$sentido&id=$id'><strong>
                  <img src='./images/go-next.png' alt='|Sig.>' border='0' /></a> &nbsp;
                  <a href='{$_SERVER['PHP_SELF']}?pagina=$ultima&q_registros=$q_registros&el_orden=$el_orden&sentido=$sentido&id=$id'>
                  <img src='./images/go-last.png' alt='||>>' border='0' /></strong></a>";
            }

         $paginador.= "</div> \n";

         return $paginador;


         }
     
     static public function host() 
         {if (isset($_SERVER['HTTP_REFERER']))
            {return substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/";
            }
          else
            {return $_SERVER['REQUEST_SCHEME']."://".$_SERVER['SERVER_NAME']."/";
            }

          
         }
    }


?>