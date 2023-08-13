#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

// Connect the GPS module's TX pin to Flora's RX pin (pin 1)
// Connect the GPS module's RX pin to Flora's TX pin (pin 0)
SoftwareSerial gpsSerial(0, 1);

Adafruit_GPS gps(&gpsSerial);

void setup() {
  // Set baud rate for GPS communication
  gpsSerial.begin(9600);

  // Set desired baud rate for Serial monitor
  Serial.begin(9600);

  // Initialize GPS
  gps.begin(9600);
  gps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  gps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  gps.sendCommand(PGCMD_ANTENNA);

  // Wait for GPS to get a fix
  while (!gps.fix) {
    delay(1000);
    Serial.println("Waiting for GPS fix...");
  }
}

void loop() {
  // Read data from GPS
  char c = gps.read();

  // Print GPS data to Serial monitor
  if (gps.newNMEAreceived()) {
    if (!gps.parse(gps.lastNMEA()))
      return;

    if (gps.fix) {
      Serial.print("Location: ");
      Serial.print(gps.latitudeDegrees, 6);
      Serial.print(", ");
      Serial.print(gps.longitudeDegrees, 6);
      Serial.println();
      
      Serial.print("Date: ");
      Serial.print(gps.day);
      Serial.print("/");
      Serial.print(gps.month);
      Serial.print("/");
      Serial.print(gps.year);
      Serial.println();

      Serial.print("Time: ");
      Serial.print(gps.hour);
      Serial.print(":");
      Serial.print(gps.minute);
      Serial.print(":");
      Serial.print(gps.seconds);
      Serial.println();
    }
  }
}
