// Pines de los LEDs
const int ledRojo = 11;
const int ledAmarillo = 12;
const int ledVerde = 13;
// Pin del interruptor
const int interruptor = 7;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(interruptor, INPUT_PULLUP); // Usa resistencia pull-up interna
}

void loop() {
  // Leer el estado del interruptor (LOW cuando se presiona)
  if (digitalRead(interruptor) == LOW) {
    // Modo interruptor activado: solo LED rojo encendido
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
    delay(1500); // Mantiene el estado mientras se presiona
  } else {
    // Modo normal: secuencia de parpadeo
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, LOW);
    delay(1500);

    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledVerde, LOW);
    delay(1500);

    digitalWrite(ledRojo, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledVerde, HIGH);
    delay(1500);
  }
}