# Projet-alarme
test
La première étape a été de coder le deteceur de mouvement et d'envoyer un mail si une presence est detecter via le code suivant : 


import serial
import time
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import datetime  # ajoute cette ligne en haut de ton script

# Configuration email
EMAIL_SENDER = "tonalarmeconnecter@gmail.com"
EMAIL_PASSWORD = "dsiv vqjd kgyt ywtm"
EMAIL_RECEIVER = ["matthis.dekermadec17@gmail.com", "vinuibrown@gmail.com", "mhadigibril@gmail.com"]
SUJET = "🚨 ALERTE INTRUSION 🚨"
MESSAGE = "UNE PRESENCE A ETE DETECTER A VOTRE DOMICILE"

mail_envoye = False


def envoyer_mail():
    try:
        maintenant = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")  # format YYYY-MM-DD HH:MM:SS
        message_complet = f"{MESSAGE}\n\nHeure de détection : {maintenant}"

        msg = MIMEMultipart()
        msg["From"] = EMAIL_SENDER
        msg["To"] = ", ".join(EMAIL_RECEIVER)
        msg["Subject"] = SUJET
        msg.attach(MIMEText(message_complet, "plain"))

        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.set_debuglevel(1)
        server.starttls()
        server.login(EMAIL_SENDER, EMAIL_PASSWORD)
        server.sendmail(EMAIL_SENDER, EMAIL_RECEIVER, msg.as_string())
        server.quit()
        print("✅ Email envoyé à tous les destinataires.")
    except Exception as e:
        print("❌ Erreur d'envoi d'email :", e)


try:
    arduino = serial.Serial("COM3", 9600, timeout=1)
    time.sleep(2)
    print("✅ Connecté à l'Arduino.")
except Exception as e:
    print("❌ Erreur de connexion Arduino :", e)
    exit()

while True:
    try:
        ligne = arduino.readline().decode("utf-8").strip()
        if ligne:
            print(f"[Arduino] {ligne}")
            if "Présence détectée !" in ligne and not mail_envoye:
                envoyer_mail()
                mail_envoye = True
    except KeyboardInterrupt:
        print("Arrêt du programme.")
        break
    except Exception as e:
        print("❌ Erreur :", e)




Pour la 2ème étape nous avons coder le bouton utilisateur SW1 qui nous sert a effectuer un code affin de désactiver l'alarme voici le code utilisé :


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




Ensuite nous avons travaillé sur le codage de l'écran oled qui affiche principalement code bon ou faux lorsque on effectue le code via le bouton grace a ce code :



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



