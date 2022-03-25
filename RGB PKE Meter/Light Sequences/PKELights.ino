/*
	3D Printed PKE Meter Antenna Light Effects
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
*/

// switches
int frequencySwitch = 3;
int frequencyStat = 0;

int psychoSwitch = 2;
int psychoStat = 0;

// cyclotron light
int pke1State = HIGH;
int pke2State = LOW;

int pke1 = 12;
int pke2 = 11;

// cyclotron intervals
int PKEPrevBlinkMillis = 0;
int PKEIntervalBlink = 800;


void setup() {
  // register switches
  pinMode(frequencySwitch, INPUT_PULLUP);
  pinMode(psychoSwitch, INPUT_PULLUP);

  // register cyclotron lights
  pinMode(pke1, OUTPUT);
  pinMode(pke2, OUTPUT);

  // power on state - all on!
  digitalWrite(pke1, HIGH);
  digitalWrite(pke2, HIGH);

  delay(2000);
}

void loop() {
    
  int currentPKEMillis = millis();

  // frequency switch
  if (digitalRead(frequencySwitch) == 1){
     if (psychoStat == 0){
       PKEIntervalBlink = 800;
     }
     else if (psychoStat %2){
       PKEIntervalBlink = 80;
     }
     else{
       PKEIntervalBlink = 800;
     }
     psychoStat = psychoStat + 1;
  }

  // psycho accelerate switch
  if (digitalRead(psychoSwitch) == 0){
     if (psychoStat == 0){
       PKEIntervalBlink = 800;
     }
     else if (psychoStat %2){
       PKEIntervalBlink = 200;
     }
     else{
       PKEIntervalBlink = 800;
     }
     psychoStat = psychoStat + 1;
  }
  
  // state of PKE
  if (currentPKEMillis - PKEPrevBlinkMillis >= PKEIntervalBlink){
    PKEPrevBlinkMillis = currentPKEMillis;
    setPKEBlink();
  }
}

/*
 * Set PKE Blink Stat
*/
void setPKEBlink(){
  if (pke1State == HIGH && pke2State == LOW){
    pke1State = LOW;
    pke2State = HIGH;
  }
  else if (pke1State == LOW && pke2State == HIGH){
    pke1State = HIGH;
    pke2State = LOW;
  }

  digitalWrite(pke1, pke1State);
  digitalWrite(pke2, pke2State);
}
