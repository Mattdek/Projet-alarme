# Projet-alarme
BIENVENUE sur notre read me ceci est un tuto pour pouvoir tester notre projet


# LA CONFIGURATION

D'abors telecharger Arduino IDE(au moins la version v1.6.8) sur votre ordinateur puis brancher la carte RFThings sur l'un des ports si la 
carte se reconnait PARFAIT vous pouvez passer à l'etape 2 sinon aller sur ce [lien](https://github.com/FabienFerrero/UCA21?tab=readme-ov-file#board-programming---board-manager) et suivez le tuto.

# LES BRANCHEMENTS

Nous avons 2 composants a brancher.

## POUR LA PARTIE DE L'ECRAN:

Mettez le sur son support rouge comme sur l'image

![IMG_499A7449-32FA-4038-A951-267053B171CA](https://github.com/user-attachments/assets/f06675af-1338-4cd1-846a-88b3cc48f356)

![IMG_2967](https://github.com/user-attachments/assets/37ffc681-7245-466d-b8b9-9e221d515eed)

Puis faites ces branchements :

GND => GND de la carte

VCC => sortie 5v

D0  => D13 de la carte

D1  => D11 de la carte

RES => D8 de la carte

DC  => D9 de la carte

CS  => D10 de la carte

## POUR LA PARTIE DU DECTEUR DE PRESENCE :

GND => GND de la carte

VN  => Sortie 3v

OUT => A3 de la carte


# LES SCRIPTS

Maintenant que 
