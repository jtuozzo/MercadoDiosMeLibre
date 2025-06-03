/*  Nombre: main.js
    Autor: Julio Tuozzo
    Función: Javascript principal.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 03/06/2025.
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

function setMail() {

    let eMail = 'mercadodiosmelibre.com.ar';
    eMail = 'info' + '@' + eMail;
    $('#emailTo').html('<a href="mailto:' + eMail +'">'+ eMail + '</a>'); 
}

function setAlto(seccion)
    {let header = $('#header').height()+15;
     let footer = $('#footer').height()+15;
     let alt=$(window).height()-header-footer; 
     $('#' + seccion).css({'height':alt+'px', 'overflow-y':'auto'}); 

    }

function changeClave() {
    if($('#ver_clave_img').attr('src')=='./images/ver.png')
        {$('#ver_clave_img').attr('src', './images/no_ver.png'); ~
         $('#clave').attr('type', 'text'); 
         
        }
    else
        {$('#ver_clave_img').attr('src', './images/ver.png'); 
         $('#clave').attr('type', 'password'); 
        }
}