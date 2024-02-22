#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ArduinoHttpClient.h>

#define SIM800_RX_PIN 7
#define SIM800_TX_PIN 8

TinyGPSPlus gps;
SoftwareSerial gpsSerial(10, 11);  // GPS module connected to pins 10 (RX) and 11 (TX)
SoftwareSerial gsmSerial(SIM800_RX_PIN, SIM800_TX_PIN);  // GSM module connected to pins 7 (RX) and 8 (TX)

const char* server = "localhost"; // or "127.0.0.1"
const int serverPort = 80;
const String endpoint = "/receive_location/";

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);  // GPS baud rate
  gsmSerial.begin(9600);  // GSM baud rate
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
        
        // Send GPS data to Django backend via GSM
        sendGPSData(latitude, longitude);
      }
    }
  }
}

void sendGPSData(float latitude, float longitude) {
  gsmSerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); // Set GPRS connection type
  delay(1000);
  gsmSerial.println("AT+SAPBR=3,1,\"APN\",\"your_APN_here\""); // Set APN
  delay(1000);
  gsmSerial.println("AT+SAPBR=1,1"); // Open GPRS context
  delay(1000);
  gsmSerial.println("AT+HTTPINIT"); // Initialize HTTP service
  delay(1000);
  gsmSerial.println("AT+HTTPPARA=\"CID\",1"); // Set HTTP session ID
  delay(1000);
  gsmSerial.print("AT+HTTPPARA=\"URL\",\"http://");
  gsmSerial.print(server);
  gsmSerial.print(endpoint);
  gsmSerial.print("?latitude=");
  gsmSerial.print(latitude, 6);
  gsmSerial.print("&longitude=");
  gsmSerial.print(longitude, 6);
  gsmSerial.println("\""); // Set URL for HTTP POST request
  delay(1000);
  gsmSerial.println("AT+HTTPACTION=0"); // Execute HTTP POST request
  delay(3000);
  gsmSerial.println("AT+HTTPTERM"); // Terminate HTTP service
  delay(1000);
  gsmSerial.println("AT+SAPBR=0,1"); // Close GPRS context
  delay(1000);
}

