////const int ProxSensor=3;
////#define SAIDA 13
////void setup() {
////  Serial.begin (9600);
////  pinMode(SAIDA, OUTPUT);   // setting the pin modes, the "13" stands for the internal Arduino uno internal LED
////  pinMode(ProxSensor,INPUT); // then we have the out pin from the module
////}
////
////void loop() {
////  if(digitalRead(ProxSensor)== HIGH)      //Check the sensor output if it's high
////             {
////               digitalWrite(SAIDA, LOW);   // Turn the LED on (Yes by writing LOW)
////               Serial.println("LOW");
////             }
////  else
////            {
////              digitalWrite(13, HIGH);    // Turn the LED OFF if there's no signal on the ProxSenso
////              Serial.println("HIGH");
////             }
////  delay(100);
////
////}
//
//
//
////void setup() {
////  Serial.begin (9600);
////  pinMode(trigPin, OUTPUT);
////  pinMode(echoPin, INPUT);
////}
////
////
////void loop() {
////  digitalWrite(trigPin, LOW);
////  delayMicroseconds(5);
////  digitalWrite(trigPin, HIGH);
////  delayMicroseconds(10);
////  digitalWrite(trigPin, LOW);
////
////  pinMode(echoPin, INPUT);
////  duration = pulseIn(echoPin, HIGH);
////
////  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
////  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
////
////  Serial.print(inches);
////  Serial.print("in, ");
////  Serial.print(cm);
////  Serial.print("cm");
////  Serial.println();
////
////  delay(250);
////}
//
//
//
//

//  for(pos = 0; pos < 90; pos++)
//  {
//    s.write(pos);
//  delay(15);
//  }
//delay(1000);
//  for(pos = 90; pos >= 0; pos--)
//  {
//    s.write(pos);
//    delay(15);
//  }
//Gira o Motor A no sentido horario
//


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
//Ultrasonic ultrassom(pino_trigger, pino_echo);
long distancia;
const int ProxSensor = 8;
//Servo s; // Variável Servo
//int pos; // Posição Servo


void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  Serial.begin(9600);
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
        Serial.println(cm);
        if (cm == 0.00) {
          continue;
        }
        if (cm < 10) {
          desligaMotor();
          break;
        }
      }
    }
  }


  delay(2000);
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
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  return true;
}

void desligaMotor() {
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
