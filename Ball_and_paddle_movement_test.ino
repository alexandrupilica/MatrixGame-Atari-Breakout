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
int potPin = A0;
int paddlePos = 0;
int potValue = 0;
//const int pinX = A1;
//const int pinY = A2;
//const int pinSW = A3;
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
unsigned long paddleTime = 0;
unsigned long currentPaddleTime = 0;
int moveInterval = 20;
bool blinkState = false;
int gameSpeed = 300;
bool joyMoved = false; 
LedControl lc = LedControl(12, 11, 10, 1); 
bool upDir = true;
bool downDir = false; 

int currBallRow = 6;
int currBallCol = 4;
int prevBallRow = 10;
int prevBallCol = 10;

void levelOne() {
  bool matrix[8][8] { 
  {1,1,0,0,0,0,0,0}, 
  {1,1,1,0,0,0,0,0}, 
  {1,1,1,0,0,0,0,0},
  {1,1,1,0,0,0,0,0},
  {1,1,1,0,0,0,0,0}, 
  {1,1,1,0,0,0,0,0},
  {1,1,1,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0}
  };
   for (row = minRow; row < maxRow; row++){
     for(col = minCol; col < maxCol; col++){
      lc.setLed(0, row, col, matrix[row][col]);
     }
  }
}

void initDisplayBoard() {
  for (col = minCol + 4; col < maxCol - 2; col++) {
    lc.setLed(0, col, maxRow - 1, true);
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(6,0);
  lcd.print("ALTCEVA");
  lc.shutdown(0, false);
  lc.setIntensity(0, 6); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);
  pinMode(potPin, INPUT);
  //pinMode(pinSW, INPUT_PULLUP);
  lc.setLed(0, currBallCol, currBallRow, true);
  Serial.begin(9600);
  randomSeed(analogRead(A5));
  levelOne();
  initDisplayBoard();
}


void loop() {
  // put your main code here, to run repeatedly:
//  if(!digitalRead(pinSW)) {
  currentTime = millis();
  currentPaddleTime = millis();
  potValue = analogRead(potPin);
  paddlePos = map(potValue, 0, 1023, 0, 7);
  if(currentPaddleTime - paddleTime >= moveInterval) {
    paddleTime = currentPaddleTime;
  for (col = minCol; col < maxCol; col++) {
    if(paddlePos == col) {
      lc.setLed(0, col, maxRow - 1, true);
      lc.setLed(0, col + 1, maxRow - 1, true);
      delay(10); 
    } else {
      lc.setLed(0, col, maxRow - 1, false);
    } 
  }
  }
  if(currentTime - previousTime >= gameSpeed) {
    previousTime = currentTime;
    lc.setLed(0, prevBallCol, prevBallRow, false);
   if(upDir == true) {
      if(currBallRow == maxRow - 2) {
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
        currBallRow--;
        Serial.println("--------===--------");
        Serial.println("if spre dreapta :");
        Serial.println(prevBallRow);
        Serial.println(prevBallCol);
      }
    }
  } 
    lc.setLed(0, currBallCol, currBallRow, true);
}    

    
   
