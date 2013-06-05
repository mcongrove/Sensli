#include <VirtualWire.h>

int RF_CHANNEL = 5;
int RF_PINS[2] = { 3, 50 };

void RadioFrequencySetup()
{
  vw_setup(2000);
  
  if (TRANSMITTER)
  {
    vw_set_tx_pin(RF_PINS[0]);
  } else if (RECEIVER) {
    vw_set_rx_pin(RF_PINS[1]);
    vw_rx_start();
  }
}

int RadioFrequencyRead()
{
  char message[4];
  int data;
  uint8_t buffer[VW_MAX_MESSAGE_LEN];
  uint8_t bufferLength = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buffer, &bufferLength))
  {
    int i;
    
    for (i = 0; i < bufferLength; i++)
    {
      message[i] = char(buffer[i]);
    }
    
    message[bufferLength] = '\0';
    
    data = atoi(message);
    
    if ((data / 1000) == RF_CHANNEL)
    {
      return data % 1000;
    }
  } else {
    return 0;
  }
}

void RadioFrequencyWrite(int data)
{
  char message[4];
  int count = 5;
  int i     = 0;
  
  data = data + (RF_CHANNEL * 1000);
  
  itoa(data, message, 10);
  
  while (i < count)
  {
    vw_send((uint8_t *)message, strlen(message));
    vw_wait_tx();
    
    i++;
    
    delay(200);
  }
}
