#include <Encoder.h>
#include <LiquidCrystal.h>
#include <LinkedList.h>

#define rotA 2
#define rotB 3
#define rotButt 11
#define dnButt 17
#define upButt 16
#define homeButt 15
#define resetButt 14
#define steps 24
#define startLife 40
#define lifeLen 3

LiquidCrystal lcd(7, 6, 5, 4, 8, 9);
Encoder knob(rotA, rotB);
bool render = true;
int lCursor = 0;
bool upLast = HIGH;
bool dnLast = HIGH;
bool homeLast = HIGH;
bool resetLast = HIGH;
long rotPos =  0;  
int resetLen = 3000;


volatile int lifes[4] = {startLife, 0, 0, 0};

LinkedList<int> lHist[4]  = { 
    LinkedList<int>(),
    LinkedList<int>(),
    LinkedList<int>(),
    LinkedList<int>()
  };


void setup() {
  lcd.begin(20,4);
  pinMode(rotButt, INPUT_PULLUP);
  pinMode(upButt, INPUT_PULLUP);
  pinMode(dnButt, INPUT_PULLUP);
  pinMode(homeButt, INPUT_PULLUP);
  pinMode(resetButt, INPUT_PULLUP);

  counter_reset();
}

void loop() {
  // put your main code here, to run repeatedly:
  long newPos;

  newPos = knob.read() / 4;

  if (newPos != rotPos) {
    lifes[lCursor] += (newPos - rotPos);
    rotPos = newPos;
    render = true;
  }

  if (digitalRead(rotButt) == LOW && lHist[lCursor].get(0) != lifes[lCursor]) {
    lHist[lCursor].unshift(lifes[lCursor]);
    knob.write(0);
    rotPos = 0;
    render = true;
  }

  if (digitalRead(upButt) == LOW) {
    if (upLast == HIGH) {
      lCursor = (lCursor + 3) % 4;
      render = true;
      upLast = LOW;
    }
  } else {
    upLast = HIGH;
  }

  if (digitalRead(dnButt) == LOW) {
    if (dnLast == HIGH) {
      lCursor = (lCursor + 1) % 4;
      render = true;
      dnLast = LOW;
    }
  } else {
    dnLast = HIGH;
  }

  int resetTimer = resetLen;
  while (digitalRead(resetButt) == LOW) {
    if (resetTimer > 0) {
      resetTimer = resetTimer - 10;
      delay(10);
    } else {
      counter_reset();
    }
  }

  if (render) {
    screenWrite();
    render = false;
  }
}

void screenWrite()
{
  lcd.clear();

  for (int i=0; i<4; i++) {
  
    String strout = " ";
    
    if (i == lCursor) {
      //strout = ">";
      
      switch (i) {
        case 0: strout = "+"; break;
        case 1: strout = "X"; break;
        case 2: strout = "P"; break;
        case 3: strout = "E"; break;
      }
    }
    
    strout.concat(lifes[i]);

    if (lifes[i] < 100 && lifes[i] > -10) {
      strout.concat(' ');
    }
    
    strout.concat('|');
  
    for (int j=0; j<lHist[i].size()-1; j++) {
      strout.concat(lHist[i].get(j));
      strout.concat(" ");
    }
    
    lcd.setCursor(0,i);

    lcd.print(strout.substring(0,20));
  }
}

void counter_reset() {

  //lifes = {startLife, 0, 0, 0};

  for (int i=0; i<4; i++) {
    lHist[i].add(lifes[i]);
  }

  rotPos = 0;
  render = true;
}
