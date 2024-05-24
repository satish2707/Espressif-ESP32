/*******************************************************************************************************************
 * @details   : This toutorials Get the Time and Date From NTP clinet  
 *
 * @authors   : Satish Kanawade (Embedded Software Developer)
 *
 * @copyright : Embedlogiclancer
 *
 * @date      : 25 NOV 2023
 *
 * @version   : V1.0
 *
 * @file      : GET_NTP_DATETIME.ino
 ********************************************************************************************************************/
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
const char *ntpServer = "asia.pool.ntp.org";
const long gmtOffset_sec = 0;      // Offset for your timezone (in seconds)
const int daylightOffset_sec = 0;  // Offset for daylight saving time (in seconds)
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec);

unsigned long previousMillis = 0;
const long interval = 1000;  // Interval in milliseconds

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  connectToWiFi();

  // Initialize NTP client
  timeClient.begin();
}

void loop() {
  Update_date_Time();
  delay(1000);
}

// Function to connect to Wi-Fi
void connectToWiFi() {
  const char *ssid = "EMPROWEB 4G";
  const char *password = "IpNJ##1789pp";

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

// Function to update NTP time every second
void Update_date_Time() {
  unsigned long currentMillis = millis();

  // Check if the specified interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the current time for the next iteration
    previousMillis = currentMillis;

    // Update NTP client
    timeClient.update();

    // Print current date and time
    Serial.print("Current Date and Time: ");
    Serial.println(getCurrentDateTime());

    // Print current time
    Serial.print("Current Time: ");
    Serial.println(getCurrentTime());

    // Print current date
    Serial.print("Current Date: ");
    Serial.println(getCurrentDate());
  }
}

// Function to get current time as a formatted string (24-hour format, UTC)
String getCurrentTime() {
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  return String(ptm->tm_hour) + ":" + String(ptm->tm_min) + ":" + String(ptm->tm_sec);
}

// Function to get current date as a formatted string (26-11-2021)
String getCurrentDate() {
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  String currentDate = String(ptm->tm_mday) + "-" + String(ptm->tm_mon + 1) + "-" + String(ptm->tm_year + 1900);
  return currentDate;
}

// Function to get current date and time as a formatted string
String getCurrentDateTime() {
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  String currentDate = String(ptm->tm_year + 1900) + "-" + String(ptm->tm_mon + 1) + "-" + String(ptm->tm_mday);
  String currentTime = getCurrentTime();

  return currentDate + " " + currentTime;
}
