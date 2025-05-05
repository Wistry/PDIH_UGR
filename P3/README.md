# PDIH_UGR

## Práctica 3. Uso de bibliotecas de programación de interfaces de usuario en modo texto

## Autores:
- William Quinn
- Laura Riesco

> **Nota:**  
> Dentro de cada carpeta hay otra subcarpeta con el codigo para ser probado en el IDE de Arduino

## Funciones básicas

### 1. `Programa parapadeo de 3 LED`
Implementar el programa de parpadeo de LED, ampliándolo para que encienda
y apague alternativamente tres LEDs (uno rojo, otro amarillo y otro verde),
conectados a las salidas digitales 11, 12 y 13 del Arduino, a un intervalo de 1.5
segundos

#### Materiales usados

- Arduino UNO  
  ![Arduino UNO](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.33.png)

- LED rojo, LED amarillo, LED verde  
  ![LEDs](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.48.png)

- Resistencias 220Ω  
  ![Resistencia](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.55.png)

#### Circuito final

- Esquema de conexión de los LEDs  
  ![Conexión LEDs](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.08.46.png)

- Foto del montaje final  
  ![Montaje final](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.14.15.png)

#### Código 

- El código enciende y apaga los tres LEDs de forma alterna cada 1.5 segundos.
- Captura del código:
  ![Captura del código](ej1/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.05.59.png)

#### Video demostrativo

- [Descargar video demostrativo](<ej1/Grabación de pantalla 2025-04-30 a las 19.09.03.mov>)

---

### 2. `Programa parpadeo de 3 LED Ampliado`
Partir del programa de parpadeo de LEDs anterior y ampliarlo con las
modificaciones necesarias para que se encienda el LED rojo solo cuando se
pulse un interruptor conectado a la entrada digital 7, y en ese momento se
apaguen los LEDs amarillo y verde.

#### Materiales usados

- Arduino UNO  
  ![Arduino UNO](ej2/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.33.png)

- LED rojo, LED amarillo, LED verde  
  ![LEDs](ej2/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.48.png)

- Resistencias 220Ω  
  ![Resistencia](ej2/Captura%20de%20pantalla%202025-04-30%20a%20las%2019.07.55.png)


#### Circuito final

- Esquema de conexión completo  
  ![Esquema completo](<ej2/Captura de pantalla 2025-05-05 165702.png>)

#### Código explicado brevemente

- El código permite encender el LED rojo solo cuando se pulsa el interruptor, apagando los otros LEDs.
- Captura del código:  
  ![Captura del código](<ej2/Captura de pantalla 2025-05-05 165728.png>)

#### Video demostrativo

- [Descargar video demostrativo](<ej2/Ej2.mp4>)

---

## Funciones avanzadas

### 1. `Secuencia de LEDs`
Secuencia de LEDs, encendiendo y apagando 4 LEDs secuencialmente, de
forma similar a las lucecitas de "El coche fantástico": https://bit.ly/3Lu7YNz

#### Materiales usados

- Arduino UNO  
  ![Arduino UNO](<op1/Captura de pantalla 2025-04-30 a las 19.27.39.png>)

- 4 LEDs (rojo, amarillo, verde, azul, etc.)  
  ![LEDs](<op1/Captura de pantalla 2025-04-30 a las 19.27.27.png>)

- 4 Resistencias 220Ω  
  ![Resistencias](<op1/Captura de pantalla 2025-04-30 a las 19.27.32.png>)


#### Circuito final

- Esquema de conexión completo  
  ![Esquema Completo](<op1/Captura de pantalla 2025-04-30 a las 19.30.38.png>)

#### Código explicado brevemente

- El código enciende y apaga los 4 LEDs secuencialmente, simulando el efecto de "El coche fantástico".
- Captura del código:  
  ![Codigo](<op1/Captura de pantalla 2025-04-30 a las 19.29.22.png>)

#### Video demostrativo

- [Descargar video demostrativo](<op1/Grabación de pantalla 2025-04-30 a las 19.30.33.mov>)

---

### 2. `Detector de la distancia a un objeto`
Detector de la distancia a un objeto (usar el buzzer para hacer sonar un pitido
en función de la distancia detectada por el sensor de ultrasonidos).

#### Materiales usados

- Arduino UNO  
  ![Arduino UNO](<op2/Captura de pantalla 2025-04-30 a las 19.42.42.png>)

- Buzzer  
  ![Buzzer](<op2/Captura de pantalla 2025-04-30 a las 19.42.57.png>)

- Sensor
  ![Sensor](<op2/Captura de pantalla 2025-04-30 a las 19.43.50.png>)


#### Circuito final

- Esquema de conexión sensor 
![Conexion1](<op2/Captura de pantalla 2025-04-30 a las 19.44.32.png>)

- Esquema de conexión buzzer
![Conexion2](<op2/Captura de pantalla 2025-04-30 a las 19.44.55.png>)


#### Código explicado brevemente

- El código hace sonar el buzzer en función de la distancia detectada por el sensor de ultrasonidos.
- Captura del código 1:  
![Codigo1](<op2/Captura de pantalla 2025-04-30 a las 19.45.31.png>)

- Captura del código 2:  
![Codigo2](<op2/Captura de pantalla 2025-04-30 a las 19.45.38.png>)


#### Video demostrativo
- [Descargar video demostrativo](<op2/Grabación de pantalla 2025-04-30 a las 19.46.09.mov>)

---
