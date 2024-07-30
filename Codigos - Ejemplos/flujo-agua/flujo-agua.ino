/*

Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32   Sensor de flujo de agua
5v----------5v
GND---------GND
GPIO35------Signal

*/

#define FLOW_SENSOR 25 // El sensor de flujo de agua esta conectado al GPIO35
volatile int flowCounter; // Este entero volatil almacena el numero de pulsos del sensor de flujo.

// Esta es la funcion de interrupcion que se activa cada vez que el sensor de flujo envia un pulso.
void IRAM_ATTR pulseCounter() {
  flowCounter++;
}

void setup() {
  Serial.begin(115200); // Inicia la comunicacion serial a 115200 bps
  pinMode(FLOW_SENSOR, INPUT_PULLUP); // Configura el pin del sensor de flujo como entrada
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, RISING);  // Asocia la funcion de interrupcion pulseCounter al pin del sensor de flujo
}

void loop() {
  flowCounter = 0; // Resetea el contador de flujo al inicio de cada ciclo de lazo.
  delay(1000); // Espera un segundo (durante este tiempo, la funcion de interrupcion estara contando los pulsos del sensor de flujo).

  // Ahora, calcula el caudal de agua en litros por minuto (L/min).
  // Los sensores de flujo normalmente envÃ­an entre 450 y 450 pulsos por litro.
  // Este valor puede variar dependiendo del sensor especifico que se utilice, consulta la documentacion del tuyo para obtener el valor exacto.
  float flowRate = (flowCounter / 450.0) * 60.0;

  Serial.print("Caudal: ");
  Serial.print(flowRate);
  Serial.println(" L/min");
}
