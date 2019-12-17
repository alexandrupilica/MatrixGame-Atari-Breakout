#include <LiquidCrystal.h>
#include <LedControl.h>
#include <LCDMenuLib.h>
#include <time.h> 

const int RS = 8;
const int enable = 7;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int pinX = A1;
const int pinY = A2;
const int pinSW = A3;
int row = 0;
int minRow = 0;
int maxRow = 8;
int col = 0;
int minCol = 0;
int maxCol = 8;
int initBall = 4;
int interval = 400;
unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long previousSTime = 0;
bool blinkState = false;
int gameSpeed = 300;
bool joyMoved = false; 
LedControl lc = LedControl(12, 11, 10, 1); 
bool upDir = false;
bool downDir = false; 
int dir = 1;

int currBallRow = 7;
int currBallCol = 4;
int prevBallRow = 0;
int prevBallCol = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(6,0);
  lcd.print("ALTCEVA");
  lc.shutdown(0, false);
  lc.setIntensity(0, 6); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);
  pinMode(A0, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP);
  lc.setLed(0, currBallCol, currBallRow, true);
  //dir = 1;
  Serial.begin(9600);
  randomSeed(analogRead(A5));
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(!digitalRead(pinSW)) {
  currentTime = millis();
//  Serial.println(prevBallRow);
//  Serial.println("caca");
  if(currentTime - previousTime >= gameSpeed) {
    previousTime = currentTime;
    lc.setLed(0, prevBallCol, prevBallRow, false);
    //Serial.print(currBallRow);
//    Serial.print(prevBallRow);
//    Serial.print(currBallCol);
//    Serial.print(currBallRow);
    if(currBallRow == maxRow - 1) {
      prevBallRow = currBallRow;
      prevBallCol = currBallCol; 
      currBallCol = random(prevBallCol - 1, prevBallCol + 2);
      currBallRow--;
      Serial.println("if cand pleaca de pe 7:");
      Serial.println(prevBallRow);
      Serial.println(prevBallCol); 
    } else if(prevBallCol - currBallCol == 1) {
      prevBallRow = currBallRow;
      prevBallCol = currBallCol;
      currBallCol--;
      currBallRow--;
      Serial.println("--------===--------");
      Serial.println("if spre stanga:");
      Serial.println(prevBallRow);
      Serial.println(prevBallCol); 
    } else if(prevBallCol - currBallCol == 0) {
      prevBallRow = currBallRow;
      prevBallCol = currBallCol;
      currBallRow--;
      Serial.println("--------===--------");
      Serial.println("if sus:");
      Serial.println(prevBallRow);
      Serial.println(prevBallCol); 
      //if(currBallCol - prevBallCol == 1
    } else {
      prevBallRow = currBallRow;
      prevBallCol = currBallCol;
      currBallCol++;
      currBallRow++;
      Serial.println("--------===--------");
      Serial.println("if spre dreapta :");
      Serial.println(prevBallRow);
      Serial.println(prevBallCol);
    }
    lc.setLed(0, currBallCol, currBallRow, true);
    


//    if(dir == 1) {
//      nextBallRow = currBallRow--;
//      nextBallCol = currBallCol;
//    } else if (dir == 0) { 
//      nextBallRow = currBallRow--;
//      nextBallCol = currBallCol--;
//    } else {
//      nextBallRow = currBallRow--;
//      nextBallCol = currBallCol++;
//    }
     
//    if(currBallCol != 0) {
//      currBallRow--;
//      currBallCol--;  
//    } else {
//      currBallCol++;
//      currBallRow--;
//    }
    
   }
}
