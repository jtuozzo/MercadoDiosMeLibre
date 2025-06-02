/*  Nombre: articulo_comprar.js
    Autor: Julio Tuozzo
    Función: Javascript de la compra del artículo.
    Fecha de creación: 31/05/2025.
    Ultima modificación: 01/06/2025.
*/


window.onload = function () {
    setAlto('comprar');
}

window.addEventListener('beforeunload', function (event) {
    $('#compro').val('Aguarde . . .');
    $('#compro').prop('disabled', true);
});

