<?php
/*
    Nombre: Articulo.inc
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de los artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 26/05/2025.
*/


class Articulo
    {    
      public function crearArticulo($titulo, $descripcion, $moneda, $precio, $foto)
         {if(empty($titulo) || empty($descripcion) || empty($moneda) || empty($precio))
             {return false;
             }
          
          // Escapo los datos
          
          $titulo = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($titulo,ENT_QUOTES,"UTF-8"));
          $descripcion = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,html_entity_decode($descripcion,ENT_QUOTES,"UTF-8"));
          $moneda = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,$moneda);
          $precio = mysqli_real_escape_string(Utils::$dbase->db->_connectionID,$precio);
          
          // Inserto el artículo en la base de datos
          
          $query = "INSERT INTO articulo (titulo, descripcion, moneda, precio, foto, user_id, create_datetime)
                    VALUES ('$titulo', '$descripcion', '$moneda', '$precio', '$foto', '{$_SESSION['DML_USER_ID']}', NOW())";
          
          $result = Utils::execute($query, __FILE__, __LINE__);
          
          return true;
         }
    }
?>
