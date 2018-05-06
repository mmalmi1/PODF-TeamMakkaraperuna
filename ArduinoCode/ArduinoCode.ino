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


//int UltSensorTrig = 2;
int ButtonIn = 13;


//init servo object
Servo myservo;
int ServoPos = 0

// current wall ( 1 = left , 2 = forward, 3 = right)
currentWall = 0;

// set wall flags
bool wallLeft = false;
bool wallForward = false;
bool wallRight = false;



#define TRIG_PIN 2
#define ECHO_PIN 3
#define INF_FORK1 A4
#define INF_FORK2 A5

//init ultsonic object with min 20 mm , max 1500mm
HCSR04 UltSonicSensor(TRIG_PIN, ECHO_PIN, 20, 1500);
// sonicsensor min dist in mm
int SSMinDist = 1000



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

void SetWallFlags()
{
  if(isWall(SSMinDist) == true)
    {
      int wallDir = CheckServodir(ServoPos);
      //if wall found set wall flags
      if( wallDir == 1)
        {
          wallLeft = true;
        }
      else if (wallDir == 2)
        {
          wallForward = true;  
        }
      else if (wallDir == 3)
        {
          wallRight == true;  
        }  
    }
  else if (isWall(SSMinDist) == false)
    {
      if( wallDir == 1)
        {
          wallLeft = false;
        }
      else if (wallDir == 2)
        {
          wallForward = false;  
        }
      else if (wallDir == 3)
        {
        wallRight == false;  
        }     
    }
    

void ServoSweep()
{
    for(ServoPos=0; ServoPos<=180; ServoPos =+ 90)
    {
        myservo.write(ServoPos);
        SetWallFlags();
        delay(500);
    } 
    
    for(ServoPos=180; ServoPos >= 0; ServoPos =- 90)
    {
        myservo.write(ServoPos);
        SetWallFlags
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
    
 if(AnglePos >= 120)
    {
      return 3;
    }  
}

bool IsWall(int minDist)
{
  //Checks if wall 
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
