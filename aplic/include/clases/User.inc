<?php
/*
    Nombre: User.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de manejo de usuarios.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 04/06/2025.
*/

class User
    {public $st_clave = "";
     public $st_nueva_clave = "";
     public $st_reingresa = "";
     public $clave_err = "";
     public $nueva_clave_err = "";
     public $reingresa_err = "";
     public $st_nombres = "";
     public $st_apellidos = "";
     public $st_email = "";
     public $nombres_err = "";
     public $apellidos_err = "";
     public $email_err = "";
     public $send_mail_err = "";
     public $msg_error = "";
     public $user_id;
     public $nombres;
        
     static public function getUser($email, $clave)
        {$query = "SELECT user_id, apellidos, nombres, email, nivel, clave, token 
              FROM user 
              WHERE email='$email' 
              AND clave='$clave'
              AND expira_clave > NOW()
              AND token IS NOT NULL";

        $result = Utils::execute($query, __FILE__, __LINE__);

        if($result->recordCount() == 0)
            {return false;
            }

        // Inicializo las variables de sesión del usuario

        foreach($result->fields as $key => $valor)
            {$_SESSION["DML_".strtoupper($key)]=$valor;
            }
        
         // Guardo la última sesión

         $query = "UPDATE user 
                   SET last_login=NOW(),
                   ip_address='".Utils::getIP()."'
                   WHERE email='$email'";

         $update = Utils::execute($query, __FILE__, __LINE__);

         return true;
        }

     public function nuevaClave($email)
        {// Genera una nueva clave y la envía al usuario

         // Verifico que el e-mail exista y se haya confirmado
         $query = "SELECT user_id
                   FROM user 
                   WHERE email='$email'
                   AND token IS NOT NULL";

         $result = Utils::execute($query, __FILE__, __LINE__);

         if($result->recordCount() == 0)
            {return true;
            }
         else
            {$user_id=$result->fields["user_id"];
            }

         // Existe el e-mail, genero una nueva clave

         while($result->recordCount() > 0)
            {// Verifico que la clave no exista

             $clave = $this->generaClave();
             $clave_sha = hash("sha512", $clave);
             $query = "SELECT user_id
                       FROM user 
                       WHERE clave='$clave_sha'";
             
             $result = Utils::execute($query, __FILE__, __LINE__);
    
            }
         
        
         // Armo el texto del e-mail con la nueva clave

         $link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/cambiar_clave.php?id=$email";

         $body = "Generaste una clave de acceso. <br />
                  Tu clave es: <strong>$clave</strong> <br /><br />
                  Ingres&aacute; al siguiente link <a href='$link'>$link</a> y cambi&aacute; esta clave. <br /><br />
                  <strong>Record&aacute; que la clave es sensible a may&uacute;sculas y min&uacute;sculas.</strong> <br /><br />"; 

         // Mando el mail con la nueva clave
         $mail = new Mail;
         if($mail->sendMail($email,"Nueva clave",$body))
            {// Actualizo la clave en la base de datos
             $clave=hash("sha512", $clave);
             $query = "UPDATE user 
                       SET clave='$clave',
                       expira_clave=SUBDATE(NOW(), INTERVAL 1 DAY),
                       update_datetime=NOW(),
                       update_user='$user_id'
                       WHERE user_id='$user_id'";
             $result = Utils::execute($query, __FILE__, __LINE__);
             return true;
            }
         else
            {return false;
            }

        }

    // Genera una nueva clave
    private function generaClave($digitos=10)
        {return substr(str_shuffle("123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNPQRSTUVWXYZ"), 0, $digitos);
        }

    // Método que cambia la clave

      public function cambiarClave($clave, $nueva_clave, $reingresa)
            {   
             if(strlen($clave)==0)
                {
                 $this->st_clave="class='st_error'";
                 $this->clave_err="<br/><span class='error'>Debe ingresar la clave actual</span>";
                 return false;
                }

            // Verifico que la clave actual sea correcta
            $clave_sha = hash("sha512", $clave);
            $query = "SELECT user_id 
                  FROM user 
                  WHERE clave='$clave_sha'";

            $result = Utils::execute($query, __FILE__, __LINE__);
   
            if($result->recordCount() == 0)
               {$this->st_clave="class='st_error'";
                $this->clave_err="<br/><span class='error'>La clave actual es incorrecta</span>";
                return false;
               }
                
               
            // Verifico que la clave nueva no sea igual a la actual
            if($clave == $nueva_clave)
                  {$this->st_nueva_clave="class='st_error'";
                   $this->nueva_clave_err="<br/><span class='error'>La nueva clave no puede ser igual a la actual</span>";
                   return false;
                  }

            if(strlen($nueva_clave) == 0)
                {// Verifico que la nueva clave no esté vacía
                 $this->st_nueva_clave="class='st_error'";
                 $this->nueva_clave_err="<br/><span class='error'>Debe ingresar una nueva clave</span>";
                 return false;
                }

            if(strlen($nueva_clave) < 8)
                  {// Verifico que la nueva clave tenga al menos 8 caracteres
                  $this->st_nueva_clave="class='st_error'";
                  $this->nueva_clave_err="<br/><span class='error'>Debe tener al menos 8 caracteres</span>";
                  return false;
                  }

            // Verifico que la clave tenga caracteres válidos
            if(!preg_match("/^[a-zA-Z0-9\!\@\#\$\^\&\*\-\_\+\=\{\}\[\]\:\;\"\'\<\>\,\.\?\/\\\|]+$/", $nueva_clave))
                  {$this->st_nueva_clave="class='st_error'";
                   $this->nueva_clave_err="<br/><span class='error'>La nueva clave contiene caracteres inválidos</span>";
                   return false;
                  }
                  
            // Verifico que las nuevas claves coincidan
            if($nueva_clave != $reingresa)
               {$this->st_reingresa="class='st_error'";
                $this->reingresa_err="<br/><span class='error'>No coincide con la nueva clave</span>";
                return false;
               }
      
            // Actualizo la clave
            $nueva_clave_sha = hash("sha512", $nueva_clave);
            $query = "UPDATE user 
                  SET clave='$nueva_clave_sha',
                  expira_clave=DATE_ADD(NOW(), INTERVAL 90 DAY),
                  update_datetime=NOW(),
                  update_user=user_id
                  WHERE clave='$clave_sha'";
      
            $result = Utils::execute($query, __FILE__, __LINE__);
            
            return true;
            }

      public function crearUsuario($nombres, $apellidos, $email, $clave, $reingresa)
            {// Crea un nuevo usuario
             $todo_ok=true;
             // Verifico que el nombre no esté vacío
             if(strlen($nombres) == 0)
                  {$this->st_nombres="class='st_error'";
                   $this->nombres_err="<br/><span class='error'>Debe ingresar un nombre</span>";
                   $todo_ok = false;
                  }

             // Verifico que el apellido no esté vacío
             if(strlen($apellidos) == 0)
                  {$this->st_apellidos="class='st_error'";
                   $this->apellidos_err="<br/><span class='error'>Debe ingresar un apellido</span>";
                   $todo_ok = false;
                  }

             // Verifico que el e-mail no esté vacío
             if(strlen($email) == 0)
                  {$this->st_email="class='st_error'";
                   $this->email_err="<br/><span class='error'>Debe ingresar un e-mail</span>";
                   $todo_ok = false;
                  }

             // Verifico que el e-mail sea válido
             elseif(!filter_var($email, FILTER_VALIDATE_EMAIL))
                {$this->st_email="class='st_error'";
                 $this->email_err="<br/><span class='error'>Formato de e-mail incorrecto</span>";
                 $todo_ok = false;
                }

             // Verifico que el e-mail no exista
             $query = "SELECT user_id 
                       FROM user 
                       WHERE email='$email'";

             $result = Utils::execute($query, __FILE__, __LINE__);

             if($result->recordCount() > 0)
                {$this->st_email="class='st_error'";
                 $this->email_err="<br/><span class='error'>El e-mail ya está registrado</span>";
                 $todo_ok = false;
                }

           if(strlen($clave) == 0)
                {// Verifico que la clave no esté vacía
                 $this->st_clave="class='st_error'";
                 $this->clave_err="<br/><span class='error'>Debe ingresar una clave</span>";
                 return false;
                }

            elseif(strlen($clave) < 8)
                  {// Verifico que la clave tenga al menos 8 caracteres
                  $this->st_clave="class='st_error'";
                  $this->clave_err="<br/><span class='error'>Debe tener al menos 8 caracteres</span>";
                  return false;
                  }

            // Verifico que la clave tenga caracteres válidos
            elseif(!preg_match("/^[a-zA-Z0-9\!\@\#\$\^\&\*\-\_\+\=\{\}\[\]\:\;\"\'\<\>\,\.\?\/\\\|]+$/", $clave))
                  {$this->st_clave="class='st_error'";
                   $this->clave_err="<br/><span class='error'>La clave contiene caracteres inválidos</span>";
                   return false;
                  }
                  
            // Verifico que las nuevas claves coincidan
            elseif($clave != $reingresa)
               {$this->st_reingresa="class='st_error'";
                $this->reingresa_err="<br/><span class='error'>No coincide con la clave</span>";
                return false;

               }
             
             // Si todo está bien, creo el usuario
 
             if($todo_ok)
                {// Envío el e-mail de confirmación
                   $mail = new Mail;
                   
                   $link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/confirmar_usuario.php?id=$email";
                   
                   $body = "Te registraste en el sitio <strong>Mercado Dios Me Libre de las cosas que tengo en casa y no uso.</strong> <br /><br />
                            
                            Para terminar el proceso, hac&eacute; click en el siguiente link: <a href='$link'>$link</a> <br /><br />
                            
                            Muchas gracias por registrarte! <br />";
                   
                    if(!$mail->sendMail($email, "Confirmación de registro", $body))
                        {// Si no se pudo enviar el e-mail, muestro un mensaje de error
                        $todo_ok = false;
                        $this->send_mail_err="No se pudo crear el usuario.";
                        }
                   else
                      {// Se envió el e-mail, guardo el usuario en la base de datos
                        $nombres=mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($nombres,ENT_QUOTES,"UTF-8"));
                        $apellidos=mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($apellidos,ENT_QUOTES,"UTF-8"));
                        $clave=html_entity_decode($clave,ENT_QUOTES,"UTF-8");
                        $clave_sha = hash("sha512", $clave);

                        $query = "INSERT INTO user VALUES 
                                 (NULL,
                                 '$apellidos', 
                                 '$nombres', 
                                 '$email', 
                                 10,
                                 '$clave_sha', 
                                 ADDDATE(NOW(), INTERVAL 90 DAY),
                                 NULL,
                                 NULL,
                                 '".Utils::getIP()."',
                                 NULL,
                                 NOW(),
                                 NULL,
                                 NOW())";

                        $result = Utils::execute($query, __FILE__, __LINE__);

                     }
               }

             return $todo_ok;
            }
      public function confirmarUsuario($email)
            {// Confirma el usuario
             $query = "UPDATE user 
                       SET token=SHA2(CONCAT(email, NOW()), 256), 
                       update_datetime=NOW(), 
                       update_user=user_id 
                       WHERE email='$email'
                       AND token IS NULL";

             $result = Utils::execute($query, __FILE__, __LINE__);

             if(Utils::$dbase->db->affected_rows() == 1)
                {return true;
                }
             else
                {// Por alguna razón que ignoro Hotmail llama dos veces a este script, así que chequeo este tema

                 $query = "SELECT user_id 
                           FROM user 
                           WHERE email='$email' 
                           AND token IS NOT NULL
                           AND update_datetime > DATE_SUB(NOW(), INTERVAL 2 second)";

                 $result = Utils::execute($query, __FILE__, __LINE__);

                 if($result->recordCount() == 1)
                    {// El usuario ya está confirmado
                     return true;
                    }
                   else
                     {// El usuario no existe o ya está confirmado
                        $this->msg_error="El usuario ya está confirmado o no existe.";
                        return false;
                     }   

                 
                }
            }
      public function tokenValido($token)
            {// Verifica si el token es válido
             $query = "SELECT user_id, nombres
                       FROM user 
                       WHERE token='$token' 
                       AND nivel > 0";

             $result = Utils::execute($query, __FILE__, __LINE__);

             if($result->recordCount() == 1)
                {foreach($result->fields as $clave=>$valor)
                     {$this->$clave=htmlentities($valor,ENT_QUOTES,"UTF-8");
                     }
                  
                 return true;
                }
             else
                {return false;
                }
            }

      public function siguiendo($token)
            {// Indica si un usuario está siguiendo las publicaciones de otro.

             if(!isset($_SESSION['DML_USER_ID']))
                  {return false;
                  }

             $query = "SELECT siguiendo_id
                       FROM siguiendo sig
                       JOIN user us ON us.user_id = sig.siguiendo_a AND us.token='$token'
                       WHERE user_id='{$_SESSION['DML_USER_ID']}'";

             $result = Utils::execute($query, __FILE__, __LINE__);

             if($result->recordCount() == 1)
                  {foreach($result->fields as $clave=>$valor)
                        {$this->$clave=htmlentities($valor,ENT_QUOTES,"UTF-8");
                        }
                     
                  return true;
                  }
             else
                  {return false;
                  }
            }
    }
?>
