/*******************************************************************************************************************
 * @details   : This tutorial demonstrates how to Operate RGB LED using ESP32
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 29 JAN 2024
 *
 * @version   : V1.0
 *
 * @file      : ESP_RGB.ino
 ********************************************************************************************************************/
const int RED_PIN = 5;
const int GREEN_PIN = 18;
const int BLUE_PIN = 19;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(GREEN_PIN, HIGH);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(BLUE_PIN, HIGH);
}

// ON led According to COLOR Input
void RGB_ON(char RGBON) {
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  // ON RED LED
  if (RGBON == 'R') {
    digitalWrite(RED_PIN, LOW);
  }
  // ON GREEN LED
  else if (RGBON == 'G') {
    digitalWrite(GREEN_PIN, LOW);
  }
  // ON BLUE LED
  else if (RGBON == 'B') {
    digitalWrite(BLUE_PIN, LOW);
  }
  // ON WHITE LED
  else if (RGBON == 'W') {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
  // ON YELLOW LED
  else if (RGBON == 'Y') {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  }
  // ON PINK LED
  else if (RGBON == 'P') {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
  // ON CYAN LED
  else if (RGBON == 'C') {
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
}

// ALL RGB led OFF
void RGB_OFF() {
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

void loop() 
{
  RGB_ON('R');
  delay(1000);
  RGB_ON('G');
  delay(1000);
  RGB_ON('B');
  delay(1000);
  RGB_ON('W');
  delay(1000);
  RGB_ON('Y');
  delay(1000);
  RGB_ON('P');
  delay(1000);
  RGB_ON('C');
  delay(1000);
}