/*
Designed for disc motor
*/
 
//#include &lt;Stepper.h&gt;

/******STEPPER MOTOR SET-UP******/
#include <Stepper.h>;
 
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

// change this to the number of steps on your motor
#define STEPS 200
#define STEPSIZE 0.9 //had to change to 0.9 for disc motor
 
Stepper motor(STEPS, in1Pin, in2Pin, in3Pin, in4Pin); 

/******VARIABLE INITIALISATION******/
float tempdata = 0;
float pos = 0;
float desiredPos = 0;
float actualPos = 0;
float deviation = 0;
int rotationDir;
 
void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  while (!Serial);
   
  Serial.begin(9600);
  motor.setSpeed(300); //set RPM
}


void loop()
{
  /******READ DEGREE DATA FROM SERIAL WINDOW******/
  if (Serial.available())
  {
     tempdata = Serial.parseInt();
     if(tempdata != 0)
     {
        desiredPos = tempdata; //read DEGREE input from serial monitor
     }
  }

  deviation = desiredPos - pos;
  rotationDir = (deviation>0) - (deviation<0); //should return 1 if +ve or -1 if -ve
  //does this need to be calculated inside loop? only if new data could be received mid loop, otherwise no
  
  /******MOVE TO DESIRED POSITION******/
  while (abs(deviation) > STEPSIZE/2) //ie while deviation is not minimal
  {
    //check if new desiredPos has been received?
    
    motor.step(rotationDir); //do (+/-) 1 step
    pos += rotationDir*STEPSIZE; //add (+/-) 1 step in DEGREES to pos
    deviation = desiredPos - pos;
  }

  /*****FEEDBACK CALC******/
  //read actual position
  //error = actualPos - pos  

  Serial.print(pos);
  Serial.print("\n");
}



