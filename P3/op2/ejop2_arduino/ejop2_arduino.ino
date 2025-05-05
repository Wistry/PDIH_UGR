const int trigPin = 9;     
const int echoPin = 8;     
const int buzzerPin = 10;  

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);    // Inicia comunicación serial para monitorización
}

void loop() {
    long duration;
    int distance;

    // Disparo del pulso ultrasónico
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Leer duracion y calcular distancia
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;  

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Control del buzzer según la distancia
    if (distance < 10) {
        tone(buzzerPin, 1000);  // Sonido agudo 
        delay(100);
        noTone(buzzerPin);
    } else if (distance < 20) {
        tone(buzzerPin, 500);   // Sonido medio 
        delay(200);
        noTone(buzzerPin);
    } else if (distance < 30) {
        tone(buzzerPin, 250);   // Sonido grave 
        delay(300);
        noTone(buzzerPin);
    } else {
        noTone(buzzerPin);      // Silencio si no hay objetos cerca 
    }

    delay(200);  // Pequeña pausa entre mediciones
}