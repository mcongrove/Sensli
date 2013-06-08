/*
 * Setup LEDs
 */
void LedSetup(int* pins)
{
  // TODO: Load initial color settings
  
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
void LedSetColor(int red, int green, int blue)
{
  RED   = red;
  GREEN = green;
  BLUE  = blue;
}

/*
 * Turn the LEDs on
 */
void LedOn(int* pins)
{
  // Save state
  LED_STATE = true;
  
  // Write to each LED pin
  digitalWrite(pins[0], RED);
  digitalWrite(pins[1], GREEN);
  digitalWrite(pins[2], BLUE);
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
