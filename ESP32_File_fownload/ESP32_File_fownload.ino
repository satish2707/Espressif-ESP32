/*******************************************************************************************************************
 * @details   : This Project Download the file from HTTP Server and Store in sd card
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 08 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : ESP32_File_Download.ino
 ********************************************************************************************************************/
#include <WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <HTTPClient.h>

const char* ssid = "123456789";
const char* password = "123456789";
const int chipSelect = SS;
const char* url = "https://URL/firmware.bin";
const char* fileName = "/Download/firmware.bin";

#define LED_PIN 2

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed");
  } else {
    Serial.println("SD card initialized successfully");
  }

  if (!SD.exists("/LINK_OTA")) {
    Serial.println("LINK_OTA folder does not exist. Creating...");
    if (!SD.mkdir("/LINK_OTA")) {
      Serial.println("Failed to create LINK_OTA folder");
      return;
    }
  }
  // Download file from URL and save to SD card
  downloadFile();
}

void loop() {
  // Your code here
}

void downloadFile() {
  HTTPClient http;

  // Begin HTTP request
  Serial.print("Downloading file from URL: ");
  Serial.println(url);

  // Set additional headers if needed
  http.addHeader("User-Agent", "ESP32");
  http.addHeader("Accept", "*/*");

  delay(2000);

  http.begin(url);

  // Start the request and check for return code
  int httpCode = http.GET();
  delay(2000);
  if (httpCode > 0) {
    // Check for valid response code
    if (httpCode == HTTP_CODE_OK) {
      // Create or open the file on the SD card
      File file = SD.open(fileName, FILE_WRITE);
      if (file) {
        // Get the response payload size
        int contentLength = http.getSize();
        Serial.print("Content-Length: ");
        Serial.println(contentLength);

        // Define chunk size and buffer
        const size_t chunkSize = 4096;
        uint8_t buffer[chunkSize];

        // Download file in chunks and write to SD card
        size_t bytesRead = 0;

        while (bytesRead < contentLength) {
          size_t bytesToRead = std::min((size_t)(contentLength - bytesRead), chunkSize);
          int bytesActuallyRead = http.getStreamPtr()->readBytes(buffer, bytesToRead);
          if (bytesActuallyRead > 0) {
            file.write(buffer, bytesActuallyRead);
            bytesRead += bytesActuallyRead;
          } else {
            break;
          }
        }

        file.close();
        Serial.print("File size: ");
        Serial.println(bytesRead);

        if (contentLength == bytesRead) {
          Serial.println("File downloaded and saved to SD card successfully");

          for (;;) {
            digitalWrite(LED_PIN, HIGH);
            delay(500);
            digitalWrite(LED_PIN, LOW);
            delay(500);
          }

        } else {
          SD.remove(fileName);
          Serial.println("Download interrupted. File deleted.");
          ESP.restart();
        }

      } else {
        Serial.println("Error opening file on SD card");
      }
    } else {
      Serial.printf("HTTP error code: %d\n", httpCode);
    }
  } else {
    Serial.println("HTTP request failed");
  }

  http.end();
}
