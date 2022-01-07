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
int stepX = 200;

Stepper myStepper(stepsPerRevolution, motorPin4, motorPin2, motorPin3, motorPin1);

int button_1 = 12; //Pulsante 1 sul pin 2
int button_2 = 11; //Pulsante 2 sul pin 3


//Var Utils
int val;
int val1 = 0;
int val2 = 0;

//Stepper Var
int valStepper = 0;
int SteperLimit = 1800;


//Var Servox
int ServoxVelocity = 30;
int ServoxPos = 90;
int ServoxConst = 15;
int ServoxLimitS = 140;
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
  // t1.set(5000);

  Serial.println("Arduino is ready");
}//setup

void loop() {

  //Timer
  if (t1.check()) {
    Serial.println("Timer 1");
    // t1.set(5000);
    moveTo(130, 10);
  }

  char x;




  if (Serial.available() > 0) {
    x = Serial.read();
    Serial.println(x);

    switch (x) {
      /*   case '1':
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
           Serial.println(ServoxVelocity);4r4rrwddddwdwdwdwrwwwwwwwawdw
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
      */
      /*Stepper Control*/
      case 'a':
        Serial.print("Giro in senso Orario");
        if (valStepper < SteperLimit) {
          myStepper.step(stepX);
          valStepper = valStepper + stepX;
          Serial.println(valStepper);
        }


        break;
      case 'd':
        Serial.print("Giro in senso Antiorario");
        if (valStepper > -SteperLimit) {
          myStepper.step(-stepX);
          valStepper = valStepper - stepX;
          Serial.println(valStepper);
        }

        break;

      /*Servo Control*/
      case 'w':
        if ((ServoxPos + ServoxConst) <= ServoxLimitS) {
          ServoxPos = ServoxPos + ServoxConst;
          moveTo(ServoxPos, ServoxVelocity);
          Serial.print("New Position Servo ");
          Serial.println(ServoxPos);
        }
        break;
      case 's':
        if ((ServoxPos - ServoxConst) >= ServoxLimitD) {
          ServoxPos = ServoxPos - ServoxConst;
          moveTo(ServoxPos, ServoxVelocity);
          Serial.print("New Position Servo ");
          Serial.println(ServoxPos);
        }
        break;
      /*
            case 'z':
              Serial.print("Step incrementati");
              Serial.println(stepX);
              stepX = stepX + 50;
              break;
            case 'x':
              Serial.print("Step decrementati");
              Serial.println(stepX);
              stepX = stepX - 50;
              break;
      */
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
  ServoxPos = 90;
  Serial.print("Reset Servox ");
  Serial.println(ServoxPos);
  moveTo(ServoxPos, 30);
}

/*Method for move Servo*/
int pos1 = 90;
int mapSpeed;
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


/*
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


    //Servo with potenziometro
    val = analogRead(potentiometerPin);
    val = map(val, 0, 1023, 45, 127);
    Serial.println(val);
    Servox.write(val);
    delay(300);
*/
