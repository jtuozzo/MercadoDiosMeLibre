<?PHP
/*
    Nombre: DBConecto.inc
    Autor: Julio Tuozzo
    Función: Definición de la clase de conexión con la base de datos.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 19/05/2025.
*/
require('adodb.inc.php');

class DBConecto
	{public $db;

	 public function __construct()
	 	{// Defino la conexión con la base de datos
		 
		 $ADODB_FETCH_MODE=ADODB_FETCH_ASSOC;

		 $this->db = &ADONewConnection('mysqli');

		 if (!$this->db->connect(DB_HOST,DB_USER,DB_PASS,DB_BASE))
        		{$this->db_error($this->db->ErrorMsg(),__FILE__,__LINE__);
        		}
		 else 
			{
			 $this->db->SetCharSet('utf8');
			 $this->db->SetFetchMode(ADODB_FETCH_ASSOC);
			 $this->db->Execute("SET NAMES 'utf8'");
			 $this->db->Execute("SET CHARACTER SET 'utf8'");
			 $this->db->Execute("SET SESSION collation_connection = 'utf8_general_ci'");
			}
		 }
	

       public function db_error($mensaje,$programa,$linea,$query="")
      		{$fecha=date("d/m/Y H:i:s");
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
				
				$css_local="DBConecto.css";
 	            require("head.inc");
				
				echo "<div class='conect_error'>
						<h1>Error de conexión número {$linea}</h1> 
						<h2>Disculpe las molestias ocasionadas, lo solucionaremos a la brevedad</h2>
						<h2>Muchas gracias.</h2>
					</div>
				";
				
				require("foot.inc");
                exit();
             }

	}
?>
