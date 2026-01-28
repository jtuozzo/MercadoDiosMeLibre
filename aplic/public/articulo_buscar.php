<?php
/*
    Nombre: articulo_buscar.php
    Autor: Julio Tuozzo.
    Función: Busca los artículos.
    Fecha de creación: 27/01/2026.
    Ultima modificación: 28/01/2026.
*/
session_start();

require("Utils.inc");

foreach($_POST as $clave => $valor)
     {$$clave=trim($valor);
     }

// Coloco el filtro si el usuario no está buscando sus artículos

if(empty($_SESSION['DML_TOKEN']) or $_SESSION['DML_TOKEN']!=$token)
    {$filtro = " AND oculto IS NULL";
    }
else
    {$filtro = "";
    }

$query = "SELECT articulo_id, titulo, moneda, precio, token, art.vendido
        FROM articulo art
        JOIN user usr ON art.user_id = usr.user_id AND usr.token = '$token'
        WHERE titulo LIKE '%$search%' 
        $filtro
        ORDER BY titulo ASC"; 

$result = Utils::execute($query,__FILE__,__LINE__);

if($result->recordCount() == 0)
    {echo "<div class='autocomplete-item'> No se encontraron resultados </div> ";
     exit;
    }

while (!$result->EOF)
    {foreach ($result->fields as $key => $value)
        {$$key = $value;
        }

      if(empty($vendido))
            {$importe = number_format($precio,2,',','.');
             $importe = "$moneda $importe";
            }
        else
            {$importe = "<span class='vendido_label'>VENDIDO</span>";
            }
    

      echo "<div class='autocomplete-item' 
            data-articulo_id='$articulo_id'
            data-token='$token'
            data-titulo='$titulo'> $titulo  - $importe
        </div>  ";
      $result->MoveNext();
    }


