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





