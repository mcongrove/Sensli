/*
  FEATURES LEFT TO IMPLEMENT:
    Channel Input
    RGB Color Input
    PIR Control
*/

#include <math.h>
#include <EEPROM.h>

// CONTROLLER INFORMATION
const boolean TRANSMITTER = false;
const boolean RECEIVER    = true;
const boolean WIRELESS    = true;

// SENSOR INFORMATION
const int SENSOR_SONAR = 1;
const int SENSOR_PIR   = 2;

// CUSTOM SETTINGS
int SENSOR       = SENSOR_SONAR;
int STUTTER      = 3000;
int LED_COLOR[3] = { 255, 255, 255 };
int LED_PINS[3]  = { 10, 11, 9 };

// STATES
boolean TRIGGER_STATE = false;
boolean LED_STATE     = false;

// DATA INFORMATION
int DATA;
unsigned long DATA_TIMESTAMP;
int EEPROM_ADDRESS = 0;

void setup()
{
  Serial.begin(9600);
  
  if (WIRELESS)
  {
    RadioFrequencySetup();
  }
  
  if (RECEIVER)
  {
    LedSetup(LED_PINS);
    LedSetColor(LED_COLOR);
  }
  
  if (!WIRELESS || TRANSMITTER)
  {
    switch(SENSOR)
    {
      case 1:
        SensorSonarSetup();
        break;
      case 2:
        
        break;
    }
  }
}

void loop()
{
  unsigned long TIMESTAMP;
  
  if (TRANSMITTER || (!WIRELESS && RECEIVER))
  {
    if (SENSOR == SENSOR_SONAR)
    {
      SensorSonarButtonListener();
      
      DATA = SensorSonarState();
    }
    
    if (SENSOR == SENSOR_PIR)
    {
      // Do Something
    }
    
    if (DATA != 0)
    {
      if (TRANSMITTER)
      {
        RadioFrequencyWrite(((SENSOR * 100) + DATA));
        
        Serial.println(DATA);
      }
      
      delay(STUTTER);
      
      return;
    }
  }
  
  if (RECEIVER)
  {
    if (WIRELESS)
    {
      DATA = RadioFrequencyRead();
      
      if (DATA == 0)
      {
        return;
      }
      
      SENSOR    = floor(DATA / 100);
      DATA      = DATA % 100;
      TIMESTAMP = millis();
      
      if ((TIMESTAMP - DATA_TIMESTAMP) > STUTTER)
      {
        Serial.println(DATA);
        
        DATA_TIMESTAMP = TIMESTAMP;
      } else {
        return;
      }
    }
    
    if (DATA == 1)
    {
      if (!LED_STATE)
      {
        LedOn(LED_PINS);
      } else {
        LedOff(LED_PINS);
      }
    }
  }
}
