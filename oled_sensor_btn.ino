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

// Bouton & LED classique
const int buttonPin = 2;
const int ledPin = 13;

// Capteur PIR
const int pirPin = A3;
bool pirActive = true;
unsigned long pirDeactivateTime = 0;
const unsigned long pirDeactivateDuration = 10000;

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
  pinMode(pirPin, INPUT);

  display.begin();
  display.setTextColor(WHITE);
  resetDisplay("");
  Serial.println("Système prêt. Entrez le code.");
}

void loop() {
  // Réactivation du PIR après désactivation temporaire
  if (!pirActive && (millis() - pirDeactivateTime >= pirDeactivateDuration)) {
    pirActive = true;
    Serial.println("PIR réactivé");
  }

  // Si code correct
  if (codeValid) {
    failedAttempts = 0;
    digitalWrite(ledPin, HIGH); // LED allumée

    pirActive = false;
    pirDeactivateTime = millis();

    delay(3000);
    digitalWrite(ledPin, LOW);
    codeValid = false;
    resetDisplay("");
    return;
  }

  // Lecture capteur PIR si actif
  bool presenceDetected = false;
  if (pirActive) {
    int presence = digitalRead(pirPin);
    if (presence == HIGH) {
      presenceDetected = true;
      Serial.println("Présence détectée !");
      digitalWrite(ledPin, HIGH); // Allume la LED en présence
    } else {
      digitalWrite(ledPin, LOW); // Éteint sinon
    }
  }

  // Lecture bouton
  int reading = digitalRead(buttonPin);

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
  }

  // Maintien bouton 3 sec après 3 pressions
  if (pressCount == 3 && buttonState == LOW) {
    if (millis() - buttonPressStartTime >= 3000) {
      codeValid = true;
      Serial.println("Code correct !");
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(20, 25);
      display.println("code bon");
      display.display();
    }
  }

  // Si bouton relâché trop tôt après 3 pressions
  if (pressCount == 3 && buttonState == HIGH && !codeValid) {
    Serial.println("Code faux. Recommencer.");
    failedAttempts++;
    resetDisplay("Code Faux");
  }

  // Temps écoulé pour entrer le code
  if (pressCount > 0 && !codeValid && millis() - codeStartTime > 10000) {
    Serial.println("Temps écoulé. Recommencer.");
    failedAttempts++;
    resetDisplay("Trop lent !");
  }

  // Alerte intrusion après 3 échecs
  if (failedAttempts >= 3) {
    intrusionAlert();
    failedAttempts = 0;
    resetDisplay("");
    return;
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
    display.setCursor(10, 50);
    display.print("               ");
  }

  display.setCursor(100, 0);
  display.print("X:");
  display.print(failedAttempts);

  display.display();

  if (strlen(message) > 0) {
    delay(2000);
    display.fillRect(0, 50, SCREEN_WIDTH, 14, 0);
    display.display();
  }
}

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
