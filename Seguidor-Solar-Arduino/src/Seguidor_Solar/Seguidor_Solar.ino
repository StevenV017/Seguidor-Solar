#include <Servo.h>
#include <EEPROM.h>

#define pinServoAzimut 9
#define pinServoElevacion 10

// Pines LDR
#define LDR_UL A0
#define LDR_UR A1
#define LDR_LL A2
#define LDR_LR A3

Servo Azimut;
Servo Elevacion;

int valorAzimut;
int valorElevacion;
int tolerancia = 20;

// --- CONFIGURACIÓN PARA MONTERREY ---
const int limiteElevMin = 40; // No bajar más de 40 grados (evita tocar la base)
const int limiteElevMax = 85; // No subir más de 85 grados (estabilidad estructural)
const int limiteAziMin = 10;  // Rango horizontal seguro
const int limiteAziMax = 170;

void setup() {
  Serial.begin(9600);

  valorAzimut = EEPROM.read(0);
  valorElevacion = EEPROM.read(1);

  // Validar rangos de Monterrey al iniciar
  valorAzimut = constrain(valorAzimut, limiteAziMin, limiteAziMax);
  valorElevacion = constrain(valorElevacion, limiteElevMin, limiteElevMax);

  Azimut.write(valorAzimut);
  Elevacion.write(valorElevacion);
  
  delay(200);

  Azimut.attach(pinServoAzimut);
  Elevacion.attach(pinServoElevacion);
}

void loop() {
  int valUL = analogRead(LDR_UL);
  int valUR = analogRead(LDR_UR);
  int valLL = analogRead(LDR_LL);
  int valLR = analogRead(LDR_LR);

  int promedioSup = (valUL + valUR) / 2;
  int promedioInf = (valLL + valLR) / 2;
  int promedioIzq = (valUL + valLL) / 2;
  int promedioDer = (valUR + valLR) / 2;

  bool huboMovimiento = false;

  // --- Lógica Elevación con límites de Monterrey ---
  if (abs(promedioSup - promedioInf) > tolerancia) {
    if (promedioSup > promedioInf) {
      if (valorElevacion < limiteElevMax) { // Solo sube si no ha llegado al tope
        valorElevacion++;
        huboMovimiento = true;
      }
    } else {
      if (valorElevacion > limiteElevMin) { // Solo baja si no ha llegado al mínimo
        valorElevacion--;
        huboMovimiento = true;
      }
    }
    Elevacion.write(valorElevacion);
  }

  // --- Lógica Azimut con límites ---
  if (abs(promedioIzq - promedioDer) > tolerancia) {
    if (promedioIzq > promedioDer) {
      if (valorAzimut > limiteAziMin) {
        valorAzimut--;
        huboMovimiento = true;
      }
    } else {
      if (valorAzimut < limiteAziMax) {
        valorAzimut++;
        huboMovimiento = true;
      }
    }
    Azimut.write(valorAzimut);
  }

  if (huboMovimiento) {
    EEPROM.update(0, valorAzimut);
    EEPROM.update(1, valorElevacion);
  }

  delay(40); 
}