
// Arduino data logger with SD card and DHT11 humidity and temperature sensor
// https://simple-circuit.com/arduino-sd-card-dht11-data-logger/

#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library
#include "dht.h"
File dataFile;
dht DHT;
#define DHTPIN A0            // DHT11 data pin is connected to Arduino pin 4

const int chipSelect = 4; 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   delay(5000); //Delay to let system boot
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  delay(2000);
}
 
uint16_t line = 1;
 
void loop() {
    delay(5000);
    DHT.read11(DHTPIN);
   // Read humidity
  int RH = DHT.humidity;
  //Read temperature in degree Celsius
  int Temp = DHT.temperature;
 
  dataFile = SD.open("DHT11Log.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (dataFile) {
    Serial.print(line);
    Serial.print(":    Temperature = ");
    Serial.print((Temp * 1.8000)+32);
    Serial.print("°F,    Humidity = ");
    Serial.print(RH);
    Serial.println("%");
    
    // Write data to SD card file (DHT11Log.txt)
    dataFile.print(line++);
    dataFile.print(":    Temperature = ");
    dataFile.print((Temp * 1.8000)+32);
    dataFile.print("°C,    Humidity = ");
    dataFile.print(RH);
    dataFile.println("%");
    dataFile.close();  
  }
  // if the file didn't open, print an error:
  else
    Serial.println("error opening DHT11Log.txt");
}
