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

#define SERVO 9 // Porta Digital 6 PWM
//Ultrasonic ultrassom(pino_trigger, pino_echo);
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
    double cm = retornaDistancia();
    bool motorLigado = ligaMotor();
    if (motorLigado) {
      while (detectaChao()) {
        cm = retornaDistancia();
        if (cm == 0.00) {
          continue;
        }
        if (cm < 15) {
          desligaMotor();
          s.write(0);
          double dist1 = retornaDistancia();
          s.write(90);
          double dist2 = retornaDistancia();
          
          s.write(179);
          double dist3 = retornaDistancia();
          if(dist1 >= dist2){
            viraDireita();
            break;
            }
          break;
        }
      }
    }
  }
  delay(1000);
}


bool viraEsquerda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  return true;
}

bool viraDireita() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  return true;
}

double retornaDistancia()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 29.1;
}

bool ligaMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  return true;
}


void desligaMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);

}

bool detectaChao() {
  if (digitalRead(ProxSensor) == HIGH)    //Check the sensor output if it's high
  {
    digitalWrite(SAIDA, LOW);   // NAO DETECTANDO COISA É LOW
    Serial.println("LOW");
    return false;
  }
  else
  {
    digitalWrite(13, HIGH);    // DETECTANDO COISA EH HIGH
    Serial.println("HIGH");
    return true;
  }
}
