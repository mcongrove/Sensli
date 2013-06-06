// Sonar information
int SENSOR_SONAR_PINS[2] = { 7, 8 };
int SENSOR_SONAR_BUTTON  = 4;
int SENSOR_SONAR_THRESHOLD = 0;
int SENSOR_SONAR_CAN_TRIGGER = true;

/*
 * Setup sonar sensor
 */
int SensorSonarSetup()
{
  // Set each pin for output or input
  pinMode(SENSOR_SONAR_PINS[0], OUTPUT);
  pinMode(SENSOR_SONAR_PINS[1], INPUT);
  pinMode(SENSOR_SONAR_BUTTON, INPUT);
}

/*
 * Listen for the button that sets the sonar threshold
 */
void SensorSonarButtonListener()
{
  // Read state of button
  int state = digitalRead(SENSOR_SONAR_BUTTON);
  
  // Check if button is pressed
  if (state == HIGH)
  {
    // Read the distance from the sonar sensor
    int distance = SensorSonarRead();
    
    // Ensure that the distance is far enough away
    if (distance <= 7)
    {
      // Exit, if value is too small
      return;
    }
    
    // Set the sonar threshold
    SENSOR_SONAR_THRESHOLD = distance;
    
    // Read the previous threshold from EEPROM
    byte EEPROM_DATA       = EEPROM.read(EEPROM_ADDRESS + (SENSOR_SONAR * 100));
    
    // Check if new threshold is different from saved threshold
    if (SENSOR_SONAR_THRESHOLD != EEPROM_DATA)
    {
      // Write new threshold if it's a different value
      EEPROM.write(EEPROM_ADDRESS + (SENSOR_SONAR * 100), SENSOR_SONAR_THRESHOLD);
    }
  }
}

/*
 * Read the distance from the sonar sensor
 */
int SensorSonarRead()
{
  long duration, inches;
  
  // Send a LOW to clear the sensor readings
  digitalWrite(SENSOR_SONAR_PINS[0], LOW);
  delayMicroseconds(2);
  
  // Send a 10uS HIGH pulse
  digitalWrite(SENSOR_SONAR_PINS[0], HIGH);
  delayMicroseconds(10);
  
  // Send a LOW to stop sending the pulse
  digitalWrite(SENSOR_SONAR_PINS[0], LOW);
  
  // Determine how long the pulse takes to return
  duration = pulseIn(SENSOR_SONAR_PINS[1], HIGH);
  
  // Convert the pulse time to a distance (inches)
  inches   = SensorSonarConvert(duration) % 100;
  
  return (int) inches;
}

/*
 * Converts a pulse time to a distance (inches)
 */
long SensorSonarConvert(long duration)
{
  return round(duration / 74 / 2);
}

/*
 * Determines if the sensor should trigger the LEDs
 */
int SensorSonarState()
{
  // Read data from the sonar sensor
  int data = SensorSonarRead();
  
  // Check if distance is inside the threshold
  if (data < SENSOR_SONAR_THRESHOLD)
  {
    // Check if the sensor can be triggered
    if (SENSOR_SONAR_CAN_TRIGGER)
    {
      // Block further triggering
      // This is to account for an object staying in front of the sensor after trigger
      SENSOR_SONAR_CAN_TRIGGER = false;
      
      // Exit, trigger
      return 1;
    } else {
      // Exit, no trigger
      return 0;
    }
  } else {
    // Set trigger as available
    // This ensures that the object has moved beyong the trigger area
    SENSOR_SONAR_CAN_TRIGGER = true;
    
    // Exit, not within threshold
    return 0;
  }
}
