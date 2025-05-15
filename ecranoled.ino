/*******************************************************
  Utilisation d'un écran OLED SSD1306 SPI 128*64
  (bibliothèque u8g2)
  Plus d'infos:
  https://electroniqueamateur.blogspot.com/2022/08/utilisation-dun-ecran-oled-spi-ssd1306.html
********************************************************/

#include <U8g2lib.h>
#include <SPI.h>

// connexion hardware spi:
U8G2_SSD1306_128X64_NONAME_1_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
// U8G2_R0 ou U8G2_R2: mode paysage, U8G2_R1 ou U8G2_R3: mode portrait

/* Définition d'une image bitmap: logo du blog Électronique en Amateur
  sauvegardé dans un fichier XBM, puis ouvert avec un éditeur de texte: */
static const unsigned char logoBitmap[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0x06, 0xf0, 0xff, 0x03, 0x3f, 0x04,
  0x00, 0xf8, 0x03, 0x1f, 0x06, 0x00, 0x80, 0x03, 0x0f, 0x84, 0x0f, 0x85,
  0x03, 0x07, 0x86, 0x9f, 0x8f, 0x03, 0x07, 0xc4, 0xdf, 0x8f, 0x03, 0x03,
  0xc4, 0xff, 0x9f, 0x03, 0x03, 0xc6, 0xff, 0x9f, 0x03, 0x03, 0xc4, 0xf9,
  0x9f, 0x03, 0x03, 0xc4, 0x70, 0x8e, 0x03, 0x03, 0xc4, 0x30, 0x8c, 0x03,
  0x03, 0x84, 0x39, 0x84, 0x03, 0x03, 0x04, 0x6f, 0x86, 0x03, 0x03, 0x04,
  0xc4, 0x81, 0x03, 0x03, 0x84, 0x01, 0x80, 0x03, 0x03, 0x84, 0x01, 0x98,
  0x03, 0x03, 0x04, 0x03, 0x98, 0x03, 0x03, 0x04, 0x0e, 0x8e, 0x03, 0x03,
  0x0c, 0xf8, 0x83, 0x03, 0x03, 0xff, 0x17, 0x80, 0x03, 0x83, 0x00, 0xfc,
  0x97, 0x03, 0x63, 0x00, 0x00, 0xfc, 0x03, 0x23, 0x00, 0x00, 0x80, 0x03,
  0x13, 0x00, 0x00, 0x80, 0x03, 0x0b, 0x00, 0x00, 0x80, 0x03, 0x8f, 0x07,
  0x00, 0x80, 0x03, 0x07, 0x06, 0x06, 0x80, 0x03, 0x03, 0x07, 0x07, 0x86,
  0x03, 0x03, 0x06, 0x86, 0x86, 0x03, 0x03, 0x06, 0x06, 0x86, 0x03, 0x03,
  0x06, 0x06, 0xc6, 0x03, 0x07, 0x07, 0x06, 0xe6, 0x03, 0x0f, 0x06, 0x06,
  0xf6, 0x03, 0x1f, 0x06, 0x06, 0xf6, 0x03, 0xff, 0x06, 0x06, 0xf6, 0x03,
  0xff, 0x06, 0x76, 0xf6, 0x03, 0xff, 0x76, 0x76, 0xf6, 0x03, 0xff, 0x76,
  0x76, 0xf6, 0x03, 0xff, 0x76, 0x76, 0xf6, 0x03, 0xff, 0x76, 0x76, 0xf6,
  0x03, 0xff, 0x76, 0x76, 0xf6, 0x03, 0xff, 0x76, 0x76, 0xf6, 0x03, 0xff,
  0x76, 0x76, 0xf6, 0x03, 0xff, 0x76, 0x76, 0xf6, 0x03, 0xff, 0x70, 0x74,
  0xf6, 0x03, 0xff, 0x7f, 0x7c, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xf8, 0x03
};

void setup(void) {

  u8g2.begin();
  u8g2.enableUTF8Print(); //nécessaire pour écrire des caractères accentués
}

void loop(void) {

  u8g2.firstPage();
  do {
    u8g2.drawXBMP( 2, 8, 34, 48, logoBitmap); // position, largeur, hauteur

    /************** On écrit "Électronique en amateur" *********************/
    u8g2.setFont(u8g2_font_7x13B_tf); // choix d'une police de caractère
    u8g2.setCursor(40, 25); // position du début du texte
    u8g2.print("Électronique"); // écriture de texte
    u8g2.setCursor(70, 35);
    u8g2.print("en");
    u8g2.setCursor(55, 45);
    u8g2.print("amateur");

  } while ( u8g2.nextPage() );

  delay(2000);

  /******************** Dessiner une ligne ******************************************/
  u8g2.firstPage();
  do {

    // ligne horizontale au centre de l'écran
    u8g2.drawLine(0, 32, 128 , 32);  // point de départ, point d'arrivée

    // ligne verticale au centre de l'écran
    u8g2.drawLine(64, 0, 64, 64);


    /********************* Dessiner des contours de formes géométriques ******************/

    u8g2.drawFrame(15, 5, 30, 15);  // coin supérieur gauche, coin inférieur droit
    u8g2.drawCircle(95, 15, 8); // centre et rayon
    u8g2.drawRFrame(15, 40, 30, 16, 5); // coin supérieur gauche, coin inférieur droit, rayon du coin

    //il n'y a pas de fonction pour tracer un triangle vide
    u8g2.drawLine(95, 40, 80, 55);
    u8g2.drawLine(80, 55, 110, 55);
    u8g2.drawLine(110, 55, 95, 40);

  } while ( u8g2.nextPage() );

  delay(2000);

  /******************* Dessiner des formes géométriqeus pleines *************************/

  u8g2.firstPage();
  do {

    // ligne horizontale au centre de l'écran
    u8g2.drawLine(0, 32, 128 , 32);  // point de départ, point d'arrivée

    // ligne verticale au centre de l'écran
    u8g2.drawLine(64, 0, 64, 64);

    u8g2.drawBox(15, 5, 30, 15);  // coin supérieur gauche, coin inférieur droit
    u8g2.drawDisc(95, 15, 8);  // centre et rayon
    u8g2.drawRBox(15, 40, 30, 16, 5); // coin supérieur gauche, coin inférieur droit, rayon du coin
    u8g2.drawTriangle(95, 40, 80, 55, 110, 55); // les 3 coins

  } while ( u8g2.nextPage() );

  delay(2000);



  /***************** dessiner pixel par pixel ***********************/

  u8g2.firstPage();
  do {
    // on trace une fonction sinusoidale, point par point
    for (int x = 1; x < 128; x++) {
      int y = 32 + round(16.0 * sin(x / 5.0));
      u8g2.drawPixel(x, y);
    }
  } while ( u8g2.nextPage() );
  delay(2000);

  /******************* Écrire du texte *******************************/
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tf); // choix de la police
    u8g2.setCursor(5, 20); // position du début du texte
    u8g2.print("Caractères");  // on écrit le texte
    u8g2.setCursor(5, 35);
    u8g2.print("accentués:");
    u8g2.setCursor(5, 55);
    u8g2.print("ÀàÂâÉéÈèÊêÇç");
  } while ( u8g2.nextPage() );
  delay(2000);
}