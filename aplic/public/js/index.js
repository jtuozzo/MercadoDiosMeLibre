/*  Nombre: index.js
    Autor: Julio Tuozzo
    Función: Javascript de Inicio.
    Fecha de creación: 25/05/2025.
    Ultima modificación: 25/05/2025.
*/


window.onload = function() {
        let header = $('#header').height();
        let alt=$(window).height()-header-10; 
        $('#index').css({'height':alt+'px', 'overflow-y':'auto'}); 
    }

