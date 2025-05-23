<?php
/*
    Nombre: User.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de manejo de usuarios.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 23/05/2025.
*/


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
    }

?>
