#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

// OLED config
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
unsigned long codeStartTime = 0;
bool codeValid = false;
unsigned long debounceDelay = 50;
unsigned long lastDebounceTime = 0;
int failedAttempts = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  display.begin();
  display.setTextColor(WHITE);
  resetDisplay("");
  Serial.println("Système prêt. Entrez le code.");
}

void loop() {
  if (codeValid) {
    // Remise à zéro des échecs quand code est bon
    failedAttempts = 0;

    delay(3000);
    digitalWrite(ledPin, LOW);
    codeValid = false;
    resetDisplay("");
    return;
  }

  // Si trop d'échecs, alerte intrusion
  if (failedAttempts >= 3) {
    intrusionAlert();
    failedAttempts = 0;  // Remise à zéro après alerte
    resetDisplay("");
    return;
  }

  int reading = digitalRead(buttonPin);
  Serial.print("Lecture bouton : ");
  Serial.println(reading);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        pressCount++;
        Serial.print("Pression n°");
        Serial.println(pressCount);

        if (pressCount == 1) {
          codeStartTime = millis();
          // Affiche "code en cours..." en bas dès la 1ère pression
          display.setCursor(10, 50);
          display.print("code en cours...");
          display.display();
        }

        display.setCursor(50 + (pressCount - 1) * 6, 30);
        display.print("*");
        display.display();

        if (pressCount == 3) {
          buttonPressStartTime = millis();
          Serial.println("Maintenez 3 sec...");
        }
      }
    }

    if (pressCount == 3 && buttonState == LOW) {
      if (millis() - buttonPressStartTime >= 3000) {
        codeValid = true;
        digitalWrite(ledPin, HIGH);
        Serial.println("Code correct !");

        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(20, 25);
        display.println("code bon");
        display.display();
      }
    }

    if (pressCount == 3 && buttonState == HIGH && !codeValid) {
      Serial.println("Code faux. Recommencer.");
      failedAttempts++;
      resetDisplay("Code Faux");
    }
  }

  if (pressCount > 0 && !codeValid && millis() - codeStartTime > 10000) {
    Serial.println("Temps écoulé. Recommencer.");
    failedAttempts++;
    resetDisplay("Trop lent !");
  }

  lastButtonState = reading;
}

void resetDisplay(const char* message) {
  pressCount = 0;
  buttonPressStartTime = 0;
  codeStartTime = 0;

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.println("Entrez le code:");
  display.setCursor(10, 30);
  display.print("Code: ");

  if (strlen(message) > 0) {
    display.setCursor(10, 50);
    display.print(message);
  } else {
    // Efface la ligne du bas si pas de message
    display.setCursor(10, 50);
    display.print("               ");
  }

  display.setCursor(100, 0);
  display.print("X:");
  display.print(failedAttempts);

  display.display();

  if (strlen(message) > 0) {
    delay(2000);
    display.fillRect(0, 50, SCREEN_WIDTH, 14, BLACK);
    display.display();
  }
}

// Affiche message intrusion clignotant pendant 5 secondes
void intrusionAlert() {
  unsigned long startTime = millis();
  bool showMessage = true;

  while (millis() - startTime < 5000) {
    display.clearDisplay();
    if (showMessage) {
      display.setTextSize(1);
      display.setCursor(5, 25);
      display.println("Tentative");
      display.setCursor(10, 50);
      display.println("d'intrusion");
    }
    display.display();
    showMessage = !showMessage;
    delay(500);
  }
}
