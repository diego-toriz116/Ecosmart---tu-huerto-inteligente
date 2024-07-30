/*

Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    transistor 2n2222
GND---------GND
GPIO14------base transistor 2n2222
Ventilador------5v

Transistor   Ventilador
Base------GND
*/

#define VENTILADOR 14 //ventilador en el pin GPIO14

void setup() {
  pinMode(VENTILADOR, OUTPUT); // Configura el pin como salida
  digitalWrite(VENTILADOR, LOW); //ventilador apagado
}

void loop() {
  // Encender el ventilador
  digitalWrite(VENTILADOR, HIGH);
  delay(5000); // Ventilador encendido por 5 segundos

  // Apagar el ventilador
  digitalWrite(VENTILADOR, LOW);
  delay(5000); // Ventilador apagado por 5 segundos
}
