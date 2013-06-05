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

int SensorSonarButtonListener()
{
  int state = digitalRead(SENSOR_SONAR_BUTTON);
  
  if (state == HIGH)
  {
    SENSOR_SONAR_THRESHOLD = SensorSonarRead() - 2;
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
