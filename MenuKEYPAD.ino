#include <Wire.h> 
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

char customKeymap[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {5, 4, 3, 2}; // connect to the row pinouts of the keypad
byte colPins[4] = {9, 8, 7, 6}; // connect to the column pinouts of the keypad

Keypad_I2C customKeypad(makeKeymap(customKeymap), rowPins, colPins, 4, 4);

int opcion = 1;
int cantidadAlimento = 0; // Cantidad inicial

void setup() {
  tft.begin();
  menu(1);
  delay(200);
  Serial.begin(9600);
}

void loop() {
  char key = customKeypad.getKey();
  if (key) {
    handleKeyPress(key);
  }
}

void handleKeyPress(char key) {
  switch (key) {
    case 'A':
      opcion++;
      if (opcion == 5) opcion = 1;
      menu(opcion);
      delay(200);
      break;
    case 'B':
      // Realizar acciones según la opción seleccionada
      switch (opcion) {
        case 1:
          // Acciones para la opción "RANGO DE FUNCIONAMIENTO"
          Serial.println("Seleccionaste: RANGO DE FUNCIONAMIENTO");
          tft.fillScreen(BLACK);  // Limpiar pantalla
          break;
        case 2:
          // Acciones para la opción "NUMERO DE DOSIFICACIONES"
          Serial.println("Seleccionaste: NUMERO DE DOSIFICACIONES");
          tft.fillScreen(BLACK);  // Limpiar pantalla
          break;
        case 3:
          // Acciones para la opción "CANTIDAD DE ALIMENTO"
          Serial.println("Seleccionaste: CANTIDAD DE ALIMENTO"); 
          tft.fillScreen(BLACK);  // Limpiar pantalla
          tft.setCursor(20, 20);
          tft.setTextColor(BLUE);
          tft.setTextSize(2);
          tft.print("Cantidad de alimento:");
          tft.setCursor(130, 100);
          tft.setTextSize(5);
          tft.println(cantidadAlimento/1000);
          tft.setCursor(160, 100);
          tft.print("gr");
          break;
        case 4:
          // Acciones para la opción "CONEXION IOT"
          tft.fillScreen(BLACK);  // Limpiar pantalla
          Serial.println("Seleccionaste: CONEXION IOT");
          break;
      }
      delay(200);
      break;
    case 'C':
      // Handle other key presses if needed
      break;
    case 'D':
      // Handle other key presses if needed
      break;
  }
}

void menu(int seleccion) {
  tft.fillScreen(BLACK);
  tft.setCursor(16, 0);
  tft.setTextColor(BLUE);
  tft.setTextSize(1);
  tft.println("DOSIFICADOR AUTOMATIZADO INGENIERIA ELECTROCNICA");
  tft.drawLine(0, 10, 320, 10, BLUE);
  int posicion[5] = {0, 18, 43, 68, 93};
  tft.fillRect(10, posicion[seleccion], 300, 25, BLUE);
  tft.setTextColor(WHITE);
  
  tft.setCursor(16, 25);
  tft.println("RANGO DE FUNCIONAMIENTO");
  tft.setCursor(16, 50);
  tft.println("NUMERO DE DOSIFICACIONES");
  tft.setCursor(16, 75);
  tft.println("CANTIDAD DE ALIMENTO");
  tft.setCursor(16, 100);
  tft.println("CONEXION IOT");
  tft.drawLine(0, 125, 320, 125, BLUE);
}
