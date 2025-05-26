import serial
import time
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import datetime

# Configuration email
EMAIL_SENDER = "tonalarmeconnecter@gmail.com"
EMAIL_PASSWORD = "dsiv vqjd kgyt ywtm"
EMAIL_RECEIVER = [
    "matthis.dekermadec17@gmail.com",
    "vinuibrown@gmail.com",
    "mhadigibril@gmail.com"
]

SUJET_INTRUSION = "🚨 ALERTE INTRUSION 🚨"
MESSAGE_INTRUSION = "UNE PRÉSENCE A ÉTÉ DÉTECTÉE À VOTRE DOMICILE."

SUJET_CODE_FAUX = "❌ CODE FAUX ❌"
MESSAGE_CODE_FAUX = "Quelqu'un a tenté d'entrer un code mais a échoué."

mail_intrusion_envoye = False
mail_codefaux_envoye = False


def envoyer_mail(sujet, message):
    try:
        maintenant = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        message_complet = f"{message}\n\nHeure : {maintenant}"

        msg = MIMEMultipart()
        msg["From"] = EMAIL_SENDER
        msg["To"] = ", ".join(EMAIL_RECEIVER)
        msg["Subject"] = sujet
        msg.attach(MIMEText(message_complet, "plain"))

        server = smtplib.SMTP("smtp.gmail.com", 587)
        server.starttls()
        server.login(EMAIL_SENDER, EMAIL_PASSWORD)
        server.sendmail(EMAIL_SENDER, EMAIL_RECEIVER, msg.as_string())
        server.quit()

        print(f"✅ Email envoyé : {sujet}")
    except Exception as e:
        print("❌ Erreur d'envoi d'email :", e)


# Connexion Arduino
try:
    arduino = serial.Serial("COM3", 9600, timeout=1)
    time.sleep(2)
    print("✅ Connecté à l'Arduino.")
except Exception as e:
    print("❌ Erreur de connexion Arduino :", e)
    exit()

# Boucle principale
while True:
    try:
        ligne = arduino.readline().decode("utf-8").strip()
        if ligne:
            print(f"[Arduino] {ligne}")

            if "Présence détectée !" in ligne and not mail_intrusion_envoye:
                envoyer_mail(SUJET_INTRUSION, MESSAGE_INTRUSION)
                mail_intrusion_envoye = True

            elif "Code Faux" in ligne and not mail_codefaux_envoye:
                envoyer_mail(SUJET_CODE_FAUX, MESSAGE_CODE_FAUX)
                mail_codefaux_envoye = True

    except KeyboardInterrupt:
        print("Arrêt du programme.")
        break
    except Exception as e:
        print("❌ Erreur :", e)
