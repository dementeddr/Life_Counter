#include <Encoder.h>
#include <LiquidCrystal.h>

#define rotA 2
#define rotB 3
#define rotButt 11
#define steps 24

LiquidCrystal lcd(7, 6, 5, 4, 8, 9);
Encoder knob(rotA, rotB);

volatile int life = 20;


//char screen[80] = "";
//String test[4] = {"", "", "", ""};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.print(life);

  pinMode(rotButt, INPUT_PULLUP);
}

long rotPos =  -999;

void loop() {
  // put your main code here, to run repeatedly:
  long newPos;

  newPos = knob.read() / 4;

  if (newPos != rotPos) {
    lcd.home();
    lcd.print(newPos);
    rotPos = newPos;
  }

  if (digitalRead(rotButt) == LOW) {
    knob.write(0);
    rotPos = 0;
    lcd.home();
    lcd.print(rotPos);
  }
}

void screenWrite()
{
  
}
