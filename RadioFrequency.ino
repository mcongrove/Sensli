// RF information
int RF_CHANNEL = 5;
int RF_PINS[2] = { 3, 50 };

/*
 * Setup RF communications
 */
void RadioFrequencySetup()
{
  // Set the data rate
  vw_setup(2000);
  
  // Check if controller is transmitter
  if (TRANSMITTER)
  {
    // Set TX pin
    vw_set_tx_pin(RF_PINS[0]);
  } else if (RECEIVER) {
    // Set RX pin
    vw_set_rx_pin(RF_PINS[1]);
    
    // Start RF communication receiver
    vw_rx_start();
  }
}

/*
 * Read data from RF communications
 */
int RadioFrequencyRead()
{
  char message[4];
  int data;
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t bufferLength = VW_MAX_MESSAGE_LEN;
  
  // Loop through RF messages
  if (vw_get_message(buffer, &bufferLength))
  {
    int i;
    
    // Save each byte to message
    for (i = 0; i < bufferLength; i++)
    {
      message[i] = char(buffer[i]);
    }
    
    message[bufferLength] = '\0';
    
    // Convert bytes to integers
    data = atoi(message);
    
    // Ensure we're on the correct RF channel
    if ((data / 1000) == RF_CHANNEL)
    {
      // Remove channel identifier from data
      return data % 1000;
    }
  } else {
    // Exit
    return 0;
  }
}

/*
 * Send data over RF
 */
void RadioFrequencyWrite(int data)
{
  char message[4];
  int count = 5;
  int i     = 0;
  
  // Add RF channel to data
  data = data + (RF_CHANNEL * 1000);
  
  // Convert integers to bytes
  itoa(data, message, 10);
  
  // Loop through each byte of message
  while (i < count)
  {
    // Send byte
    vw_send((uint8_t *)message, strlen(message));
    
    // Wait until transmission is complete
    vw_wait_tx();
    
    i++;
    
    delay(200);
  }
}
