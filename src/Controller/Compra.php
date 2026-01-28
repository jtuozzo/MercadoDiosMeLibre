<?php
/*
    Nombre: Compra.php
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de las compras.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 28/01/2026.
*/

namespace App\Controller;

use App\Util\Utils;
use App\Mail\Mail;

Class Compra extends Articulo
   {public $registrado = false;
    public $articulo_compra_id = 0;
    public $apellidos = "";
    public $nombres = "";
    public $email = "";
    public $whatsapp = "";
    public $comentarios = "";
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
    public $repetida = false;
    public $salio_email = true;
    public $confirmado = "";

    private $comprador_user_id = "";
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
                $this->confirmado = "S";
                $this->comprador_user_id = $_SESSION['DML_USER_ID'];
               }


         }

    public function crearCompra()
          {if ($this->validoCompra())
                 {$apellidos = Utils::$dbase->db->Quote(html_entity_decode($this->apellidos,ENT_QUOTES,"UTF-8"));
                  $nombres = Utils::$dbase->db->Quote(html_entity_decode($this->nombres,ENT_QUOTES,"UTF-8"));
                  $comentarios = Utils::$dbase->db->Quote(html_entity_decode($this->comentarios,ENT_QUOTES,"UTF-8"));

                  $query = "INSERT INTO articulo_compra VALUES
                            (NULL,
                             '{$this->articulo_id}',
                             '{$this->comprador_user_id}',
                             $apellidos,
                             $nombres,
                             '{$this->email}',
                             '{$this->whatsapp}',
                             $comentarios,
                             '{$this->confirmado}',
                             NOW(),
                             NOW()
                            )";
                   $query =str_replace("''", "NULL", $query);
                   $result = Utils::execute($query, __FILE__, __LINE__);

                   $this->articulo_compra_id = mysqli_insert_id(Utils::$dbase->db->_connectionID);

                   if(!$this->registrado )
                         {if(!$this->envioMailConfirmacion())
                              {// No pudo enviar el mail con el aviso, invalida la compra
                               $query = "UPDATE articulo_compra
                                         SET email = 'INVALID_{{$this->email}}'
                                         WHERE articulo_compra_id='{$this->articulo_compra_id}'";
                               $result = Utils::execute($query, __FILE__, __LINE__);

                               $this->salio_email = false;
                               return false;
                              }
                          return true;
                         }
                   else
                         {$this->envioMailCompra();
                          return true;
                         }

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

           // Valido que no esté la misma compra solicitada

           if(!empty($this->comprador_user_id))
               {$query = "SELECT articulo_id
                          FROM articulo_compra
                          WHERE articulo_id='{$this->articulo_id}'
                          AND user_id='{$this->comprador_user_id}'";
               }

           else
               {$query = "SELECT articulo_id
                          FROM articulo_compra
                          WHERE articulo_id='{$this->articulo_id}'
                          AND email='{$this->email}'";
               }

           $result = Utils::execute($query, __FILE__, __LINE__);

           if($result->recordCount()>0)
               {$todo_ok = false;
                $this->repetida = true;
               }

           return $todo_ok;
          }

     private function envioMailConfirmacion()
          {// Envío el e-mail de confirmación
           $mail = new Mail;
           $link=Utils::host()."confirmar_compra.php?id={$this->articulo_compra_id}&key={$this->articulo_id}&email={$this->email}";
           $link_user=Utils::host()."usuario.php";

               $body = "Has solicitado comprar: <strong>{$this->titulo}.</strong> <br /><br />

                         Para confirmar la compra, hac&eacute; click en el siguiente link: <a href='$link' target='_blank'>$link</a> <br /><br />
                         En el futuro si querés saltear este paso de verificación, podés crear tu usuario aquí: <a href='$link_user' target='_blank'>$link_user</a><br /><br />

                         Muchas gracias! <br />";

               return $mail->sendMail($this->email, "Confirmá la compra", $body);

          }

     private function envioMailCompra()
          {// Busco el mail del dueño del artículo

           $query = "SELECT email
                     FROM user us
                     JOIN articulo art ON art.user_id=us.user_id
                     WHERE art.articulo_id='{$this->articulo_id}'";

           $result = Utils::execute($query,__FILE__,__LINE__);
           if($result->recordCount()!=1)
               {return false;
               }

           // Envío el e-mail de confirmación
           $mail = new Mail;

           $body = "Han solicitado comprar: <strong>{$this->titulo}.</strong> <br /><br />

                    Podés verla en <strong>Mis ventas</strong>.<br /><br />

                    Muchas gracias! <br />";

           return $mail->sendMail($result->fields['email'], "Tenés una nueva compra!", $body);
          }

      public function confirmarCompra($id, $key, $email)
          {$query = "UPDATE articulo_compra
                     SET confirmado='S',
                     update_datetime = NOW()
                     WHERE articulo_compra_id='$id'
                     AND articulo_id='$key'
                     AND email='$email'";

           $result= Utils::execute($query,__FILE__,__LINE__);

           if(Utils::$dbase->db->affected_rows() == 1)
                {$this->getArticulo($key);
                 $this->envioMailCompra();
                 return true;
                }
           else
                {return false;
                }
          }

     }

?>
