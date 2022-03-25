/*
	3D Printed Ghost Trap Remote Door Electronic Sender
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

// RF variables
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

// switch to send signal
int switch1 = 8;

// track switch status (prevent duplicated signal)
int switchStat = 0;

void setup() {
  Serial.begin(9600);
  pinMode(switch1, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN); // using minimum distance signal
  radio.stopListening();
}

void loop() {

  // send switch pressed
  if (digitalRead(switch1) == 0 && digitalRead(switch1) != switchStat){
    int val = 0;
    radio.write(&val, sizeof(val));
    switchStat = 0;
    Serial.println(switchStat);
  }

  // send switch released
  if (digitalRead(switch1) == 1 && digitalRead(switch1) != switchStat){
    int val = 1;
    radio.write(&val, sizeof(val));
    switchStat = 1;
    Serial.println(switchStat);
  }

}
