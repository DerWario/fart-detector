/*
    Name:       fart.ino
    Created:	06.07.2018 22:41:19
    Author:     Marlon Kersting
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

const int xAss = 11;
const int yAss = 32;
int maxWert = 0;

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

void setup() {
	Serial.begin(9600);
	// initialize display
	display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
	display.display();
	delay(5);	//Datenübertragung und boot.
}

void loop() {
	display.clearDisplay();
	int wert = analogRead(A15);
	if (wert > maxWert) { maxWert = wert; }
	fart(wert, maxWert);
	delay(1000);
}


//------------------------DISPLAY------------------------//
void fart(int x, int xMax) {
	display.clearDisplay();
	emptyFart(xMax);
	//Kreise
	int viertel = (getY(x) - getNegY(x)) / 4;						// Viertel für die Position und Radien der Kreise
	display.fillCircle(x, yAss + viertel, viertel, WHITE);			// x bleibt x; y wird um ein Viertel der Länge der Base verschoben.; Radius ist ein Viertel
	display.fillCircle(x, yAss - viertel, viertel, WHITE);
	display.fillCircle(x + (x / 10) - 1, yAss, viertel, WHITE);		// Kreis in der Mitte. 

	drawAss();
	//Dreieick
	display.fillTriangle(xAss, yAss, x, getY(x), x, getNegY(x), WHITE);
	display.display();
}

void emptyFart(int x) {
	//Kreise
	int viertel = (getY(x) - getNegY(x)) / 4;						// Viertel für den Position und Radien der Kreise
	display.drawCircle(x, yAss + viertel, viertel, WHITE);			// x bleibt x; y wird um ein Viertel der Länge der Base verschoben.; Radius ist ein Viertel
	display.drawCircle(x, yAss - viertel, viertel, WHITE);
	display.drawCircle(x + (x / 10) - 1, yAss, viertel, WHITE);		// Kreis in der Mitte.

	//Linien Entfernen
	//display.fillCircle(x, yAss + viertel, viertel - 1, BLACK);    // Radius der Löschkreise um eins reduziert um Linien in den Kreisen zu entfernen.
	//display.fillCircle(x, yAss - viertel, viertel - 1, BLACK);	// Benötigt Rechteck zum entfernen der linken Kreishälften.
	//display.fillCircle(x + (x / 10) - 1, yAss, viertel - 1, BLACK);
	//display.fillRect(xAss, 0, x - xAss, 64, BLACK); // Feld kann kleiner sein.

	display.fillCircle(x-1, yAss + viertel, viertel , BLACK);      // Löschkreise auf X-Achse verschoben, spaart einen Befehlt, es entsteht aber eine kleine Lücke.
	display.fillCircle(x-1, yAss - viertel, viertel , BLACK);
	display.fillCircle(x + (x / 10) - 2, yAss, viertel , BLACK);


	//Dreieick
	display.drawTriangle(xAss, yAss, x, getY(x), x, getNegY(x), WHITE);

	//Linie Entfernen
	display.drawLine(x, getY(x) - 1, x, getNegY(x) + 1, BLACK);
}


void drawAss() {
	display.fillRect(0, 0, 16, 63, WHITE);
	display.fillTriangle(16, 30, 16, 0, 7, 0, BLACK);
	display.fillCircle(xAss, yAss, 10, WHITE);
}

int getY(float x) {
	return (int)(x * 0.22) + 32; //Funktion zur Berechnung der Geraden
}

int getNegY(float x) {
	return (int)-(x * 0.22) + 32; //Funktion zur Berechnung der Geraden
}