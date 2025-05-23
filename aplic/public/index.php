<?php
/*
    Nombre: index.php
    Autor: Julio Tuozzo.
    Función: index.
    Fecha de creación: 17/05/2025.
    Ultima modificación: 19/05/2025.
*/

session_start();

require("Utils.inc");

// Veo si el usuario está guardado en el dispositivo

if(!isset($_SESSION['DML_NIVEL']) and isset($_COOKIE['DML_EMAIL']) and isset($_COOKIE['DML_CLAVE']))
    {$hay_usuario=User::getUser($_COOKIE['DML_EMAIL'], $_COOKIE['DML_CLAVE']);
     
     if($hay_usuario)
        {// Prorrogo por 30 días la cookie
         setcookie('DML_EMAIL', $_COOKIE['DML_EMAIL'], time()+60*60*24*30);
         setcookie('DML_CLAVE', $_COOKIE['DML_CLAVE'], time()+60*60*24*30);
        }
     else
        {// Los datos de la cookie no son válidos, la borro
         unset($_COOKIE['DML_EMAIL']);
         unset($_COOKIE['DML_CLAVE']);
         setcookie('DML_EMAIL', '', time()-3600);
         setcookie('DML_CLAVE', '', time()-3600);
        }
    }

require("head.inc");
require("foot.inc");

?>