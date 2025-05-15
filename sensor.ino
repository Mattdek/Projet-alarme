#include <Wire.h>
#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS    21
#define BRIGHTNESS  32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

#define PIR_OUT     A3
#define PIR_POWER   A2

CRGB leds[NUM_LEDS];

// Durée pendant laquelle les LEDs restent rouges après détection (en millisecondes)
const unsigned long presenceDuration = 2000;
unsigned long lastDetectionTime = 0;

void setColor(int redValue, int blueValue, int greenValue) {
  fill_solid(leds, NUM_LEDS, CRGB(greenValue, redValue, blueValue));
  FastLED.show();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIR_POWER, OUTPUT);
  pinMode(PIR_OUT, INPUT);

  digitalWrite(PIR_POWER, HIGH);  // Alimente le capteur PIR

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
         .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  setColor(255, 0, 0);  // LEDs vertes au démarrage
}

void loop() {
  bool presence = digitalRead(PIR_OUT);

  if (presence) {
    Serial.println("Présence détectée !");
    lastDetectionTime = millis();  // Mémorise le moment de la détection
  }

  if (millis() - lastDetectionTime < presenceDuration) {
    // Affiche rouge pendant la durée spécifiée après détection
    setColor(0, 0, 255);  // Rouge
  } else {
    setColor(255, 0, 0);  // Vert
  }

  delay(100);
}
