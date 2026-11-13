
const express = require('express');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.static('public'));


// Etat initial de la LED
let ledState = "OFF";

// Route pour consulter l'etat
app.get('/api/led', (req, res) => {
    res.json({
        led: ledState
    });
});

// Route pour allumer la LED
app.post('/api/led/on', (req, res) => {
    ledState = "ON";

    res.json({
        message: "LED allumee",
        led: ledState
    });
});

// Route pour eteindre la LED
app.post('/api/led/off', (req, res) => {
    ledState = "OFF";

    res.json({
        message: "LED eteinte",
        led: ledState
    });
});

// Demarrer le serveur
app.listen(PORT, () => {
    console.log(`Serveur demarre sur http://localhost:${PORT}`);
});
app.listen(PORT, () => {
    console.log(`Serveur demarre sur le port ${PORT}`);
});