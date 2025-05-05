int leds[] = {8, 9, 10, 11}; // Pines conectados a los LEDs
int numLeds = 4;

void setup() {
    for (int i = 0; i < numLeds; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    // Encender de izquierda a derecha
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
    }

    // Encender de derecha a izquierda
    for (int i = numLeds - 2; i >= 0; i--) { // Evita repetir extremos
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
    }
}