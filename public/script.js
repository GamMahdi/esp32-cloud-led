
// Recuperer l'etat de la LED depuis le serveur
async function getLEDStatus() {

    try {
        const response = await fetch('/api/led');

        const data = await response.json();

        updateInterface(data.led);

    } catch (error) {
        document.getElementById('message').textContent =
            "Erreur de connexion au serveur";
    }
}

// Envoyer une commande ON ou OFF
async function controlLED(command) {

    try {
        const response = await fetch(`/api/led/${command}`, {
            method: 'POST'
        });

        const data = await response.json();

        updateInterface(data.led);

        document.getElementById('message').textContent =
            data.message;

    } catch (error) {
        document.getElementById('message').textContent =
            "Erreur de communication";
    }
}

// Mettre a jour l'interface
function updateInterface(state) {

    const led = document.getElementById('ledIndicator');
    const status = document.getElementById('ledStatus');

    if (state === "ON") {
        led.classList.add('on');
        status.textContent = "LED ALLUMEE";
    } else {
        led.classList.remove('on');
        status.textContent = "LED ETEINTE";
    }
}

// Lire l'etat initial
getLEDStatus();
