/*******************************************************************************************************************
 * @details   : This Project are Update the OTA firmware update of ESP32 using SD card 
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 10 MAY 2024
 *
 * @version   : V1.0
 *
 * @file      : ESP_OTA.ino
 ********************************************************************************************************************/
#include <SPI.h>
#include <Update.h>
#include <SD.h>

#define LED_BUILTIN 2
const int chipSelect = SS;

void progressCallBack(size_t currSize, size_t totalSize) {
  Serial.printf("OTA Update Completed %d of %d bytes\n", currSize, totalSize);
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!SD.begin(SS)) {
    Serial.println("SD card initialization failed");
  } else {
    Serial.println("SD card Initialization Successfully");
  }

  File firmware = SD.open("/firmware.bin");

  if (firmware) {

    Serial.println("Firmware Update Available");

    Serial.println("Start the OTA Update");

    Update.onProgress(progressCallBack);

    Update.begin(firmware.size(), U_FLASH);

    Update.writeStream(firmware);

    if (Update.end()) {

      Serial.println("OTA Update finished!");

    } else {

      Serial.println("OTA Update error!");

      Serial.println(Update.getError());
    }

    firmware.close();

    if (SD.remove("/firmware.bin")) {

      Serial.println(F("Firmware remove succesfully!"));

    } else {

      Serial.println(F("Firmware remove error!"));
    }

    delay(1000);

    ESP.restart();

  } else {

    Serial.println("OTA not found");
  }
}

void loop(void) {
  Serial.println("LED Blink for 2000 MS");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}