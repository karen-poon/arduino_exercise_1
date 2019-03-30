#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int swPin = 3, swPin2 = 4, ledPin = 13, beepPin = 2;
int swValue, swValue2;
int previous = HIGH, previous2 = HIGH;
int Time = 0, Time2 = 0;
int debounce = 200;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(swPin, INPUT);
  pinMode(swPin2, INPUT);
  pinMode(beepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin();
  lcd.backlight();
  showNum();
}

void loop() {
  swValue = digitalRead(swPin);
  swValue2 = digitalRead(swPin2);

  if (swValue && previous == LOW && millis() - Time > debounce) {
    digitalWrite(beepPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(50);
    count++;
    Time = millis();
    showNum();
  }

  if (swValue2 && previous2 == LOW && millis() - Time2 > debounce) {
    digitalWrite(beepPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(50);
    count--;
    Time2 = millis();
    showNum();
  }
 
  digitalWrite(beepPin, LOW);
  digitalWrite(ledPin, LOW);
  previous = swValue;
  previous2 = swValue2;
  Serial.println(count);

}

void showNum() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Number : ");
  lcd.setCursor(9,0);
  lcd.print(count);
}

