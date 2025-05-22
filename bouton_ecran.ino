#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_DC     9
#define OLED_CS     10
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// Bouton & LED
const int buttonPin = 2;
const int ledPin = 13;

int buttonState = HIGH;
int lastButtonState = HIGH;
int pressCount = 0;
unsigned long buttonPressStartTime = 0;
bool codeValid = false;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  display.begin();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.println("Entrez le code:");
  display.setCursor(10, 30);
  display.print("Code: ");
  display.display();

  Serial.println("Systeme pret. Entrez le code.");
}

void loop() {
  if (codeValid) return;

  int reading = digitalRead(buttonPin);

  // Anti-rebond
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && lastButtonState == HIGH) {
      pressCount++;
      Serial.print("Pression n°");
      Serial.println(pressCount);

      // Affiche une étoile
      display.setCursor(50 + (pressCount - 1) * 6, 30);
      display.print("*");
      display.display();

      if (pressCount == 2) {
        buttonPressStartTime = millis();
        Serial.println("Maintenez 3 sec...");
      }
    }

    // Vérifie appui long après 2 pressions
    if (pressCount == 2 && reading == LOW) {
      if (millis() - buttonPressStartTime >= 3000) {
        codeValid = true;
        digitalWrite(ledPin, HIGH);
        Serial.println("Code correct !");

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(20, 25);
        display.println("code bon");
        display.display();
        delay(3000);
      }
    }

    // Si relâché trop tôt après 2 pressions
    if (reading == HIGH && lastButtonState == LOW && !codeValid && pressCount >= 2) {
      Serial.println("Relâché trop tôt. Recommencer.");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(10, 10);
      display.println("Entrez le code:");
      display.setCursor(10, 30);
      display.print("Code: ");
      display.display();

      pressCount = 0;
      buttonPressStartTime = 0;
    }
  }

  lastButtonState = reading;
}
