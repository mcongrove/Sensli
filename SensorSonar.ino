int SENSOR_SONAR_PINS[2] = { 7, 8 };

int SensorSonarSetup()
{
  pinMode(SENSOR_SONAR_PINS[0], OUTPUT);
  pinMode(SENSOR_SONAR_PINS[1], INPUT);
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
