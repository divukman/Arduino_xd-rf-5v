#include <VirtualWire.h>

// Constants
//*********************************************************
const char * MSG_DEFAULT = "DEFAULT MSG";
const char * MSG_ONE = "BTN1";
const char * MSG_TWO = "BTN2";
const char * MSG_THREE = "BTN3";
//*********************************************************
 
void setup()
{
    Serial.begin(9600);          // Configure the serial connection to the computer
    vw_set_ptt_inverted(true);  // Required by the RF module
    vw_setup(2000);            // bps connection speed
    vw_set_rx_pin(3);         // Arduino pin to connect the receiver data pin
    vw_rx_start();           // Start the receiver

    // Set blinking LED, for info purposes
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop()
{

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  char myBuffer[30] = {'\0'};

  if (vw_get_message(buf, &buflen))      // We check if we have received data
  {
    int i;
    // Message with proper check    
    for (i = 0; i < buflen; i++)
    {
      Serial.write(buf[i]);  // The received data is stored in the buffer
                            // and sent through the serial port to the computer                     
    }
    Serial.println();



    strncpy(myBuffer,buf,buflen);
    myBuffer[buflen] = '\0';


  if (compareBuffers(myBuffer, "BTN1")) {
          Serial.write('1');
          Serial.println();
          digitalWrite(LED_BUILTIN, HIGH); // Blinkaj prijo
    } else if (compareBuffers(myBuffer, "BTN2")) {
          Serial.write('2');
          Serial.println();
          digitalWrite(LED_BUILTIN, LOW);
    } else if (compareBuffers(myBuffer, "BTN3")) {
          Serial.write('3');
          Serial.println();
          digitalWrite(LED_BUILTIN, LOW);
    } else {
          Serial.write('0');
          Serial.println();
          digitalWrite(LED_BUILTIN, LOW);
    } 
  }
}

boolean compareBuffers( char * strOne, char * strTwo) {
  return  ( strOne[0] == strTwo[0] 
            && strOne[1] == strTwo[1]  
            && strOne[2] == strTwo[2]   
            && strOne[3] == strTwo[3]); 
  }