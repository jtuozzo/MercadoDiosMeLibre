/*  Nombre: ventas_list.js
    Autor: Julio Tuozzo
    Función: Javascript del listado de artículos vendidos.
    Fecha de creación: 02/06/2025.
    Ultima modificación: 25/01/2026.
*/


window.onload = function () {
    setAlto('list_ventas');
}

function ocultarEncabezado() {
    $('.encabezado').hide();
}

function compraDelete(articulo_compra_id, nombres, apellidos) {
    Swal.fire({
        title: 'Elimina la compra de ' + nombres + ' ' + apellidos + '??',
        text: 'Esta acción no se puede deshacer.',
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

                $.get('compra_delete.php',
                   {articulo_compra_id: articulo_compra_id
                    },
               function(data, status)
                        {
                         if(status!='success')
                               { alert('Estado: ' + status);
                               }
                         else if(data.length>0)
                                    {$('html').html(data);
                                    }
                               else
                                    {window.location.reload();
                                    }
                         }

                   );
            }

        }
        )
}

$(document).ajaxStart(function () {
    $.blockUI({
        message: "<img src='./images/loading_136_136.gif'  />",
        css: {
            padding: '20px',
            border: 'none',
            width: '160px',
            left: ($(window).width() - 160) / 2 + 'px',
        }
    })
})

$(document).ajaxStop(
    $.unblockUI
)