/*
Ecosmart - tu huerto inteligente
Fecha: 20240729

Conexiones:

ESP32    BC548     Bomba de agua
5v----------Colector
GPIO26------Base
            Emisor----Positivo
GND-------------------Negativo

ESP32    DHT11
GND------GND
5V-------5V
GPIO27---signal

ESP32   Sensor de flujo de agua
5v----------5v
GND---------GND
GPIO35------Signal

ESP32    Sensor de humedad
5v----------5v
GND---------GND
GPIO33 -----Signal/A0

ESP32    Sensor de nivel de agua
5v----------5v
GND---------GND
GPIO35------Signal/A0

ESP32    transistor 2n2222
GND---------GND
GPIO14------base transistor 2n2222
Ventilador------5v

Transistor   Ventilador
Base------GND

*/

// Bibliotecas
#define HUMIDITY_SENSOR 33 // Sensor de humedad en el pin GPIO2
#define WATER_LEVEL 35 // Sensor de nivel de agua en el pin GPIO14
#define LDR 34 // Fotoresistencia en el pin GPIO32
#define FLOW_SENSOR 25 // Sensor de flujo de agua en el pin GPIO13
#define WATER_PUMP 26 // Bomba de agua en el pin GPIO12
#define DHTPIN 27 // Pin para conectar el DHT11, pin GPIO13 del ESP32CAM
#define DHTTYPE DHT11 // Configura el modelo de sensor, compatible tambien con DHT22
#define VENTILADOR 14 //ventilador en el pin GPIO14
#define LED 12 //led en el pin GPIO12

#include <WiFi.h> // Biblioteca WiFi
#include <PubSubClient.h> // Biblioteca MQTT
#include "DHT.h" // Biblioteca para el sensor DHT11

// Datos de red
const char* ssid = "HOME-80B8";
const char* password = "0005635413";
const char* mqtt_server = "broker.hivemq.com";

// Datos del sensor

// Variables para envio de mensajes
unsigned long lastMsg = 0; // Contador de tiempo mensajes
#define MSG_BUFFER_SIZE  (50) // Buffer para envio de mensajes
char msg[MSG_BUFFER_SIZE]; // Variable para conversion de mensaje

// Variables para el manejo de tiempo
double timeLast, timeNow; // Variables para el control de tiempo no bloqueante
long lastReconnectAttempt = 0; // Variable para el conteo de tiempo entre intentos de reconexion
double WAIT_MSG = 5000;  // Espera de 1 segundo entre mensajes
double RECONNECT_WAIT = 5000; // Espera de 5 segundos entre conexiones
int threshold = 340; // Ajusta este valor segun tus pruebas

// Temas MQTT
const char* mqttMsg = "codigoIoT/esp32/msg";
const char* mqttCallback = "codigoIoT/esp32/callback";
const char* mqttsensores = "codigoIoT/mor/huerto/sensores";

// Objetos WiFi, MQTT y sensor
WiFiClient espClient; // Objeto para conexion a WiFi
PubSubClient client(espClient); // Objeto para conexion a MQTT
DHT dht(DHTPIN, DHTTYPE); // Objeto que inicia el sensor
int maxHum = 70;

// Funcion para conectarse a WiFi
void setup_wifi() {
  delay(10);
  
  // Mensajes de intento de conexion
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  // Funciones de conexion
  WiFi.mode(WIFI_STA); // STA inicia el micro controlador como cliente, para accespoint se usa WIFI_AP
  WiFi.begin(ssid, password); // Proporcionar caracteristicas de red

  // Esta funcion mejora los resultados de las funciones aleatorias y toma como semilla el contador de tiempo
  randomSeed(micros());

  // Mensajes de confirmacion
  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

// Funcion Callback, Se ejecuta al recivir un mensaje
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en [");
  Serial.print(topic);
  Serial.print("] ");

  // Esta secuencia imprime y construye el mensaje recibido
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]); // Imprime
    messageTemp += (char)payload[i]; // Construye el mensaje en una variable String
  }
  Serial.println();

  // Se comprueba que el mensaje se haya concatenado correctamente
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);
  if (String(topic) == "codigoIoT/mor/huerto/maxHum") {
    maxHum = messageTemp.toInt();
  }
}

// Funcion de recomexion. Devuelve valor booleano para indicar exito o falla
boolean reconnect() {
  Serial.print("Intentando conexion MQTT...");
  // Generar un Client ID aleatorio
  String clientId = "ESP32Client-";
  clientId += String(random(0xffff), HEX);
  // Intentar conexion
  if (client.connect(clientId.c_str())) {
    // Una vez conectado, dar retroalimentacion
    client.publish(mqttMsg,"Conectado");
    // Funcion de suscripcion
    client.subscribe(mqttCallback);
    client.subscribe("codigoIoT/mor/huerto/maxHum");
  } 
  else {
      // En caso de error
      Serial.print("Error rc=");
      Serial.print(client.state());
      Serial.println(" Intentando de nuevo");
      // Esperar 5 segundos
      delay(5000);
    }
  return client.connected();
}

volatile int flowCounter; // Este entero volatil almacena el numero de pulsos del sensor de flujo.
float flowRate = 0; // Inicializa el flujo de agua
unsigned long oldTime;
unsigned long msgTime;

// Esta es la funcion de interrupcion que se activa cada vez que el sensor de flujo envia un pulso.
void IRAM_ATTR pulseCounter() {
  flowCounter++;
}

// Inicio del programa
void setup() {
  // Inician las comunicaciones
Serial.begin(115200); // Inicia la comunicacion serial a 115200 bps
 dht.begin(); // Funcion que inicia el sensor
  pinMode(HUMIDITY_SENSOR, INPUT);
  pinMode(WATER_LEVEL, INPUT);
  pinMode(FLOW_SENSOR, INPUT_PULLUP); // Configura el pin del sensor de flujo como entrada
  pinMode(WATER_PUMP, OUTPUT);
  pinMode(VENTILADOR, OUTPUT);
  pinMode(LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, RISING);  // Asocia la funcion de interrupcion pulseCounter al pin del sensor de flujo
  
  //Conef  
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);

  // Iniciar secuencias de tiempo
  timeLast = millis (); // Inicia el control de tiempo
  lastReconnectAttempt = timeLast; // Control de secuencias de tiempo
}


// Cuerpo del programa
void loop() {

  // Funcion principal de seguimiento de tiempo
  timeNow = millis();

  // FunciÃƒÆ’Ã‚Â³n de conexion y seguimiento
  if (!client.connected()) { // Se pregunta si no existe conexion
    if (timeNow - lastReconnectAttempt > RECONNECT_WAIT) { // Espera de reconexion
      // Intentar reconectar
      if (reconnect()) {
        lastReconnectAttempt = timeNow; // Actualizacion de seguimiento de tiempo
      }
    }
  } else {
    // Funcion de seguimiento
    client.loop();
  }
  
  // Enviar un mensaje cada WAIT_MSG
  if (timeNow - timeLast > WAIT_MSG && client.connected() == 1) { // Manda un mensaje por MQTT cada cinco segundos
    timeLast = timeNow; // Actualizacion de seguimiento de tiempo
  
  int sensorValue = analogRead(LDR);

  if (sensorValue < threshold) {
    digitalWrite(LED, HIGH);
    client.publish("codigoIoT/mor/huerto/luz", "Luz artificial activada");
  } else {
    digitalWrite(LED, LOW);
    client.publish("codigoIoT/mor/huerto/luz"," ");
  }



  // Cada 1 segundo, calcula el caudal de agua en litros por minuto (L/min)
  if (millis() - oldTime >= 1000) {
    oldTime = millis();
    flowRate = (flowCounter / 450.0) * 60.0; // Los sensores de flujo normalmente envian 450 pulsos por litro
    flowCounter = 0; // Resetea el contador de flujo
  }

    // Obtener temperatura y humedad
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    // Secuencia que se asegura de que la conexion con el sensor exista
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    float humiditySensor =analogRead(HUMIDITY_SENSOR); // Lee el sensor de humedad
    float waterLevel = analogRead(WATER_LEVEL); // Lee el sensor de nivel de agua

humiditySensor = (humiditySensor*100)/4095;
waterLevel = (waterLevel*100)/4095;

if (t > 27){
   // Encender el ventilador
  digitalWrite(VENTILADOR, HIGH);
   client.publish("codigoIoT/mor/huerto/ventilador", "Ventilador activado");
  }
  else {
  digitalWrite(VENTILADOR, LOW);
  client.publish("codigoIoT/mor/huerto/ventilador", " ");
  
  }
if ( humiditySensor < maxHum && waterLevel > 10) {
     client.publish("codigoIoT/mor/huerto/bomba", "Bomba de agua activada");
    digitalWrite(WATER_PUMP, HIGH); // Activa la bomba de agua
    delay(5000);
    digitalWrite(WATER_PUMP, LOW);
 } 
  else {
    client.publish("codigoIoT/mor/huerto/bomba", " ");
    digitalWrite(WATER_PUMP, LOW); // Desactiva la bomba de agua
  }
  if ( waterLevel < 10 ){
  client.publish("codigoIoT/mor/huerto/tanque", "Llenar tanque de agua");
  }

  else{
      client.publish("codigoIoT/mor/huerto/tanque", " ");
    }
    //Se construye el string correspondiente al JSON que contiene 3 variables
    String json = "{\"humtierra\":" + String(humiditySensor) + ",\"nivagua\":" + String(waterLevel) + ",\"flujoagua\":" + String(flowRate) + ",\"temp\":" + String(t) + ",\"hum\":" + String(h) + "}";
    Serial.println(json); // Se imprime en monitor solo para poder visualizar que el string esta correctamente creado
    int str_len = json.length() + 1;//Se calcula la longitud del string
    char char_array[str_len];//Se crea un arreglo de caracteres de dicha longitud
    json.toCharArray(char_array, str_len);//Se convierte el string a char array    
    client.publish(mqttsensores, char_array); // Esta es la funcion que envia los datos por MQTT, especifica el tema y el valor
  }// fin del if (timeNow - timeLast > wait)
}
