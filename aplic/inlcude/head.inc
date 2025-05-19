<?php
/*
    Nombre: head.inc
    Autor: Julio Tuozzo.
    Función: Header de las páginas.
    Fecha de creación: 17/05/2025.
    Ultima modificación: 19/05/2025.
*/
?>

<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="./css/general.css">
    <title>Mercado Dios Me Libre</title>
</head>

<body>
    <header>
        <div id="logo">
            <a href="/">
                <img src="./images/logo_455_175.png" alt="Mercado Dios Me Libre de las cosas que tengo en casa y no uso" title="Mercado Dios Me Libre de las cosas que tengo en casa y no uso">
            </a>
        </div>
        <nav id="barraNav">
            <div class="burger-menu">
                <i class="fas fa-bars"></i>
            </div>
            <ul id="barraNavUl" class="">
                <li>
                    <a href="/">Home</a>
                </li>
                <li>
                    <a href="/products/create">Crear producto</a>
                </li>
                <li>
                    <a href="/products">Tienda</a>
                </li>
                <li>
                    <a href="/register">Registro</a>
                </li>
                <li>
                    <a href="/login">Login</a>
                </li>
                <li>
                    <a href="/perfil">Hola,</a>
                </li>
            </ul>
    </nav>
    </header>