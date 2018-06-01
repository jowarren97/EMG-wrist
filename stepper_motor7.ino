#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::FULL4WIRE,12,11,10,9,true); //flexion
AccelStepper stepper2(AccelStepper::FULL4WIRE,7,6,5,4,true); //rotation
//4pin stepper, pin1, pin2, pin3, pin4, enableOutput()

MultiStepper steppers;

long pos;
long positions[2] = {0, 0}; 
//position[0]: stepper1: flexion
//position[1]: stepper2: rotation

int encoderpin1 = 2;
int encoderpin2 = 3;
int counter;
boolean change = false;

#define USBSERIAL 1 //0 for manual window, 1 for matlab communication

void setup()
{
  Serial.begin(9600);

  //ENCODER SET UP
  counter = 0;
  /* Setup encoder pins as inputs */
  pinMode(encoderpin1, INPUT); // Pin 2
  pinMode(encoderpin2, INPUT); // Pin 4 
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, decoder, FALLING);

  //USB SET UP
  if (USBSERIAL == 1)
  {
    Serial.println('a');
    char a = 'b';
    while (a != 'a')
    {
      a = Serial.read();
    }
  }

  //MOTOR SET UP
  stepper1.setMaxSpeed(1000); //150rpm
  stepper2.setMaxSpeed(500); //150rpm

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  positions[0] = 0; //in steps
  positions[1] = 0; //in steps
  steppers.moveTo(positions); 
  //Calls AccelStepper::setSpeed() and AccelStepper::moveTo().
  //Calculates speed (and therefore time-interval-per-step, T) such 
  //that both steppers reach final positions as same time.
}

void loop()
{ 
  if (Serial.available())
  {
    //Read in Serial Data
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
  if (change == true)
  { 
  //Serial.println(counter);
  }
  change = false;
}

void decoder()
  //very short interrupt routine 
  //Remember that the routine is only called when pin1
  //changes state, so it's the value of pin2 that we're
  //interrested in here
  {
  if (digitalRead(encoderpin1) == digitalRead(encoderpin2))
  {
    counter++;
    change = true;
  }
  else
  {
    change = true;
    counter--;
  }
}

