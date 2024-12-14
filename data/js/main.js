
$(function () {
    $("#wifiModeSwitch").on('change', function () {
        $('#ssid').val('');
        $('#password').val('');
    });

    $('#save_network').on('click', function (event) {
        saveNetwork();
    });
})

function saveNetwork() {
    const data = {
        ssid: $('#ssid').val(),
        password: $('#password').val(),
        wifiMode: $('input[name="mode"]:checked').val(),
    };

    $.ajax({
        url: '/savenetwork',
        type: 'GET',
        contentType: 'application/json',
        data: data,
        success: function (response) {
            console.log('data saved');
            console.log(data);

        },
        error: function (xhr, status, error) {
            console.log('error occured: ' + error);
        }
    });
}

