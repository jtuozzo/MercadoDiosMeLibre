<?php
/*
    Nombre: Compra.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de una compra.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 31/05/2025.
*/

    
Class Compra
   {public $registrado = false;
    public $apellidos = "";
    public $nombres = "";
    public $email = "";
    public $whatsapp = "";
    public $comentarios = "";
    public $activo = "";
    public $apellidos_err = "";
    public $nombres_err = "";
    public $email_err = "";
    public $whatsapp_err = "";
    public $comentarios_err = "";
    public $st_apellidos = "";
    public $st_nombres = "";
    public $st_email = "";
    public $st_whatsapp = "";
    public $st_comentarios = "";
    public $user_id = "";
    
    private $obligatorios = array('apellidos', 'nombres', 'email', 'whatsapp');

    public function __construct() 
         {foreach($this->obligatorios as $valor)
               {$valor = $valor."_err";
                $this->$valor = "<span class='obligatorio'>(*)</span>";
               }
          
          
          
          if(isset($_SESSION['DML_USER_ID']))
               {$this->registrado = true;
                $this->email = $_SESSION['DML_EMAIL'];
                $this->apellidos = $_SESSION['DML_APELLIDOS'];
                $this->nombres = $_SESSION['DML_NOMBRES'];
                $this->activo = "S";
                $this->user_id = $_SESSION['DML_USER_ID'];
               }
         }

    public function crearCompra($articulo_id)
          {if ($this->validoCompra())
                 {$query = "INSERT INTO articulo_compra VALUES 
                            (NULL,
                             '{$articulo_id}',
                             '{$this->user_id}',
                             '{$this->apellidos}',
                             '{$this->nombres}',
                             '{$this->email}',
                             '{$this->whatsapp}',
                             '{$this->comentarios}',
                             '{$this->activo}',
                             NOW(),
                             NOW()
                            )";
                   $query =str_replace("''", "NULL", $query);
                   $result = Utils::execute($query, __FILE__, __LINE__);

                   return true;
                 }
           return false;
          }


    public function validoCompra()
          {$todo_ok = true;

          // Valido los campos obligatorios
          foreach($this->obligatorios as $campo)
               {if(empty($this->$campo))
                    {$this->{$campo . '_err'} = "<span class='error'>Campo obligatorio.</span>";
                     $this->{'st_' . $campo} = "class='st_error'";
                     $todo_ok = false;
                    }
               }
           if($todo_ok and !filter_var($this->email, FILTER_VALIDATE_EMAIL))
               {$this->email_err = "<span class='error'>Formato inválido</span>";
                $this->st_email = "class='st_error'";
                $todo_ok = false;
               }

           if(strlen($this->whatsapp)>0 and !preg_match("^\+?[1-9]\d{1,14}$^",$this->whatsapp))
               {$this->whatsapp_err = "<span class='error'>Formato inválido</span>";
                $this->st_whatsapp = "class='st_error'";
                $todo_ok = false;
               }


               
           return $todo_ok;
          }      
   }
?>
