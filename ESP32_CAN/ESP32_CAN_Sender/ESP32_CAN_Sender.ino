/***********************************************************************************************************
 * @details : This is the final version of the Project ESP32 CAN Recived and Send tehe Data Over CAN bus
 *
 * @author  : Satish Kanawade (Embedded Software developer)
 *
 * @copright: Embedlogiclancer
 *
 * @date    : 06 FEB 2024
 *
 **********************************************************************************************************/

#include <CAN.h>

#define TX_GPIO_NUM 21  // Connects to CTX
#define RX_GPIO_NUM 22  // Connects to CRX

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(1000);

  Serial.println("CAN Receiver/Receiver");

  // Set the pins
  CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("CAN Initialize failed!");
    while (1)
      ;
  } else {
    Serial.println("CAN Initialized Successfully");
  }
}

void loop() {
  CANSender();
  delay(5000);
}

char Data[] = "TEST 1 2 3 4 ";

// This function send the Data Over CAN bus
void CANSender() 
{
  Serial.print("Sending CAN packet ... ");

  // Send data in chunks of 8 bytes or less
  for (int i = 0; i < sizeof(Data); i += 8) {
    CAN.beginPacket(0x12);  // sets the ID and clears the transmit buffer
    for (int j = i; j < i + 8 && j < sizeof(Data); j++) {
      CAN.write(Data[j]);
    }
    CAN.endPacket();
    delay(10);  // Delay to allow receiver to process packet
  }

  Serial.println("done");
}
