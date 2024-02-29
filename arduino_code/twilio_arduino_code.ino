#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ArduinoHttpClient.h>

#define SIM800_RX_PIN 7
#define SIM800_TX_PIN 8

TinyGPSPlus gps;
SoftwareSerial gpsSerial(10, 11);  // GPS module connected to pins 10 (RX) and 11 (TX)
SoftwareSerial gsmSerial(SIM800_RX_PIN, SIM800_TX_PIN);  // GSM module connected to pins 7 (RX) and 8 (TX)

const char* twilioPhoneNumber = "+1234567890"; // Twilio phone number to send SMS
const char* twilioAccountSID = "your_account_sid"; // Your Twilio Account SID
const char* twilioAuthToken = "your_auth_token"; // Your Twilio Auth Token

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
        
        // Send GPS data to Twilio number via GSM
        sendGPSData(latitude, longitude);
      }
    }
  }
}

void sendGPSData(float latitude, float longitude) {
  // Format the message
  String message = "Latitude: " + String(latitude, 6) + ", Longitude: " + String(longitude, 6);
  
  // Connect to GSM network
  gsmSerial.println("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
  
  // Send SMS message via Twilio
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(twilioPhoneNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.println(message);
  delay(1000);
  gsmSerial.write(0x1A); // Send Ctrl+Z to indicate end of message
  delay(1000);
}
