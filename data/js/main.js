$(function () {
    getSensorData(); // Uruchom natychmiast po załadowaniu strony

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

    $("#wifiModeSwitch").change(function () {
        $('#ssid').val('');
        $('#password').val('');
    });

    $('#save_network').click( function (event) {
        saveNetwork();
    });

    $('#getSensorData').click(function(event){
        getSensorData();
    })
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

function getSensorData() {
    $.ajax({
        url: '/getData',
        method: 'GET',
        dataType: 'json',
        success: function(response) {
            console.log('Odebrane dane:', response);

            // Sprawdź, czy odpowiedź to tablica i ma przynajmniej jeden element
            if (Array.isArray(response) && response.length > 0) {
                const sensorData = response[0]; // Pobierz pierwszy (i jedyny) obiekt w tablicy

                // Zaktualizuj dane na stronie
                $('#temp').text(sensorData.temperature !== null ? sensorData.temperature.toFixed(1) : 'Brak danych');
                $('#hum').text(sensorData.humidity !== null ? sensorData.humidity.toFixed(1) : 'Brak danych');
                $('#soil_hum').text(sensorData.soil_humidity !== null ? sensorData.soil_humidity.toFixed(1) : 'Brak danych');
                $('#co2').text(sensorData.CO2 !== null ? sensorData.CO2 : 'Brak danych');
                $('#timestamp').text(sensorData.timestamp || 'Brak danych');
            } else {
                console.error('Nieprawidłowa odpowiedź: brak danych w tablicy');
                $('#temp').text('Błąd');
                $('#hum').text('Błąd');
                $('#soil_hum').text('Błąd');
                $('#co2').text('Błąd');
                $('#timestamp').text('Błąd');
            }
        },
        error: function(xhr, status, error) {
            console.error('Błąd pobierania danych:', error);

            // Ustaw komunikaty o błędzie
            $('#temp').text('Błąd');
            $('#hum').text('Błąd');
            $('#soil_hum').text('Błąd');
            $('#co2').text('Błąd');
            $('#timestamp').text('Błąd');
        }
    });
}


