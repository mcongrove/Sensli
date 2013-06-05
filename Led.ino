int RED   = 255;
int GREEN = 255;
int BLUE  = 255;

void LedSetup(int* pins)
{
  for (int i = 0; i < 3; i++)
  {
    pinMode(pins[i], OUTPUT);
  }
}

void LedSetColor(int* color)
{
  RED   = color[0];
  GREEN = color[1];
  BLUE  = color[2];
}

void LedOn(int* pins)
{
  LED_STATE = true;
  
  digitalWrite(pins[0], RED);
  digitalWrite(pins[1], GREEN);
  digitalWrite(pins[2], BLUE);
}

void LedOff(int* pins)
{
  LED_STATE = false;
  
  digitalWrite(pins[0], 0);
  digitalWrite(pins[1], 0);
  digitalWrite(pins[2], 0);
}