/*********************************************************************
    Utilisation d'un écran OLED SSD1306 SPI 128*64 
    (avec les biliothèques SSD1306 et GFX d'Adafruit)
    Pour plus d'infos:
    https://electroniqueamateur.blogspot.com/2022/08/utilisation-dun-ecran-oled-spi-ssd1306.html
    
*********************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_DC     9
#define OLED_CS     10
#define OLED_RESET  8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, OLED_DC, OLED_RESET, OLED_CS);

/* Définition d'une image bitmap: logo du blog Électronique en Amateur
  Réalisée avec l'outil en ligne  http://javl.github.io/image2cpp/  */

const unsigned char myBitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf0, 0x00, 0x00, 0x03, 0x9f, 0xff, 0xe0, 0x00, 0x07,
  0x9f, 0xff, 0xfe, 0x00, 0x0f, 0xdf, 0x0f, 0xbe, 0x00, 0x1f, 0xde, 0x06, 0x0e, 0x00, 0x3f, 0xdc,
  0x04, 0x0e, 0x00, 0x3f, 0xdc, 0x00, 0x06, 0x00, 0x3f, 0xdc, 0x00, 0x06, 0x00, 0x3f, 0xdc, 0x60,
  0x06, 0x00, 0x3f, 0xdc, 0xf1, 0x8e, 0x00, 0x3f, 0xdc, 0xf3, 0xce, 0x00, 0x3f, 0xde, 0x63, 0xde,
  0x00, 0x3f, 0xdf, 0x09, 0x9e, 0x00, 0x3f, 0xdf, 0xfc, 0x7e, 0x00, 0x3f, 0xde, 0x7f, 0xfe, 0x00,
  0x3f, 0xde, 0x7f, 0xf6, 0x00, 0x3f, 0xdf, 0x3f, 0xe6, 0x00, 0x3f, 0xdf, 0x8f, 0x8e, 0x00, 0x3f,
  0xdf, 0xe0, 0x3e, 0x00, 0x3f, 0x00, 0x3f, 0xfe, 0x00, 0x3e, 0xff, 0xc0, 0x1e, 0x00, 0x3d, 0xff,
  0xff, 0xc0, 0x00, 0x3b, 0xff, 0xff, 0xfe, 0x00, 0x37, 0xff, 0xff, 0xfe, 0x00, 0x2f, 0xff, 0xff,
  0xfe, 0x00, 0x0e, 0x1f, 0xff, 0xfe, 0x00, 0x1f, 0x9f, 0x9f, 0xfe, 0x00, 0x3f, 0x9f, 0x9f, 0x9e,
  0x00, 0x3f, 0x9f, 0x9f, 0x9e, 0x00, 0x3f, 0x9f, 0x9f, 0x9e, 0x00, 0x3f, 0x9f, 0x9f, 0x9c, 0x00,
  0x1f, 0x9f, 0x9f, 0x98, 0x00, 0x0f, 0x9f, 0x9f, 0x90, 0x00, 0x07, 0x9f, 0x9f, 0x90, 0x00, 0x00,
  0x9f, 0x9f, 0x90, 0x00, 0x00, 0x9f, 0x91, 0x90, 0x00, 0x00, 0x91, 0x91, 0x90, 0x00, 0x00, 0x91,
  0x91, 0x90, 0x00, 0x00, 0x91, 0x91, 0x90, 0x00, 0x00, 0x91, 0x91, 0x90, 0x00, 0x00, 0x91, 0x91,
  0x90, 0x00, 0x00, 0x91, 0x91, 0x90, 0x00, 0x00, 0x91, 0x91, 0x90, 0x00, 0x00, 0x91, 0x91, 0x90,
  0x00, 0x00, 0xf1, 0xd1, 0x90, 0x00, 0x00, 0x01, 0xc1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00
};


void setup()   {

  display.begin();  // initialisation de l'afficheur
  display.clearDisplay();   // ça efface à la fois le buffer et l'écran
}


void loop() {

  /**************** Éxcriture de texte  ***************/

  // taille par défaut
  display.setCursor(30, 15);  // coordonnées du point de départ du texte
  display.setTextColor(WHITE);
  display.setTextSize(1);  // taille par défaut
  display.println("Petit...");

  display.display();  // affichage à l'écran
  delay(1000);

  // deux fois plus gros
  display.setCursor(30, 35);  // coordonnées du point de départ du texte
  display.setTextSize(2);  // taille double
  display.println("GROS!");

  display.display();  // affichage à l'écran
  delay(1000);
  display.clearDisplay();  // on efface tout

  /******************** Dessiner une ligne ******************************************/

  // ligne horizontale au centre de l'écran
  display.drawLine(0, display.height() / 2, display.width() , display.height() / 2,  WHITE);

  // ligne verticale au centre de l'écran

  display.drawLine(display.width() / 2, 0, display.width() / 2, display.height(), WHITE);


  /********************* Dessiner des contours de formes géométriques ******************/

  display.drawRect( 15, 5, 30, 15, WHITE); // contour d'un rectangle
  display.drawCircle(95, 15, 8, WHITE);  // contour d'un cercle
  display.drawRoundRect(15, 40, 30, 16, 5, WHITE);  // contour d'un rectangle à coins arrondis
  display.drawTriangle(95, 40, 80, 55, 110, 55, WHITE);  // contour d'un triangle

  display.display();
  delay(1000);


  /******************* Dessiner des formes géométriqeus pleines *************************/

  display.fillRect( 15, 5, 30, 15, WHITE); // contour d'un rectangle
  display.fillCircle(95, 15, 8, WHITE);  // contour d'un cercle
  display.fillRoundRect(15, 40, 30, 16, 5, WHITE);  // contour d'un rectangle à coins arrondis
  display.fillTriangle(95, 40, 80, 55, 110, 55, WHITE);  // contour d'un triangle

  display.display();
  delay(1000);
  display.clearDisplay();
  
  /********************** Dessiner un pixel à la fois ***********************************************/


  // on trace une fonction sinusoidale, point par point
  for (int x = 1; x < 128; x++) {
    int y = 32 + round(16.0 * sin(x / 5.0));
    display.drawPixel(x, y, WHITE);
  }

  display.display();

  delay(1000);
  display.clearDisplay();


  /**************************** Dessiner une image  bitmap **********************************/

  // on affiche l'image stockée dans la constante myBitmap définie au début de ce fichier.

  display.fillRect(5,5,44,58,WHITE);  // fond blanc derrière l'image bitmap
  
  display.drawBitmap(10, 10, myBitmap, 34, 48, BLACK);

  display.setCursor(60, 30);  // coordonnées du point de départ du texte
  display.setTextColor(WHITE);
  display.setTextSize(1);  // taille par défaut
  display.println("Au revoir!");

  display.display();
  delay(2000);
  display.clearDisplay();

}