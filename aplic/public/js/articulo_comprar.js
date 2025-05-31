/*  Nombre: articulo_comprar.js
    Autor: Julio Tuozzo
    Función: Javascript de la compra del artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 31/05/2025.
*/


window.onload = function () {
    let header = $('#header').height();
    let alt = $(window).height() - header - 10;
    $('#comprar').css({ 'height': alt + 'px', 'overflow-y': 'auto' });
}

window.addEventListener('beforeunload', function (event) {
    $('#compro').val('Aguarde . . .');
    $('#compro').prop('disabled', true);
});

