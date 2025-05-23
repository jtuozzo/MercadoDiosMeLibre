<?php
/*
    Nombre: User.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de manejo de usuarios.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 23/05/2025.
*/

require("Mail.inc");

class User
    {static public function getUser($email, $clave)
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

         // Existe el e-mail, genero una nueva clave

         $clave = $this->generaClave();

         // Armo el texto del e-mail con la nueva clave

         $link=substr($_SERVER['HTTP_REFERER'],0,strrpos($_SERVER['HTTP_REFERER'],"/"))."/cambiar_clave.php";

         $body = "Ha generado una nueva clave de acceso. <br />
                  Su nueva clave es: <strong>$clave</strong> <br /><br />
                  Ingrese al siguiente link <a href='$link'>$link</a> y cambie la clave por una que usted prefiera. <br /><br />
                  <strong>Recuerde que la clave es sensible a may&uacute;sculas y min&uacute;sculas.</strong> <br /><br />"; 

         // Mando el mail con la nueva clave
         $mail = new Mail;
         return $mail->sendMail($email,"Nueva clave",$body);

        }

    // Genera una nueva clave
    private function generaClave($digitos=10)
        {return substr(str_shuffle("123456789abcdefghijkmnopqrstuvwxyzABCDEFGHIJKLMNPQRSTUVWXYZ"), 0, $digitos);
        }
    }
?>
