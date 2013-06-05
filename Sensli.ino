/*
  FEATURES LEFT TO IMPLEMENT:
    Channel Input
    RGB Color Input
    Sonar Distance Input
    PIR Control
*/

#include <math.h>

// CONTROLLER INFORMATION
const boolean TRANSMITTER = true;
const boolean RECEIVER    = false;
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
    
    if (DATA != DATA_PREVIOUS)
    {
      Serial.print("Writing: ");
      Serial.println(DATA);
      
      RadioFrequencyWrite(((SENSOR * 100) + DATA));
      
      DATA_PREVIOUS = DATA;
      
      delay(500);
    }
  }
  
  
  
  
  
  
  
  
  /*
  if (WIRELESS && RECEIVER)
  {
    DATA = RadioFrequencyRead();
    
    if (DATA == 0)
    {
      return;
    }
    
    Serial.println(DATA);
    
    SENSOR = floor(DATA / 100);
  }
  
  switch(SENSOR)
  {
    // ULTRASONIC
    case 1:
      if (TRANSMITTER || !WIRELESS)
      {
        DATA = SensorSonarRead();
      } else {
        DATA = DATA - (SENSOR_SONAR * 100);
      }
      
      if (RECEIVER)
      {
        if (DATA < SENSOR_SONAR_THRESHOLD)
        {
          TRIGGER_STATE = true;
        } else {
          TRIGGER_STATE = false;
        }
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
  } else if (TRANSMITTER) {
    if (DATA != DATA_PREVIOUS)
    {
      RadioFrequencyWrite(((SENSOR * 100) + DATA));
      
      DATA_PREVIOUS = DATA;
      
      delay(200);
    } else {
      delay(100);
    }
    
    return;
  }
  */
}