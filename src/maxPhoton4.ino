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

char inChar;       // type for data read
String readings = "";
char charArray[4]; // array to store range data
int range = 0;     // type declaration

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
  // clearInputBuffer();
  range = maxRead();
  Serial.print("Range: ");
  Serial.println(range);
  delay(5000);
}

void clearInputBuffer() // Sensor continuously outputs data to built-in buffer
{                       // This code is intended to empty sensor buffer
  // Serial1.flush();
  if (Serial1.available() != 0)
  {
    Serial1.read();
  }
}

int maxRead()  // Two example methods 
{
  while (Serial1.available() > 0)
  {
    inChar = Serial1.read(); // continuously read sensor input in while loop
    if (inChar == 'R')       // test if char == R for beginning data
    Serial.println("Got an R");
      for (int i = 0; i < 4; i++) // capture the next three characters
      {
        inChar = Serial1.read();
        readings += inChar; // build a string and then convert to int
        Serial.println(readings);

        charArray[i] = inChar; // assign input char to charArray index
        Serial.print("char =");
        Serial.println(inChar);
      }

    range = atoi(readings); // extract integer range from char charArray
    Serial.print("charArray =");
    Serial.println(charArray);
    range = atoi(charArray); // extract integer range from char charArray
  }
  return range;
}

// int maxRead()
// {
//   while (Serial1.available() >= 0)
//   {
//     inChar = Serial1.read();
//     if (inChar == 82)
//     {
//       Serial.println("Got 82");
//       range = Serial1.parseInt();
//       // Serial.println(range);
//     }
//   }
//   return range;
// }