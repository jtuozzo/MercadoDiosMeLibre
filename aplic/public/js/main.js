/*  Nombre: main.js
    Autor: Julio Tuozzo
    Función: Javascript principal.
    Fecha de creación: 19/05/2025.
    Ultima modificación: 30/05/2025.
*/

function toggleMenu() {
    $("#barraNavUl").toggleClass('mostrar');
}

function ocultoForm() {
    $("#form").hide();
}

function copyClipp(value) {
    try {navigator.clipboard.writeText(value);
         window.alert('Copiado!');
        }
    catch(e) {
         $(".link").html(function(i, origText){
            return origText + ": <br/>" + value; });
        window.alert('No se pudo copiar, cópielo manualmente');
    }

};