

#include <hcsr04.h>
#include <Servo.h>
#include <PWM.h>
//#include <Dcmotor.h>


//outputs
int ServoPin = 11;
int Motor1In1 = 5;
int Motor1In2 = 6;
int Motor2In1 = 9;
int Motor2In2 = 10;
//int UltSensorEcho = 3;


//int UltSensorTrig = 2;
int ButtonIn = 13;


//init servo object
Servo myservo;
int ServoPos = 0;

// current wall ( 1 = left , 2 = forward, 3 = right)
int currentWall = 0;

// set wall flags
bool wallLeft = false;
bool wallForward = false;
bool wallRight = false;



#define TRIG_PIN 2
#define ECHO_PIN 3
#define INF_FORK1 A4
#define INF_FORK2 A5

//init ultsonic object with min 20 mm , max 1500mm
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 5, 5000);
// sonicsensor min dist in mm
int SSMinDist = 1000;



void setup()
  {
    Serial.begin(9600);

    myservo.attach(ServoPin);
    
    pinMode(11,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
 
    pinMode(13, INPUT);
    pinMode(A5, INPUT);
    pinMode(A4, INPUT);    
  }
bool IsWall(int minDist)
{
  //Checks if wall 
  int dist = hcsr04.distanceInMillimeters();
 // Serial.println(dist);
  if(dist <= minDist && dist > 1 )
  {
   // Serial.print("IsWall");
    return true;
    
    
  }
  else
  {
    //Serial.print("NOWall");
    return false;
  } 
}


int CheckServoDir(int AnglePos)
{
  //returns 1 for left, 2 for mid, 3 for right(or not)
  if(AnglePos <= 60)
    {
      return 1;
    }
  else if(AnglePos > 60 && AnglePos < 120)
    {
      return 2;
    }
    
  else if(AnglePos >= 120)
    {
      return 3;
    }  
}


void SetWallFlags()
{
  Serial.println(CheckServoDir(ServoPos));
  int wallDir = CheckServoDir(ServoPos);
  if(IsWall(SSMinDist) == true)
    {
      
      //if wall found set wall flags
      
      if( wallDir == 1)
        {
          wallLeft = true;
        }
      else if (wallDir == 2)
        {
          wallForward = true;  
        }
      if (wallDir == 3)
        {
          wallRight = true;  
        }  
      
    }
  else if (IsWall(SSMinDist) == false)
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
          wallRight = false;  
        }     
    }
  }
    

void ServoSweep()
{
    for(ServoPos = 90; ServoPos<=180; ServoPos = ServoPos + 90)
    {
        myservo.write(ServoPos);
        delay(200);
        SetWallFlags();
        Serial.print(" ");
        Serial.print(wallLeft);
        Serial.print(wallForward);
        Serial.print(wallRight);
        Serial.println("");
        
        //Serial.println(ServoPos);
        
        delay(500);
    } 
    
    for(ServoPos = 90; ServoPos >= 0; ServoPos = ServoPos - 90)
    {
        myservo.write(ServoPos);
        delay(200);
        SetWallFlags();
        Serial.print(" ");
        Serial.print(wallLeft);
        Serial.print(wallForward);
        Serial.print(wallRight);
        Serial.println("");
        
        delay(500);  
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
  //Serial.println(hcsr04.distanceInMillimeters());
 ServoSweep();
  
  
  //IsWall(1000);
}
