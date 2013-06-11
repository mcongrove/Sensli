// Menu information
const int MENU_LCD_PIN        = 5;
const int MENU_DPAD_UP        = 8;
const int MENU_DPAD_DOWN      = 10;
const int MENU_DPAD_LEFT      = 11;
const int MENU_DPAD_RIGHT     = 9;
const int MENU_DPAD_PUSH      = 12;
const int MENU_LIST_LENGTH[7] = { 7, 255, 255, 255, 3, 5, 0 };
int MENU_INDEX                = 1;
int MENU_LIST                 = 0;
int MENU_VALUE                = 0;
int MENU_VALUES[7]            = { 1, 255, 255, 255, 1, 1, 0 };

// Instantiate LCD screen
SoftwareSerial MENU_LCD = SoftwareSerial(255, MENU_LCD_PIN);

/*
 * Set up menu
 */
void MenuSetup()
{ 
  // Set pins for input and output
  pinMode(MENU_LCD_PIN, OUTPUT);
  pinMode(MENU_DPAD_UP, INPUT);
  pinMode(MENU_DPAD_DOWN, INPUT);
  pinMode(MENU_DPAD_LEFT, INPUT);
  pinMode(MENU_DPAD_RIGHT, INPUT);
  pinMode(MENU_DPAD_PUSH, INPUT);
  
  // Write LCD pin to HIGH to start serial connection
  digitalWrite(MENU_LCD_PIN, HIGH);
  
  // Start serial connection to LCD
  MENU_LCD.begin(9600);
  
  delay(100);
  
  // Reset the LCD
  MENU_LCD.write(18);
  MENU_LCD.write(21);
  MENU_LCD.write(12);
  
  delay(5);
  
  // Define custom character, arrow
  MENU_LCD.write(249);
  MENU_LCD.write((byte)00000);
  MENU_LCD.write(B00100);
  MENU_LCD.write(B00010);
  MENU_LCD.write(B11111);
  MENU_LCD.write(B00010);
  MENU_LCD.write(B00100);
  MENU_LCD.write((byte)00000);
  MENU_LCD.write((byte)00000);
  
  delay(5);
}

/*
 * Turn LCD on
 */
void MenuOn()
{
  MENU_STATE = true;
  
  // Turn on LEDs for visual editing
  LedOn(LED_PINS);
  
  // Turn on LCD and reset
  MENU_LCD.write(22);
  MENU_LCD.write(17);
  MENU_LCD.write(12);
  
  delay(5);
  
  // Print welcome message
  MENU_LCD.print("   Welcome to   ");
  MENU_LCD.print("     Sensli     ");
  
  delay(1000);
  
  // Show the menu
  MenuShowItem();
}

/*
 * Turn LCD off
 */
void MenuOff()
{
  // Turn off and reset the LCD
  MENU_LCD.write(18);
  MENU_LCD.write(21);
  MENU_LCD.write(12);
  
  delay(5);
  
  // Reset variables
  MENU_STATE = false;
  MENU_LIST  = 0;
  MENU_INDEX = 1;
  MENU_VALUE = 0;
  
  // Turn off LEDs
  LedOff(LED_PINS);
}

/*
 * Handle menu navigation
 */
void MenuShowItem()
{
  // Clear the LCD
  MENU_LCD.write(12);
  
  delay(5);
  
  // Switch on menu depth
  switch(MENU_LIST)
  {
    // Main menu
    case 0:
      // Switch on menu index
      switch(MENU_INDEX)
      {
        case 1:
          MENU_LCD.write(1);
          MENU_LCD.print("Color: Red");
          MENU_LCD.write(13);
          MENU_LCD.print(" Color: Green");
          break;
        case 2:
          MENU_LCD.write(1);
          MENU_LCD.print("Color: Green");
          MENU_LCD.write(13);
          MENU_LCD.print(" Color: Blue");
          break;
        case 3:
          MENU_LCD.write(1);
          MENU_LCD.print("Color: Blue");
          MENU_LCD.write(13);
          MENU_LCD.print(" Color: Presets");
          break;
        case 4:
          MENU_LCD.write(1);
          MENU_LCD.print("Color: Presets");
          MENU_LCD.write(13);
          MENU_LCD.print(" Radio Channel");
          break;
        case 5:
          MENU_LCD.write(1);
          MENU_LCD.print("Radio Channel");
          MENU_LCD.write(13);
          MENU_LCD.print(" Done");
          break;
        case 6:
          MENU_LCD.write(1);
          MENU_LCD.print("Done");
          MENU_LCD.write(13);
          MENU_LCD.print(" Color: Red");
          break;
      }
      break;
    // Color: Red menu
    case 1:
      MENU_LCD.print("Red:");
      MENU_LCD.write(13);
      MENU_LCD.print(MENU_VALUE);
      
      MENU_VALUES[1] = MENU_VALUE;
      RED            = MENU_VALUE;
      
      LedOn(LED_PINS);
      
      // TODO: Save value
      break;
    // Color: Green menu
    case 2:
      MENU_LCD.print("Green:");
      MENU_LCD.write(13);
      MENU_LCD.print(MENU_VALUE);
      
      MENU_VALUES[2] = MENU_VALUE;
      GREEN          = MENU_VALUE;
      
      LedOn(LED_PINS);
      
      // TODO: Save value
      break;
    // Color: Blue menu
    case 3:
      MENU_LCD.print("Blue:");
      MENU_LCD.write(13);
      MENU_LCD.print(MENU_VALUE);
      
      MENU_VALUES[3] = MENU_VALUE;
      BLUE           = MENU_VALUE;
      
      LedOn(LED_PINS);
      
      // TODO: Save value
      break;
    // Color: Presets menu
    case 4:
      MENU_LCD.print("Presets:");
      MENU_LCD.write(13);
      
      switch(MENU_VALUE)
      {
        case 1:
          MENU_LCD.print("Bright White");
          
          MENU_VALUES[1] = 255;
          MENU_VALUES[2] = 255;
          MENU_VALUES[3] = 255;
          
          LedSetColor(255, 255, 255);
          LedOn(LED_PINS);
          break;
        case 2:
          MENU_LCD.print("Warm White");
          
          MENU_VALUES[1] = 135;
          MENU_VALUES[2] = 120;
          MENU_VALUES[3] = 30;
          
          LedSetColor(135, 120, 30);
          LedOn(LED_PINS);
          break;
        case 3:
          MENU_LCD.print("Soft White");
          
          MENU_VALUES[1] = 80;
          MENU_VALUES[2] = 70;
          MENU_VALUES[3] = 15;
          
          LedSetColor(80, 70, 15);
          LedOn(LED_PINS);
          break;
      }
      
      MENU_VALUES[4] = MENU_VALUE;
      
      // TODO: Save values
      break;
    // Fade menu
    /*
    case 5:
      MENU_LCD.print("Fade:");
      MENU_LCD.write(13);

      switch(MENU_VALUE)
      {
        case 1:
          MENU_LCD.print("On");
          
          FADE = 1;
          break;
        case 2:
          MENU_LCD.print("Off");
          
          FADE = 0;
          break;
      }
      
      MENU_VALUES[5] = MENU_VALUE;
      
      // TODO: Save value
      break;
    */
    // RF Channel menu
    case 5:
      MENU_LCD.print("Radio Channel:");
      MENU_LCD.write(13);
      MENU_LCD.print(MENU_VALUE);
      
      MENU_VALUES[6] = MENU_VALUE;
      RF_CHANNEL     = MENU_VALUE;
      
      // TODO: Save value
      break;
    // Done
    case 6:
      MenuOff();
      break;
  }
}

/*
 * Listen for button push to turn on menu
 */
void MenuStartListener()
{
  // Check if button is pressed
  if(digitalRead(MENU_DPAD_PUSH) == LOW)
  {
    // Turn on menu
    MenuOn();
  }
}

/*
 * Listen for button inputs
 */
void MenuDpadListener()
{
  // Check if UP button is being pressed
  if (digitalRead(MENU_DPAD_UP) == LOW)
  {
    // Check menu depth
    if (MENU_LIST > 0)
    {
      // If in sub-menu, handle value
      if (MENU_VALUE >= MENU_LIST_LENGTH[MENU_LIST])
      {
        MENU_VALUE = 1;
      } else {
        MENU_VALUE++;
      }
    } else {
      // If in main menu, handle index
      if (MENU_INDEX == 1)
      {
        MENU_INDEX = MENU_LIST_LENGTH[MENU_LIST];
      } else {
        MENU_INDEX--;
      }
    }
    
    MenuShowItem();
  }
  
  // Check if DOWN button is being pressed
  if(digitalRead(MENU_DPAD_DOWN) == LOW)
  {
    // Check menu depth
    if (MENU_LIST > 0)
    {
      // If in sub-menu, handle value
      if (MENU_VALUE <= 1)
      {
        MENU_VALUE = MENU_LIST_LENGTH[MENU_LIST];
      } else {
        MENU_VALUE--;
      }
    } else {
      // If in main menu, handle index
      if (MENU_INDEX >= MENU_LIST_LENGTH[MENU_LIST])
      {
        MENU_INDEX = 1;
      } else {
        MENU_INDEX++;
      }
    }
    
    MenuShowItem();
  }
  
  // Check if LEFT button is being pressed
  if (digitalRead(MENU_DPAD_LEFT) == LOW)
  {
    // Check menu depth
    if (MENU_LIST == 0) {
      // If in main menu, turn off
      MenuOff();
    } else {
      // If in sub-menu, go back to main menu
      MENU_LIST  = 0;
      MENU_INDEX = 0;
      
      MenuShowItem();
    }
  }
  
  // Check if RIGHT or CENTER button is being pressed
  if (digitalRead(MENU_DPAD_RIGHT) == LOW || digitalRead(MENU_DPAD_PUSH) == LOW)
  {
    // Check menu depth
    if (MENU_LIST == 0)
    {
      // If in main menu, open sub-menu
      MENU_LIST  = MENU_INDEX;
      MENU_VALUE = MENU_VALUES[MENU_LIST];
    } else if (digitalRead(MENU_DPAD_PUSH) == LOW) {
      // If in sub-menu and CENTER button is pressed, go back to main menu
      MENU_LIST  = 0;
    }
    
    MenuShowItem();
  }
}
