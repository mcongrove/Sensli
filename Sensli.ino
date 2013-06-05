/*
  FEATURES LEFT TO IMPLEMENT:
    Channel Input
    RGB Color Input
    Sonar Distance Input
    PIR Control
*/

#include <math.h>

// CONTROLLER INFORMATION
const boolean TRANSMITTER = false;
const boolean RECEIVER    = true;
const boolean WIRELESS    = true;

// SENSOR INFORMATION
const int SENSOR_SONAR     = 1;
const int SENSOR_PIR       = 2;

// CUSTOM SETTINGS
int SENSOR       = SENSOR_SONAR;
int STUTTER      = 3000;
int LED_COLOR[3] = { 255, 255, 255 };
int LED_PINS[3]  = { 10, 11, 9 };

// STATES
boolean CAN_TRIGGER   = true;
boolean TRIGGER_STATE = false;
boolean LED_STATE     = false;
int DATA;
int DATA_PREVIOUS;

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
  if (TRANSMITTER || (WIRELESS && RECEIVER))
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
    
    if (TRANSMITTER)
    {
      if (DATA != DATA_PREVIOUS)
      {
        RadioFrequencyWrite(((SENSOR * 100) + DATA));
        
        DATA_PREVIOUS = DATA;
        
        delay(STUTTER);
        
        return;
      }
    }
  }
  
  if (WIRELESS && RECEIVER)
  {
    DATA = RadioFrequencyRead();
    
    if (DATA == 0)
    {
      return;
    }
    
    Serial.println(DATA);
    
    SENSOR = floor(DATA / 100);
    DATA   = DATA % 100;
  }
  
  switch(SENSOR)
  {
    // ULTRASONIC
    case 1:
      if (DATA == 1)
      {
        TRIGGER_STATE = true;
      } else {
        TRIGGER_STATE = false;
      }
      break;
    // PIR
    case 2:
      break;
  }
  
  if (RECEIVER)
  {
    if (!CAN_TRIGGER && !TRIGGER_STATE)
    {
      CAN_TRIGGER = true;
      
      return;
    }
    
    if (CAN_TRIGGER && TRIGGER_STATE)
    {
      if (!LED_STATE)
      {
        LedOn(LED_PINS);
      } else {
        LedOff(LED_PINS);
      }
      
      CAN_TRIGGER = false;
      
      delay(STUTTER);
      
      return;
    }
  }
}
