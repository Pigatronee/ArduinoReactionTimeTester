const int BUTTON_PIN = 2;
const int STOP_PIN = 6;
const int START_PIN = 7;

unsigned long start_time = 0;
bool waiting_for_reaction = false;

void setup() {
  Serial.begin(9600);

  Serial.print("Beep beep boop boop");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, OUTPUT);
  pinMode(START_PIN, OUTPUT);
}

void loop() {

  // Start test when button is pressed
  if (!waiting_for_reaction && digitalRead(BUTTON_PIN) == LOW) {
    // Wait for button release before proceeding
    while (digitalRead(BUTTON_PIN) == LOW) {}

    Start_Test(3000);
  }

  // If we are waiting for reaction, measure time until button press
  if (waiting_for_reaction) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      unsigned long reaction = millis() - start_time;
      Serial.print("Your reaction time was: ");
      Serial.println(reaction);

      waiting_for_reaction = false;

      // Turn off LED(s)
      digitalWrite(START_PIN, LOW);
      digitalWrite(STOP_PIN, LOW);

      // Wait for release
      while (digitalRead(BUTTON_PIN) == LOW) {}
    }
  }
}

void Start_Test(int delayTime) {
  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(START_PIN, LOW);

  delay(delayTime);

  digitalWrite(START_PIN, HIGH);
  digitalWrite(STOP_PIN, LOW);

  start_time = millis();
  waiting_for_reaction = true;
}
