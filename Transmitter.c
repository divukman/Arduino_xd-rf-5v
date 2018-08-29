#include <VirtualWire.h>

// Constants
//*********************************************************
const char * MSG_DEFAULT = "DEFAULT MSG";
const char * MSG_ONE = "BTN1";
const char * MSG_TWO = "BTN2";
const char * MSG_THREE = "BTN3";
//*********************************************************



// BUTTONS SETUP
//*********************************************************
const int button1Pin = 8; 
int button1State = 0; 
const int button2Pin = 9; 
int button2State = 0;  
const int button3Pin = 10; 
int button3State = 0;    
//*********************************************************


// Message pointer
//*********************************************************
char *msg = 0;
//*********************************************************



// Setup function
void setup()
{
    // Init button input PINs
    pinMode(button1Pin, INPUT);
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT);
    pinMode(button3Pin, INPUT_PULLUP);
    
    // Transmitter setup
    vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_tx_pin(3);         // Arduino pin to connect the receiver data pin
}



// Main loop function 
void loop()
{

  // Read input button PINs
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);


  // React to button digital PIN state changes
  if (button1State == LOW) {
    msg = MSG_ONE;
  } else if (button2State == LOW) {
     msg = MSG_TWO;
  } else if (button3State == LOW) {
     msg = MSG_THREE;
  } else {
    msg = MSG_DEFAULT;
  }

  // Sent the message
  vw_send((uint8_t *)msg, strlen(msg));

  vw_wait_tx();        // We wait to finish sending the message
  delay(500);         // Wait 1/2 second to send the message again                
}
