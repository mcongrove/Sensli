// Include required libraries
#include <math.h>
#include <VirtualWire.h>
#include <EEPROM.h>

// Controller information
const boolean TRANSMITTER = false;
const boolean RECEIVER    = true;
const boolean WIRELESS    = true;

// Sensor information
const int SENSOR_SONAR = 1;
const int SENSOR_PIR   = 2;

// States
boolean TRIGGER_STATE = false;
boolean LED_STATE     = false;

// Data Information
int DATA;
unsigned long DATA_TIMESTAMP;
int EEPROM_ADDRESS = 0;

// User-defined settings
int SENSOR       = SENSOR_SONAR;
int STUTTER      = 3000;
int LED_COLOR[3] = { 255, 255, 255 };
int LED_PINS[3]  = { 10, 11, 9 };

/*
 * Setup function, runs once at Arduino start
 */
void setup()
{
  // Open serial communications
  Serial.begin(9600);
  
  // Check if controller is wireless-enabled
  if (WIRELESS)
  {
    // Set up RF communications
    RadioFrequencySetup();
  }
  
  // Check if controller is receiver
  if (RECEIVER)
  {
    // Set up LEDs
    LedSetup(LED_PINS);
    LedSetColor(LED_COLOR);
  }
  
  // Check if we have a sensor on-board
  if (!WIRELESS || TRANSMITTER)
  {
    // Determine the sensor
    switch(SENSOR)
    {
      case 1:
        // Set up the Sonar sensor
        SensorSonarSetup();
        break;
      case 2:
        break;
    }
  }
}

/*
 * Loop function, runs indefinitely after Arduino start and setup
 */
void loop()
{
  // Check if the sensor is on-board
  if (TRANSMITTER || (!WIRELESS && RECEIVER))
  {
    // Check if using sonar sensor
    if (SENSOR == SENSOR_SONAR)
    {
      // Listen for the button to set sonar threshold
      SensorSonarButtonListener();
      
      // Read the state of the sonar sensor
      DATA = SensorSonarState();
    }
    
    // Check if using PIR sensor
    if (SENSOR == SENSOR_PIR)
    {
      // Do Something
    }
    
    // Check if we have data
    if (DATA != 0)
    {
      // Check if controller is transmitter
      if (TRANSMITTER)
      {
        // Send data over RF
        RadioFrequencyWrite(((SENSOR * 100) + DATA));
        
        // Output data for debugging
        // Serial.println(DATA);
      }
      
      // Delay to purposefully miss data immediately after trigger
      delay(STUTTER);
      
      // Exit, done transmitting data
      return;
    }
  }
  
  // Check if controller is receiver
  if (RECEIVER)
  {
    // Check if controller is wireless-enabled
    if (WIRELESS)
    {
      // Read RF communication data
      DATA = RadioFrequencyRead();
      
      // Check if we have data
      if (DATA == 0)
      {
        return;
      }
      
      // Determine what kind of sensor sent the data
      SENSOR    = floor(DATA / 100);
      
      // Remove sensor identifier from data
      DATA      = DATA % 100;
      
      // Get timestamp of data retrieval
      unsigned long timestamp = millis();
      
      // Check if data was retrieved too soon after last data retrieval
      if ((timestamp - DATA_TIMESTAMP) > STUTTER)
      {
        // Output data for debugging
        //Serial.println(DATA);
        
        // Save timestamp of data retrieval
        DATA_TIMESTAMP = timestamp;
      } else {
        // Exit, data was retrieved too soon after last retrieval
        return;
      }
    }
    
    // Check if sensor has been triggered
    if (DATA == 1)
    {
      // Check if LEDs are on or off
      if (!LED_STATE)
      {
        // Turn LEDs on
        LedOn(LED_PINS);
      } else {
        // Turn LEDs off
        LedOff(LED_PINS);
      }
    }
  }
}
