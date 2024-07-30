#define LDR 34
#define LED 12
int threshold = 340; // Ajusta este valor segun tus pruebas

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  int sensorValue = analogRead(LDR);
  Serial.println(sensorValue);

  if (sensorValue < threshold) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
delay(3000);
}
