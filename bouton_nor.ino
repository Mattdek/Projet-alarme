// Déclaration des variables
int buttonPin = 2;         // Le bouton est connecté à la broche 2
int ledPin = 13;           // La LED est connectée à la broche 13

int buttonState = 0;       // État actuel du bouton
int lastButtonState = 0;   // Dernier état du bouton
int pressCount = 0;        // Compteur des pressions du bouton
unsigned long buttonPressStartTime = 0; // Temps de début de la pression longue

void setup() {
  Serial.begin(9600);        // Initialisation du port série
  pinMode(buttonPin, INPUT_PULLUP); // Le bouton est configuré en entrée avec résistance pull-up
  pinMode(ledPin, OUTPUT);   // La LED est configurée en sortie
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lire l'état actuel du bouton

  // Détecter une nouvelle pression du bouton
  if (buttonState == LOW && lastButtonState == HIGH) {
    pressCount++;  // Compter une pression
    Serial.print("Pression n°: ");
    Serial.println(pressCount);
    delay(50); // Anti-rebond
  }

  // Si le bouton est relâché et que la pression a été détectée
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Attendre un peu pour éviter les faux changements d'état
    delay(50);
  }

  // Si 2 pressions ont été comptées
  if (pressCount == 2) {
    // Vérifier si le bouton est maintenu pendant 3 secondes
    if (buttonState == LOW) {
      if (buttonPressStartTime == 0) {
        // Le début de la pression longue
        buttonPressStartTime = millis();
      }
      // Vérifier si la pression dure 3 secondes
      if (millis() - buttonPressStartTime >= 3000) {
        digitalWrite(ledPin, HIGH);  // Allumer la LED
        Serial.println("LED allumée !");
      }
    } else {
      // Si le bouton est relâché avant 3 secondes, réinitialiser le compteur et l'état
      pressCount = 0;
      buttonPressStartTime = 0;
      digitalWrite(ledPin, LOW);   // Éteindre la LED
      Serial.println("Pression annulée. Réinitialisation.");
    }
  }

  // Enregistrer l'état du bouton
  lastButtonState = buttonState;
}
