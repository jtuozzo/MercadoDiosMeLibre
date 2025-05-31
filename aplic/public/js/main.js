/*  Nombre: main.js
    Autor: Julio Tuozzo
    Función: Javascript principal.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 31/05/2025.
*/

function toggleMenu() {
    $("#barraNavUl").toggleClass('mostrar');
}

function ocultoID(id) {
    $("#" + id).hide();
}

function copyClipp(value) {
    try {
        navigator.clipboard.writeText(value);
        window.alert('Copiado!');
    }
    catch (e) {
        $('.link').html(function (i, origText) {
            return origText + ": <br/>" + value;
        });
        $('.link').removeAttr('onclick');
        $('.link').css({ 'cursor' : 'default'});
        window.alert('No se pudo copiar, cópielo manualmente');
    }

};