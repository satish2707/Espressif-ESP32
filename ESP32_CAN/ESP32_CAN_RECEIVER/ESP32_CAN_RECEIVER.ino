/***********************************************************************************************************
 * @details : This is the final version of the Project ESP32 CAN Recived and Send the Data Over CAN bus
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

#define MAX_MESSAGE_LENGTH 4096
char receivedMessage[MAX_MESSAGE_LENGTH];
int messageIndex = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(1000);

  CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("ReceiverCAN Initialize failed!");
    while (1)
      ;
  } else {
    Serial.println("Receiver CAN Initialized Successfully");
  }
}

void loop() 
{
  CANReceiver();
}

// This Function Recived the CAN messages Over CAN
void CANReceiver() {
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    while (CAN.available()) {
      char receivedChar = CAN.read();
      if (messageIndex < MAX_MESSAGE_LENGTH - 1) {
        receivedMessage[messageIndex++] = receivedChar;
        receivedMessage[messageIndex] = '\0';
      }
    }
    
    if (messageIndex > 0 && receivedMessage[messageIndex - 1] == '\0') {

      Serial.print("Received Packet ID: 0x");
      Serial.println(CAN.packetId(), HEX);
      Serial.print("Received Packet length: ");
      Serial.println(packetSize);
      Serial.print("Received Packet Data: ");
      Serial.println(receivedMessage);

      messageIndex = 0;
    }
  }
}