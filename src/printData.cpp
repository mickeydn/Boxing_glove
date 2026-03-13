/*
 * Project myProject
 * Author: Your Name
 * Date:
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */


// *Note*, build w device OS 5.6.0 to avoid memory overflow error 
//
// This example prints a wav file to the USB serial debugging port in hex
// particle serial monitor | tee t1.hex
//
//replace the first two lines of the csv with a header:
//timestamp,accX,accY,accZ



#include "Particle.h"
#include "adxl343.h"
#include <math.h>

void readAccelerometer();

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

SerialLogHandler logHandler(LOG_LEVEL_INFO);
ADXL343 accelerometer;
Timer accelerometerTicker(10, readAccelerometer);

unsigned long ms, msStart;
float accelX = 0.0f;
float accelY = 0.0f;
float accelZ = 0.0f;
float threshold = 1.5f;
unsigned long lastPunch = 0;
int marker = 0;

int timer = 0;

void readAccelerometer()
{
  // add timestamp im millis
  ms = millis() - msStart;
  accelerometer.readAccelerationG(&accelX, &accelY, &accelZ);
  // Log.info("X: %0.3f g, Y: %0.3f g, Z: %0.3f g", accelX, accelY, accelZ);
  
  // Calculate total acceleration
  float totalAcc = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  
  // Check for punch detection
  if (totalAcc > threshold && (ms - lastPunch) > 500) {
    marker = 1; // Mark this data point as a punch
    lastPunch = millis();
    digitalWrite(D7, HIGH); // Flash the built-in LED to indicate a punch was detected
  }else {
    marker = 0;
    digitalWrite(D7, LOW);
  }
    
    
    // Update last punch time
  Serial.print(ms);
  Serial.print(',');
  Serial.print((int)(1000 * accelX));
  Serial.print(',');
  Serial.print((int)(1000 * accelY));
  Serial.print(',');
  Serial.print((int)(1000 * accelZ));
  Serial.print(',');
  Serial.print((int)(1000 * totalAcc));
  Serial.print(',');
  Serial.print(marker);
  Serial.print('\n');
  timer++;
    
}

void setup()
{
  Serial.begin(115200);

  pinMode(D7, OUTPUT);
  digitalWrite(D7, LOW); // Turn on the built-in LED to indicate setup is running


  Log.info("Initializing ADXL343...");
  if (!accelerometer.begin())
  {
    Log.error("Failed to initialize ADXL343.");
    // while (1); // Halt execution
  }
  //print header
  Serial.print("timestamp,accX,accY,accZ,totalAcc,marker");
  accelerometerTicker.start();
  msStart = millis();
}

void loop()
{
  // Main loop can perform other tasks if necessary
  // if((timer % 10) == 0)
  // Log.info("tick");
}

