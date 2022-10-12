#include <LiquidCrystal.h>
#include <Keypad.h>     // importa libreria Keypad//
int led1 = 30;
int led2 = 31;
int led3 = 32;
int led4 = 33;
int led5 = 34;
int led6 = 35;
int led7 = 36;
bool dentro = false;
bool bloc = false;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte FILAS = 4;     // define numero de filas
const byte COLUMNAS = 4;    // define numero de columnas
char keys[FILAS][COLUMNAS] = {    // define la distribucion de teclas
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {22, 23, 24, 25}; // pines correspondientes a las filas
byte pinesColumnas[COLUMNAS] = {26, 27, 28, 29}; // pines correspondientes a las columnas

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

char TECLA;       // almacena la tecla presionada
char CLAVE[4];        // almacena en un array 6 digitos ingresados
char CLAVE_MAESTRA[4] = "0000";   // almacena en un array la contraseña maestra
byte INDICE = 0;    // indice del array
byte INTENTOS = 0;
byte CONTEO = 0;
int pinLed[7] = {30, 31, 32, 33, 34, 35, 36};
int tiempo = 27;

void setup() {
  int i = 0;
  for (i = 0; i < 7; i++) // creamos la varialble i que será asignada a cada uno de los leds
  {
    pinMode(pinLed[i], OUTPUT); // configuramos los pinleds como salida
  }
  Serial.begin(9600);      // inicializa comunicacion serie
  lcd.begin(16, 2);
}

void loop() {

  if (INTENTOS == 3) {
    bloqueo();
  }
  mensaje();
  digitar();
  claves();
}

void mensaje() {
  lcd.setCursor(0, 0);
  lcd.print("INGRESAR CLAVE:");
  delay(500);
  INDICE = 0;
}


void digitar() {
  do {
    TECLA = teclado.getKey();   // obtiene tecla presionada y asigna a variable
    if (TECLA)        // comprueba que se haya presionado una tecla
    {
      lcd.setCursor(INDICE, 1);
      lcd.print("*");//MOSTRAR EN PANTALLA
      delay(100);
      CLAVE[INDICE] = TECLA;
      INDICE++;
    }
  } while (INDICE < 4);
}
void claves() {

  if (INDICE == 4)
  {
    if (CLAVE[0] == CLAVE_MAESTRA[0] && CLAVE[1] == CLAVE_MAESTRA[1] && CLAVE[2] == CLAVE_MAESTRA[2] && CLAVE[3] == CLAVE_MAESTRA[3]) {
      delay(500);
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("CLAVE");
      lcd.setCursor(4, 1);
      lcd.print("CORRECTA");
      delay(500);
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);
      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
      delay(500);
      lcd.clear();
    } else {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("CLAVE");
      lcd.setCursor(3, 1);
      lcd.print("INCORRECTA");
      delay(1700);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      delay(1700);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      lcd.clear();
      INTENTOS++;
      INDICE = 0;
    }
  }
}
void bloqueo() {

  lcd.setCursor(4, 0);
  lcd.print("SISTEMA");
  lcd.setCursor(3, 1);
  lcd.print("BLOQUEADO");
  digitalWrite(led5, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  delay(2000);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  delay(1500);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("SISTEMA");
  lcd.setCursor(2, 1);
  lcd.print("DESBLOQUEADO");
  delay(1900);
  int i = 0;
  for (i = 0; i < 7; i++)
  {
    digitalWrite(pinLed[i], HIGH); //enciende led
    delay(tiempo);
    digitalWrite(pinLed[i], LOW); //apaga led
    delay(tiempo);
  }
  for (i = 7; i >= 0; i--)
  {
    digitalWrite(pinLed[i], HIGH); //enciende led
    delay(tiempo);
    digitalWrite(pinLed[i], LOW); //apaga led
    delay(tiempo);
  }
  lcd.clear();
  INTENTOS = 0;
  INDICE = 0;
}