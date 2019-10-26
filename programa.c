int trigPin = 3;    // Trigger
int echoPin = 2;    // Echo
long duration, cm, inches;

#include <Ultrasonic.h>
#include <Servo.h>
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define SAIDA 12
#define FRENTE 90
#define ESQUERDA 0
#define DIREITA 180

#define SERVO 9 // Porta Digital 6 PWM
Ultrasonic ultrasonic(trigPin, echoPin);
long distancia;
const int ProxSensor = 8;

Servo s; // Variável Servo
int pos; // Posição Servo


void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  Serial.begin(9600);
  s.attach(SERVO);
  s.write(179); // 0 direita 90 reto 180 esquerda
  pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(SAIDA, OUTPUT);
  pinMode(ProxSensor, INPUT);
  //  s.attach(SERVO);
  //  s.write(0); // Inicia motor posição zero
}

void loop()
{
  if (detectaChao()) {
    s.write(FRENTE);
    if (retornaDistancia() > 20.0) {
      andaReto();
    } else {
      desligaMotor();
      int direcao = retornaMaiorDistancia();
      s.write(FRENTE);
      switch (direcao) {
        case FRENTE:
          andaReto();
          break;
        case DIREITA:
          viraDireita();
          delay(500);
          andaReto();
          break;
        case ESQUERDA:
          viraEsquerda();
          delay(500);
          andaReto();
          break;
      }
    }
  } else {
    desligaMotor();
  }
}


void viraEsquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void viraDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void andaReto() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void darRe() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void paraMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

}

void desligaMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}

bool detectaChao() {
  if (digitalRead(ProxSensor) == HIGH)    //Check the sensor output if it's high
  {
    digitalWrite(SAIDA, LOW);   // NAO DETECTANDO COISA É LOW
    return false;
  }
  else
  {
    digitalWrite(13, HIGH);    // DETECTANDO COISA EH HIGH
    return true;
  }
}

double retornaDistancia()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 29.1;
}


int retornaMaiorDistancia() {
  delay(1000);
  s.write(0);
  delay(1000);
  double d1 = retornaDistancia();
  //  Serial.print("d1 ");
  //  Serial.print(d1);
  //  Serial.println();
  s.write(90);
  delay(1000);
  double d2 = retornaDistancia();
  //  Serial.print("d2 ");
  //  Serial.print(d2);
  //  Serial.println();
  s.write(180);
  delay(1000);
  double d3 = retornaDistancia();
  //  Serial.print("d3 ");
  //  Serial.print(d3);
  //  Serial.println();
  //  Serial.println("nao vai confundir");
  if ((d1 > d2) && (d1 > d3)) {

    return DIREITA;
  }
  else if ((d2 > d1) && (d2 > d3)) {

    return FRENTE;
  }
  else if ((d3 > d1) && (d3 > d2)) {

    return ESQUERDA;
  }

}
