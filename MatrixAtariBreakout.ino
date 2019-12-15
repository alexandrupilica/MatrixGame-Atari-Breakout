#include <LiquidCrystal.h>
#include <LedControl.h>


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
int x = 6; //x coordonate on the matrix
int y = 4; // y coordonate on the matrix 
int gameSpeed = 300;
bool joyMoved = false; 

bool upDir = false;
bool downDir = false; 

LedControl lc = LedControl(12, 11, 10, 1); 
//
//bool matrix[8][8] {
//  {0,0,0,0,0,0,0,0}, 
//  {0,1,1,0,0,1,1,0}, 
//  {0,1,1,0,0,1,1,0},
//  {0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0}, 
//  {0,0,0,0,0,0,0,0},
//  {0,0,0,0,0,0,0,0}, 
//  {1,0,0,0,0,0,0,1}
//};

void lostGame() {
  
 bool matrix[8][8] {
  {0,0,0,0,0,0,0,1}, 
  {0,1,1,0,0,0,1,0}, 
  {0,1,1,0,0,1,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,1,0,0,0}, 
  {0,1,1,0,0,1,0,0},
  {0,1,1,0,0,0,1,0}, 
  {0,0,0,0,0,0,0,1}
};
  for (row = minRow; row < maxRow; row++){
     for(col = minCol; col < maxCol; col++){
      lc.setLed(0, row, col, matrix[row][col]);
     }
  }
}

void wonGame() {
  
}



void levelOne() {
  for (row = minRow; row < minRow + 2; row++) {
    for (col = minCol; col < maxCol; col++) {
      lc.setLed(0, col, row, true);  
    }
  }
}

void initDisplayBoard() {
  for (col = minCol + 4; col < maxCol - 2; col++) {
    lc.setLed(0, col, maxRow - 1, true);
  }
}

void initDisplayBall() {
  if(currentTime - previousTime >= interval) {
     previousTime = currentTime;
     if (blinkState == false) {
      blinkState = true;
     } else {
      blinkState = false;
     }
     lc.setLed(0, y, x, blinkState);  
  }
}

void startPlay() { 
    lc.setLed(0, y, x, true); 
//    upDir = true;  
//
//    while(upDir = true) {
//      if(currentTime - previousSTime >= gameSpeed) {
//        previousSTime = currentTime;
//        lc.setLed(0, y, x, false);
//        x++;
//        y++;
//        lc.setLed(0, y, x, true); 
//      }
//    }
//    
    }
//void moveBall()

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(6,0);
  lcd.print("ORICE");
  lc.shutdown(0, false);
  lc.setIntensity(0, 6); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);
  pinMode(A0, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  initDisplayBall();
  initDisplayBoard();
  levelOne();
  //lostGame();
   if(!digitalRead(pinSW)){
  startPlay();
   }
}
  
