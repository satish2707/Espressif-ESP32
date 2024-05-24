
/*******************************************************************************************************************
 * @details   : This Project are For ST7735 Display for Tft_espi Library on ESP32
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 10 MAY 2024
 *
 * @version   : V1.0
 *
 * @file      : Smooth_font_ST7735.ino
 ********************************************************************************************************************/

// Step 1: Download font from - https://www.dafont.com/

// Step 2: install in our System

// Step 3: Open Processing tools - https://processing.org/download

// Step 4: Open our Processing tools go to font conversion select the font and convert this font

// Step 5: Open our Processing tools go to sketch data folder and font .vlw

// Step 6: Convert this file into hex using - https://tomeko.net/online_tools/file_to_hex.php?lang=en

// Step 7: Copy output to clipboard and paste into our font header file 

#include <SPI.h>
#include <TFT_eSPI.h>

// Add custom font header file here
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

TFT_eSPI tft = TFT_eSPI();

void setup(void) 
{
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  tft.loadFont(AA_FONT_SMALL);   // load the User font
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 10);
  tft.println("Satish");
  tft.unloadFont();              // Unload the User font

  tft.setTextColor(TFT_RED);
  tft.setTextSize(0);      
  tft.setCursor(111, 5);
  tft.print("SD");
}
