#define ledPin 10
#define puntotiempo 200
#define rayatiempo 600 

//Codigo morse para letras A-Z
String abecedario[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", 
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", 
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."         
};

// Función para convertir una letra en código Morse
void letratomorse(char c) {
  
  //Pausa larga entre cada palabra
  if (c == ' ') {
    delay(1600);
    return;
  }
  
   c = toupper(c); // Pasamos a mayuscula toda la informacion obtenida.

  // Validamos que sea una letra válida
  if (c < 'A' || c > 'Z') return; 

  int indice = c - 'A'; // Restamos la primera letra para asi obtener el indice, es decir que la A valga 0

  // Obtenemos que letra es
  String letra = abecedario[indice];
  
  for (int i=0; i<letra.length(); i++) {
    if (letra[i] == '.') {
      digitalWrite(ledPin, HIGH);
      delay(puntotiempo);  
    } 
    else if (letra[i] == '-') {
      digitalWrite(ledPin, HIGH);
      delay(rayatiempo); 
    }
    digitalWrite(ledPin, LOW);
    delay(300);  // Pausa entre cada elemento ( es decir . o - ) 
  }
  delay(800);  // Pausa entre cada letra
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available() > 0) {
    String mensaje = Serial.readString();  
    for (int i = 0; i < mensaje.length(); i++) {
      letratomorse(mensaje[i]); 
    }
  }
}
