<?php
/*
    Nombre: Utils.php
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos estáticos de uso global.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 28/01/2026.
*/

namespace App\Util;

use App\Database\DBConecto;
use App\Mail\Mail;

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

require_once __DIR__ . '/../../config/dataconf.php';

// Seteos varios
date_default_timezone_set('America/Argentina/Buenos_Aires');
ini_set('default_charset', 'utf-8');
error_reporting(E_ALL & ~E_NOTICE & ~E_DEPRECATED);

class Utils
    {static public $dbase;
     static public $max_fotos = 10; // Cantidad máxima de fotos por artículo.
     static public $max_articulos = 16; // Cantidad máxima de artículos por página.
     static public $moneda = array("ARS" => "ARS Pesos", "USD" => "USD Dólares", "EUR" => "Euros"); // Monedas. Si se modifica este array hay que cambiar la estructura de articulo.moneda en la base de datos.


      // Funcióm que ejecuta una consulta SQL y devuelve el resultado.

     static public function execute($query, $file, $line)
        {if(!isset(self::$dbase))
            {self::$dbase = new DBConecto();
            }

         if(!$result = self::$dbase->db->Execute($query))
            {self::$dbase->db_error(self::$dbase->db->ErrorMsg(),$file,$line,$query);
            return false;
            }
         return $result;
        }

     // Función que ejecuta una consulta SQL en un rango de registros y devuelve el resultado.
     static public function selectLimit($query, $desde, $file, $line)
        {if(!isset(self::$dbase))
            {self::$dbase = new DBConecto();
            }

         if(!$result = self::$dbase->db->selectLimit($query, Utils::$max_articulos, $desde))
            {self::$dbase->db_error(self::$dbase->db->ErrorMsg(),$file,$line,$query);
             return false;
            }
         return $result;
        }


      // Función que inicia una transacción
      static public function startTrans($file, $line)
         {if(!isset(self::$dbase))
               {self::$dbase = new DBConecto();
               }

          if(!self::$dbase->db->StartTrans())
               {self::$dbase->db_error(self::$dbase->db->ErrorMsg(),$file,$line);
               }
         }

      // Función que completa una transacción
      static public function completeTrans($file, $line)
         {if(!isset(self::$dbase))
               {self::$dbase = new DBConecto();
               }

          if(!self::$dbase->db->CompleteTrans())
               {self::$dbase->db_error(self::$dbase->db->ErrorMsg(),$file,$line);
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

     static public function hayNovedades()
         {// Busca si hay novedades que no se avisaron y envía un mensaje a los usuarios.

          $query = "SELECT sig.siguiendo_id, sigo_a.nombres, sigo_a.apellidos, sigo_a.token, usr.email
                    FROM siguiendo sig
                    JOIN user sigo_a ON sigo_a.user_id = sig.siguiendo_a
                    JOIN user usr ON usr.user_id = sig.user_id
                    WHERE sig.activo='S'
                    AND sig.avisar_novedades='S'";

          $result = self::execute($query, __FILE__, __LINE__);

          if($result->recordCount() > 0)
               {$mail = new Mail;
                while(!$result->EOF)
                     {foreach($result->fields as $clave => $valor)
                           {$$clave = htmlentities($valor,ENT_QUOTES,"UTF-8");
                           }
                     $result->moveNext();

                     // Envío el mensaje de novedades

                     $body = "Hola!!,<br /><br />
                              Hay novedades en los artículos que estás siguiendo de $nombres $apellidos. <br /><br />
                              Ingresá a <a href='".Utils::host()."articulo_list.php?id=$token'>MercadoDiosMeLibre</a> para verlos.<br />";


                      if($mail->sendMail($email, "Novedades en artículos", $body))
                           {// Actualizo el aviso de novedades
                            $query = "UPDATE siguiendo
                                      SET avisar_novedades=NULL,
                                      update_datetime=NOW()
                                      WHERE siguiendo_id='$siguiendo_id'";

                            $update = self::execute($query, __FILE__, __LINE__);
                           }
                     }
               }

         }


     static private function fecha_valida($fecha_hora)
         {list($fecha, $hora)=explode(' ',$fecha_hora); ## separo la fecha de la hora.


         if(strlen(trim($fecha))>10) ## La fecha y la hora no estaban separadas por espacio
            {return false;
            }

         if(!preg_match('#([0-9]{2})/([0-9]{2})/([0-9]{4})#', $fecha, $array_fecha)) ## controlo si la fecha tiene un formato válido
            {return false;
            }

         list($fecha, $dia, $mes, $anio)=$array_fecha;  ## separo día, mes y anio en variables identificables

         if($mes<1 or $mes>12) ## valido el mes
            {return false;
            }

      ## Valido los días de Febrero

         if(self::anio_bisiesto($anio))
            {$febrero=29;
            }
         else
            {$febrero=28;
            }

         if (($mes==2) and (($dia<1) or ($dia>$febrero)))
            {return false;
            }

      ## Valido los meses de 30 días

         if ((($mes==4) or ($mes==6) or ($mes==9) or ($mes==11)) and (($dia<1) or ($dia>30)))
            {return false;
            }

      ## Valido los meses de 31 días

         if ((($mes==1) or ($mes==3) or ($mes==5) or ($mes==7) or ($mes==8) or ($mes==10) or ($mes==12)) and (($dia<1) or ($dia>31)))
            {return false;
            }

      ## Me fijo si hay hora y la valido
         if (strlen(trim($hora))>0)
            {if(!preg_match('#([0-9]{2}):([0-9]{2}):([0-9]{2})#', $hora, $array_hora))  // veo si la hora tiene un formato válido
                  { return false;
                  }

            }
         list($hora, $hor, $min, $seg)=$array_hora;  // separo horas, minutos y segundos en variables identificables

         if($hor<0 or $hor>23)  // valido la hora
            { return false;
            }

         if($min<0 or $min>59)  // valido los minutos
            { return false;
            }

         if($seg<0 or $seg>59)  // valido los segundos
            {return false;
            }

         return true;
         }

     static private function anio_bisiesto($anio)
            {
            if ($anio % 4 != 0)
               {return false;
               }
            else
               {if ($anio % 100 == 0)
                     {if ($anio % 400 == 0)
                        {return true;
                        }
                     else
                           {return false;
                           }
                     }
               else
                     {return true;
                     }
               }
            }


      static public function fecha_format ($fecha)
         {## fecha_format (fecha en formato ISO Y-m-d H:i:s)
          ## pasa la fecha de formato ISO al español dd/mm/yyyy hh:mm:ss

         $fecha=substr($fecha,8,2).'/'.substr($fecha,5,2).'/'.substr($fecha,0,4).substr($fecha,10);
         if (self::fecha_valida($fecha))
            {return $fecha;
            }
         else
            {return "";
            }
         }


     static public function error_log($mensaje,$programa,$linea)
         {// Log de errores generales

          $fecha=date("d/m/Y H:i:s");
          $error_msg="\n$fecha Error programa: $programa, línea $linea
mensaje: $mensaje
============================================================================================================";

         file_put_contents(LOGS."error_log.txt", $error_msg, FILE_APPEND | LOCK_EX);

			require(__DIR__ . '/../../resources/views/DBConecto_vista.php');
			exit();
         }
    }

?>
