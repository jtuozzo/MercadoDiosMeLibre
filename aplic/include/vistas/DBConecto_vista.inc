<?php
/*
    Nombre: DBConecto_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del error de conexión con la base de datos y otros errores.
    Fecha de creación: 20/05/2025.
    Ultima modificación: 20/05/2025.
*/

$css_local="DBConecto.css";

require("head.inc");
				
echo "<div class='conect_error'>
        <img src='./images/el_grito.png' alt='Error de conexión'/>
        <h1>Error de conexión número {$linea}</h1> 
        <h2>Disculpe las molestias ocasionadas, lo solucionaremos a la brevedad</h2>
        <h2>Muchas gracias.</h2>
    </div>
";
				
require("foot.inc");

?>