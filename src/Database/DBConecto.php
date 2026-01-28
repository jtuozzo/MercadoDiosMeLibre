<?PHP
/*
    Nombre: DBConecto.php
    Autor: Julio Tuozzo
    Función: Definición de la clase de conexión con la base de datos.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 28/01/2026.
*/

namespace App\Database;

require_once __DIR__ . '/../../lib/adodb/adodb.inc.php';

class DBConecto
	{public $db;

	 public function __construct()
	 	{// Defino la conexión con la base de datos

		 $this->db = &ADONewConnection('mysqli');

		if (!$this->db->Connect(DB_HOST, DB_USER, DB_PASS, DB_BASE)) 
			{$this->db_error($this->db->ErrorMsg(),__FILE__,__LINE__);
			}

		$this->db->SetCharSet('utf8');
		$this->db->SetFetchMode(ADODB_FETCH_ASSOC);
		$this->db->Execute("SET NAMES 'utf8'");
		$this->db->Execute("SET CHARACTER SET 'utf8'");
		$this->db->Execute("SET SESSION collation_connection = 'utf8_general_ci'");

		}

       public function db_error($mensaje,$programa,$linea,$query="")
      		{$fecha=date("d/m/Y H:i:s");
			 // Si el query es muy largo, dejo los primeros 1000 caracteres y dejo los últimos 1000 caracteres
			 if(strlen($query)>2000)
				{$query=substr($query,0,1000)."   /....../   ".substr($query,-1000);
				}

			 // Armo el mensaje de error
       	 	 $error_msg="
$fecha Error acceso MySQL. programa: $programa, línea $linea
mensaje: $mensaje
";
             if (strlen($query)>1)
                  {$error_msg.="QUERY: $query
";

                  }
             $error_msg.="
============================================================================================================
";
           	    file_put_contents(LOGS."db_error_log.txt", $error_msg, FILE_APPEND | LOCK_EX);

				require(__DIR__ . '/../../resources/views/DBConecto_vista.php');

                exit();
             }

	}
?>
