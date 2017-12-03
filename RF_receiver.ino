#include <VirtualWire.h>
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "LiquidCrystal_I2C.h" // Added library*

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article
char cad[100];
int pos = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Device is ready");
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
   lcd.begin (16,2); // 16 x 2 LCD module
   lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);
}

void loop()
{
{
byte buf[VW_MAX_MESSAGE_LEN]; 
byte buflen = VW_MAX_MESSAGE_LEN; 
int i;
if( vw_get_message(buf, &buflen) )
{
if(pos < 2)
lcd.setCursor(0, pos);
else
{
pos=0;
lcd.clear();
}
for (i = 0; i < buflen; i++)
{
lcd.print((char)buf[i]);
pos++;

}
}
}
}

