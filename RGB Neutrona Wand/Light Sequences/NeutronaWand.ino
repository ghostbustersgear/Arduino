/*
	3D Printed RGB Neutrona Wand Light Sequences
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

int fireSwitch1 = 4;
int fireSwitch2 = 3;
int fireSwitch3 = 2;

int prevBlinkMillis = 0;
int intervalBlink = 1000;
int led1State = LOW;
int led2State = HIGH;
int led3State = LOW;

int led1 = 12;
int led2 = 11;
int redLight = 10;
int switchLight1 = 9;
int switchLight2 = 8;

int prevFireMillis = 0;
int intervalFire = 10;
int redPin= 7;
int greenPin = 6;
int bluePin = 5;

void setup() {
  pinMode(fireSwitch1, INPUT_PULLUP);
  pinMode(fireSwitch2, INPUT_PULLUP);
  pinMode(fireSwitch3, INPUT_PULLUP);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(switchLight1, OUTPUT);
  pinMode(switchLight2, OUTPUT);

  digitalWrite(switchLight1, HIGH);
  digitalWrite(switchLight2, HIGH);
  digitalWrite(redLight, HIGH);
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

void loop() {

  int currentFireMillis = millis();
  int currentBlinkMillis = millis();
  
  if (digitalRead(fireSwitch1) == 0) {
    if (currentFireMillis - prevFireMillis >= intervalFire){
      prevFireMillis = currentFireMillis;
  
      int r = random(0, 255);
      int g = random(0, 150);
      int b = random(0, 255);
  
      setColor(r, g, b); // Random color 1
    }
    intervalBlink = 200;
    if (currentBlinkMillis - prevBlinkMillis >= intervalBlink){
      prevBlinkMillis = currentBlinkMillis;
      setBlink();
    }
  }
  else if (digitalRead(fireSwitch2) == 0) {
    if (currentFireMillis - prevFireMillis >= intervalFire){
      prevFireMillis = currentFireMillis;
  
      int r = random(100,200);
      int g = random(225,255);
      int b = random(0,0);
  
      setColor(r, g, b); // Random color 2
    }
    intervalBlink = 200;
    if (currentBlinkMillis - prevBlinkMillis >= intervalBlink){
      prevBlinkMillis = currentBlinkMillis;
      setBlink();
    }
  }
  else if (digitalRead(fireSwitch3) == 0) {
    if (currentFireMillis - prevFireMillis >= intervalFire){
      prevFireMillis = currentFireMillis;
  
      int r = random(0,0);
      int g = random(225,255);
      int b = random(0,10);
  
      setColor(r, g, b); // Random color 3
    }
    intervalBlink = 200;
    if (currentBlinkMillis - prevBlinkMillis >= intervalBlink){
      prevBlinkMillis = currentBlinkMillis;
      setBlink();
    }
  }
  else{
    intervalBlink = 1000;
    setColor(0, 0, 0); // off
    if (currentBlinkMillis - prevBlinkMillis >= intervalBlink){
      prevBlinkMillis = currentBlinkMillis;
      setBlink();
    }
  }

}

void setBlink(){
  if (led1State == HIGH){
    led1State = LOW;
  }
  else{
    led1State = HIGH;
  }
  
  if (led2State == HIGH){
    led2State = LOW;
  }
  else{
    led2State = HIGH;
  }

  if (led3State == HIGH){
    led3State = LOW;
  }
  else{
    led3State = HIGH;
  }

  digitalWrite(led1, led1State);
  digitalWrite(led2, led2State);
  digitalWrite(redLight, led3State);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
