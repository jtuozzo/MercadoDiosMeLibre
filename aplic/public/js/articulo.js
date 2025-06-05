/*  Nombre: articulo.js
    Autor: Julio Tuozzo
    Función: Javascript del artículo.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 05/06/2025.
*/


window.onload = function () {
    setAlto('articulo');
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
            $('#' + foto).focus();
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

function delHayFoto(i) {

    Swal.fire({
        title: 'Elimina la foto??',
        icon: 'question',
        showCancelButton: true,
        confirmButtonColor: '#1b998b',
        cancelButtonColor: '#d7263d',
        cancelButtonText: 'No',
        confirmButtonText: 'Si',
        focusCancel: true
    })
        .then((result) => {
            if (result.isConfirmed) {
                $('#id_articulo_foto_' + i).hide(500);
                $('#articulo_foto_id_' + i).val('');

            }
        }
        )


}

function setFotoPpal(articulo_foto_id, key)
        {$('#fotoPpal').attr('src', 'getFoto.php?id=' + articulo_foto_id + '&key=' + key); 
        }

