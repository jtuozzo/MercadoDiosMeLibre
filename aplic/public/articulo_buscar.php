<?php
require("Utils.inc");

foreach($_POST as $clave => $valor)
     {$$clave=trim($valor);
     }


$query = "SELECT articulo_id, titulo, moneda, precio, token
        FROM articulo art
        JOIN user usr ON art.user_id = usr.user_id AND usr.token = '$token'
        WHERE titulo LIKE '%$search%' "; 

$result = Utils::execute($query,__FILE__,__LINE__);

if($result->recordCount() == 0)
    {echo "<div class='autocomplete-item'> No se encontraron resultados </div> ";
     exit;
    }

while (!$result->EOF)
    {foreach ($result->fields as $key => $value)
        {$$key = $value;
        }


      echo "<div class='autocomplete-item' 
            data-articulo_id='$articulo_id'
            data-token='$token'
            data-titulo='$titulo'> $titulo  - $moneda $precio 
        </div>  ";
      $result->MoveNext();
    }


