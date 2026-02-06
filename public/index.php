<?php
/*
    Nombre: index.php
    Autor: Julio Tuozzo.
    Función: index.
    Fecha de creación: 17/05/2025.
    Ultima modificación: 06/02/2026.
*/

session_start();

require_once __DIR__ . '/../vendor/autoload.php';

use App\Controller\User;

$user = new User;

$user->setPermisos();


require(__DIR__ . '/../resources/views/index_vista.php');
?>