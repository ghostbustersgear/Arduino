/*
	3D Printed RGB Proton Pack Light Effects
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
int polaritySwitch = 3;
int polarityStat = 0;

int nuclearSwitch = 2;
int nuclearStat = 0;

// cyclotron light
int cyclotron1State = HIGH;
int cyclotron2State = LOW;
int cyclotron3State = LOW;

int cyclotron1 = 12;
int cyclotron2 = 11;
int cyclotron3 = 10;

// power cell light
int power1State = HIGH;
int power2State = LOW;
int power3State = LOW;

int power1 = 9;
int power2 = 8;
int power3 = 7;

// ion indicator light
int ion1State = HIGH;
int ion2State = LOW;

int ion1 = 6;
int ion2 = 5;

// overload light
int overloadState = HIGH;

int overload = 4;

// cyclotron intervals
int cycloPrevBlinkMillis = 0;
int cycloIntervalBlink = 800;

// power cell intervals
int powerPrevBlinkMillis = 0;
int powerIntervalBlink = 200;

// ion intervals
int ionPrevBlinkMillis = 0;
int ionIntervalBlink = 800;

// overload intervals
int overloadPrevBlinkMillis = 0;
int overloadIntervalBlink = 1500;


void setup() {
  // register switches
  pinMode(polaritySwitch, INPUT_PULLUP);
  pinMode(nuclearSwitch, INPUT_PULLUP);

  // register cyclotron lights
  pinMode(cyclotron1, OUTPUT);
  pinMode(cyclotron2, OUTPUT);
  pinMode(cyclotron3, OUTPUT);

  // register power cell
  pinMode(power1, OUTPUT);
  pinMode(power2, OUTPUT);
  pinMode(power3, OUTPUT);

  // register ion indicators
  pinMode(ion1, OUTPUT);
  pinMode(ion2, OUTPUT);

  // register overload
  pinMode(overload, OUTPUT);

  // power on state - all on!
  digitalWrite(cyclotron1, HIGH);
  digitalWrite(cyclotron2, HIGH);
  digitalWrite(cyclotron3, HIGH);
  digitalWrite(power1, HIGH);
  digitalWrite(power2, HIGH);
  digitalWrite(power3, HIGH);
  digitalWrite(ion1, HIGH);
  digitalWrite(ion2, HIGH);
  digitalWrite(overload, HIGH);

  delay(4000);
}

void loop() {
    
  int currentCycloMillis = millis();
  int currentPowerMillis = millis();
  int currentIonMillis = millis();
  int currentOverloadMillis = millis();

  // polarity switch
  if (digitalRead(polaritySwitch) == 0){
     if (polarityStat == 0){
       cyclotron1 = 12;
       cyclotron2 = 11;
       cyclotron3 = 10;

       power1 = 9;
       power2 = 8;
       power3 = 7;
       
       pinMode(cyclotron1, OUTPUT);
       pinMode(cyclotron2, OUTPUT);
       pinMode(cyclotron3, OUTPUT);

       pinMode(power1, OUTPUT);
       pinMode(power2, OUTPUT);
       pinMode(power3, OUTPUT);
     }
     else if (polarityStat %2){
       cyclotron1 = 12;
       cyclotron2 = 11;
       cyclotron3 = 10;

       power1 = 9;
       power2 = 8;
       power3 = 7;
       
       pinMode(cyclotron1, OUTPUT);
       pinMode(cyclotron2, OUTPUT);
       pinMode(cyclotron3, OUTPUT);

       pinMode(power1, OUTPUT);
       pinMode(power2, OUTPUT);
       pinMode(power3, OUTPUT);
     }
     else{
       cyclotron1 = 10;
       cyclotron2 = 11;
       cyclotron3 = 12;

       power1 = 7;
       power2 = 8;
       power3 = 9;
       
       pinMode(cyclotron1, OUTPUT);
       pinMode(cyclotron2, OUTPUT);
       pinMode(cyclotron3, OUTPUT);
       
       pinMode(power1, OUTPUT);
       pinMode(power2, OUTPUT);
       pinMode(power3, OUTPUT);
     }

     polarityStat = polarityStat + 1;
  }

  // nuclear accelerate switch
  if (digitalRead(nuclearSwitch) == 0){
     if (nuclearStat == 0){
       cycloIntervalBlink = 800;
       powerIntervalBlink = 200;
       ionIntervalBlink = 800;
       overloadIntervalBlink = 1500;
     }
     else if (nuclearStat %2){
       cycloIntervalBlink = 200;
       powerIntervalBlink = 80;
       ionIntervalBlink = 150;
       overloadIntervalBlink = 50;
     }
     else{
       cycloIntervalBlink = 800;
       powerIntervalBlink = 200;
       ionIntervalBlink = 800;
       overloadIntervalBlink = 1500;
     }

     nuclearStat = nuclearStat + 1;
  }


  // state of cyclotron
  if (currentCycloMillis - cycloPrevBlinkMillis >= cycloIntervalBlink){
    cycloPrevBlinkMillis = currentCycloMillis;
    setCycloBlink();
  }

  // state of power cell
  if (currentPowerMillis - powerPrevBlinkMillis >= powerIntervalBlink){
    powerPrevBlinkMillis = currentPowerMillis;
    setPowerBlink();
  }

  // state of ion indicators
  if (currentIonMillis - ionPrevBlinkMillis >= ionIntervalBlink){
    ionPrevBlinkMillis = currentIonMillis;
    setIonBlink();
  }

  // state of overload indicators
  if (currentOverloadMillis - overloadPrevBlinkMillis >= overloadIntervalBlink){
    overloadPrevBlinkMillis = currentOverloadMillis;
    setOverloadBlink();
  }
}

/*
 * Set Cyclotron Blink Stat
*/
void setCycloBlink(){
  if (cyclotron1State == HIGH && cyclotron2State == LOW && cyclotron3State == LOW){
    cyclotron1State = LOW;
    cyclotron2State = HIGH;
    cyclotron3State = LOW;
  }
  else if (cyclotron1State == LOW && cyclotron2State == HIGH && cyclotron3State == LOW){
    cyclotron1State = LOW;
    cyclotron2State = LOW;
    cyclotron3State = HIGH;
  }
  else if (cyclotron1State == LOW && cyclotron2State == LOW && cyclotron3State == HIGH){
    cyclotron1State = HIGH;
    cyclotron2State = LOW;
    cyclotron3State = LOW;
  }
  else if (cyclotron1State == HIGH && cyclotron2State == HIGH && cyclotron3State == HIGH){
    cyclotron1State = HIGH;
    cyclotron2State = LOW;
    cyclotron3State = LOW;
  }

  digitalWrite(cyclotron1, cyclotron1State);
  digitalWrite(cyclotron2, cyclotron2State);
  digitalWrite(cyclotron3, cyclotron3State);
}

/*
 * Set Power Cell Blink Stat
*/
void setPowerBlink(){
  if (power1State == LOW && power2State == LOW && power3State == LOW){
    power1State = HIGH;
    power2State = LOW;
    power3State = LOW;
  }
  else if (power1State == HIGH && power2State == LOW && power3State == LOW){
    power1State = HIGH;
    power2State = HIGH;
    power3State = LOW;
  }
  else if (power1State == HIGH && power2State == HIGH && power3State == LOW){
    power1State = HIGH;
    power2State = HIGH;
    power3State = HIGH;
  }
  else if (power1State == HIGH && power2State == HIGH && power3State == HIGH){
    power1State = LOW;
    power2State = LOW;
    power3State = LOW;
  }

  digitalWrite(power1, power1State);
  digitalWrite(power2, power2State);
  digitalWrite(power3, power3State);
}

/*
 * Set Ion Indicators Blink Stat
*/
void setIonBlink(){
  if (ion1State == HIGH && ion2State == LOW){
    ion1State = LOW;
    ion2State = HIGH;
  }
  else if (ion1State == LOW && ion2State == HIGH){
    ion1State = HIGH;
    ion2State = LOW;
  }
  else if (ion1State == HIGH && ion2State == HIGH){
    ion1State = HIGH;
    ion2State = LOW;
  }

  digitalWrite(ion1, ion1State);
  digitalWrite(ion2, ion2State);
}

/*
 * Set Overload Indicator Blink Stat
*/
void setOverloadBlink(){
  if (overloadState == HIGH){
    overloadState = LOW;
  }
  else if (overloadState == LOW){
    overloadState = HIGH;
  }

  digitalWrite(overload, overloadState);
}
