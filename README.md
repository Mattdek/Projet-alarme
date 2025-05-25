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




pour la 2ème étape nous avons coder le bouton utilisateur SW1 qui nous sert a effectuer un code affin de désactiver l'alarme voici le code utilisé :








