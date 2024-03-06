#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ArduinoHttpClient.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(11, 10);  // GPS module connected to pins 10 (RX) and 11 (TX)
SoftwareSerial gsmSerial(2, 3);  // GSM module connected to pins 2 (RX) and 3 (TX)

const char* twilioPhoneNumber = "+areacode phonenumber"; // Twilio phone number to send SMS

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);  // GPS baud rate
  
}

void loop() {
 while (gpsSerial.available() > 0){
    if (gps.encode(gpsSerial.read())){
        if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());

    sendGPSData(gps.location.lat(), gps.location.lng());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
    }
  }
  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void sendGPSData(float latitude, float longitude) {
  // Format the message
  String message = "Latitude: " + String(latitude, 6) + ", Longitude: " + String(longitude, 6);
  
  gsmSerial.begin(9600);  // GSM baud rate
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
  delay(10000);
}
