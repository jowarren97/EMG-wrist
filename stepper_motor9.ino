#include <AccelStepper.h>
#include <MultiStepper.h>

AccelStepper stepper1(AccelStepper::FULL4WIRE,12,11,10,9,true); //flexion
AccelStepper stepper2(AccelStepper::FULL4WIRE,7,6,5,4,true); //rotation
//4pin stepper, pin1, pin2, pin3, pin4, enableOutput()

MultiStepper steppers;

long pos;
long prevpos;
long positions[2] = {0, 0}; 
//position[0]: stepper1: flexion
//position[1]: stepper2: rotation

int encoderpin1 = 2;
int encoderpin2 = 3;
int counter;
float encoderPos = 0;
boolean change = false;

char recvChar;
boolean newData = false;
boolean sendData = false;
boolean sendR=false;

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

#define USBSERIAL 0 //0 for manual window, 1 for matlab communication

void setup() {
  Serial.begin(9600);

  //ENCODER SET UP
  counter = 1;
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
  stepper1.setMaxSpeed(500); //150rpm
  stepper2.setMaxSpeed(750); //150rpm

  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  positions[0] = 0; //in steps
  positions[1] = 0; //in steps
  steppers.moveTo(positions); 
  //Calls AccelStepper::setSpeed() and AccelStepper::moveTo().
  //Calculates speed (and therefore time-interval-per-step, T) such 
  //that both steppers reach final positions as same time.
}

void loop() {
  recvWithEndMarker();
  if(showNewData())
  {
  parseData();
  //printNewData();
  steppers.moveTo(positions);
  }
  steppers.run();
  sendEncoderData();

  //if (change == true)
  //{ 
  //  Serial.println(counter);
  //}
  //change = false;
}

void recvWithEndMarker() 
//places serial input (up until \n) into a string buffer
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
 
  //if (Serial.available() > 0) {
  while (Serial.available() > 0 && newData == false) 
  //exit when entire data package read (or serial comm fails)
  {
    rc = Serial.read();
  
    if (rc != endMarker) 
    {
      if (rc == 'R')
      {
        sendData = true;
        sendR=true;
      }
      else
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) 
        {
          ndx = numChars - 1;
        }
      }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true; //exit as entire data packet read
    }  //}
  }
}

int showNewData() 
//shows newly created string which should contain same data as serial input
{
  if (newData == true) 
  {
    newData = false;
    return 1;
  }
  else
  {
    return 0;
  }
}

void parseData() 
// split the data into its parts
{ 
  if(sendR == false)
  {
  char* strtokIndx; // this is used by strtok() as an index

  char *tempstr = strdup(receivedChars);
      
  strtokIndx = strtok(tempstr,",");      // get the first part - the string
  positions[0] = atof(strtokIndx);
  positions[0] = (positions[0]*400)/360;
    
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left 
  positions[1] = atof(strtokIndx);     // convert this part to an integer
  positions[1] = (positions[1]*400)/360;


  free(tempstr);
  }
  sendR=false;
}


void printNewData()
//prints parsed positionsc
{
  //Serial.println(tempStr);
  Serial.print("Position 1: ");
  Serial.println(positions[0]);
  Serial.print("Position 2: ");
  Serial.println(positions[1]);
}

void sendEncoderData()
{
  if (sendData == true)
  {
    encoderPos = ((float)counter/256)*360;
    Serial.println(encoderPos);
    sendData = false;
  }
}

void decoder()
  //very short interrupt routine 
  //Remember that the routine is only called when pin1
  //changes state, so it's the value of pin2 that we're
  //interrested in here
  {
  if (digitalRead(encoderpin1) == digitalRead(encoderpin2))
  {
    counter--;
    change = true;
  }
  else
  {
    change = true;
    counter++;
  }
}
