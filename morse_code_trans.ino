#include <LiquidCrystal.h>

// Define LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 8, 9, 10, 11, 2);

#define RED_LED 3
#define GREEN_LED 4
#define BUZZER 5

#define DOT_TIME 250
#define DASH_TIME (DOT_TIME * 3)
#define SYMBOL_GAP DOT_TIME
#define LETTER_GAP (DOT_TIME * 3)
#define WORD_GAP (DOT_TIME * 7)

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAHANA'S MORSE");

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Input: " + input);
    sendMorseCode(input);
  }
}

void sendMorseCode(String text) {
  for (int i = 0; i < text.length(); i++) {
    char letter = text[i];
    lcd.setCursor(0, 1);
    lcd.print(letter);
    playMorse(letter);
    delay(LETTER_GAP);
  }
}

void playMorse(char c) {
  switch (tolower(c)) {
    case 'a': dot(); dash(); break;
    case 'b': dash(); dot(); dot(); dot(); break;
    case 'c': dash(); dot(); dash(); dot(); break;
    case 'd': dash(); dot(); dot(); break;
    case 'e': dot(); break;
    case 'f': dot(); dot(); dash(); dot(); break;
    case 'g': dash(); dash(); dot(); break;
    case 'h': dot(); dot(); dot(); dot(); break;
    case 'i': dot(); dot(); break;
    case 'j': dot(); dash(); dash(); dash(); break;
    case 'k': dash(); dot(); dash(); break;
    case 'l': dot(); dash(); dot(); dot(); break;
    case 'm': dash(); dash(); break;
    case 'n': dash(); dot(); break;
    case 'o': dash(); dash(); dash(); break;
    case 'p': dot(); dash(); dash(); dot(); break;
    case 'q': dash(); dash(); dot(); dash(); break;
    case 'r': dot(); dash(); dot(); break;
    case 's': dot(); dot(); dot(); break;
    case 't': dash(); break;
    case 'u': dot(); dot(); dash(); break;
    case 'v': dot(); dot(); dot(); dash(); break;
    case 'w': dot(); dash(); dash(); break;
    case 'x': dash(); dot(); dot(); dash(); break;
    case 'y': dash(); dot(); dash(); dash(); break;
    case 'z': dash(); dash(); dot(); dot(); break;
    case ' ': delay(WORD_GAP); break;
    default: break;
  }
}

void dot() {
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER, 1000);
  delay(DOT_TIME);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);
  delay(SYMBOL_GAP);
}

void dash() {
  digitalWrite(GREEN_LED, HIGH);
  tone(BUZZER, 1000);
  delay(DASH_TIME);
  digitalWrite(GREEN_LED, LOW);
  noTone(BUZZER);
  delay(SYMBOL_GAP);
}
