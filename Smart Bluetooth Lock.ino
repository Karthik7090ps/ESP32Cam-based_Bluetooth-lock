#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

String pasw = "Jamesbond";
String getinput = "";
BluetoothSerial SerialBT;
int lockpin = 2;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("SmartLock");
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(2, OUTPUT); // Set pin 15 as an output pin
}

void loop() {
  if (SerialBT.available()) {
    getinput = SerialBT.readStringUntil('\n');
    getinput.trim(); // Remove leading/trailing whitespace
    Serial.println(getinput);

    if (getinput.equals(pasw)) {
      Serial.println("Password correct, toggling lock...");
      digitalWrite(lockpin, !digitalRead(lockpin)); // Toggle the state of the GPIO pin
      delay(1000);
    } else {
      Serial.println("Incorrect password");
    }
  }
}

