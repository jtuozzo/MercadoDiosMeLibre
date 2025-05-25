/*  Nombre: me_olvide.js
    Autor: Julio Tuozzo
    Función: Javascript de Me olvidé la clave.
    Fecha de creación: 23/05/2025.
    Ultima modificación: 25/05/2025.
*/


window.onload = function() {
        let header = $('#header').height();
        let alt=$(window).height()-header-10;
        $('#me_olvide').css({'height':alt+'px', 'overflow-y':'auto'});
    }

