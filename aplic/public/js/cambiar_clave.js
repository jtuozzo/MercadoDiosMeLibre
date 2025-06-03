/*  Nombre: cambiar_clave.js
    Autor: Julio Tuozzo
    Función: Javascript del login de usuario.
    Fecha de creación: 24/05/2025.
    Ultima modificación: 03/06/2025.
*/


window.onload = function() {
        setAlto('cambiar_clave');
    }

function changeNuevaClave() {
    if($('#ver_nueva_clave_img').attr('src')=='./images/ver.png')
        {$('#ver_nueva_clave_img').attr('src', './images/no_ver.png'); ~
         $('#nueva_clave').attr('type', 'text'); 
         
        }
    else
        {$('#ver_nueva_clave_img').attr('src', './images/ver.png'); 
         $('#nueva_clave').attr('type', 'password'); 
        }
    }