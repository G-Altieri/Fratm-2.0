#include <Stepper.h> //Stepper Motor
#include <Servo.h> //Servo
#include "MyTimer.h" //Timer for Function

MyTimer t1 = MyTimer();

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

int button_1 = 12; //Pulsante 1 sul pin 2
int button_2 = 11; //Pulsante 2 sul pin 3


//Var Utils
int val;
int val1 = 0;
int val2 = 0;
int valStepper = 250;


//Var Servox
int ServoxVelocity = 15;
int ServoxPos = 90;
int ServoxConst = 5;
int ServoxLimitS = 130;
int ServoxLimitD = 40;

void setup() {
  //Setup Porta Seriale
  Serial.begin(9600);

  //Button Input
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);

  //Setup Servo
  Servox.attach (servoPin);
  Servox.write(ServoxPos);
  Serial.println("Servo position 90");

  //Stepper Motor
  myStepper.setSpeed(15);




  //Timer set
  t1.set(5000);

  Serial.println("Arduino is ready");
}//setup

void loop() {

  //Timer
  /*if (t1.check()) {
     Serial.println("Timer 1");
     t1.set(5000);
     moveTo(100,10);
    }*/

  val1 = digitalRead(button_1);
  if (val1 == HIGH) {
    Serial.println("Senso Orario");
    // myStepper.step(stepsPerRevolution);
    // delay(500);
    // myStepper.step(valStepper);
    moveTo(100, 10);
    delay(500);
  }

  val2 = digitalRead(button_2);  //Quando premo il pulsante 2 gira a destra
  if (val2 == HIGH) {
    Serial.println("Senso AntiOrario");
    // myStepper.step(-stepsPerRevolution);
    // delay(500);
    // myStepper.step(-valStepper);
    moveTo(60, 20);
    delay(500);
  }

  /*
    //Servo with potenziometro
    val = analogRead(potentiometerPin);
    val = map(val, 0, 1023, 45, 127);
    Serial.println(val);
    Servox.write(val);
    delay(300);
  */

  char x;




  if (Serial.available() > 0) {
    x = Serial.read();
    Serial.println(x);

    switch (x) {
      case '1':

        Serial.print("ServoxVelocity ");
        if (ServoxVelocity < 30) {
          ServoxVelocity = ServoxVelocity + 1;
        }
        Serial.println(ServoxVelocity);
        break;
      case '2':
        if (ServoxVelocity > 2) {
          ServoxVelocity = ServoxVelocity - 1;
        }
        Serial.print("ServoxVelocity ");
        Serial.println(ServoxVelocity);

        break;
      case '3':
        ServoxConst = ServoxConst + 1;
        Serial.print("ServoxConst ");
        Serial.println(ServoxConst);
        break;
      case '4':
        ServoxConst = ServoxConst - 1;
        Serial.print("ServoxConst ");
        Serial.println(ServoxConst);
        break;
      case 'a':
        moveTo(120, 10);
        break;
      case 'w':
        moveTo(ServoxPos + ServoxConst, ServoxVelocity);
        Serial.print("New Position Servo ");
        Serial.println(ServoxPos + ServoxConst);
        if (ServoxPos >= ServoxLimitD) {
          ServoxPos = ServoxPos - ServoxConst;
        }
        break;
      case 'd':
        moveTo(120, 10);
        break;
      case 's':
        moveTo(ServoxPos + ServoxConst, ServoxVelocity);
        Serial.print("New Position Servo ");
        Serial.println(ServoxPos + ServoxConst);
        if (ServoxPos <= ServoxLimitS) {
          ServoxPos = ServoxPos + ServoxConst;
        }
        break;
      case 'z':
        myStepper.step(1000);
        break;
      case 'x':
        myStepper.step(-1024);
        break;
      case 'c':
        myStepper.step(1000);
        break;
      case 'v':
        myStepper.step(1002);
        break;
      case 'g':
        prendiChiavi();
        break;
      case 'r':
        reset();
        break;

    }

  }
}//loop

void prendiChiavi() {
  myStepper.step(1000);
  delay(1000);
  myStepper.step(-1000);
  delay(600);
  moveTo(45, 20);
  delay(3000);
  moveTo(90, 17);
  delay(500);
  myStepper.step(1200);
  delay(100);
  moveTo(135, 20);
}

void reset() {
  Serial.print("Reset Servox ");
  Serial.println(90);
  moveTo(90, 30);
}


int pos1 = 90;
int mapSpeed ;
int pos;
void moveTo(int position, int speed) {

  mapSpeed = map(speed, 0, 30, 30, 0);
  if (position > pos) {
    for (pos = pos1; pos <= position; pos += 1) {
      Servox.write(pos);
      pos1 = pos;
      delay(mapSpeed);
    }
  } else {
    for (pos = pos1; pos >= position; pos -= 1) {
      Servox.write(pos);
      pos1 = pos;
      delay(mapSpeed);
    }
  }


}
