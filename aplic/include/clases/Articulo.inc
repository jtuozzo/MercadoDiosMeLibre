<?php
/*
    Nombre: Articulo.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de los artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 21/07/2025.
*/

#[AllowDynamicProperties]
class Articulo
    {public $articulo_id = 0;
     public $titulo = "";
     public $descripcion = "";
     public $moneda = "";
     public $precio = "";
     public $user_id = "";
     public $vendido = "";
     public $orden = 0;
     public $oculto = "";
     public $st_titulo = "";
     public $st_descripcion = "";
     public $st_precio = "";
     public $st_orden = "";
     public $titulo_err = "";
     public $descripcion_err = "";
     public $precio_err = "";
     public $orden_err = "";
     public $foto = "";
     public $foto_tipo_file = "";
     public $las_fotos = array();
     public $vista = ""; // Define el tipo de vista de artículo que va a haber
     public $chk_vendido;
     public $chk_oculto;
     public $token = "";

     private $campos_check = array("vendido", "oculto");

     

     public function __construct()
         {for($i = 1; $i <= Utils::$max_fotos; $i++)
               {$foto_err = "foto_err_{$i}";
                $st_foto = "st_foto_$i";
                $this->$foto_err = "";
                $this->$st_foto = "";
               }
          $this->orden = 0;
         }
      
     public function validoID($articulo_id, $token)
         {$query = "SELECT articulo_id
                    FROM articulo art
                    JOIN user usr ON usr.user_id=art.user_id AND usr.token='$token'
                    WHERE art.articulo_id='$articulo_id'";
          
          $result = Utils::execute($query, __FILE__, __LINE__);

          if($result->recordCount()==1)
               {$this->token = $token;
                return $articulo_id;
               }
          else
               {return null;
               }
         }
      
     public function crearArticulo($fotos)
         {
          if($this->validoArticulo())
             {// Inicio la transacción
                Utils::startTrans(__FILE__, __LINE__);

               $titulo = Utils::$dbase->db->Quote(html_entity_decode($this->titulo,ENT_QUOTES,"UTF-8"));
               $descripcion = Utils::$dbase->db->Quote(html_entity_decode($this->descripcion,ENT_QUOTES,"UTF-8"));
   
               // Inserto el artículo en la base de datos
               
               $query = "INSERT INTO articulo VALUES
                        (NULL,
                        '{$_SESSION['DML_USER_ID']}',
                        $titulo,
                        $descripcion,
                        '{$this->moneda}',
                        '{$this->precio}',
                        '{$this->vendido}',
                         NULL,
                        '{$this->oculto}',
                        '{$this->orden}',
                        '{$_SESSION['DML_USER_ID']}',
                        NOW(),
                        '{$_SESSION['DML_USER_ID']}',
                        NOW())";
               
               $query =str_replace("''", "NULL", $query); 
               $result = Utils::execute($query, __FILE__, __LINE__);

               $articulo_id = mysqli_insert_id(Utils::$dbase->db->_connectionID);

               // Guarda las fotos
               $this->insertFotos($articulo_id, $fotos);
              
               // Informa que hubo novedades en el artículo de ese usuario.
               $this->hayNovedades();

               // Fin de la transacción
               Utils::completeTrans(__FILE__, __LINE__);
               return true;
             }
          else
             {return false;
             }
          
          
         }

      public function modifArticulo($fotos_actuales, $fotos_nuevas)
            {if(!$this->validoArticulo())
                  {return false;
                  }
             
             // Inicio la transacción
             Utils::startTrans(__FILE__, __LINE__);
             
             // Veo si hay que eliminar de la base de datos alguna de las fotos

             $query ="SELECT articulo_foto_id
                      FROM articulo_foto
                      WHERE articulo_id='{$this->articulo_id}'";

             $result = Utils::execute($query, __FILE__, __LINE__);
             
             while (!$result->EOF)
                  {if(!in_array($result->fields['articulo_foto_id'], $fotos_actuales))
                        {$query="DELETE FROM articulo_foto
                                 WHERE articulo_foto_id='{$result->fields['articulo_foto_id']}'";
                         
                         $delete = Utils::execute($query, __FILE__, __LINE__);
                        }
                   $result->moveNext();
                  }


             // Modifico los datos en la tabla de artículos
             $titulo = Utils::$dbase->db->Quote(html_entity_decode($this->titulo,ENT_QUOTES,"UTF-8"));
             $descripcion = Utils::$dbase->db->Quote(html_entity_decode($this->descripcion,ENT_QUOTES,"UTF-8"));
             
             $query = "UPDATE articulo SET
                       titulo=$titulo,
                       descripcion = $descripcion,
                       moneda = '{$this->moneda}',
                       precio = '{$this->precio}',
                       vendido = '{$this->vendido}',
                       orden = '{$this->orden}',
                       oculto = '{$this->oculto}',
                       update_user='{$_SESSION['DML_USER_ID']}',
                       update_datetime=NOW()
                       WHERE articulo_id='{$this->articulo_id}'";
             
             $query =str_replace("''", "NULL", $query);
             $result = Utils::execute($query, __FILE__, __LINE__);

             // Inserto las fotos nuevas
             $this->insertFotos($this->articulo_id, $fotos_nuevas);

             // Informa que hubo novedades en el artículo de ese usuario.
             $this->hayNovedades();

             // Fin de la transacción
             Utils::completeTrans(__FILE__, __LINE__);
             return true;
            }

      private function hayNovedades()
         {// Informa que hubo novedades en el artículo de ese usuario.
          $query = "UPDATE siguiendo    
                    SET avisar_novedades = 'S',
                    update_datetime=NOW()
                    WHERE siguiendo_a='{$_SESSION['DML_USER_ID']}'
                    AND activo='S'";

          $result = Utils::execute($query, __FILE__, __LINE__);
          return;
         }

      private function validoArticulo()
         {// Inicializo precio y check
          $this->precio = str_replace(",",".", $this->precio);

          foreach($this->campos_check as $campo)
               {$aux="chk_".$campo;
                if($this->$campo=='S')
                    {$this->$aux="checked='checked'";
                    }
               else
                    {$this->$aux="";
                    }

               }
          

          $todo_ok = true;
          $obligatorios = array('titulo', 'descripcion', 'precio');

         // Valido los campos obligatorios
         foreach($obligatorios as $campo)
            {if(empty($this->$campo))
               {$this->{$campo . '_err'} = "<span class='error'>Campo obligatorio.</span>";
                $this->{'st_' . $campo} = "class='st_error'";
                $todo_ok = false;
               }
            }

          if(!is_numeric($this->precio) or $this->precio <= 0)
             {$this->precio_err = "<span class='error'>El precio debe ser un número positivo.</span>";
              $this->st_precio = "class='st_error'";
              $todo_ok = false;
             }

          if(!is_numeric($this->orden) or $this->orden < 0)
               {$this->orden_err = "<span class='error'>Debe ser un número positivo.</span>";
               $this->st_orden = "class='st_error'";
               $todo_ok = false;
               }

           return $todo_ok;
          }
      private function armoFotos($fotos)
         {$tmp = array();
          $foto_tamanio = array();
          $foto_tipo_file = array();
          $foto_nombre_file = array();
          $foto = array();
          $las_fotos = array();
            
          for($i = 1; $i <= Utils::$max_fotos; $i++)
               {if(isset($fotos[$i]) and strlen($fotos[$i]['tmp_name'])>0)
                  {$tmp[$i] = $fotos[$i]['tmp_name'];
                   $foto_tamanio[$i] = $fotos[$i]['size'];
                   $foto_tipo_file[$i] = $fotos[$i]['type'];
                   $foto_nombre_file[$i] = $fotos[$i]['name'];
                        
                  if(strlen($foto_nombre_file[$i])>0)
                              {// Valido si el adjunto es un jpg ó jpeg para comprimirlo

                              $nombre_aux=strtolower($foto_nombre_file[$i]);
                              $extension=substr($nombre_aux,strrpos($nombre_aux, "." )+1);

                              if(($extension=="jpg" or $extension=="jpeg") and exif_imagetype($tmp[$i])==IMAGETYPE_JPEG)
                                 {$nombre_tmp="adjunto_".date("Y_m_d_H_i_s").".jpg";
                                 $im = imagecreatefromjpeg($tmp[$i]);
                                 $im = imagescale($im,800,-1,IMG_BILINEAR_FIXED);

                                 // Arreglo la orientación de la imagen
                                 $exif = @exif_read_data($tmp[$i]);
                                 if(!empty($exif['Orientation']))
                                    {switch($exif['Orientation'])
                                         {case 3:
                                              $im = imagerotate($im, 180, 0);
                                              break;
                                          case 6:
                                              $im = imagerotate($im, -90, 0);
                                              break;
                                          case 8:
                                              $im = imagerotate($im, 90, 0);
                                              break;
                                         }
                                    }

                                 imagejpeg($im,TMP.$nombre_tmp);
                                 $fp = fopen(TMP.$nombre_tmp, "rb");
                                 $foto[$i] = fread($fp,filesize(TMP.$nombre_tmp));
                                 $foto[$i] = addslashes($foto[$i]);
                                 fclose($fp); 
                                 unlink(TMP.$nombre_tmp);
                                 }
                              elseif($extension=="png" and exif_imagetype($tmp[$i])==IMAGETYPE_PNG)
                                 {$nombre_tmp="adjunto_".date("Y_m_d_H_i_s").".png";
                                  $im = imagecreatefrompng($tmp[$i]);
                                  $im = imagescale($im,700,-1,IMG_BILINEAR_FIXED);
                                  imagepng($im,TMP.$nombre_tmp);
                                  $fp = fopen(TMP.$nombre_tmp, "rb");
                                  $foto[$i] = fread($fp,filesize(TMP.$nombre_tmp));
                                  $foto[$i] = addslashes($foto[$i]);
                                  fclose($fp); 
                                  unlink(TMP.$nombre_tmp);
                                 }
                              else
                                 {$fp = fopen($tmp[$i], "rb");
                                    $foto[$i] = fread($fp, $foto_tamanio[$i]);
                                    $foto[$i] = addslashes($foto[$i]);
                                    fclose($fp);
                                 }
                              }
                        $las_fotos[$i] = array(
                                                'foto' => $foto[$i],
                                                'tamanio' => $foto_tamanio[$i],
                                                'tipo_file' => $foto_tipo_file[$i],
                                                'nombre_file' => $foto_nombre_file[$i]
                                             );
                        }

                    

                   }
      
                 return $las_fotos;

         }

   private function insertFotos($articulo_id, $fotos)
         {// Preparo el array con las fotos
          $las_fotos = $this->armoFotos($fotos);

          // Inserta las fotos en la base de datos
          for($i = 1; $i <= Utils::$max_fotos; $i++)
               {if(isset($las_fotos[$i]) and strlen($las_fotos[$i]['foto'])>0)
                  {// Inserto la foto en la base de datos
                     $query = "INSERT INTO articulo_foto VALUES
                              (NULL,
                              '$articulo_id',
                               NULL,
                              '{$las_fotos[$i]['foto']}',
                              '{$las_fotos[$i]['tipo_file']}',
                              '{$_SESSION['DML_USER_ID']}',
                              NOW(),
                              '{$_SESSION['DML_USER_ID']}',
                              NOW())";

                     $query =str_replace("''", "NULL", $query);
                     $result = Utils::execute($query, __FILE__, __LINE__);
                  }
               }

          // Marco la foto principal

          $query="UPDATE articulo_foto
                  SET principal='S'
                  WHERE articulo_foto_id= (SELECT MIN(articulo_foto_id) 
                                           FROM articulo_foto
                                           WHERE articulo_id='$articulo_id')";

          $result = Utils::execute($query, __FILE__, __LINE__);

          return;
         }


    public function countArticulos($user_id)
         {// Si es el usuario que está sesionado cuenta todos los artículos, si no, excluye los ocultos
          if(isset($_SESSION['DML_USER_ID']) and $user_id==$_SESSION['DML_USER_ID'])
               {$excluyo_ocultos="";
               }
          else
               {$excluyo_ocultos="AND oculto IS NULL";
               }

          $query = "SELECT articulo_id
                    FROM articulo
                    WHERE user_id='$user_id'
                    $excluyo_ocultos";

          $result = Utils::execute($query,__FILE__,__LINE__);

          return $result->recordCount();
         }
    
    public function queryArticulos($user_id, $el_orden, $sentido) 
         {// Si es el usuario que está sesionado cuenta todos los artículos, si no, excluye los ocultos
          if(isset($_SESSION['DML_USER_ID']) and $user_id==$_SESSION['DML_USER_ID'])
               {$excluyo_ocultos="";
               }
          else
               {$excluyo_ocultos="AND oculto IS NULL";
               }

          return "SELECT DISTINCT ar.articulo_id, ar.titulo, ar.descripcion, ar.moneda, ar.precio, ar.vendido, ar.vendido_el, af.articulo_foto_id, ar.oculto, ar.orden
                  FROM articulo ar
                  LEFT JOIN articulo_foto af ON af.articulo_id=ar.articulo_id AND af.principal='S'
                  WHERE user_id='$user_id'
                  $excluyo_ocultos
                  ORDER BY $el_orden $sentido";
         }

    public function getFoto($articulo_foto_id=0,$token="")
         {// Trae una foto del artículo

          $query="SELECT foto, foto_tipo_file
                  FROM articulo_foto af
                  JOIN articulo art ON art.articulo_id=af.articulo_id
                  JOIN user usr ON usr.user_id=art.user_id AND usr.token='$token'
                  WHERE articulo_foto_id='$articulo_foto_id'";
          
          $result = Utils::execute($query,__FILE__,__LINE__);

          if($result->recordCount()==1)
               {foreach($result->fields as $clave=>$valor)
                  {$this->$clave=$valor;
                  }
                return true;
               }   
          else 
               {return false;
               }

         }

    public function getArticulo($articulo_id)
         {if(!isset($articulo_id) or !is_numeric($articulo_id))
               {return false;
               }
          
          // Trae los datos de un artículo

          $query = "SELECT articulo_id, user_id, titulo, descripcion, moneda, precio, vendido, oculto, orden
                    FROM articulo 
                    WHERE articulo_id='$articulo_id'";

          $result = Utils::execute($query,__FILE__,__LINE__);

          if($result->recordCount()==0)
               {return false;
               }
            
          foreach($result->fields as $campo=>$valor)
               {$this->$campo=htmlentities($valor,ENT_QUOTES,"UTF-8");
               }


          // Inicializo los checks
          foreach($this->campos_check as $campo)
               {$aux="chk_".$campo;
                if($this->$campo=='S')
                    {$this->$aux="checked='checked'";
                    }
               else
                    {$this->$aux="";
                    }

               }


          // Busco las fotos

          $query = "SELECT articulo_foto_id
                    FROM articulo_foto
                    WHERE articulo_id='$articulo_id'
                    ORDER BY principal DESC, articulo_foto_id";

          $result = Utils::execute($query,__FILE__,__LINE__);
          $i=0;
          while(!$result->EOF)
               {$i++;

                $this->las_fotos[$i]=$result->fields['articulo_foto_id'];

                $result->moveNext();
               }
          return true;
         }
   }


    
Class Compra extends Articulo
   {public $registrado = false;
    public $articulo_compra_id = 0;
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
    public $repetida = false;
    public $salio_email = true;

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
                $this->activo = "S";
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
                             '{$this->activo}',
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
                     SET activo='S',
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

Class Ventas extends Compra 
     {public function countVentas($user_id)
          {$query = "SELECT articulo_compra_id
                     FROM articulo_compra ac
                     JOIN articulo art ON art.articulo_id=ac.articulo_id
                     WHERE art.user_id='$user_id'
                     AND ac.activo='S'";

           $result = Utils::execute($query,__FILE__,__LINE__);

           return $result->recordCount();

          }

      public function queryVentas($user_id, $el_orden, $sentido="ASC")
          {return "SELECT DISTINCT art.titulo, art.moneda, art.precio, art.vendido, af.articulo_foto_id, art.articulo_id
                   FROM articulo_compra ac
                   JOIN articulo art ON art.articulo_id=ac.articulo_id
                   LEFT JOIN articulo_foto af ON af.articulo_id=art.articulo_id AND af.principal='S'
                   WHERE art.user_id='$user_id'
                   AND ac.activo='S'
                   ORDER BY $el_orden $sentido";
          }

      public function getCompradores($articulo_id)
          {
           $query = "SELECT ac.apellidos, ac.nombres, ac.email, ac.whatsapp, ac.comentarios, ac.insert_datetime
                     FROM articulo_compra ac
                     WHERE ac.articulo_id='$articulo_id'
                     AND ac.activo='S'";

           return Utils::execute($query,__FILE__,__LINE__);
          }
     }

?>
