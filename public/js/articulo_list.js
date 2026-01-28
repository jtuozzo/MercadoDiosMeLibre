/*  Nombre: articulo_list.js
    Autor: Julio Tuozzo
    Función: Javascript del listado de artículos.
    Fecha de creación: 26/05/2025.
    Ultima modificación: 27/01/2026.
*/

function sin_articulos() {
    window.onload = function () {
        setAlto('list_articulos');
        $('#list_articulos').css('background-color', '#f0f0f0');
        $('.link').hide();
        $('h2').css('background-color', '#f0f0f0');

    }

}
$(document).ready(function () {
    $('#articulo').on('input', function () {
        const search = $(this).val();
        const token = $('#token').val();
        if (search.length > 2) {
            $.ajax({
                url: 'articulo_buscar.php',
                method: 'POST',
                data: {
                    search: search,
                    token: token
                },
                success: function (response) {
                    $('#resultados').html(response).removeClass('d-none');
                }
            });
        } else {
            $('#resultados').addClass('d-none');
        }
    });

    // Comenzamos a traer los demas campos para mostrar el resultado.
    $(document).on('click', '.autocomplete-item', function () {
        const data = $(this).data();

        window.open("articuloGet.php?id=" + data.articulo_id + "&key=" + data.token);
        $('#resultados').addClass('d-none');
        $('#articulo').val('');
    });

});