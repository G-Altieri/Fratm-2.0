#include <Stepper.h> //Stepper Motor
#include <Servo.h> //Servo
#include "MyTimer.h" //Timer for Function

MyTimer t1 = MyTimer();

//Servo Utils
Servo Servox;
int servoPin = 7;
int ServoxVelocity = 30;
int ServoxPos = 90;
int ServoxConst = 15;
int ServoxLimitS = 140;
int ServoxLimitD = 40;

//Stepper Motor Utils
const int stepsPerRevolution = 2048;
int motorPin1 = 51;
int motorPin2 = 50;
int motorPin3 = 49;
int motorPin4 = 48;
Stepper myStepper(stepsPerRevolution, motorPin4, motorPin2, motorPin3, motorPin1);
int stepX = 256;
int valStepper = 0;
int SteperLimit = 1024;



//Var Utils
boolean power = false;

//Led Utils 
const int pinLedAccensione = 10;


void setup() {
  //Setup Porta Seriale
  Serial.begin(9600);

  //Button Input
  //pinMode(button_1, INPUT);
  //pinMode(pinLedAccensione, OUTPUT);

  //Setup Servo
  Servox.attach (servoPin);
  Servox.write(ServoxPos);
  Serial.println("Servo position 90");

  //Stepper Motor
  myStepper.setSpeed(15);


  //Output Pin
  pinMode(pinLedAccensione, OUTPUT);


  //Timer set
  // t1.set(5000);

  Serial.println("Arduino is ready, power Off");

}//setup

void loop() {


  char x;
  if (Serial.available() > 0) {
    x = Serial.read();
    Serial.println(x);

    //Power On/Off
    if (x == '1') {
      if (power) {
        reset();
        power = false;
        digitalWrite(pinLedAccensione,LOW);
        Serial.print("Power Off");
      } else {
         ServoxPos = 120;
         moveTo(ServoxPos, ServoxVelocity);
         power = true;
         digitalWrite(pinLedAccensione,HIGH);
         Serial.print("Power On");
      }

    }

    //Status on
    if (power) {

      switch (x) {
        /*Stepper Control*/
        case 'a':
          if (valStepper < SteperLimit) {
            myStepper.step(stepX);
            valStepper = valStepper + stepX;
            Serial.print("Round positive = ");
            Serial.println(valStepper);
          }
          break;
        case 'd':
          if (valStepper > -SteperLimit) {
            myStepper.step(-stepX);
            valStepper = valStepper - stepX;
            Serial.print("Round negative = ");
            Serial.println(valStepper);
          }
          break;

        /*Servo Control*/
        case 'w':
          if ((ServoxPos + ServoxConst) <= ServoxLimitS) {
            ServoxPos = ServoxPos + ServoxConst;
            moveTo(ServoxPos, ServoxVelocity);
             Serial.print("Servo Position = ");
            Serial.println(ServoxPos);
          }
          break;
        case 's':
          if ((ServoxPos - ServoxConst) >= ServoxLimitD) {
            ServoxPos = ServoxPos - ServoxConst;
            moveTo(ServoxPos, ServoxVelocity);
            Serial.print("Servo Position = ");
            Serial.println(ServoxPos);
          }
          break;
        //Reset
        case 'r':
          reset();
          break;

      }



    }

  }
}//loop


void reset() {
  ServoxPos = 90;
  moveTo(ServoxPos, 30);

   valStepper = -valStepper;
   myStepper.step(valStepper);
   valStepper = 0;
  Serial.println("Reset");
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
   //Button var
  int val;
  int val1 = 0;
  int val2 = 0;
  int button_1 = 12; //Pulsante 1 sul pin 2
  int button_2 = 11; //Pulsante 2 sul pin 3

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


/*TImer
  //Timer
  if (t1.check()) {
    Serial.println("Timer 1");
    // t1.set(5000);
    moveTo(130, 10);
  }


*/
