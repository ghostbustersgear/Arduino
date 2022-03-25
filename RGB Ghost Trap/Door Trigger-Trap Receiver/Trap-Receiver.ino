/*
	3D Printed Ghost Trap Remote Door Electronic Receiver
	Copyright (C) 2022  Nathan Miller
	https://www.patreon.com/ghostbustersgear

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>
	
	NOTE: 
	Contains modified code from an example provided by           
	Dejan Nedelkovski, www.HowToMechatronics.com
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// RF variables
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

// servos
Servo servo1;
Servo servo2;

// tracking signal value
int valStatus;
int valCount;

void setup() {
  // Servo pins and initialize
  servo1.attach(8);
  servo2.attach(7);
  servo1.write(90);
  servo2.write(90);

  // initialize signal value
  valCount = 0;

  // Radio
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    //char text[32] = "";
    int val;
    radio.read(&val, sizeof(val));
    if (valStatus != val)
    {
      Serial.println(val);
      valStatus = val;

      // check if the status is "pressed"
      if (valStatus == 0){
        valCount++;
      }

      // if the valCount is even, close
      if ((valCount % 2) == 0){
        servoClose();
      }
      else {
        servoOpen();
      }
    }
  }
}

// servo door open
void servoOpen(){
    servo1.write(0.00);
    servo2.write(0.00);
}

// servo door closed
void servoClose(){
    servo1.write(125);
    servo2.write(120);
}
