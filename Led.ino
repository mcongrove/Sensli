// Color values for each RGB channel
int RED   = 255;
int GREEN = 255;
int BLUE  = 255;

/*
 * Setup LEDs
 */
void LedSetup(int* pins)
{
  // Loop through all LEDs
  for (int i = 0; i < 3; i++)
  {
    // Setup each pin for output
    pinMode(pins[i], OUTPUT);
  }
}

/*
 * Save the color for the LEDs
 */
void LedSetColor(int* color)
{
  RED   = color[0];
  GREEN = color[1];
  BLUE  = color[2];
}

/*
 * Turn the LEDs on
 */
void LedOn(int* pins)
{
  // Save state
  LED_STATE = true;
  
  // Write to each LED pin
  analogWrite(pins[0], RED);
  analogWrite(pins[1], GREEN);
  analogWrite(pins[2], BLUE);
}

/*
 * Turn the LEDs off
 */
void LedOff(int* pins)
{
  // Save state
  LED_STATE = false;
  
  // Write to each LED pin
  digitalWrite(pins[0], 0);
  digitalWrite(pins[1], 0);
  digitalWrite(pins[2], 0);
}
