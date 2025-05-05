void setup() {
    pinMode(11, OUTPUT); // LED rojo
    pinMode(12, OUTPUT); // LED amarillo
    pinMode(13, OUTPUT); // LED verde
}

void loop() {
    // Enciende el LED rojo 
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(1500); 

    // Enciende el LED amarillo 
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    delay(1500);

    // Enciende el LED verde 
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    delay(1500);
}
