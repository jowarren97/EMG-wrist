#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::FULL4WIRE,12,11,10,9,true); //flexion
AccelStepper stepper2(AccelStepper::FULL4WIRE,7,6,5,3,true); //rotation
//4pin stepper, pin1, pin2, pin3, pin4, enableOutput()

MultiStepper steppers;

long pos;
long positions[2] = {0, 0}; 
//position[0]: stepper1: flexion
//position[1]: stepper2: rotation

void setup()
{
  Serial.begin(9600);
  
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(500);

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  //positions[0] = 400; //in steps
  //positions[1] = 2000; //in steps
  steppers.moveTo(positions); 
  //Calls AccelStepper::setSpeed() and AccelStepper::moveTo().
  //Calculates speed (and therefore time-interval-per-step, T) such 
  //that both steppers reach final positions as same time.
}

void loop()
{ 
  if (Serial.available())
  {
    pos = Serial.parseInt();

    if ((pos != positions[0]) && (pos != 0))
    {
    positions[0] = pos;
    positions[1] = pos;
    steppers.moveTo(positions);
    }
  }
  steppers.run(); 
  //Performs 1 step per call (as long as T ms has elapsed since last 
  //call) until all positions reached.
  //Calls AccelStepper::runSpeed(), which performs 1 step every T ms.
  //NEEDS TO BE CALLED REPEATEDLY & REGULARLY
}

