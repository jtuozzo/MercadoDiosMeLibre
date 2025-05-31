/*  Nombre: articulo_list.js
    Autor: Julio Tuozzo
    Función: Javascript del listado de artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 31/05/2025.
*/


function sin_articulos() {
    let header = $('#header').height();
    let alt = $(window).height() - header - 15;
    $('#list_articulos').css({ 'height': alt + 'px', 'overflow-y': 'auto' });
    $('#list_articulos').css('background-color', '#f0f0f0');
    $('.link').hide();
    $('h2').css('background-color', '#f0f0f0');
}

