#include <Stepper.h> //Stepper Motor
#include <Servo.h> //Servo

//Servo Utils
Servo Servox;
int servoPin = 7;
int potentiometerPin = 1;

//Stepper Motor Utils
const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
int motorPin1 = 2;
int motorPin2 = 3;
int motorPin3 = 4;
int motorPin4 = 5;
int motor_Speed = 2;
Stepper myStepper(stepsPerRevolution, 5, 3, 4, 2);

int button_1 = 12; //Pulsante 1 sul pin 2
int button_2 = 11; //Pulsante 2 sul pin 3


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
  Servox.write(90);
  // set the speed at 20 rpm:
  myStepper.setSpeed(15);
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
   // myStepper.step(valStepper);
   moveTo(100,10);
    delay(500);
  }

  val2 = digitalRead(button_2);  //Quando premo il pulsante 2 gira a destra
  if (val2 == HIGH) {
    Serial.println("Senso AntiOrario");
    // myStepper.step(-stepsPerRevolution);
    // delay(500);
   // myStepper.step(-valStepper);
 moveTo(60,20);
 delay(500);
  }
  /*
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
        Servox.write(50);
        break;
      case '2':
        Servox.write(70);
        break;
      case '3':
        Servox.write(60);
        break;
         case '4':
        Servox.write(110);
        break;
         case 'a':
        myStepper.step(200);
        break;
         case 's':
         myStepper.step(-200);
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
      default:

        break;
    }

  }
}//loop

void prendiChiavi(){
   myStepper.step(1000);
  delay(1000);
   myStepper.step(-1000);
    delay(600);
    moveTo(45,20);
    delay(3000);
    moveTo(90,17);
    delay(500);
     myStepper.step(1200);
     delay(100);
     moveTo(135,20);
  }


int pos1 =45;
int mapSpeed ;
int pos;
void moveTo(int position, int speed){

mapSpeed =map(speed,0,30,30,0);
if(position > pos){
  for(pos = pos1;pos<=position;pos+=1){
    Servox.write(pos);
    pos1=pos;
    delay(mapSpeed);
    }
  }else{
  for(pos = pos1;pos>=position;pos-=1){
    Servox.write(pos);
    pos1=pos;
    delay(mapSpeed);
    }
  }

  
  }
