# AN-IOT-BASED-SMART-HELMET-WITH-REAL-TIME-COMMUNICATION-FOR-ACCIDENT-DETECTION-AND-PREVENTION

An advanced IoT-enabled smart helmet that integrates real-time communication systems to enhance motorcycle rider safety. This system detects helmet usage, alcohol consumption, and accidents, and transmits emergency alerts with GPS coordinates via GSM to reduce response time during critical situations.

---

## 📌 Project Objectives

- ✅ Detect helmet usage before ignition
- 🚫 Prevent drunk driving using alcohol sensors
- 📍 Real-time GPS tracking of the rider
- 📲 Send emergency SMS alerts using GSM in case of accidents
- 📡 Wireless communication using Zigbee modules

---

## 🛠️ Technologies & Components

### 🔧 Hardware
- Arduino Uno (ATmega328P)
- IR Proximity Sensor
- MQ3 Alcohol Sensor
- ADXL335 Accelerometer (Gyroscope)
- GPS Module (Neo-6M)
- GSM Module (SIM900)
- Buzzer, DC Relay, DC Motor
- LCD Display, Rechargeable Battery
- Zigbee RF Transceiver
- Arduino Protosheild

### 💻 Software
- Arduino IDE (v1.8.18 or above)
- Arduino C++ Programming Language
- Required Libraries:
  - `Wire.h`, `LiquidCrystal_I2C.h`
  - `SoftwareSerial.h`, `TinyGPS++.h`
  - `MPU6050.h`

---

## 🔄 System Architecture

The system is divided into two main units:

- **Helmet Unit (Transmitter):**
  - Detects alcohol levels and helmet status.
  - Sends data wirelessly to the bike unit via Zigbee.

- **Bike Unit (Receiver):**
  - Controls engine ignition based on data received.
  - Sends SMS alerts and GPS location in case of an accident.

---

## 🚨 Features

| Feature               | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| Helmet Detection     | Ensures engine starts only when the helmet is worn                          |
| Alcohol Monitoring   | Detects rider’s alcohol level and disables ignition if drunk                |
| Accident Detection   | Uses accelerometer to detect abnormal motion or impact                      |
| GPS & GSM Module     | Sends real-time accident location via SMS                                   |
| Real-Time Alerts     | Alerts sent instantly to predefined emergency contacts                      |

---

## 🧪 Results & Testing

The system was tested under four rider conditions (helmet/no helmet & drunk/sober). Only when both conditions—helmet worn and rider sober—are met, the bike starts. During an accident, an SMS with GPS coordinates is sent to emergency contacts.

---

## 📷 Screenshots

- Transmitter and receiver setup
- SMS alert with GPS location

---

## 🚀 Future Enhancements

- Add bioelectric sensors (heart rate, fatigue detection)
- Front camera for visual monitoring
- Solar-powered helmet module
- Inter-vehicle communication for traffic alerts
- Integration with mobile apps for tracking and alerts

---

## 📚 Authors

- P. Thirupathi Reddy (22275A0402)  
- S. Inderjeet Singh (22275A0418)  
- M. Amani (22275A0404)  
- V. Sahith Kumar (22275A0403)  
- G. Mahibabu (22275A0407)  

Project Guide: Mr. D. Ravi Kiran Babu (Associate Professor, Dept. of ECE, JITS)

---

## 📜 License

This project is developed as part of the B.Tech Mini Project requirement at Jyothishmathi Institute of Technology and Science. It is intended for academic use.

---

## 🤝 Acknowledgements

We thank the faculty of the ECE Department, Jyothishmathi Institute of Technology and Science, and our guide Mr. D. Ravi Kiran Babu for continuous support and guidance.
