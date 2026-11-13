
#include <WiFi.h>
#include <HTTPClient.h>

// Configuration Wi-Fi
#include "secrets.h"

// Adresse du serveur Node.js
const char* serverURL = "http://192.168.1.16:3000/api/led";

#define LED_PIN 2

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Connexion Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connexion Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connecte !");
  Serial.println(WiFi.localIP());
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverURL);

    int httpCode = http.GET();
    Serial.print("Code HTTP : ");
    Serial.println(httpCode);

    if (httpCode == 200) {

      String response = http.getString();

      Serial.println(response);

      if (response.indexOf("\"ON\"") != -1) {
        digitalWrite(LED_PIN, HIGH);
      }
      else if (response.indexOf("\"OFF\"") != -1) {
        digitalWrite(LED_PIN, LOW);
      }

    } else {
      Serial.print("Erreur HTTP : ");
      Serial.println(httpCode);
    }

    http.end();
  }

  delay(1000);
}
