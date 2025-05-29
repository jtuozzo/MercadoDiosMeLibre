<?php
/*
    Nombre: Articulo.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de los artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 29/05/2025.
*/

#[AllowDynamicProperties]
class Articulo
    {public $articulo_id = 0;
     public $st_titulo = "";
     public $st_descripcion = "";
     public $st_precio = "";
     public $sel_ARS = "";
     public $sel_USD = "";
     public $titulo_err = "";
     public $descripcion_err = "";
     public $precio_err = "";
     public $solo_en_venta = true;
     public $foto = "";
     public $foto_tipo_file = "";
     public $las_fotos = array();
     public $titulo = "";
     public $descripcion = "";
     public $moneda = "";
     public $precio = "";
     public $user_id = "";
     public $vista = ""; // Define el tipo de vista de artículo que va a haber

     

     public function __construct()
         {for($i = 1; $i <= MAX_FOTOS; $i++)
               {$foto_err = "foto_err_{$i}";
                $st_foto = "st_foto_$i";
                $this->$foto_err = "";
                $this->$st_foto = "";
               }

         }
      
      
     public function crearArticulo($titulo, $descripcion, $moneda, $precio, $fotos)
         {// Inicializo el select del tipo de moneda
          $aux="sel_{$moneda}";
          $this->$aux = "selected='selected'";
          $precio = str_replace(",",".", $precio);

          if($this->validoArticulo($titulo,$descripcion,$precio))
             {// Inicio la transacción
                Utils::startTrans(__FILE__, __LINE__);

               $titulo = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($titulo,ENT_QUOTES,"UTF-8"));
               $descripcion = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($descripcion,ENT_QUOTES,"UTF-8"));
   
               // Inserto el artículo en la base de datos
               
               $query = "INSERT INTO articulo VALUES
                        (NULL,
                        '{$_SESSION['DML_USER_ID']}',
                        '$titulo',
                        '$descripcion',
                        '$moneda',
                        '$precio',
                        'S',
                        NULL,
                        '{$_SESSION['DML_USER_ID']}',
                        NOW(),
                        '{$_SESSION['DML_USER_ID']}',
                        NOW())";
               
               $query =str_replace("''", "NULL", $query);
               $result = Utils::execute($query, __FILE__, __LINE__);

               $articulo_id = mysqli_insert_id(Utils::$dbase->db->_connectionID);

               // Preparo el array con las fotos
               $las_fotos = $this->armoFotos($fotos);
               // Guarda las fotos
               $this->insertFotos($articulo_id, $las_fotos);
              

               // Fin de la transacción
               Utils::completeTrans(__FILE__, __LINE__);
               return true;
             }
          else
             {return false;
             }
          
          
         }

      public function modifArticulo($articulo_id, $titulo, $descripcion, $moneda, $precio, $fotos_actuales, $fotos_nuevas)
            {$precio = str_replace(",",".", $precio);
             if(!$this->validoArticulo($titulo, $descripcion, $precio))
                  {return false;
                  }
             
             // Inicio la transacción
             Utils::startTrans(__FILE__, __LINE__);
             
             // Veo si hay que eliminar de la base de datos alguna de las fotos

             $query ="SELECT articulo_foto_id
                      FROM articulo_foto
                      WHERE articulo_id='$articulo_id'";

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
             $titulo = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($titulo,ENT_QUOTES,"UTF-8"));
             $descripcion = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($descripcion,ENT_QUOTES,"UTF-8"));
             
             $query = "UPDATE articulo SET
                       titulo='$titulo',
                       descripcion = '$descripcion',
                       moneda = '$moneda',
                       precio = '$precio',
                       update_user='{$_SESSION['DML_USER_ID']}',
                       update_datetime=NOW()";

             $result = Utils::execute($query, __FILE__, __LINE__);

             // Inserto las fotos nuevas

             $this->insertFotos($articulo_id, $fotos_nuevas);
             // Fin de la transacción
             Utils::completeTrans(__FILE__, __LINE__);
             return true;
            }

      private function validoArticulo($titulo, $descripcion, $precio)
         {$todo_ok = true;
          $obligatorios = array('titulo', 'descripcion', 'precio');

         // Valido los campos obligatorios
         foreach($obligatorios as $campo)
            {if(empty($$campo))
               {$this->{$campo . '_err'} = "<span class='error'>Campo obligatorio.</span>";
                $this->{'st_' . $campo} = "class='st_error'";
                $todo_ok = false;
               }
            }

          if(!is_numeric($precio) || $precio <= 0)
             {$this->precio_err = "<span class='error'>El precio debe ser un número positivo.</span>";
              $this->st_precio = "class='st_error'";
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
            
          for($i = 1; $i <= count($fotos); $i++)
               {if(strlen($fotos[$i]['tmp_name'])>0)
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

                                 imagejpeg($im,TMP.$nombre_tmp,20);
                                 $fp = fopen(TMP.$nombre_tmp, "rb");
                                 $foto[$i] = fread($fp,filesize(TMP.$nombre_tmp));
                                 $foto[$i] = addslashes($foto[$i]);
                                 fclose($fp); 
                                 unlink(TMP.$nombre_tmp);
                                 }
                              elseif($extension=="png" and exif_imagetype($tmp[$i])==IMAGETYPE_PNG)
                                 {$nombre_tmp="adjunto_".date("Y_m_d_H_i_s").".png";
                                  $im = imagecreatefrompng($tmp[$i]);
                                  imagepng($im,TMP.$nombre_tmp,9);
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

   private function insertFotos($articulo_id, $las_fotos)
         {
          // Inserta las fotos en la base de datos
          for($i = 1; $i <= count($las_fotos); $i++)
               {if(strlen($las_fotos[$i]['foto'])>0)
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
         {$query = "SELECT articulo_id
                    FROM articulo
                    WHERE user_id='$user_id'";

          $result = Utils::execute($query,__FILE__,__LINE__);

          return $result->recordCount();
         }
    
    public function queryArticulos($user_id, $orden, $sentido) 
         {if($this->solo_en_venta)
               {$en_venta=" AND en_venta='S'";
               }
          else
               {$en_venta="";
               }

          return "SELECT DISTINCT ar.articulo_id, ar.titulo, ar.descripcion, ar.moneda, ar.precio, ar.en_venta, ar.vendido_el, af.articulo_foto_id
                  FROM articulo ar
                  LEFT JOIN articulo_foto af ON af.articulo_id=ar.articulo_id AND af.principal='S'
                  WHERE user_id='$user_id'
                  $en_venta
                  ORDER BY $orden $sentido";
         }

    public function getFoto($articulo_foto_id=0)
         {// Trae una foto del artículo

          $query="SELECT foto, foto_tipo_file
                  FROM articulo_foto
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
         {if(!is_numeric($articulo_id))
               {return false;
               }
          
          // Trae los datos de un artículo

          $query = "SELECT articulo_id, user_id, titulo, descripcion, moneda, precio
                    FROM articulo 
                    WHERE articulo_id='$articulo_id'";

          $result = Utils::execute($query,__FILE__,__LINE__);

          if($result->recordCount()==0)
               {return false;
               }
            
          foreach($result->fields as $campo=>$valor)
               {$this->$campo=htmlentities($valor,ENT_QUOTES,"UTF-8");
               }

          // Inicializo el select del tipo de moneda
          $aux="sel_{$this->moneda}";
          $this->$aux = "selected='selected'";

          // Busco las fotos

          $query = "SELECT articulo_foto_id
                    FROM articulo_foto
                    WHERE articulo_id='$articulo_id'
                    ORDER BY principal DESC";

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
    
?>
