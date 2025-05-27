/*  Nombre: articulo.js
    Autor: Julio Tuozzo
    Función: Javascript del artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 26/05/2025.
*/


window.onload = function () {
    let header = $('#header').height();
    let alt = $(window).height() - header - 10;
    $('#articulo').css({ 'height': alt + 'px', 'overflow-y': 'auto' });
}

window.addEventListener('beforeunload', function (event) {
     $('#crear').val('Aguarde . . .');
     $('#crear').prop('disabled', true);
});


function addFoto(max_fotos) {
    for (i = 1; i <= max_fotos; i++) {
        let foto = 'foto_' + i;
        if (i == max_fotos) {
            $('#nueva_foto').hide(500);

        }
        if ($('#id_' + foto).is(':hidden')) {
            $('#id_' + foto).show(500);
            break;
        }
    }
}

function delFoto(i) {
    $('#foto_' + i).val('');
    $('#id_foto_' + i).hide(500);


    if ($('#nueva_foto').is(':hidden')) {
        $('#nueva_foto').show(500);
    }

}
