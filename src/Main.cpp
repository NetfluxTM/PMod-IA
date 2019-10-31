/*
 * Description:
 *    Reads/Writes data to PmodIA via I2C.
 *    Sends commands to slave to initiate impedance analysis
 *    Reads impedance data back to arduino board (master).
 * 
 * Questions / Look into:
 *    Step 1 could be condensed. if desired.
 *    getByte returns an int, but inside the code actually returns true and false.
 *       Should we change it to a bool?
 *    Do we need to set clock source or set internal clock?
 *       A: default clock option on power-up is internal clock
 * 
 * Most Recent Changes:
 *    added numberMeasurements
 *    changed initial variables into unsigned
 *    added comments for freq. sweep sequence
 *    added register setting
 *    added arrays for holding data
 *    added frequencySweep call
 * 
 * To Do: 
 *    Frequency Sweep goes back and forth between working and failing.
 *       PLUS, weird bug where it only prints the first two characters starts happening
 *       again as soon as it's past the function call.
 *    Verify data being returned is good & complete. start printing to a file instead of monitor?
 *    Use setOutputRange to...set output range
 *       
 */

#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>
#include "AD5933.h"

const int address = 0x0D; // can also use "AD5933_ADDR" defined in AD5933.h


int main(){
   unsigned long  startFrequency     = 15000; // start frequency
   unsigned long  incrementFrequency = 1;  // frequency increment
   unsigned int   numberIncrements   = 100;   // number of increments (points in the sweep)
   int   numberMeasurements = numberIncrements+1;   // number of discrete measurements to be taken
   
   int realArray [numberMeasurements] = { };
   int imagArray [numberMeasurements] = { };


   // Startup Initialization Procedures
   sei(); //enable global interrupts... 
   Serial.begin(9600);
   AD5933 pmodIA;
   Wire.begin(); // join i2c bus (address optional for master)

/* Frequency Sweep Sequence:
 * 1) Program Frequency Sweep Parameters into relevant registers
 *    a) Start Frequency
 *    b) # of increments
 *    c) frequency increment
 * 
 * 2) AD5933::frequencySweep
 *    a) This function will:
 *          Enter standby mode
 *          Enter initialize mode
 *          Enter freq sweep mode
 *    b) Will also perform the sweep for us
 */
   //Step 1
   if(pmodIA.setStartFrequency(startFrequency) == false) {
      Serial.println("Setting start frequency failed.");
   }

   if(pmodIA.setIncrementFrequency(incrementFrequency) == false) {
      Serial.println("Setting frequency increment failed.");
   }

   if(pmodIA.setNumberIncrements(numberIncrements) == false) {
      Serial.println("Setting number of increments failed.");
   }


   // Step 2




   // int magn;
   // for(unsigned int i=0; i<numberIncrements; i++) {
   // Serial.print(realArray[i]);
   // Serial.print("  ");
   // Serial.print(imagArray[i]);
   // Serial.print("   ");
   // magn = sqrt(pow(realArray[i],2) + pow(imagArray[i],2));
   // Serial.println(magn);
   // }


while(1){ //Need this to stop from exiting main at end of code. Otherwise the world explodes
   if(!(pmodIA.frequencySweep(realArray, imagArray, numberMeasurements))) {
      Serial.println("Frequency sweep failed.");
   }
}


   // Serial.println("Got to here 2");
   // //set start frequency
   // pmodIA.setStartFrequency(startFrequency);
   // Serial.println("Got to here 3");
   // //number of increments
   // pmodIA.setIncrementFrequency(incrementFrequency);
   // Serial.println("Got to here 4");
   // //frequency increment
   // pmodIA.setNumberIncrements(numberIncrements);
   // Serial.println("Got to here 5");
   // while(1) {
   //    Serial.println("Got to here 6");
   //    Serial.print("Start frequency set");
   //    Serial.print("Set Value: "); 
   //    Serial.println(startFrequency);

   //    long frequencySet1=pmodIA.readRegister(START_FREQ_1);

   //    long frequencySet2=pmodIA.readRegister(START_FREQ_2);
   //    Serial.println("actuall read data");
   //    Serial.println(frequencySet2);
   //    long frequencySet3=pmodIA.readRegister(START_FREQ_3);
   //    long frequency=(frequencySet1<<16)||(frequencySet2<<8)||(frequencySet3);
   //    Serial.print("Actual Value: ");
   //    Serial.println(frequency);
   //    delay(1000);
   // }


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