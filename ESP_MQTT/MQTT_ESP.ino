/*******************************************************************************************************************
 * @details   : This is a template to connect the ESP8266/ESP32 with MQTT
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 04 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : MQTT_ESP.ino
 ********************************************************************************************************************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Define your WiFi credentials
const char* ssid = "12345678";
const char* password = "12345678";

// Define your MQTT server credentials
const char* mqtt_server = "143.110.245.40";    // Replace with your MQTT server IP
const int mqtt_port = 1883;                    // Replace with your MQTT server port (default is 1883)
const char* mqtt_username = "admin";           // Replace with your MQTT username
const char* mqtt_password = "Reset1234";       // Replace with your MQTT password
const char* mqtt_client_id = "ESP8266Client";  // Replace with your MQTT client ID (same as Device ID)
const char* mqtt_topic = "100002";             // Set to device ID or desired topic

// Create the object For wifi and MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Function to handle MQTT connection and reconnection
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect with the provided credentials
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");

      // Once connected, subscribe to the desired topic
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Callback function to handle messages received from the MQTT broker
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT received from topic: ");
  Serial.print(topic);
  Serial.print(" - ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Wait for the connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
