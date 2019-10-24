// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

byte x = 0;

void loop() {
  Serial.println("Writing to register");
  Wire.beginTransmission(0x0D); // transmit to device #8
  Wire.write(0x80);        // sends five bytes
  Wire.write(0xAA);              // sends one byte
  int num=Wire.endTransmission();    // stop 
  
  Serial.println("Setting pointer");
  Wire.beginTransmission(0x0D); // transmit to device #8
  Wire.write(0xB0);        // sends five bytes
  Wire.write(0x80);              // sends one byte
  num=Wire.endTransmission(); 

  Serial.print("end transmit code");
  Serial.println(num);
  Serial.println("Finished write, Begin read");
  Wire.requestFrom(0x0D, 1); // requst 6 bytes
  if(Wire.available()>=1){
    Serial.println("contact made");
  }
  Serial.println("reading");
  int c= Wire.read();
  Serial.println(c);
  
  delay(5000);
}
