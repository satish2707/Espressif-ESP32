/*******************************************************************************************************************
 * @details   : This Project are for CRC32 Calculation of any file on Ardunio and Platform-IO on any MCU
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 08 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : CRC32.ino
 ********************************************************************************************************************/
#include <CRC32.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = SS;               // Define SD card Chip select pin
const char* filename = "/firmware.bin";  // Filename for CRC calculation

void setup() {
  Serial.begin(115200);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed");
    return;
  }

  Serial.println("SD card initialized successfully");

  // Open the file
  File file = SD.open(filename);
  if (!file) {
    Serial.println("Failed to open file.");
    return;
  }

  // Create the Object for CRC32 lib
  CRC32 crc;

  // Calculate CRC
  while (file.available()) {
    uint8_t data = file.read();
    crc.update(data);
  }
  file.close();

  // Get the final CRC value
  uint32_t checksum = crc.finalize();

  // Print CRC
  Serial.print("CRC32 of ");
  Serial.print(filename);
  Serial.print(": 0x");
  Serial.println(checksum, HEX);
}

void loop() {
  // Nothing in loop for this example
}
