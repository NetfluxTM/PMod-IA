/* @file Main.cpp
 *
 * @brief Reads impedance values from the AD5933
 * 
 * ! The gain settings need to be chosen to place the excitation signal in the linear region of the on-board ADC.!
 * Must recalculate gain if any of these parameters change:
 *    Current-to-voltage gain setting resistor
 *    Output excitation voltage
 *    PGA gain
 * 
 * To save memory and allow for data to be processed in real time, remove abstraction 
 * example) https://github.com/mjmeli/arduino-ad5933/blob/master/examples/ad5933-test/ad5933-test.ino
 * 
 * 
 * Impedance is (gain * magnitude)^-1
 * Phase is unknown_phase - system_phase
 * 
 * 
 */
#include <avr/io.h>
#include <Arduino.h>
#include <Wire.h>
#include "AD5933.h"

#define REF_RESIST (500.1) // The known reference resistor for calibration

int main(){
   // unsigned long  startFrequency     = 15000; // start frequency
   // unsigned long  incrementFrequency = 1;  // frequency increment
   // unsigned int   numberIncrements   = 2;   // number of increments (points in the sweep)
   // int   numberMeasurements = numberIncrements+1;   // number of discrete measurements to be taken
   // int real [numberMeasurements] = { };
   // int imag [numberMeasurements] = { };


   unsigned long  startFrequency     = 15000;   // start frequency
   unsigned long  incrementFrequency = 1;       // frequency increment
   unsigned int   numberIncrements   = 10;     // number of increments (points in the sweep)
   unsigned int   numberMeasurements=numberIncrements+1;
   int real [numberMeasurements] = { };         // array to hold the real data
   int imag [numberMeasurements] = { };         // array to hold the imaginary data
   int phase [numberMeasurements];         // array to hold the system phase data
   int phaseZ [numberMeasurements];     // Calculated phase of the impedance
   double gain [numberMeasurements];       // array to hold the gain factors
   double magZ [numberMeasurements];       // Calculated magnitude of the impedance

   // Initializations
   sei(); // enable global interrupts... 
   Serial.begin(9600);
   AD5933 pmodIA;
   Wire.begin(); // join i2c bus (address optional for master)
   //delay(3000);
  
   Serial.println("Starting");

   //TestCode Remove down
 

   //TestCode Remove ^^^^^




   // Setting Frequency Sweep Registers
   if(!(pmodIA.setStartFrequency(startFrequency))) {
      Serial.println("Setting start frequency failed.");
   }
   if(!(pmodIA.setIncrementFrequency(incrementFrequency))) {
      Serial.println("Setting frequency increment failed.");
   }
   if(!(pmodIA.setNumberIncrements(numberIncrements))) {
      Serial.println("Setting number of increments failed.");
   }
   if(pmodIA.setPGAGain(CTRL_PGA_GAIN_X5)==false){
      Serial.println("Setting PGA Gain Failed.");
   }
   if(!(pmodIA.setOutputRange(CTRL_OUTPUT_RANGE4))){
     Serial.println("Setting output Range Failed");
  }
  


   if(!(pmodIA.calibrate(gain, phase, real, imag, REF_RESIST, numberMeasurements))){
      Serial.println("Calibration failed.");
   } // Do Not Modify Past This Point: PGA gain, output excitation voltage, or current-to-voltage gain setting resistor.
   //Serial.println(gain[1]);
 
 
 //Headings
        Serial.print("Real");
        Serial.print("    ");
        Serial.print("Imaginary");
        Serial.print("    ");
        Serial.print("Impedance");
        Serial.print("    ");
        Serial.print("Phase");
        Serial.println("    "); 

   while(1){
      Serial.println("Loop Iteration");
   if(!(pmodIA.frequencySweep(real, imag, numberMeasurements))) {
      Serial.println("Frequency sweep failed.");
      }
      pmodIA.calculate(magZ, phaseZ, gain, phase, real, imag, numberMeasurements);
      double sum=0;
      for(int i =0;i<=numberMeasurements;i++){
         
         sum+=magZ[i];
      }
      Serial.println(sum/numberMeasurements-REF_RESIST);
   }
      //pmodIA.calculate(magZ, phaseZ, gain, phase, real, imag, numberMeasurements);



   // int magn;
   // for(unsigned int i=0; i<numberIncrements; i++) {
   // Serial.print(realArray[i]);
   // Serial.print("  ");
   // Serial.print(imagArray[i]);
   // Serial.print("   ");
   // magn = sqrt(pow(realArray[i],2) + pow(imagArray[i],2));
   // Serial.println(magn);
   // }

/*
   int magnitude;
   for(unsigned int i=0; i<numberIncrements; i++) {
   Serial.print(realArray[i]);
   Serial.print("  ");
   Serial.print(imagArray[i]);
   Serial.print("   ");
   magnitude = sqrt(pow(realArray[i],2) + pow(imagArray[i],2));
   Serial.println(magnitude);
   } */

/*
      //******program parameters into relavant registers******
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
      */
}