/*
	3D Printed PKE Meter LCD Radar Effect
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

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>

// tft
MCUFRIEND_kbv tft;

int rot = 0;
int rotPrev = 0;

uint16_t w = 0;
uint16_t h = 0;
uint16_t wMid = 0;
uint16_t hMid = 0;

int entityCount = 1;

int pulseSize = 1;
int pulseInc = 15;
int pulseCountMax = 5;
int pulseCount = 0;

String pkePrev = "";

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));
  
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(PI/2);
  tft.fillScreen(BLACK);

  entityCount = random(1,5);
  drawRadar();
  drawReadings();
}

void loop() {
   int pulse = random(3,6);
   drawPKESignal(pulse);
   delay(200);

   drawReadings();
}

void drawReadings(){
  int randPKE = random(100,2000);
  String pke = "PKE:";
  String pkeReading = pke + randPKE;

  String ent = "ENTITIES DETECTED:";
  String entities = ent + entityCount;

  
  tft.setCursor(5, 5);
  tft.setTextColor(RED);  tft.setTextSize(2);
  tft.println("CLASS 5");
  tft.setCursor(5, 30);
  tft.setTextColor(RED);  tft.setTextSize(1);
  tft.println(entities);
  tft.setCursor(5, h-20);
  tft.setTextColor(BLACK);  tft.setTextSize(2);
  tft.println(pkePrev);
  tft.setCursor(5, h-20);
  tft.setTextColor(GREEN);  tft.setTextSize(2);
  tft.println(pkeReading);
  pkePrev = pkeReading;
}

// draw radar function
void drawRadar() {
  // put your main code here, to run repeatedly:
  w = tft.width();
  h = tft.height();
  wMid = w/2;
  hMid = h/2;

  
  // draws the arc lines
  tft.drawCircle(wMid,hMid,10,BLUE);
  tft.drawCircle(wMid,hMid,20,BLUE);
  tft.drawCircle(wMid,hMid,40,BLUE);
  tft.drawCircle(wMid,hMid,80,BLUE);
  tft.drawCircle(wMid,hMid,115,BLUE);

  // crosshairs
  tft.drawLine(wMid,5, wMid,h-5, WHITE);
  tft.drawLine(5,hMid, w-5,hMid, WHITE);

  //X ticks
  tft.drawLine(5,hMid+20, 5,hMid-20, WHITE);
  tft.drawLine(w-5,hMid+20, w-5,hMid-20, WHITE);
  tft.drawLine(w/6,hMid+10, w/6,hMid-10, WHITE);
  tft.drawLine(w-(w/6),hMid+10, w-(w/6),hMid-10, WHITE);
  tft.drawLine(w/3,hMid+5, w/3,hMid-5, WHITE);
  tft.drawLine(w-(w/3),hMid+5, w-(w/3),hMid-5, WHITE);

  //Y ticks
  tft.drawLine(wMid+20,5, wMid-20,5, WHITE);
  tft.drawLine(wMid+20,h-5, wMid-20,h-5, WHITE);
  tft.drawLine(wMid+10,h/6, wMid-10,h/6, WHITE);
  tft.drawLine(wMid+10,h-(h/6), wMid-10,h-(h/6), WHITE);
  tft.drawLine(wMid+5,h/3, wMid-5,h/3, WHITE);
  tft.drawLine(wMid+5,h-(h/3), wMid-5,h-(h/3), WHITE);
}

// draw the PKE radar detection
void drawPKESignal(int pulse){

   int randomXVals[entityCount];
   int randomYVals[entityCount];
   for (int i = 0; i < entityCount; i++){
    randomXVals[i] = random(30,w-30);
    randomYVals[i] = random(30,h-30);
   }
   
   int randomX = random(30,w-30);
   int randomY = random(30,h-30);

   for (int i = 0; i < pulse; i++){
    for (int j = 0; j < entityCount; j++){
     tft.drawCircle(randomXVals[j],randomYVals[j],pulseSize,YELLOW);
    }
    delay(50);
    pulseSize = pulseSize + pulseInc;
   } 

   pulseSize = 1;
   for (int i = 0; i < pulse; i++){
     for (int j = 0; j < entityCount; j++){
      tft.drawCircle(randomXVals[j],randomYVals[j],pulseSize,BLACK);
     } 
     delay(100);
     pulseSize = pulseSize + pulseInc;
   } 
   drawRadar();
   pulseSize = 1;
}

/* draw rotating line
void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(960,1000); // moves the starting coordinats to new location
  line(0,0,950*cos(radians(iAngle)),-950*sin(radians(iAngle))); // draws the line according to the angle
  popMatrix();
}
*/
