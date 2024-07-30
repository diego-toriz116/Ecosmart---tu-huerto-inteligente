/*
Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    BC548     Bomba de agua
5v----------Colector
GPIO26------Base
            Emisor----Positivo
GND-------------------Negativo


*/

#define WATER_PUMP 26 // La bomba de agua esta conectada al GPIO26

void setup() {
  Serial.begin(115200); // Inicia la comunicacion serial a 115200 bps
  pinMode(WATER_PUMP, OUTPUT); // Configura el pin de la bomba de agua como salida
}

void loop() {
  // Enciende y apaga la bomba de agua con un ciclo de trabajo del 30% durante 3 segundos
  for(int i = 0; i < 300; i++) { // 30 repeticiones, cada una durando 100ms, resultara en un total de 3 segundos.
    digitalWrite(WATER_PUMP, HIGH); // Enciende la bomba de agua. En el modo de drenaje, la bomba se activa cuando el pin esta en estado HIGH.
    delay(3); // Mantiene la bomba encendida durante el 30% del tiempo (30ms)
    digitalWrite(WATER_PUMP, LOW); // Apaga la bomba de agua.
    delay(7); // Mantiene la bomba apagada durante el 70% del tiempo (70ms)
  }
  Serial.println("Bomba de agua desactivada por 5 segundos"); // Imprime el estado de la bomba de agua en el monitor serial
  delay(5000); // Apaga la bomba de agua durante 5 segundos
}
