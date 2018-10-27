#include <SoftwareSerial.h>

SoftwareSerial minhaSerial(6, 7);

// variaveis de auxilio
int ledAceso = 0;
String comando = " ";

// variaveis para os pinos dos motores
const int MotorDLOW1 = 1;  // (pwm) pino 9 conectado ao pino A-IA do Módulo
const int MotorDLOW2 = 2;  // (pwm) pino 5 conectado ao pino A-IB do Módulo
const int MotorELOW1 = 3; // (pwm) pino 1LOW conectado ao pino B-IA do Módulo
const int MotorELOW2 = 4;  // (pwm) pino 6 conectado ao pino B-IB do Módulo

// definindo as variaveis para os leds
const int ledAfirmacao = 8;
const int ledNegacao = 9;
const int ledNormal = 10;
const int ledLanterna = 11;

void pararMotores(){
  digitalWrite(MotorDLOW1, LOW);
  digitalWrite(MotorDLOW2, LOW);
  digitalWrite(MotorELOW1, LOW);
  digitalWrite(MotorELOW2, LOW);
}

void apagarLeds(){
  digitalWrite(ledNormal, LOW);
  digitalWrite(ledAfirmacao, LOW);
  digitalWrite(ledNegacao, LOW);
  digitalWrite(ledLanterna, LOW);
}

void setup(){
  Serial.begin(115200);
  Serial.println("Recebendo comando: ");
  minhaSerial.begin(9600);

  // definindo a saida das variaveis para os leds
  pinMode(ledAfirmacao, OUTPUT);
  pinMode(ledNegacao, OUTPUT);
  pinMode(ledNormal, OUTPUT);
  pinMode(ledLanterna, OUTPUT);

  // definindo saida de variaveis para os motores
  pinMode(MotorDLOW1, OUTPUT);
  pinMode(MotorDLOW2, OUTPUT);
  pinMode(MotorELOW1, OUTPUT);
  pinMode(MotorELOW2, OUTPUT);

  pararMotores();
}

void frente(){
  pararMotores();
  digitalWrite(MotorDLOW1, HIGH);
  digitalWrite(MotorDLOW2, LOW);
  digitalWrite(MotorELOW1, HIGH);
  digitalWrite(MotorELOW2, LOW);
}

void tras(){
  pararMotores();
  digitalWrite(MotorDLOW1, LOW);
  digitalWrite(MotorDLOW2, HIGH);
  digitalWrite(MotorELOW1, LOW);
  digitalWrite(MotorELOW2, HIGH);
}

void direita(){
  pararMotores();
  digitalWrite(MotorDLOW1, LOW);
  digitalWrite(MotorDLOW2, HIGH);
}

void esquerda(){
  pararMotores();
  digitalWrite(MotorELOW1, LOW);
  digitalWrite(MotorELOW2, HIGH);
}

void mudarLed(){
  apagarLeds();
  if (ledAceso == 0) {
    digitalWrite(ledNormal, HIGH);
    ledAceso = 1;  
  } else if(ledAceso == 1) {
    digitalWrite(ledAfirmacao, HIGH);
    ledAceso = 2;
  } else if (ledAceso == 2) {
    digitalWrite(ledNegacao, HIGH);
    ledAceso = 3;
  }else if (ledAceso == 3) {
    digitalWrite(ledLanterna, HIGH);
    ledAceso = 4;
  } else {
    digitalWrite(ledNormal, HIGH);
    ledAceso = 1;
  }
}

void balancar(){
  pararMotores();
  for(int i = 0;i < 3; i++){
    digitalWrite(MotorDLOW1, HIGH);
    digitalWrite(MotorDLOW2, LOW);
    digitalWrite(MotorELOW1, LOW);
    digitalWrite(MotorELOW2, HIGH);
    delay(1000);
    digitalWrite(MotorDLOW1, LOW);
    digitalWrite(MotorDLOW2, HIGH);
    digitalWrite(MotorELOW1, HIGH);
    digitalWrite(MotorELOW2, LOW);
    delay(1000);
  }
  pararMotores();
}

void dancar(){
  // codigo aqui
}

void loop(){
  if(minhaSerial.available()){
    Serial.println("entrou no if");
    while(minhaSerial.available()){
      char cmd = ' ';
      comando = (char) minhaSerial.read();
      cmd = (char) minhaSerial.read();
      Serial.println(comando);
      switch(cmd){
        // comandos do controle remoto
        case '0':
          pararMotores();
        break;
        case '1':
          // frente
          frente();
        break;
        case '2':
          // tras
          tras();
        break;
        case '3':
          // esquerda
          esquerda();
        break;
        case '4':
          // direita
          direita();
        break;
        case '5':
          // leds
          mudarLed();
        break;
        // comandos de acoes
        case 'a':
          // andar para frente
          pararMotores();
          frente();
          delay(2000);
          pararMotores();
        break;
        case 'b':
          // andar para tras
          pararMotores();
          tras();
          delay(2000);
          pararMotores();
        break;
        case 'c':
          // andar para esquerda
          pararMotores();
          esquerda();
          delay(1000);
          pararMotores();
          frente();
          delay(2000);
          pararMotores();
        break;
        case 'd':
          // andar para direita
          pararMotores();
          direita();
          delay(1000);
          pararMotores();
          frente();
          delay(2000);
          pararMotores();
        break;
        case 'e':
          // negar
          apagarLeds();
          digitalWrite(ledNegacao, HIGH);
        break;
        case 'f':
          apagarLeds();
          digitalWrite(ledAfirmacao, HIGH);
          // afirmar
        break;
        case 'g':
          // balancar
          balancar();
        break;
        case 'h':
          // virar para esquerda
          pararMotores();
          esquerda();
          delay(500);
          pararMotores();
        break;
        case 'i':
          // virar para direita
          pararMotores();
          direita();
          delay(500);
          pararMotores();
        break;
        case 'j':
          // dançar
          dancar();
        break;
      }
    }
  }
}
