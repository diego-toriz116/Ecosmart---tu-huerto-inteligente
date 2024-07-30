/*

Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    Sensor de nivel de agua
5v----------5v
GND---------GND
GPIO35------Signal/A0

*/


#define WATER_LEVEL 35 // El sensor esta conectado a GPIO35

void setup() {
  Serial.begin(115200); // Iniciar comunicaciÃ³n serie a 115200 bps
  pinMode(WATER_LEVEL, INPUT); // Definir el pin del sensor como entrada
}

void loop() {
  int waterLevel = analogRead(WATER_LEVEL); // Leer el valor en el pin analogico 35
  Serial.println(waterLevel); // Imprimir el valor en el monitor serie
  delay(1000); // Hacer una pausa de un segundo para poder observar el resultado
}
