#include <Stepper.h>

int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

Stepper motor(200, in1Pin, in2Pin, in3Pin, in4Pin); 
int val = 0;


void setup() 
{
  Serial.begin(9600);
  Serial.println('a');
  char a = 'b';
  while (a != 'a')
  {
    a = Serial.read();
  }
  motor.setSpeed(200); //set RPM
}

void loop() 
{
  while (Serial.available() == 0)
  {
  }
  
  if (Serial.available() > 0)
  {
   val = Serial.read();
   {
    motor.step(val);
   } 
  }
}
