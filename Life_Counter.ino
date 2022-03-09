#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 8, 9);

const int rotA = 2;
const int rotB = 3;
const int rotButt = 11;
const int steps = 24;

int angle = 0;
int encPos = 0;
int rotALast = LOW;

volatile int life = 20;
volatile byte interrupted = 0;

//char screen[80] = "";
//String test[4] = {"", "", "", ""};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.print(life);

  pinMode(rotA, INPUT);
  pinMode(rotB, INPUT);
  pinMode(rotButt, INPUT_PULLUP);

  attachInterrupt(0, rotary_interrupt, RISING);

  digitalWrite(rotA, HIGH);
  digitalWrite(rotB, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (interrupted) {
    lcd.home();
    lcd.print(life);
    interrupted = 0;
  }
}


void rotary_interrupt() {
  //boolean encA = digitalRead(rotA);
  //boolean encB = digitalRead(rotB);
  interrupted = 1;

  if (digitalRead(rotA) && !digitalRead(rotB)) {
    life--;
  }
  if (digitalRead(rotA) && digitalRead(rotB)) {
    life++;
  }
}

void screenWrite()
{
  
}
