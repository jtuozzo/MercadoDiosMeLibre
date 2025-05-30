/*  Nombre: articulo_list.js
    Autor: Julio Tuozzo
    Función: Javascript del listado de artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 30/05/2025.
*/


function sin_articulos() {
    let header = $('#header').height();
    let alt = $(window).height() - header - 15;
    $('#list_articulos').css({ 'height': alt + 'px', 'overflow-y': 'auto' });
    $('#list_articulos').css('background-color', '#f0f0f0');
}

function copyClipp(value) {
    try {navigator.clipboard.writeText(value);
         window.alert('Copiado!');
        }
    catch(e) {
         $(".link").html(function(i, origText){
            return origText + ": <br/>" + value; });
        window.alert('No se pudo copiar, copielo manualmente');
    }

};