/*  Nombre: usuario.js
    Autor: Julio Tuozzo
    Función: Javascript de nuevo usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 25/05/2025.
*/


window.onload = function() {
        let header = $('#header').height();
        let alt=$(window).height()-header;
        $('#usuario').css({'height':alt+'px', 'overflow-y':'auto'}); alert(alt); alert(header);
    }

