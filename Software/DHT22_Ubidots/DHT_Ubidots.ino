#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// Replace with your network credentials
const char* ssid = "Comet_2Ghz_Guest";
const char* password = "expl0r3r";

// Ubidots parameters
const char* ubidotsToken = "PUT YOUR TOKEN HERE"; // Replace with your Ubidots Token
const char* deviceLabel = "YOUR DEVICE LABEL"; // Device label
const char* temperatureVariable = "temperature"; // Temperature variable label
const char* humidityVariable = "humidity"; // Humidity variable label

// DHT22 parameters
#define DHTPIN 4 // Pin connected to DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read data from DHT22
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C  Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Send data to Ubidots
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String serverPath = "http://things.ubidots.com/api/v1.6/devices/" + String(deviceLabel);
//if you are a industrial user use: http://industrial.api.ubidots.com/api/v1.6/devices/


    // Prepare the payload in JSON format
    String payload = "{\"" + String(temperatureVariable) + "\": " + String(temperature) + ", ";
    payload += "\"" + String(humidityVariable) + "\": " + String(humidity) + "}";

    http.begin(serverPath.c_str());
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-Auth-Token", ubidotsToken);

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }

  // Wait 10 seconds before sending the next data
  delay(10000);
}
