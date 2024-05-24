
/*******************************************************************************************************************
 * @details   : This tutorial demonstrates how to send data to an HTTP server using ESP32
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 25 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : POST_Data_To_Server.ino
 ********************************************************************************************************************/
#include <WiFi.h>

const char* ssid = "Your_SSID";            // Replace with your WiFi SSID
const char* password = "Your_PASSWORD";    // Replace with your WiFi password
const char* serverUrl = "yourserver.com";  // Replace with your server URL
const uint16_t port = 80;                  // HTTP port

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

  String payload = "{\"name\":\"xyz\",\"age\":\"21\"}";

  WiFiClient client;
  if (client.connect(serverUrl, port)) {
    Serial.println("Connected to server");

    // Make a HTTP POST request
    client.println("POST /data/student HTTP/1.1");
    client.print("Host: ");
    client.println(serverUrl);
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(payload.length());
    client.println();
    client.println(payload);

    // Read all the lines of the reply from server and print them to Serial
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }

    // Close the connection
    client.stop();
    Serial.println("Disconnected from server");
  } else {
    Serial.println("Connection to server failed");
  }

  delay(5000);  // Wait for 5 seconds before sending the next request
}
