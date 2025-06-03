# ALARME SILENCIEUX
BIENVENUE sur notre README ceci est un tuto pour pouvoir tester notre projet

# SOMMAIRE

### [BRANCHEMENT ET FONCTIONNEMENT](https://github.com/Mattdek/Projet-alarme/blob/main/README.md#materiel)
### [EXPLICATION CODE](https://github.com/Mattdek/Projet-alarme/blob/main/README.md#code-arduino)

# MATERIEL
Pour pouvoir tester il vous faut :<br/>
-un capteur PIR <br/>
-un écran OLED <br/>

# LA CONFIGURATION

D'abors telecharger Arduino IDE(au moins la version v1.6.8) sur votre ordinateur puis brancher la carte RFThings sur l'un des ports si la 
carte se reconnait **PARFAIT** vous pouvez passer à l'etape 2 sinon aller sur ce [lien](https://github.com/FabienFerrero/UCA21?tab=readme-ov-file#board-programming---board-manager) et suivez le tuto.

# LES BRANCHEMENTS

Nous avons 2 composants a brancher.

## POUR LA PARTIE DE L'ECRAN:

 !! IMPORTANT : DEBRANCHER LA CARTE A VOTRE ORDINATEUR POUR EVITER LES COURT-CIRCUIT

Mettez le sur son support comme sur l'image

![IMG_499A7449-32FA-4038-A951-267053B171CA](https://github.com/user-attachments/assets/f06675af-1338-4cd1-846a-88b3cc48f356) ![IMG_2967](https://github.com/user-attachments/assets/37ffc681-7245-466d-b8b9-9e221d515eed)

Puis faites ces branchements :

GND => GND de la carte

VCC => sortie 5v

D0  => D13 de la carte

D1  => D11 de la carte

RES => D8 de la carte

DC  => D9 de la carte

CS  => D10 de la carte

## POUR LA PARTIE DU DECTEUR DE PRESENCE :

 !! IMPORTANT : DEBRANCHER LA CARTE A VOTRE ORDINATEUR POUR EVITER LES COURT-CIRCUIT
 
GND => GND de la carte

VN  => Sortie 3v

OUT => A3 de la carte


# LES SCRIPTS 
## ARDUINO

Maintenant que nous avons tous nos composants branché vous pouvez connecter la carte à votre ordinateur puis selctionner bien carte et verifier bien que vous etes sur le port "COM3" puis copier ce scipt<br/>

   https://github.com/Mattdek/Projet-alarme/blob/db9e4c2a9641eba62687088eb3b9fb727a06c42d/oled_sensor_btn.ino#L1-L204

   Faites televerser
   
   Si cela ne marche pas c'est qu'il faut que vous installer les bibliothèques qu'on utilise donc :<br/>
     -Adafruit_GFX.h<br/>
     -Adafruit_SSD1306.h<br/>

 Pour pouvoir installer il faut faire Sketch > Include Library > puis mettre celui qui nous interesse

## PYTHON
### Comme nous avons ni Bluetooth ni Wifi sur cette carte on utiliseras le wifi de l'ordinateur pour envoyer un mail via SMTP
Etape 1: Telecharger Python

Etape 2:ouvrir l'invite de commande(CMD) et installer les bibliothèques nécessaires :

    pip install pyserial
Etape 3: copier coller ce script sur python et l'enregister dans un dossier que l'on connait son chemin

https://github.com/Mattdek/Projet-alarme/blob/db9e4c2a9641eba62687088eb3b9fb727a06c42d/alarme_presence.py#L1-L77

Modifié cette ligne par vos mails 
   
   https://github.com/Mattdek/Projet-alarme/blob/db9e4c2a9641eba62687088eb3b9fb727a06c42d/alarme_presence.py#L11-L14


### Imaginons que vous avez mis ce fichier dans le repertoire "U Roy-Natty Rebel" par exemple 
![chemin_absolue](https://www.macbookcity.fr/wp-content/uploads/2018/10/Afficher-le-chemin-dacces-dun-fichier-sur-Mac-en-bas-du-finder-uniquement.jpg) 

Donc faut faire 

    cd Utilisateurs/job/Musique/U Roy-Natty Rebel
  
  Verifier bien que la console arduino(moniteur de serie) est fermée ou vous pouvez fermer completement arduino

  Puis faite ceci 

    python alarme_presence.py
  
 
# FONCTIONNEMENT
### Voici où se situe notre bouton 
![board](https://github.com/user-attachments/assets/bca35b1a-089e-4148-b956-e36560219e1a)

## Pour pouvoir desactiver le detecteur il faut appauyer 2 fois sur le bouton puis rester appuyer sur ce meme bouton pendant 3 fois

## SI TU FAIS 3 ERREURS TU RECEVRAS UN MAIL COMME CELUI CI AVEC L'HEURE LOCALE DE L'ORDINATEUR

![IMG_7682](https://github.com/user-attachments/assets/563d5415-4ffe-4a7f-9297-821af4741b01)

## SI QUELQU'UN RENTRE SANS METTRE LE CODE TU RECEVRAS UN MAIL COMME CECI AVEC L'HEURE LOCALE DE L'ORDINATEUR EGALEMENT

![IMG_7685](https://github.com/user-attachments/assets/4dcd24dd-8971-44bf-be95-72bec52d2f61)

# EXPLICATION DU CODE 
## [ARDUINO]() // [PYTHON]()
### Ce bloc de code ci-dessous permet d'importer les bibliotheques nécessaire

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L1-L3

### Puis on initialise nos compasants 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L5-L42

### Le capteur PIR se reactiver pret à detecter les mouvements (se reactive pour creer une boucle à la fin)

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L45-L50

### Initialise les tentatives à 0 et desactive le capteur PIR pendant 10sec 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L53-L65

### Si quelqu'un passe sans mettre le code la carte va envoyer "Présence détectée !" dans la console 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L68-L78

### On lit les bouton et on configure le code 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L81-L140

### Si il y a plus de 3 tentatives il lance l'alerte intrution 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L143-L151

### Voici l'alerte intrutuion 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L186-L204

### Se reset pour faire la boucle 

https://github.com/Mattdek/Projet-alarme/blob/16c9cb513701ec9fecbdc7c88554dc8067ab4b5a/oled_sensor_btn.ino#L153-L184

## PYTHON
