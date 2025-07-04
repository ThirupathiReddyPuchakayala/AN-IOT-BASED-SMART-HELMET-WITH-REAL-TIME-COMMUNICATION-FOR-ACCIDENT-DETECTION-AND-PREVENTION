#include <SoftwareSerial.h>    // For Zigbee and GSM communication
#include <Wire.h>

// Pin definitions
const int motorPin = 9;        // Motor control pin
const int gsmTx = 10;          // TX pin for GSM
const int gsmRx = 11;          // RX pin for GSM

// Zigbee setup
SoftwareSerial zigbee(7, 8);   // RX, TX for Zigbee communication
SoftwareSerial gsm(gsmTx, gsmRx); // GSM communication

const int alcoholThreshold = 500;
const String familyPhoneNumber = "+1234567890";  // Replace with actual phone number

void setup() {
  Serial.begin(9600);
  zigbee.begin(9600);   // Start Zigbee communication
  gsm.begin(9600);      // Start GSM communication

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);  // Motor off initially
}

void loop() {
  // Check if data is available from the transmitter
  if (zigbee.available()) {
    String receivedData = zigbee.readStringUntil('\n');
    processReceivedData(receivedData);
  }

  delay(1000);
}

// Function to process the received data
void processReceivedData(String data) {
  // Split the received data
  int helmetOn = data.substring(0, data.indexOf(',')).toInt();
  data.remove(0, data.indexOf(',') + 1);

  int alcoholLevel = data.substring(0, data.indexOf(',')).toInt();
  data.remove(0, data.indexOf(',') + 1);

  float accelX = data.substring(0, data.indexOf(',')).toFloat();
  data.remove(0, data.indexOf(',') + 1);

  float accelY = data.substring(0, data.indexOf(',')).toFloat();
  data.remove(0, data.indexOf(',') + 1);

  float accelZ = data.substring(0, data.indexOf(',')).toFloat();
  data.remove(0, data.indexOf(',') + 1);

  float latitude = data.substring(0, data.indexOf(',')).toFloat();
  data.remove(0, data.indexOf(',') + 1);

  float longitude = data.toFloat();

  String gpsLocation = "https://maps.google.com/?q=" + String(latitude, 6) + "," + String(longitude, 6);

  // Process helmet detection
  if (!helmetOn) {
    Serial.println("Helmet not worn! Stopping motor and sending alert...");
    digitalWrite(motorPin, LOW);  // Stop motor
    sendAlert("Alert: Helmet not worn! Please wear your helmet. Location: " + gpsLocation);  // Send SMS alert
  } else {
    digitalWrite(motorPin, HIGH); // Run motor
  }

  // Check alcohol level
  if (alcoholLevel > alcoholThreshold) {
    Serial.println("High alcohol level detected! Sending SMS and making call...");
    sendAlert("Alert: High alcohol level detected! Rider is drunk. Location: " + gpsLocation);
    makeCall(familyPhoneNumber);  // Make a call when alcohol is detected
  }

  // Check for accident detection (based on acceleration values)
  if (abs(accelX) > 2.0 || abs(accelY) > 2.0 || abs(accelZ) > 2.0) {
    Serial.println("Accident detected! Sending alert and making a call...");
    sendAlert("Alert: Accident detected! Immediate action needed. Location: " + gpsLocation);
    makeCall(familyPhoneNumber);  // Make a call when an accident is detected
  }
}

// Function to send an SMS alert via GSM
void sendAlert(String message) {
  gsm.print("AT+CMGF=1\r");             // Set SMS mode to text
  delay(1000);
  gsm.print("AT+CMGS=\"");
  gsm.print(familyPhoneNumber);         // Send to family member's phone number
  gsm.print("\"\r");
  delay(1000);
  gsm.print(message);                   // The alert message with GPS location
  delay(1000);
  gsm.write(26);                        // Ctrl+Z to send the SMS
  delay(1000);
  Serial.println("Alert message sent.");
}

// Function to make a call via GSM
void makeCall(String phoneNumber) {
  gsm.print("ATD");
  gsm.print(phoneNumber);     // Dial the family member's phone number
  gsm.print(";\r");           // Semi-colon indicates a voice call
  delay(10000);               // Call duration (e.g., 10 seconds)
  gsm.println("ATH");         // Hang up the call
  Serial.println("Call made and hung up.");
}
