// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>
#include "AD5933.h"
const int address=0x0D;


int main(){
   long startFrequency=1000;
   long incrementFrequency=100;
   long numberIncrements=10;
  



    //Wire.begin(); // join i2c bus (address optional for master)
    sei();//enable interrupts... 
    Serial.begin(9600);
    Serial.println("Got to here 1");
    AD5933 pmodIA;
    Wire.begin(); 

    //set start frequency
    Serial.println("Got to here 2");
    pmodIA.setStartFrequency(startFrequency);
    Serial.println("Got to here 3");
    //number of increments
    pmodIA.setIncrementFrequency(incrementFrequency);
    Serial.println("Got to here 4");
    //frequency increment
    pmodIA.setNumberIncrements(numberIncrements);
    Serial.println("Got to here 5");
    while(1) {
       Serial.println("Got to here 6");
       Serial.print("Start frequency set");
       Serial.print("Set Value: "); 
       Serial.println(startFrequency);

       long frequencySet1=pmodIA.readRegister(START_FREQ_1);

       long frequencySet2=pmodIA.readRegister(START_FREQ_2);
       Serial.println("actuall read data");
       Serial.println(frequencySet2);
       long frequencySet3=pmodIA.readRegister(START_FREQ_3);
       long frequency=(frequencySet1<<16)||(frequencySet2<<8)||(frequencySet3);
       Serial.print("Actual Value: ");
       Serial.println(frequency);
       delay(1000);
       //NOTE: find out if we need to do stuf like set clock sorce or set internal clock....
       //******************************************************//
       //******program parameters into relavant registers***********(we could have some sort of user input from the computer to do this...)
            //start frequency register

            //number of increments
            //frequency increment





      // Wire.beginTransmission(address); // transmit to device #8
      // Wire.write(0x80);        // sends five bytes
      // Wire.write(0xAA);              // sends one byte
      // int num=Wire.endTransmission();    // stop 
      
      // Serial.println("Setting pointer");
      // Wire.beginTransmission(address); // transmit to device #8
      // Wire.write(0xB0);        // sends five bytes
      // Wire.write(0x80);              // sends one byte
      // num=Wire.endTransmission(); 

      // Serial.print("end transmit code");
      // Serial.println(num);
      // Serial.println("Finished write, Begin read");
      // Wire.requestFrom(0x0D, 1); // requst 6 bytes
      // if(Wire.available()>=1){
      //   Serial.println("contact made");
      // }
      // Serial.println("reading");
      // int c= Wire.read();
      // Serial.println(c);
      
      // delay(5000);
   }
}