#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const int button1Pin = 2; 
const int button2Pin = 3; 
const int button3Pin = 4; 
const int button4Pin = 5;
const int LEDPin = 6;

// Morse code dictionary
String morseCodeAlphabet[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

String currentCode = ""; // Store the current Morse code input
String translated = "";   // Store the translated words

void setup() {
  lcd.begin(16, 2); 
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);
  lcd.print("Enter Morse Code:");
  lcd.setCursor(0, 1);
}

void loop() {
  int buttonState1 = digitalRead(button1Pin);
  int buttonState2 = digitalRead(button2Pin);
  int buttonState3 = digitalRead(button3Pin);
  int buttonState4 = digitalRead(button4Pin);
  
  if (buttonState1 == LOW) {
    buttonPress(".", 500);
  }
  if (buttonState2 == LOW) {
    buttonPress("-", 800);
  }
  if (buttonState3 == LOW) {
    delay(500);
    currentCode += " ";
    lcd.print(" ");
  }
  if (buttonState4 == LOW) {
    displayResult();
  }
  
  if (currentCode.endsWith(" ")) {
    interpretCode(currentCode);
    currentCode = "";
  }
}

void buttonPress(String code, int duration) {
  digitalWrite(LEDPin, HIGH);
  delay(duration);
  digitalWrite(LEDPin, LOW);
  currentCode += code;
  lcd.print(code);
}

void displayResult() {
  lcd.clear();
  lcd.print(translated);
  delay(5000);
  translated = "";
  lcd.clear();
  lcd.print("Enter Morse Code:");
  lcd.setCursor(0, 1);
}

void interpretCode(String code) {
  code.trim();  // Remove spaces
  
  if (code == "") {
    translated += " ";
  } else {
    bool valid = false; // Flag to check if the code is valid
    for (int i = 0; i < 26; i++) {
      if (code == morseCodeAlphabet[i]) {
        lcd.clear();
        lcd.print("Letter: ");
        lcd.print(char('A' + i));
        delay(500); 
        translated += char('A' + i);
        valid = true;
        break; // Exit the loop when a valid code is found
      }
    }

    if (!valid) {
      lcd.clear();
      lcd.print("Invalid code");
      delay(1000);      
    }
  }

  lcd.clear();
  lcd.print("Enter Morse Code:");
  lcd.setCursor(0, 1);
}
