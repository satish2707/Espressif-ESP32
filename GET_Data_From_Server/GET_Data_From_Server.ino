/*******************************************************************************************************************
 * @details   : This tutorial demonstrates how to GET data from an HTTP server using ESP32
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 25 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : GET_Data_From_Server.ino
 ********************************************************************************************************************/
#include <WiFi.h>

const char* ssid = "Your_SSID";           // Replace with your WiFi SSID
const char* password = "Your_PASSWORD";   // Replace with your WiFi password
const char* serverUrl = "yourserver.com"; // Replace with your server URL
const uint16_t port = 80;                 // HTTP port

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  WiFiClient client;
  if (client.connect(serverUrl, port)) {
    Serial.println("Connected to server");

    // Make a HTTP GET request
    client.println("GET /data/student HTTP/1.1"); // Replace with your endpoint
    client.print("Host: ");
    client.println(serverUrl);
    client.println("Connection: close");
    client.println();

    // Read all the lines of the reply from server and print them to Serial
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

    // Close the connection
    client.stop();
    Serial.println("Disconnected from server");
  } else {
    Serial.println("Connection to server failed");
  }

  delay(5000); // Wait for 5 seconds before sending the next request
}
