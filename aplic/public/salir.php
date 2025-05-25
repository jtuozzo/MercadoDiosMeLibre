<?php
/*
    Nombre: salir.php
    Autor: Julio Tuozzo.
    Función: Controlador del logout del usuario.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 25/05/2025.
*/

session_start();

require("Utils.inc");

Utils::logout();

header("Location: index.php");