/*

Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    Sensor de humedad
5v----------5v
GND---------GND
GPIO33 -----Signal/A0

*/


#define HUMIDITY_SENSOR 33 // El sensor esta conectado al GPIO33

void setup() {
  Serial.begin(115200); // Inicia la comunicaciÃ³n serial a 115200 bps
  pinMode(HUMIDITY_SENSOR, INPUT); // Configura el pin del sensor de humedad como entrada
}

void loop() {
  int humiditySensor = analogRead(HUMIDITY_SENSOR); // Lee la entrada en el pin analogico 33
  Serial.println(humiditySensor); // Imprime el valor al monitor serial
  delay(1000); // Espera un segundo para que tengamos tiempo de ver el resultado
}
