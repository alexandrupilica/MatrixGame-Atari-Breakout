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

const int pinX = A1;
const int pinY = A2;
const int pinSW = A3;

int row = 0;
int minRow = 0;
int maxRow = 8;
int col = 0;
int minCol = 0;
int maxCol = 8;
int currBallRow = 6;
int currBallCol = 4;
int prevBallRow = 10;
int prevBallCol = 10;

int initBall = 4;
int interval = 400;
int xValue = 0;
int yValue = 0;
bool joyMoved = false; 
const int minThreshold = 250;
const int maxThreshold = 900;

unsigned long currentTime = 0;
unsigned long previousTime = 0;
unsigned long previousSTime = 0;
unsigned long paddleTime = 0;
unsigned long currentPaddleTime = 0;
int moveInterval = 10; //millis for paddle
//bool blinkState = false;
int gameSpeed = 300;

LedControl lc = LedControl(12, 11, 10, 1); 
bool upDir = true; 
int menu = 1;

int startingLevelValue = 1;
int currentLevelValue = 1;
int startingScore = 0;
int currentScore = 0;
int startingHighScore = 0;
int startingLives = 3;

void updateMenu() { 
  switch(menu) {
    case 0: 
      menu = 1;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Atari Breakout");
      lcd.setCursor(3,1);
      lcd.print("START GAME");
      break;
    case 2: 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Atari Breakout");
      lcd.setCursor(3,1);
      lcd.print("HIGH SCORE");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Atari Breakout");
      lcd.setCursor(4,1);
      lcd.print("SETTINGS");
      break;
    case 4: 
      menu = 3;
      break;
  }
}

void executeAction() {
  switch(menu) {
    case 1:
      startGame();
      break;
    case 2:
      highScore();      
      break;
    case 3:
      settings();
      break;
   }
}

void startGame() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lives:");
  lcd.print(startingLives);
  lcd.setCursor(8,0);
  lcd.print("Level:");
  lcd.print(startingLevelValue);
  lcd.setCursor(0,1);
  lcd.print("Score:"); 
  lcd.print(startingScore);
  delay(10000);
}

void highScore() {
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("High Score: ");
  lcd.setCursor(1,1);
  lcd.print("ALEX");
  lcd.setCursor(10,1);
  lcd.print(startingHighScore); 
  delay(6000);
}

void settings() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Start Level: ");
  lcd.print(startingLevelValue);
  lcd.setCursor(0,1);
  lcd.print("Name:ALEX"); 
  delay(6000);

}

void GameOver() { 
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Congrats!");
  lcd.setCursor(0,1);
  lcd.print("Press btn->quit");

}

void levelOne() {
  bool matrix[8][8] { 
  {1,1,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0}, 
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0}
  };
  for (row = minRow; row < maxRow; row++){
    for(col = minCol; col < maxCol; col++){
      lc.setLed(0, row, col, matrix[row][col]);
     }
  }
}

void levelTwo(){
  bool matrix[8][8] { 
  {1,1,0,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0},
  {1,1,0,0,0,0,0,0}, 
  {1,1,0,0,0,0,0,0}
  };
  for (row = minRow; row < maxRow; row++){
    for(col = minCol; col < maxCol; col++){
      lc.setLed(0, row, col, matrix[row][col]);
     }
  }
}

void levelThree() {
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
   lc.shutdown(0, false);
   lc.setIntensity(0, 6); // sets brightness (0~15 possible values)
   lc.clearDisplay(0);
   pinMode(potPin, INPUT);
   pinMode(pinSW, INPUT_PULLUP);
   lc.setLed(0, currBallCol, currBallRow, true);
   Serial.begin(9600);
   randomSeed(analogRead(A5));
   levelOne();
   initDisplayBoard();
   updateMenu();
}

void left() {
   prevBallRow = currBallRow;
   prevBallCol = currBallCol;
   currBallCol--;
   currBallRow--;
   Serial.println("--------===--------"); //DEBUG
   Serial.println("stanga:");
   Serial.println(prevBallRow);
   Serial.println(prevBallCol); 
}

void right() {
   prevBallRow = currBallRow;
   prevBallCol = currBallCol;
   currBallCol++;
   currBallRow--;
   Serial.println("--------===--------"); //DEBUG
   Serial.println("dreapta :");
   Serial.println(prevBallRow);
   Serial.println(prevBallCol);
}

void straight() {
   prevBallRow = currBallRow;
   prevBallCol = currBallCol;
   currBallRow--;
   Serial.println("--------===--------"); //DEBUG
   Serial.println("if sus:");
   Serial.println(prevBallRow);
   Serial.println(prevBallCol); 
}

void down() {
   prevBallRow = currBallRow;
   prevBallCol = currBallCol;
   currBallRow++; 
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);

  if(xValue < minThreshold && joyMoved == false){
    menu--;
    updateMenu();
    delay(100);
    joyMoved = true;
  
  }
  
  if(xValue > maxThreshold && joyMoved == false){
    menu++;
    updateMenu();
    delay(100);
    joyMoved = true;
  
  }

  if(xValue > minThreshold && xValue < maxThreshold) {
    joyMoved = false; 
  }
    
  if(!digitalRead(pinSW)) { 
     executeAction();
     updateMenu();
     delay(100);
  
  }
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
        Serial.println("plecare initiala:"); //DEBUG
        Serial.println(prevBallRow);
        Serial.println(prevBallCol); 
    } else if(prevBallCol - currBallCol == 1) {
        if(currBallCol == 0) {
          right();
        } else {
          left();
        }
    } else if(prevBallCol - currBallCol == 0) {
        straight();
    } else {
        if(currBallCol == 7) {
          left();      
      } else {
          right();
      }
    }
   } 
   lc.setLed(0, currBallCol, currBallRow, true);
  }    
}
    
   
