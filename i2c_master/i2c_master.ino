#include <Arduino.h>
#include <Wire.h>
#include <WireSlaveRequest.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define SLAVE_ADDR 0x1E

#define MAX_SLAVE_RESPONSE_LENGTH 32

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.begin(115200);
  Serial.println("\nI2C");
}

void loop() {
    static unsigned long lastReadMillis = 0;

    // request data from Slave every 1000 ms
    if (millis() - lastReadMillis > 1000) {
        // first create a WireSlaveRequest object
        // first argument is the Wire bus the slave is attached to (Wire or Wire1)
        WireSlaveRequest slaveReq(Wire, SLAVE_ADDR, MAX_SLAVE_RESPONSE_LENGTH);

        // optional: set delay in milliseconds between retry attempts.
        // the default value is 10 ms
        slaveReq.setRetryDelay(5);

        // attempts to read a packet from an ESP32 slave.
        // there's no need to specify how many bytes are requested,
        // since data is expected to be packed with WirePacker,
        // and thus can have any length.
        bool success = slaveReq.request();
        
        if (success) {
            while (1 < slaveReq.available()) {  // loop through all but the last byte
                char c = slaveReq.read();       // receive byte as a character
                Serial.print(c);                // print the character
            }
            
            int x = slaveReq.read();    // receive byte as an integer
            Serial.println(x);          // print the integer
        }
        else {
            // if something went wrong, print the reason
            Serial.print("slaveReq status: ");
            Serial.println(slaveReq.lastStatusToString());
        }

        lastReadMillis = millis();
    }   
}
