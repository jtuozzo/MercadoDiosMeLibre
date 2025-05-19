<?php
/*
    Nombre: Utils.inc
    Autor: Julio Tuozzo.
    Función: Inicialización de variables y utilidades generales.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 19/05/2025.
*/

// Datos de la instalación

/* Conexión con las bases de datos

define('DB_HOST', '');
define('DB_USER', '');
define('DB_PASS', '');
define('DB_BASE', '');

# Carpeta de logs

define('LOGS', './carpeta/');

*/

require("config_data.inc");

// Seteo zona horaria
date_default_timezone_set('America/Argentina/Buenos_Aires');

// Conecto con la base de datos
require("DBConecto.inc");
$dbase = new DBConecto();

?>