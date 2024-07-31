# Ecosmart - Tu Huerto Inteligente

## Tabla de Contenidos
1. [Descripción](#descripción)
2. [Objetivos](#objetivos)
3. [Materiales](#materiales)
4. [Dependencias de código](#dependencias-de-código)
5. [Guía de implementación](#guía-de-implementación)
6. [Resultado Final](#resultado-final)
7. [Créditos](#créditos)

## Descripción
Ecosmart - Tu Huerto Inteligente es un sistema que está diseñado con una visión hacia las personas que tienen afición por el autocultivo, la buena salud y el medio ambiente, proporcionando una solución que integra una variedad de sensores, actuadores y plataformas de control para monitorear y ajustar las condiciones ambientales, asegurando un entorno ideal para el crecimiento de las plantas.

## Objetivos
- Desarrollar un invernadero accesible, optimizado e inteligente: Crear un sistema que utilice la tecnología para hacer los cultivos más eficiente y accesible para todos.
- Fomentar una alimentación saludable: Incentivar a las personas a cultivar sus propios alimentos, promoviendo así hábitos alimenticios más saludables.
- Mejorar la calidad de las cosechas: Implementar tecnologías y técnicas que aumenten la calidad y el rendimiento de las cosechas en huertos e invernaderos.
- Optimizar el funcionamiento del huerto mediante plataformas de control: Mediante plataformas de control, desarrollar un programa que permita monitorear y controlar en tiempo real los factores que afectan el crecimiento de las plantas, asegurando condiciones óptimas para su desarrollo.

## Materiales
### Hardware
- [Raspberry Pi 4B](https://www.raspberrypi.com/products/raspberry-pi-4-model-b/)
- [ESP32](https://todomaker.com/blog/conociendo-al-esp32/)
- [Micro SD 32GB](https://muytecnologicos.com/diccionario-tecnologico/tarjeta-microsd)
### Componentes electrónicos
- [Protoboard](https://portalacademico.cch.unam.mx/cibernetica1/implementacion-de-circuitos-logicos/tableta-protoboard)
- [Cables Jumpers](https://www.hwlibre.com/cable-jumper/)
- [Resistencias de 220 Ω y 1 kΩ](arduino.cc/en/software)
- [Sensor de humedad de tierra](https://www.330ohms.com/products/sensor-de-humedad-en-tierra-1)
- [Sensor de nivel de agua resistivo](https://www.tostatronic.com/product/sensor-de-nivel-de-agua-para-arduino/?gad_source=1&gclid=CjwKCAjw2Je1BhAgEiwAp3KY7z6wg0eJ8fREsY57eyAPW9IIW6BBdSjvqXGnEmjgDpXtGdkoaXtTJxoC2kwQAvD_BwE)
- [Sensor de flujo de agua](https://naylampmechatronics.com/blog/47_tutorial-sensor-de-flujo-de-agua.html)
- [Bomba de agua de 5V](https://sonrobots.com/producto/bomba-de-agua-sumergible-5v/)
- [Sensor DHT11](https://components101.com/sensors/dht11-temperature-sensor)
- [Ventilador de 5V](https://www.330ohms.com/products/ventilador-5v-para-raspberry-pi-3)
- [Transistor BC548](https://www.inventable.eu/2017/07/09/transistor-bc548/)
- [Transistor 2N2222](https://descubrearduino.com/2n2222-todo-lo-que-necesitas-saber-sobre-este-transitor/)
- [LDR](https://www.tecnosalva.com/que-es-y-como-funciona-una-ldr/)
- [LED](https://www.ledtecnologia.com/que-es-un-led/)
  
### Software
- [Raspberry Pi OS](https://www.raspberrypi.com/software/)
- [Node-Red](https://nodered.org/)
- [Arduino IDE 1.8.18](https://www.ceac.es/blog/que-es-el-ide-de-arduino-en-robotica)
  
## Dependencias de código
### Dependencias de Arduino
**ESP32**
1. Abre Aruino IDE -> Ve a 'Archivo' -> Preferencias.

2. Busca el campo 'Gestor de URLs Adicionales de Tarjetas' y añade la siguiente URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json. Haz clic en OK para guardar y cerrar las Preferencias.

3. Ve a 'Herramientas' -> Placa -> 'Gestor de Placas'. Escribe 'esp32' en el cuadro de búsqueda. Busca el paquete 'esp32' de 'Espressif Systems' y haz clic en Instalar.

4. Ve a 'Herramientas' -> 'Placa' y selecciona 'ESP32 Dev Module'.

5. Conecta la esp32 por vía USB a la Raspberry. Ve a 'Herramientas' -> 'Puerto' y selecciona el puerto al que está conectada la ESP32.

**Librerias**

1. Ve a 'Programa' -> 'Incluir Librería' -> 'Gestionar Librerías'. Escribe 'WiFi' y busca la biblioteca 'WiFi' de 'Espressif Systems' y luego da click en 'Instalar'.

Repite los mismos pasos con la librería 'DHT sensor library'.

### Dependencias de Node-red

1. Inicia node-red en una terminal con el comando node-red. Abre tu navegador web y ve a http://<tu_IP>:1880 o http://localhost:1880.

2. Haz clic en el menú en la esquina superior derecha (tres líneas horizontales) y selecciona 'Manage palette'. 

3. En la pestaña 'Install', busca 'node-red-dashboard' y haz click en el boton 'install'.

Repite los mismos pasos e instala 'node-red-contrib-string'.


## Guía de implementación
1. Realiza el siguiente diagrama:
![Diagrama - Ecosmart](https://github.com/diego-toriz116/Ecosmart_tu_huerto_inteligente/raw/main/imagenes/Ecosmart-Diagrama.jpg)

2. Clona el repositorio con el comando  ```git clone https://github.com/diego-toriz116/Ecosmart---tu-huerto-inteligente.git``` .
3. Dirígete al documento llamado "Codigo-final-Ecosmart.ino" con "Files Manager" de la interfaz de raspberry pi y abre el documento con Arduino IDE, o con el comando  ```arduino home/tu_usuario/Ecosmart_tu_huerto_inteligente/Codigo-final-Ecosmart/Codigo-final-Ecosmart.ino```.
4. Conecta tu esp32 a un puerto de la raspberry pi, dirígete a "Herramientas", asegurate que la placa seleccionada sea "ESP32 Dev Module" y en la opción de "puerto" revisa que se encuentre el que esta conectado a la esp32. Ve a la opcion "Upload Speed" y selecciona "115200".
5. Sube el código con la flecha que se encuentra en la esquina superior izquierda.
6. Abre una terminal y escribe el comando  ```node-red```, a continuación, en tu navegador escribe http://<tu_IP>:1880 o http://localhost:1880, haz clic en el menú en la esquina superior derecha (tres líneas horizontales) y selecciona la opción "Import", da clic en "select a file to import" y elige el archivo llamado "codigo-ecosmart-node-red.json", da clic en "Import" y selecciona el botón de "Deploy". Se debe ver de la siguiente manera:
  ![node-red-Ecosmart](https://github.com/diego-toriz116/Ecosmart_tu_huerto_inteligente/raw/main/imagenes/Node-red-Ecosmart.png)
8. Abre una nueva pestaña con la direccion http://<tu_IP>:1880/ui o http://localhost:1880/ui.
9. Haz llegado al final, puedes amodar tus sensores y actuadores como te sea más util, adememas de conectar el circuito a una fuente de 5V (no es necesario que se mantenga conectada a la Raspberry Pi).
   
**Nota:** Si no funciona algún componente electrónico, dirígete a la carpeta de "Codigos-Ejemplos", en ella podrás encontrar los códigos individuales de los componente y asi verificar su funcionamiento.

## Resultado Final

**Funcionamiento**

Da clic en la imagen para ver el video de funcionamiento

[![Funcionamiento](https://github.com/diego-toriz116/Ecosmart_tu_huerto_inteligente/raw/main/imagenes/Funcionamiento-Ecosmart.jpg)](https://youtu.be/6BYqDhQFSaY)


**Dashboard**
  ![node-red-Ecosmart](https://github.com/diego-toriz116/Ecosmart_tu_huerto_inteligente/raw/main/imagenes/Dashboard-Ecosmart.png)


## Créditos

Este proyecto fue realizado en el marco del curso IoT Essentials Developer impartido por [Codigo IoT ](https://www.codigoiot.com/) y organizado por la [Asociación Mexicana del Internet de las Cosas](https://www.asociacioniot.org/).

Emiliano Sánchez Bautista

Alan Cerezo Albarran

Diego Leonardo Toriz Flores

Jesús Manuel García Cirilo





