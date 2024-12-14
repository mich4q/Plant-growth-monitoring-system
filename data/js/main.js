$(function () {
    
    setInterval(getSensorData,10000);

    // Funkcja zmiany widoczności sekcji
    function showSection(sectionId) {
        $("section").addClass("hidden").removeClass("visible");
        $(sectionId).addClass("visible").removeClass("hidden");
    }

    // Obsługa kliknięcia w linki menu
    $("#home-link").click(function() {
        showSection("#home");
    });

    $("#network-link").click(function() {
        showSection("#networksettings");
    });

    $("#wifiModeSwitch").on('change', function () {
        $('#ssid').val('');
        $('#password').val('');
    });

    $('#save_network').on('click', function (event) {
        saveNetwork();
    });

    // $('#getSensorData').on('click',function(event){
    //     getSensorData();
    // })
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

// function getSensorData(){
//     $.ajax({
//         url: '/getData',
//         method: 'GET',
//         dataType: 'json',
//         success: function(response) {
//             // Wyświetl temperaturę
//             $('#temp').text(response.temperature.toFixed(1));
            
//             // Wyświetl wilgotność
//             $('#hum').text(response.humidity.toFixed(1));

//             $('#timestamp').text(response.timestamp);
//             $('#soil_hum').text(response.soil_humidity.toFixed(1));
//             $('#co2').text(response.CO2);
//         },
//         error: function(xhr, status, error) {
//             // Obsługa błędu - wyświetlenie komunikatu
//             $('#temp').text('Błąd');
//             $('#hum').text('Błąd');
//             $('#timestamp').text('Błąd');
//             $('#timestamp').text('Błąd');
//             $('#soil_hum').text('Błąd');
//             $('#co2').text('Błąd');
//             console.error('Błąd pobierania danych:', error);
//         }
//     });
// }

