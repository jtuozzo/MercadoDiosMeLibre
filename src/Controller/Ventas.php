<?php
/*
    Nombre: Ventas.php
    Autor: Julio Tuozzo.
    Función: Definición de los atributos y métodos de las ventas.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 28/01/2026.
*/

namespace App\Controller;

use App\Util\Utils;

Class Ventas extends Compra
     {public function countVentas($user_id)
          {$query = "SELECT COUNT(DISTINCT art.articulo_id) as cuantos
                     FROM articulo_compra ac
                     JOIN articulo art ON art.articulo_id=ac.articulo_id
                     WHERE art.user_id='$user_id'";

           $result = Utils::execute($query,__FILE__,__LINE__);

           return $result->fields['cuantos'];

          }

      public function queryVentas($user_id, $el_orden, $sentido="ASC")
          {return "SELECT DISTINCT art.titulo, art.moneda, art.precio, art.vendido, af.articulo_foto_id, art.articulo_id
                   FROM articulo_compra ac
                   JOIN articulo art ON art.articulo_id=ac.articulo_id
                   LEFT JOIN articulo_foto af ON af.articulo_id=art.articulo_id AND af.principal='S'
                   WHERE art.user_id='$user_id'
                   ORDER BY $el_orden $sentido";
          }

      public function getCompradores($articulo_id)
          {
           $query = "SELECT ac.articulo_compra_id, ac.apellidos, ac.nombres, ac.email, ac.whatsapp, ac.comentarios, ac.confirmado, ac.insert_datetime
                     FROM articulo_compra ac
                     WHERE ac.articulo_id='$articulo_id'";

           return Utils::execute($query,__FILE__,__LINE__);
          }

      public function deleteComprador($articulo_compra_id)
          {$query = "DELETE FROM articulo_compra
                     WHERE articulo_compra_id='$articulo_compra_id'";

           return Utils::execute($query,__FILE__,__LINE__);
          }
     }

?>
