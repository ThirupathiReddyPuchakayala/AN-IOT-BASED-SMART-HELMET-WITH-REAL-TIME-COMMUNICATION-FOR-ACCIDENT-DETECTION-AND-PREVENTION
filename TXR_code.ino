#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>  // Include TinyGPS++ library

// Pin definitions
const int alcoholPin = A0;  
const int helmetPin = 2;    
const int motorPin = 9;     
const int gpsRx = 4;        // GPS RX pin
const int gpsTx = 3;        // GPS TX pin

// GPS and Accelerometer setup
TinyGPSPlus gps;
SoftwareSerial gpsSerial(gpsTx, gpsRx);  // RX, TX for GPS
SoftwareSerial zigbee(7, 8);   // RX, TX for Zigbee communication

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  zigbee.begin(9600);
  gpsSerial.begin(9600);  // Start GPS communication

  if (!accel.begin()) {
    Serial.println("Failed to initialize ADXL345 accelerometer!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  pinMode(alcoholPin, INPUT);
  pinMode(helmetPin, INPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
}

void loop() {
  // Read GPS data
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  int alcoholLevel = analogRead(alcoholPin);
  bool helmetOn = digitalRead(helmetPin);

  sensors_event_t event;
  accel.getEvent(&event);

  bool accidentDetected = (abs(event.acceleration.x) > 2.0 ||
                           abs(event.acceleration.y) > 2.0 ||
                           abs(event.acceleration.z) > 2.0);

  if (!helmetOn) {
    digitalWrite(motorPin, LOW);
  } else {
    digitalWrite(motorPin, HIGH);
  }

  // Prepare GPS location
  float latitude = gps.location.isValid() ? gps.location.lat() : 0.0;
  float longitude = gps.location.isValid() ? gps.location.lng() : 0.0;

  // Prepare data for transmission (add latitude and longitude)
  String data = String(helmetOn) + "," + String(alcoholLevel) + "," +
                String(event.acceleration.x) + "," + String(event.acceleration.y) + "," +
                String(event.acceleration.z) + "," + String(latitude, 6) + "," + 
                String(longitude, 6);

  zigbee.println(data);  // Transmit data via Zigbee

  delay(1000);
}
