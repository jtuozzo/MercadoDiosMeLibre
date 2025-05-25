<?php
/*
    Nombre: head.inc
    Autor: Julio Tuozzo.
    Función: Header de las páginas.
    Fecha de creación: 17/05/2025.
    Ultima modificación: 25/05/2025.
*/

$saludo="";
// Verifica el nivel de acceso para mostrar el menú correspondiente

if (isset($_SESSION['DML_NIVEL']) and $_SESSION['DML_NIVEL'] > 0) 
    {$menu_bar = "<li><a href='articulo_nuevo.php'>Nuevo artículo</a></li>
                  <li class='li_derecha'><a href='login.php'>Salir</a></li>";
    
    if(isset($_SESSION['DML_NOMBRES']))
        {$saludo = "Hola {$_SESSION['DML_NOMBRES']}!";
         }

     }
else {$menu_bar = "<li class='li_derecha'><a href='usuario.php' >Crear usuario</a></li>
                  <li class='li_derecha'><a href='login.php'>Ingresar</a></li>";
    
     }

// Incluyo el CSS local si es que existe
if (isset($css_local)) 
    {$css_local = "<link rel='stylesheet' href='./css/$css_local'>";
    } 
else 
    {$css_local = "";
    }

echo "
<!DOCTYPE html>
<html lang='es'>

<head>
    <meta charset='UTF-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <link rel='shortcut icon' href='./images/favicon.ico' type='image/x-icon' />
    <link rel='preconnect' href='https://fonts.googleapis.com'>
    <link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>
    <link href='https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,100..900;1,100..900&display=swap' rel='stylesheet'>
    <link rel='stylesheet' href='./css/main.css'>
    <link rel='stylesheet' href='./sweetalert/sweetalert2.min.css' type='text/css' charset='utf-8' />
    <script type='text/javascript' src='./sweetalert/sweetalert2.all.min.js'></script>
    {$css_local}
    <script type='text/javascript' src='./js/jquery-3.7.1.min.js'></script>
    <script type='text/javascript' src='./js/main.js'></script>
    <title>Mercado Dios Me Libre</title>
</head>

<body>
    <header id='header'>
        <div class='logo'>
            <a href='index.php'>
                <img id='logo' src='./images/logo_455_175.png' alt='Mercado Dios Me Libre de las cosas que tengo en casa y no uso' title='Mercado Dios Me Libre de las cosas que tengo en casa y no uso'>
            </a>
            <div id='saludo'>
                {$saludo}
            </div>
        </div>

        <nav id='barraNav'>
            <div id='burger-menu' onclick='toggleMenu()'>
                <img src='./images/burger.png' alt='menu' />
            </div>
            <ul id='barraNavUl'>
                <li>
                    <a href='index.php'>Home</a>
                </li>
                {$menu_bar}
            </ul>
        </nav>
    </header>
";
?>