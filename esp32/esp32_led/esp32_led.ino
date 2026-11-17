
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Configuration Wi-Fi
#include "secrets.h"

// Adresse publique du serveur Render
const char* serverURL =
  "https://esp32-cloud-led.onrender.com/api/led";

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

    WiFiClientSecure client;
    client.setInsecure(); // Test uniquement

    HTTPClient http;

    if (http.begin(client, serverURL)) {

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
        Serial.println(http.errorToString(httpCode));
      }

      http.end();

    } else {
      Serial.println("Impossible de demarrer la connexion HTTP");
    }
  }

  delay(1000);
}
