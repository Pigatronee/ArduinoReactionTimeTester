#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 16, 2);

const int BUTTON_PIN = 2;
const int STOP_PIN = 6;
const int START_PIN = 7;

unsigned long start_time = 0;
bool waiting_for_reaction = false;

void setup() {
  Serial.begin(9600);
  // Lcd setup
  lcd.init();       
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Press the button");
  lcd.setCursor(0, 1);
  lcd.print("    to begin.");
  // End lcd setup

  Serial.print("Beep beep boop boop");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, OUTPUT);
  pinMode(START_PIN, OUTPUT);
}

void loop() {

  // Start test when button is pressed
  if (!waiting_for_reaction && digitalRead(BUTTON_PIN) == LOW) {
    // Wait for button to go high
    while (digitalRead(BUTTON_PIN) == LOW) {}

    Start_Test(3000);
  }

  // If we are waiting for reaction, measure time until button press
  if (waiting_for_reaction) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      unsigned long reaction = millis() - start_time;
      Serial.print("Your reaction time was: ");
      Serial.println(reaction);
      // show your reaction time on the lcd
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Your reaction");
      lcd.setCursor(0, 1);
      lcd.print("was ");
      lcd.print(reaction);
      lcd.print("ms");


      waiting_for_reaction = false;

      // Turn off leds
      digitalWrite(START_PIN, LOW);
      digitalWrite(STOP_PIN, LOW);

      // Wait for the button to be released
      while (digitalRead(BUTTON_PIN) == LOW) {}
    }
  }
}

void Start_Test(int delayTime) {

  // Change lCd display
  lcd.setCursor(0, 0);
  lcd.print("Press again when");
  lcd.setCursor(0, 1);
  lcd.print("you see green");

  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(START_PIN, LOW);

  delay(delayTime);

  digitalWrite(START_PIN, HIGH);
  digitalWrite(STOP_PIN, LOW);

  start_time = millis();
  waiting_for_reaction = true;
}
