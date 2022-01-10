#include <Stepper.h> //Stepper Motor
#include <Servo.h> //Servo
#include "MyTimer.h" //Timer for Function
#include "pitches.h"

//Timer
MyTimer t1 = MyTimer();

//Servo Utils
Servo Servox;
Servo Servox2;
Servo Servoy;
Servo Servoy2;
Servo Servo1;
Servo Servo2;
//Pin Servo
int ServoPinX = 7;
int ServoPinX2 = 6;
int ServoPinY = 41;
int ServoPinY2 = 39;
int ServoPin1 = 29;
int ServoPin2 = 43;

//Servo X
int ServoxPos = 90;
int Servox2Pos = 90;
int ServoxVelocity = 5;
int ServoxConst = 35;
int ServoxLimitS = 150;
int ServoxLimitD = 40;
int ServoxVelocityStatus = false;

//Servo Y
int ServoyPos = 0;
int Servoy2Pos = 0;
int ServoyVelocity = 15;
int ServoyConst = 15;
int ServoyLimitS = 0;
int ServoyLimitD = 180;
int ServoyVelocityStatus = true;

//Servo 1

//Servo 2


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



//Power and Status Uti
boolean power = false;

//Buzzer Utils
int pinBuzzer = 4;
boolean songRun = false;
int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5,
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
int durations[] = {
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8
};
int songLength = sizeof(melody) / sizeof(melody[0]);

//Led Utils
const int pinLedAccensione = 10;

//Save movement Utils
int posArm1[5];
int posBase[5];
int movementCont = 0;

void setup() {
  //Setup Porta Seriale
  Serial.begin(9600);

  //Setup Servo
  Servox.attach(ServoPinX);
  Servox2.attach(ServoPinX2);
  Servoy.attach(ServoPinY);
  Servoy2.attach(ServoPinY2);
 // moveTo(ServoxPos, ServoxVelocity, Servox, ServoxVelocityStatus,90);
 // moveTo(Servox2Pos, ServoxVelocity, Servox2, ServoxVelocityStatus,90);

/*Servox.write(90);
Servox2.write(90);*/
delay(500);
//int a = 180;
//int b = 0;
/*for(int i;i<90;i=i+1){
  a = a-1;
  b = b+1;
     Serial.print("a");
   Serial.println(a);
     Serial.print("b");
   Serial.println(b);
  Servoy.write(a);
Servoy2.write(b);
delay(30);
  }
/*
Servoy.write(90);
Servoy2.write(90);
delay(500);
Servoy.write(0);
Servoy2.write(180);*/
/*
Servox.write(90);
Servox2.write(90);
/*delay(500);
 * 
 */Servoy.write(0);
Servoy2.write(180);
delay(500);
Servox.write(90);
Servox2.write(90);

int a = 90;
int b = 90;
/*
for(int i;i<130;i=i+1){
  a = a+1;
  b = b-1;
  Servox.write(a);
Servox2.write(b);
delay(20);
  }
  */
  
 /* for(int i=0;i<30;i=i+1){
  a = a+1;
  b = b-1;
  Servoy.write(a);
Servoy2.write(b);
delay(20);
  }/*
  delay(1500);
Servoy.write(90);
Servoy2.write(90);
delay(500);*/

  //Stepper Motor
  myStepper.setSpeed(15);

  //Output Pin
  pinMode(pinLedAccensione, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);


  //Timer set
  // t1.set(5000);

  Serial.println("Arduino is ready, power Off");

}//setup

void loop() {


  char x;
  if (Serial.available() > 0 ) {
    if (!songRun) {
      x = Serial.read();
      Serial.println(x);
    }



    //Power On/Off
    if (x == '1') {
      if (power) {
        reset();
        power = false;
        digitalWrite(pinLedAccensione, LOW);
        tone(pinBuzzer, 500, 100);
        Serial.print("Power Off");
      } else {
        // ServoxPos = 120;
        //  moveTo(ServoxPos, ServoxVelocity, Servox);
        power = true;
        digitalWrite(pinLedAccensione, HIGH);
        tone(pinBuzzer, 1500  , 100);
        Serial.print("Power On");
      }

    }

    //Status on
    if (power) {
      switch (x) {
        /*Stepper*/
        case 'n':
          stepperRight();
          break;
        case 'm':
          stepperLeft();
          break;

        /*Servo X e X2*/
        case 'w':
          moveUpServoX();
          break;
        case 's':
          moveDownServoX();
          break;

        /*Servo Y e Y2*/
        case 'a':
          moveUpServoY();
          break;
        case 'd':
          moveDownServoY();
          break;

        /*Save Movement*/
        case 'z':
          movementSavePosition();
          break;
        case 'x':
          movementStart();
          break;
        case 'c':
          movementRemoveLastPosition();
          break;
        case 'v':
          movementShow();
          break;
        /*Buzzer*/
        case 't':
          playSong();
          break;
        case 'y':
          playSirena();
          break;
        /*Reset*/
        case 'r':
          reset();
          break;

      }



    }

  }
}//loop


void reset() {
  /*
    ServoxPos = 95;
    moveTo(ServoxPos, 30, Servox);
    ServoyPos = 95;
    moveTo(ServoyPos, 30, Servoy);

    valStepper = -valStepper;
    myStepper.step(valStepper);
    valStepper = 0;
    Serial.println("Reset not work");*/
}

/*Method for move Servo*/
int pos1 = 90;
int mapSpeed;
int pos;
void moveTo(int position, int speed, Servo x, boolean type, int oldPos) {
  if (type) {
    x.write(position);
  } else {
    Serial.print("movimento lento");
    mapSpeed = map(speed, 0, 30, 30, 0);
    if (position > oldPos) {
          Serial.print("movimento 1");
      for (oldPos = pos1; oldPos <= position; oldPos += 1) {
        x.write(oldPos);
        pos1 = oldPos;
        delay(mapSpeed);
      }
    } else {
      for (oldPos = pos1; oldPos >= position; oldPos -= 1) {
        x.write(oldPos);
         Serial.print("movimento 2");
        pos1 = oldPos;
        delay(mapSpeed);
      }
    }
  }

}
int pos12 = 90;
void moveTo(int position, int speed, Servo x, boolean type, int oldPos, Servo x2) {
  if (type) {
    x.write(position);
  } else {
    Serial.print("movimento lento");
    mapSpeed = map(speed, 0, 30, 30, 0);
    if (position > oldPos) {
       Serial.print("movimento 1");
      for (oldPos = pos12; oldPos <= position; oldPos += 1) {
        x.write(oldPos);
        x2.write(oldPos);
        pos1 = oldPos;
        delay(mapSpeed);
      }
    } else {
      for (oldPos = pos12; oldPos >= position; oldPos -= 1) {
        x.write(oldPos);
         x2.write(oldPos);
        pos12 = oldPos;
        delay(mapSpeed);
      }
    }
  }

}
/*Method for Servo X*/
void moveUpServoX() {
  if ((ServoxPos + ServoxConst) <= ServoxLimitS) {
  int pos = ServoxPos;
     int pos2 = Servox2Pos;
    ServoxPos = ServoxPos + ServoxConst;
    Servox2Pos = Servox2Pos - ServoxConst;
    //moveTo(ServoxPos, ServoxVelocity, Servox, ServoxVelocityStatus,pos);
   // moveTo(Servox2Pos, ServoxVelocity, Servox2, ServoxVelocityStatus,pos2);
    Serial.print("Servo X Position = ");
    Serial.print(ServoxPos);
    Serial.print(" Servo X2 Position = ");
    Serial.println(Servox2Pos);
  }

  /* if ((ServoxPos + ServoxConst) <= ServoxLimitS) {
     ServoxPos = ServoxPos + ServoxConst;
     moveTo(ServoxPos, ServoxVelocity, Servox);
     Serial.print("Servo X Position = ");
     Serial.println(ServoxPos);
    }*/
}
void moveDownServoX() {
 /* if ((ServoxPos - ServoxConst) >= ServoxLimitD) {
    int pos = ServoxPos;
  
    ServoxPos = ServoxPos - ServoxConst;
    Servox2Pos = Servox2Pos + ServoxConst;
   // moveTo(ServoxPos, ServoxVelocity, Servox, ServoxVelocityStatus,pos);
   // moveTo(Servox2Pos, ServoxVelocity, Servox2, ServoxVelocityStatus,pos2);
   // moveTo2(ServoxPos, ServoxVelocity, Servox, ServoxVelocityStatus,pos, Servox2);
     Serial.print("movimento lento");
   // mapSpeed = map(10, 0, 30, 30, 0);
    if (140 > pos) {*/
       Serial.print("movimento 1");
       int c=90;
        int p=90;
      for (pos = 0; pos <= 270; pos += 1) {
        
        Servox.write(p+1);
        Servox2.write(c-1);
        pos12 = pos;
        delay(30);
      }
 /*   } else {
      for (oldPos = pos12; oldPos >= position; oldPos -= 1) {
        x.write(oldPos);
         x2.write(oldPos);
        pos12 = oldPos;
        delay(mapSpeed);
      }
    }*/
    Serial.print("Servo X Position = ");
    Serial.print(ServoxPos);
    Serial.print(" Servo X2 Position = ");
    Serial.println(Servox2Pos);
  }
  /* if ((ServoxPos + ServoxConst) <= ServoxLimitS) {
     ServoxPos = ServoxPos + ServoxConst;
     moveTo(ServoxPos, ServoxVelocity, Servox);
     Serial.print("Servo X Position = ");
     Serial.println(ServoxPos);
    }*/

/*Method for Servo Y*/
void moveUpServoY() {
  if ((ServoyPos + ServoyConst) <= ServoyLimitS) {
    ServoyPos = ServoyPos + ServoyConst;
    Servoy2Pos = Servoy2Pos - ServoyConst;
  //  moveTo(ServoyPos, ServoyVelocity, Servoy, ServoyVelocityStatus);
   // moveTo(Servoy2Pos, ServoyVelocity, Servoy2, ServoyVelocityStatus);
    Serial.print("Servo Y Position = ");
    Serial.print(ServoyPos);
    Serial.print(" Servo Y2 Position = ");
    Serial.println(Servoy2Pos);
  }
}
void moveDownServoY() {
  if ((ServoyPos - ServoyConst) >= ServoyLimitD) {
    ServoyPos = ServoyPos - ServoyConst;
    Servoy2Pos = Servoy2Pos + ServoyConst;
   // moveTo(ServoyPos, ServoyVelocity, Servoy, ServoyVelocityStatus);
   // moveTo(Servoy2Pos, ServoyVelocity, Servoy2, ServoyVelocityStatus);
    Serial.print("Servo Y Position = ");
    Serial.print(ServoyPos);
    Serial.print(" Servo Y2 Position = ");
    Serial.println(Servoy2Pos);
  }
}

/*Method for Stepper Movement*/
void stepperRight() {
  if (valStepper < SteperLimit) {
    myStepper.step(stepX);
    valStepper = valStepper + stepX;
    Serial.print("Round positive = ");
    Serial.println(valStepper);
  }
}

void stepperLeft() {
  if (valStepper > -SteperLimit) {
    myStepper.step(-stepX);
    valStepper = valStepper - stepX;
    Serial.print("Round negative = ");
    Serial.println(valStepper);
  }
}

/*Method for Save Movement*/
void movementSavePosition() {
  if (movementCont < 5) {
    posArm1[movementCont] = ServoxPos;
    Serial.print("Save Servo Position = ");
    Serial.println(ServoxPos);
    posBase[movementCont] = valStepper;
    Serial.print("Save Stepper position = ");
    Serial.println(valStepper);

    movementCont = movementCont + 1;
    Serial.print("Movement Cont = ");
    Serial.println(movementCont);
  }
}

void movementStart() {
  if (movementCont > 0) {
    for (int i = 0; i < movementCont; i++) {
      Serial.print("Movement Cont = ");
      Serial.println(i);
      //Base

      valStepper = -valStepper;
      myStepper.step(valStepper);
      valStepper =   posBase[i];
      myStepper.step(valStepper);
      Serial.print("Stepper position = ");
      Serial.println(valStepper);
      // Arm 1

      ServoxPos = posArm1[i];
      moveTo(ServoxPos, ServoxVelocity, Servox, true, 90);
      Serial.print("Servo Position = ");
      Serial.println(ServoxPos);
      delay(2000);
    }
  }
}

void movementRemoveLastPosition() {
  if (movementCont > 0) {
    posBase[movementCont] = 0;
    posBase[movementCont] = 0;
    movementCont = movementCont - 1;
    Serial.println("Remove last Movement");
  }
}
void movementShow() {
  Serial.println("Movement Save Show:");
  if (movementCont > 0) {
    for (int i = 0; i < movementCont; i++) {
      Serial.print("Movement Cont = ");
      Serial.println(i + 1);
      Serial.print("Servo Position = ");
      Serial.println(posArm1[i]);
      Serial.print("Stepper position = ");
      Serial.println(posBase[i]);
    }
  }
}

/*Method for Buzzer*/
void playSong() {
  songRun = true;
  Serial.println(songRun);
  for (int thisNote = 0; thisNote < songLength; thisNote++) {
    // determine the duration of the notes that the computer understands
    // divide 1000 by the value, so the first note lasts for 1000/8 milliseconds
    int duration = 1000 / durations[thisNote];
    tone(pinBuzzer, melody[thisNote], duration);
    // pause between notes
    int pause = duration * 1.3;
    delay(pause);
    // stop the tone
    noTone(pinBuzzer);
  }
  songRun = false;
  Serial.println(songRun);
}
void playSirena() {
  songRun = true;
  Serial.println(songRun);
  for (int j = 0; j < 2; j++) {
    for (int i = 700; i < 800; i++) {
      tone(pinBuzzer, i);
      delay(15);
    }
    for (int i = 800; i > 700; i--) {
      tone(pinBuzzer, i);
      delay(15);
    }
    noTone(pinBuzzer);
  }
  songRun = false;
  Serial.println(songRun);
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
