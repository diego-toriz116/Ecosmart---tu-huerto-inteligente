/*

Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    DHT11
GND------GND
5V-------5V
GPIO27---signal

*/
#include <DHT.h>

#define DHTPIN 27     // Pin GPIO del ESP32 conectado al pin Data del DHT11
#define DHTTYPE DHT11 // Definir el tipo de sensor DHT

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // Espera entre lecturas
  delay(2000);

  // Leer la humedad
  float humidity = dht.readHumidity();
  // Leer la temperatura en grados Celsius
  float temperature = dht.readTemperature();

  // Verifica si alguna lectura ha fallado
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Mostrar los valores en el monitor serie
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("Temperature: ");
  Serial.print(temperature);
}
