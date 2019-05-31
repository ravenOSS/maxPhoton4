#include "application.h"
#line 1 "/Users/raventt/MBP_Projects/arduino/maxPhoton4/src/maxPhoton4.ino"
 /*
 * Project maxPhoton4
 * Description: Interface Maxbotix serial sensor to Particle Photon or Arduino compatible
 * Author: David Richards / ravenIoT LLC
 * Date: May 22, 2019
 */

// If controller does NOT have a hardware serial port available (e.g. Serial1),
// add and configure SoftwareSerial and define Rx & Tx pins. Can also invert RS232.

// Using hardware UART on Photon
// Maxbotix sensor with RS232 conversion to TTL with MAX3232
// Name mySerial => Serial1 (Photon definition)

void setup();
void loop();
int maxRead();
#line 15 "/Users/raventt/MBP_Projects/arduino/maxPhoton4/src/maxPhoton4.ino"
char inChar; // type for data read
char buf[5]; // array to store range data
int range = 0;   // type declaration
char inByte;  // not used

void setup()
{
  Serial.begin(57600);
  while (!Serial)
  {
    ; // wait for serial port to connect.
  }
  Serial.println("Serial open");
  // set the data rate from the sensor
  Serial1.begin(9600, SERIAL_8N1); // Default but set explicitly anyway
  while (!Serial1)
  {
    ; // wait for Serial1 port to connect.
  }
  Serial.println("Sensor connected");
}

void loop()
{
  range = maxRead();
  Serial.print("Range: ");
  Serial.println(range);
  delay(5000);
}

int maxRead()
{
  // Serial1.flush();
  if (Serial1.available() != 0){
    Serial1.read();
  }
  if (Serial1.available() > 0)
  {
    inChar = Serial1.read();
    if (inChar == 82)
    {
       Serial.println("Got 82");
      range = Serial1.parseInt();
      // Serial.println(range);
    }
  }
  return range;
}

// int maxRead()
// {
//   while (Serial1.available() > 0)
//   {
//     inChar = Serial1.read();  // continuously read sensor input in while loop
//     if (inChar == 'R')        // test if char == R for beginning data
//     {
//       for (int i; i < 4; i++) // capture the next three characters
//       {
//         inChar = Serial1.read();
//         buf[i] = inChar; // assign input char to buf index
//         Serial.print("char =");
//         Serial.println(inChar);
//       }
//     }
//     Serial.print("buf =");
//     Serial.println(buf);
//     range = parseInt(buf); // extract integer range from char buf
//   }
//   return range;
// }
