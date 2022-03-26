/*
	3D Printed RGB Gizmo Light Sequences
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

/********************************
* name:I2C LCD1602
* function:You should now see your I2C LCD1602 display the flowing characters: "SunFounder" and "hello, world".
********************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
/**********************************************************/
char array1[]="ECTO-1 BEACON ALERT           "; //the string to print on the LCD
char array2[]="CLASS 5 DETECTED              "; //the string to print on the LCD
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int prevScrollMillisA = 0;
int prevScrollMillisB = 0;
int positionCounterA = 0;
int positionCounterB = 0;
int positionCounterMax = 30;
int scrollInterval = 500;

int button1 = 9;
int button2 = 8;
int button3 = 7;
int button1State = LOW;
int button2State = LOW;
int button3State = LOW;
int buttonPrevBlinkMillis = 0;
int buttonIntervalBlink = 200;
/*********************************************************/
void setup()
{
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  Serial.begin(9600);

  // register power cell
  pinMode(button1, OUTPUT);
  pinMode(button2, OUTPUT);
  pinMode(button3, OUTPUT);

  digitalWrite(button1, HIGH);
  digitalWrite(button2, HIGH);
  digitalWrite(button3, HIGH);

  lcd.setCursor(15,0); // set the cursor to column 15, line 0
  delay(2000);
}
/*********************************************************/
void loop() 
{
  int currentScrollMillisA = millis();
  int currentScrollMillisB = millis();
  int currentButtonMillis = millis();

  // state of button lights
  if (currentButtonMillis - buttonPrevBlinkMillis >= buttonIntervalBlink){
    buttonPrevBlinkMillis = currentButtonMillis;
    setBlink();
  }

  if (positionCounterA <= positionCounterMax){
    if (currentScrollMillisA - prevScrollMillisA >= scrollInterval){
      prevScrollMillisA = currentScrollMillisA;
      lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
      lcd.print(array1[positionCounterA]); // Print a message to the LCD.
      positionCounterA++;
      Serial.println(positionCounterA);
      if (positionCounterA >= positionCounterMax){
        lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
        lcd.setCursor(15,1);
        positionCounterB = 0;  
      }   
    }
  }
  if (positionCounterA >= positionCounterMax){
     if (currentScrollMillisB - prevScrollMillisB >= scrollInterval){
      prevScrollMillisB = currentScrollMillisB;
      lcd.scrollDisplayLeft(); //Scrolls the contents of the display one space to the left.
      lcd.print(array2[positionCounterB]); // Print a message to the LCD.
      positionCounterB++;
      if (positionCounterB >= positionCounterMax){
        lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left  corner.
        lcd.setCursor(15,0);  
        positionCounterA = 0;
        positionCounterB = 0; 
      }   
    }
  }
  //lcd.clear(); //Clears the LCD screen and positions the cursor in the upper-left corner.
}

/*
 * Light blinking
 */
void setBlink(){
  if (button1State == LOW && button2State == LOW && button3State == LOW){
    button1State = HIGH;
    button2State = LOW;
    button3State = LOW;
  }
  else if (button1State == HIGH && button2State == LOW && button3State == LOW){
    button1State = HIGH;
    button2State = HIGH;
    button3State = LOW;
  }
  else if (button1State == HIGH && button2State == HIGH && button3State == LOW){
    button1State = HIGH;
    button2State = HIGH;
    button3State = HIGH;
  }
  else if (button1State == HIGH && button2State == HIGH && button3State == HIGH){
    button1State = LOW;
    button2State = HIGH;
    button3State = HIGH;
  }
  else if (button1State == LOW && button2State == HIGH && button3State == HIGH){
    button1State = LOW;
    button2State = LOW;
    button3State = HIGH;
  }
  else if (button1State == LOW && button2State == LOW && button3State == HIGH){
    button1State = LOW;
    button2State = LOW;
    button3State = LOW;
  }

  digitalWrite(button1, button1State);
  digitalWrite(button2, button2State);
  digitalWrite(button3, button3State);
}
/************************************************************/
