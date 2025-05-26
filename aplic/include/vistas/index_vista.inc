<?php
/*
    Nombre: index_vista.inc
    Autor: Julio Tuozzo.
    Función: Vista del inicio.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 25/05/2025.
*/

$css_local = "index.css";

require_once('head.inc');
?>

<script type='text/javascript' src='./js/index.js'></script>

<div id='index'>
<h1>¡Bienvenido!</h1>
<p>¿Necesitás vender y/u ofrecer las cosas que tenés en casa y no vas a usar, a tus amigos y conocidos?</p>
<p>¿Te da fiaca armar un documento con el listado y los precios?</p>
<p>¿Querés actualizar el listado y lo tenés que repartir de nuevo?</p>
<h2>¡Basta de sufrir!</h2>
<p></p>Con <strong>Mercado Dios Me Libre de las cosas que tengo en casa y no uso</strong> podés crear un listado de artículos para ofrecer a tus amigos y conocidos, y actualizarlo cuando quieras.</p>
<h2>¿Cómo?</h2>
<p>Fácil, tenés que <a href='usuario.php'>crear un usuario</a> y luego ingresas los artículos que vas a ofrecer.</p> 
<p>Podés subir fotos, precio, descripción y cambiarlo las veces que quieras, siempre lo van a tener actualizado!</p>
<p>Compartis el link del listado o el artículo con tus amigos y conocidos.</p>
<h3>Y listo!</h3>
<p>Útil y práctico, para la cartera de la dama y el bolsillo del caballero!</p>

</div>

<?php
require_once('foot.inc');
?>
