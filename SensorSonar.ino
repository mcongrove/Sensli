int SENSOR_SONAR_PINS[2] = { 7, 8 };
int SENSOR_SONAR_BUTTON  = 4;
int SENSOR_SONAR_THRESHOLD = 0;
int SENSOR_SONAR_CAN_TRIGGER = true;

int SensorSonarSetup()
{
  pinMode(SENSOR_SONAR_PINS[0], OUTPUT);
  pinMode(SENSOR_SONAR_PINS[1], INPUT);
  pinMode(SENSOR_SONAR_BUTTON, INPUT);
}

void SensorSonarButtonListener()
{
  int state = digitalRead(SENSOR_SONAR_BUTTON);
  
  if (state == HIGH)
  {
    int distance = SensorSonarRead();
    
    if (distance <= 7)
    {
      return;
    }
    
    SENSOR_SONAR_THRESHOLD = distance;
    byte EEPROM_DATA       = EEPROM.read(EEPROM_ADDRESS + (SENSOR_SONAR * 100));
    
    if (SENSOR_SONAR_THRESHOLD != EEPROM_DATA)
    {
      EEPROM.write(EEPROM_ADDRESS + (SENSOR_SONAR * 100), SENSOR_SONAR_THRESHOLD);
    }
  }
}

int SensorSonarRead()
{
  long duration, inches;
  
  digitalWrite(SENSOR_SONAR_PINS[0], LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_SONAR_PINS[0], HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_SONAR_PINS[0], LOW);
  
  duration = pulseIn(SENSOR_SONAR_PINS[1], HIGH);
  inches   = SensorSonarConvert(duration) % 100;
  
  return (int) inches;
}

long SensorSonarConvert(long duration)
{
  return round(duration / 74 / 2);
}

int SensorSonarState()
{
  int data = SensorSonarRead();
  
  if (data < SENSOR_SONAR_THRESHOLD)
  {
    if (SENSOR_SONAR_CAN_TRIGGER)
    {
      SENSOR_SONAR_CAN_TRIGGER = false;
      
      return 1;
    } else {
      return 0;
    }
  } else {
    SENSOR_SONAR_CAN_TRIGGER = true;
    
    return 0;
  }
}
