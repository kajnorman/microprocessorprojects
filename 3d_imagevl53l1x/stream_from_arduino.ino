#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>


char opticalCenter[256] = { 
  128,136,144,152,160,168,176,184,  192,200,208,216,224,232,240,248
  , 129,137,145,153,161,169,177,185,  193,201,209,217,225,233,241,249
  , 130,138,146,154,162,170,178,186,  194,202,210,218,226,234,242,250
  , 131,139,147,155,163,171,179,187,  195,203,211,219,227,235,243,251
  , 132,140,148,156,164,172,180,188,  196,204,212,220,228,236,244,252
  , 133,141,149,157,165,173,181,189,  197,205,213,221,229,237,245,253
  , 134,142,150,158,166,174,182,190,  198,206,214,222,230,238,246,254
  , 135,143,151,159,167,175,183,191,  199,207,215,223,231,239,247,255
  
  , 127,119,111,103, 95, 87, 79, 71,  63, 55, 47, 39, 31, 23, 15, 7
  , 126,118,110,102, 94, 86, 78, 70,  62, 54, 46, 38, 30, 22, 14, 6
  , 125,117,109,101, 93, 85, 77, 69,  61, 53, 45, 37, 29, 21, 13, 5
  , 124,116,108,100, 92, 84, 76, 68,  60, 52, 44, 36, 28, 20, 12, 4
  , 123,115,107, 99, 91, 83, 75, 67,  59, 51, 43, 35, 27, 19, 11, 3
  , 122,114,106, 98, 90, 82, 74, 66,  58, 50, 42, 34, 26, 18, 10, 2
  , 121,113,105, 97, 89, 81, 73, 65,  57, 49, 41, 33, 25, 17, 9, 1
  , 120,112,104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0 };
/*
  Reading distance from the laser based VL53L1X
  Originally By: Nathan Seidle
  Extended by jweh@eaaa.dk, knn@eaaa.dk 
  SparkFun Electronics
  Date: April 4th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SparkFun labored with love to create this code. Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14667

  This example prints the distance to an object sets the ROI to 4x4 
  It sends a matrix of 13 x 13 distance 
  values are sent according to the following protocol.
      <x-value><space><y-value><space><distance measured><newline>
  example :
    2 5 676
    3 5 620
    4 5 633
    5 5 578
    6 5 555
    7 5 503
    8 5 523
    9 5 474
    10 5 524
    11 5 554
    12 5 574

  A 3-d visualization program to map the measurements in space exists.
  Are you getting weird readings? Be sure the vacuum tape has been removed from the sensor.
*/

#include <Wire.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X

//Optional interrupt and shutdown pins.
#define SHUTDOWN_PIN 2
#define INTERRUPT_PIN 3

SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
//SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void setup(void)
{
  Wire.begin();

  Serial.begin(115200);
  Serial.println("VL53L1X Qwiic Test");

  if (distanceSensor.begin() != 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Serial.println("Sensor online!");
  distanceSensor.setDistanceModeShort();
//  distanceSensor.setROI(4,4,199);
  distanceSensor.setTimingBudgetInMs(20);
  distanceSensor.setIntermeasurementPeriod(20);
}

void loop(void)
{


  
  for(int y=2;y<=13;y++)
  for(int x=2;x<=13;x++)
  //for(int n=0;n<=255;n++)
  {
          int n=x + y*16;
          distanceSensor.setROI(4,4,opticalCenter[n]);

          distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
          while (!distanceSensor.checkForDataReady())
          {
            delay(1);
          }
          int distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
          distanceSensor.clearInterrupt();
          distanceSensor.stopRanging();
//         Serial.print(n);
//          Serial.print(" Distance(mm): ");
          Serial.print(x);
          Serial.print(" ");
          Serial.print(y);
          Serial.print(" ");
          Serial.print(distance);
          Serial.println();
  }


//  Serial.println("-------------------------");
}
