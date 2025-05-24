<?php
/*
    Nombre: User.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de manejo de usuarios.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 24/05/2025.
*/

require("Mail.inc");

class User
    {public $st_clave = "";
     public $st_nueva_clave = "";
     public $st_reingresa = "";
     public $clave_err = "";
     public $nueva_clave_err = "";
     public $reingresa_err = "";
        
     static public function getUser($email, $clave)
        {$query = "SELECT user_id, apellidos, nombres, email, nivel, clave, token 
              FROM user 
              WHERE email='$email' 
              AND clave='$clave'";

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
                   SET last_login=NOW() 
                   WHERE email='$email'";

         $update = Utils::execute($query, __FILE__, __LINE__);

         return true;
        }

     public function nuevaClave($email)
        {// Genera una nueva clave y la envía al usuario

         // Verifico que el e-mail exista
         $query = "SELECT user_id
                   FROM user 
                   WHERE email='$email'";

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

         $body = "Generaste una nueva clave de acceso. <br />
                  Tu nueva clave es: <strong>$clave</strong> <br /><br />
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
            {$todo_ok = true;
                
             // Verifico que la clave actual sea correcta
             $clave_sha = hash("sha512", $clave);
             $query = "SELECT user_id 
                       FROM user 
                       WHERE clave='$clave_sha'";
    
            $result = Utils::execute($query, __FILE__, __LINE__);
    
            if($result->recordCount() == 0)
                {$todo_ok = false;             
                }
             else
                {$user_id=$result->fields["user_id"];
                }
    
            // Verifico que las nuevas claves coincidan
            if($nueva_clave != $reingresa)
                {$todo_ok = false;
                 $this->reingresa_err = "Las claves no coinciden.";
                 
                }
    
            // Actualizo la clave
            $nueva_clave_sha = hash("sha512", $nueva_clave);
            $query = "UPDATE user 
                    SET clave='$nueva_clave_sha',
                    expira_clave=DATE_ADD(NOW(), INTERVAL 90 DAY),
                    update_datetime=NOW(),
                    update_user='{$_SESSION['DML_USER_ID']}'
                    WHERE user_id='{$_SESSION['DML_USER_ID']}'";
            
            $result = Utils::execute($query, __FILE__, __LINE__);
            
            return $todo_ok;
            }
    }
?>
