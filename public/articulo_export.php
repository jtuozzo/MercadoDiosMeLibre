<?php
/*
    Nombre: articulo_export.php
    Autor: Julio Tuozzo.
    Función: Exporta el listado de artículos a un archivo Excel (.xlsx).
    Fecha de creación: 22/07/2026.
    Ultima modificación: 22/07/2026.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Util\Utils;
use App\Controller\User;
use App\Controller\Articulo;
use PhpOffice\PhpSpreadsheet\Spreadsheet;
use PhpOffice\PhpSpreadsheet\Writer\Xlsx;
use PhpOffice\PhpSpreadsheet\Style\Alignment;
use PhpOffice\PhpSpreadsheet\Style\Fill;

$usuario = new User;
$usuario->setPermisos();

// Acá accede con la sesión del usuario o con el link de invitado

if((!isset($_SESSION['DML_NIVEL']) or $_SESSION['DML_NIVEL'] < 2) and (!isset($_GET['id'])))
     {// No tiene permisos para listar los artículos
      header("Location: index.php");
      exit;
     }

// Guardo los datos en variables
$id="";

foreach($_GET as $clave => $valor)
     {$$clave=trim(htmlentities($valor,ENT_QUOTES,'UTF-8'));
     }

$articulo = new Articulo();

if(strlen($id)>0)
     {$token = $id;
     }
elseif(isset($_SESSION['DML_TOKEN']))
     {$token = $_SESSION['DML_TOKEN'];
     }
else
     {// No hay token
      header("Location: index.php");
      exit;
     }

if(!$usuario->tokenValido($token))
     {// El token no es válido
      header("Location: index.php");
      exit;
     }

// Armo y ejecuto la consulta con todos los artículos del listado

$query = $articulo->queryArticulosExport($usuario->user_id);
$result = Utils::execute($query, __FILE__, __LINE__);

// Armo la planilla de Excel

$spreadsheet = new Spreadsheet();
$hoja = $spreadsheet->getActiveSheet();
$hoja->setTitle("Artículos");

// Cabecera de columnas
$columnas = array("Título", "Descripción", "Moneda", "Precio", "Estado", "Orden");
$hoja->fromArray($columnas, null, "A1");

// Estilo de la cabecera
$rango_cabecera = "A1:F1";
$hoja->getStyle($rango_cabecera)->getFont()->setBold(true)->getColor()->setARGB("FFFFFFFF");
$hoja->getStyle($rango_cabecera)->getFill()
     ->setFillType(Fill::FILL_SOLID)
     ->getStartColor()->setARGB("FFD22518");
$hoja->getStyle($rango_cabecera)->getAlignment()->setHorizontal(Alignment::HORIZONTAL_CENTER);

// Cargo los datos
$fila = 2;

while(!$result->EOF)
     {// Estado del artículo
      if($result->fields['vendido']=="S")
            {$estado = "Vendido";
            }
      elseif($result->fields['oculto']=="S")
            {$estado = "Oculto";
            }
      else
            {$estado = "En venta";
            }

      // Etiqueta de la moneda
      $moneda = $result->fields['moneda'];
      if(isset(Utils::$moneda[$moneda]))
            {$moneda = Utils::$moneda[$moneda];
            }

      $hoja->setCellValue("A$fila", $result->fields['titulo']);
      $hoja->setCellValue("B$fila", $result->fields['descripcion']);
      $hoja->setCellValue("C$fila", $moneda);
      $hoja->setCellValueExplicit("D$fila", $result->fields['precio'], \PhpOffice\PhpSpreadsheet\Cell\DataType::TYPE_NUMERIC);
      $hoja->setCellValue("E$fila", $estado);
      $hoja->setCellValueExplicit("F$fila", $result->fields['orden'], \PhpOffice\PhpSpreadsheet\Cell\DataType::TYPE_NUMERIC);

      $fila++;
      $result->moveNext();
     }

// Formato de la columna de precio y ancho de columnas
$hoja->getStyle("D2:D" . ($fila - 1))->getNumberFormat()->setFormatCode("#,##0.00");

foreach(range("A", "F") as $columna)
     {$hoja->getColumnDimension($columna)->setAutoSize(true);
     }

// Preparo la descarga del archivo

$nombre_archivo = "articulos_" . date("Y-m-d_H-i-s") . ".xlsx";

header("Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
header("Content-Disposition: attachment; filename=\"$nombre_archivo\"");
header("Cache-Control: max-age=0");

$writer = new Xlsx($spreadsheet);
$writer->save("php://output");
exit;
?>
