#include <Stepper.h> //Stepper Motor
#include <Servo.h> //Servo

//Servo Utils
Servo Servox;
int servoPin = 7;
int potentiometerPin = 1;

//Stepper Motor Utils
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
int motorPin1 = 51;
int motorPin2 = 50;
int motorPin3 = 49;
int motorPin4 = 48;
int motor_Speed = 2;
Stepper myStepper(stepsPerRevolution, motorPin4, motorPin2, motorPin3, motorPin1);

int button_1 = 12; 
int button_2 = 11; 


//Var Utils
int val;
int val1 = 0;
int val2 = 0;
int valStepper = 250;


void setup() {
  //Button Input
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);

  //Setup Servo
  Servox.attach (servoPin);

  // set the speed at 20 rpm:
  myStepper.setSpeed(10);
 /* pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);*/

  //Setup Porta Seriale
  Serial.begin(9600);


}//setup

void loop() {


  val1 = digitalRead(button_1);
  if (val1 == HIGH) {
    Serial.println("Senso Orario");
     // myStepper.step(stepsPerRevolution);
     // delay(500);
     myStepper.step(valStepper);
  }

  val2 = digitalRead(button_2);  //Quando premo il pulsante 2 gira a destra
  if (val2 == HIGH) {
      Serial.println("Senso AntiOrario");
     // myStepper.step(-stepsPerRevolution);
     // delay(500);
       myStepper.step(-valStepper);
   
  }

  val = analogRead(potentiometerPin);
  // Serial.println(val);
  val = map(val, 0, 1023, 40, 140);
  //Serial.println(val);
  Servox.write(val);
  delay(100);

}//loop
