#include <hcsr04.h>
#include <Servo.h>
#include <PWM.h>
#include <Dcmotor.h>


//outputs
int ServoPin = 11;
int Motor1In1 = 5;
int Motor1In2 = 6;
int Motor2In1 = 9;
int Motor2In1 = 10;
//int UltSensorEcho = 3;

//inputs
//int UltSensorTrig = 2;
int ButtonIn = 13;

//Analog
int InfFork1 =  5;
int InfFork1 =  4;

Servo myservo;
int ServoPos = 0

#define TRIG_PIN 2
#define ECHO_PIN 3

HCSR04 UltSonicSensor(TRIG_PIN, ECHO_PIN, 20, 1500);



void setup()
  {
    Serial.begin(9600);
    myservo.attach(ServoPin);
    
    pinMode(11,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(3,OUTPUT);

    pinMode(2, INPUT);
    pinMode(13, INPUT);
    pinMode(A5, INPUT);
    pinMode(A4, INPUT);    
  }

void ServoSweep()
{
    for(ServoPos=0; ServoPos<=180; ServoPos =+ 90)
    {
        myservo.write(ServoPos);
        if(isWall == true)
        {
         int wallDir = CheckServodir(ServoPos);
         if(wallDir == 2)
         {
           //AVOID WALL
         }
        }
        delay(500); 
    } 
    
    for(ServoPos=180; ServoPos >= 0; ServoPos =- 90)
    {
        myservo.write(ServoPos);
        if(isWall == true)
        {
         int wallDir = CheckServodir(ServoPos);
         if(wallDir == 2)
         {
          //AVOID WALL 
         } 
        }
        delay(500);  
    }  
    
}

int CheckServoDir(int AnglePos)
{
  //returns 1 for left, 2 for mid, 3 for right(or not)
  if(AnglePos <= 60)
    {
      return 1;
    }
 if(AnglePos > 60 && AnglePos < 120)
    {
      return 2;
    }
 if(AnglePos >= 120)
    {
      return 3;
    }  
}

bool IsWall(int minDist)
{
  if(UltSonicSensor.distanceInMillimeters()<= minDist)
  {
    return true;
    Serial.print("IsWall");
    
  }
  else
  {
    return false;
  } 
}



void TurnFromWall(int WallDir)
{
  if(WallDir == 1)
    {
       //turn to dir 3
    }
  else if(WallDir == 3)
    {
      //turn to dir 1
    }
}
  

void loop() 
{
  

}
