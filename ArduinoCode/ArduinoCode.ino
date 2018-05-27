

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
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 5, 15000);
// sonicsensor min dist in mm
int SSMinDist = 1000 ;



void setup()
  {
    Serial.begin(9600);
    //InitTimersSafe();

    myservo.attach(ServoPin);
    
    //SetPinFrequencySafe(Motor1In1, 450);
   // SetPinFrequencySafe(Motor1In2, 35);

    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    
    
    pinMode(11,OUTPUT);
   
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
   Serial.print("IsWall");
    return true;
    
    
  }
  else
  {
    //Serial.print("NOWall");
    return false;
  } 
}

void TurnLeft(int speed)
  {
    //add pwm
    analogWrite(5,speed);
    analogWrite(10,speed);
    // adjust delay
    
    delay (600);
    Serial.println("Turning Left!");
    analogWrite(5,0);
    analogWrite(10,0);
    
    //turn left 
  }
void TurnRight(int speed)
  {
    analogWrite(6,speed);
    analogWrite(9,speed);
    // adjust delay
    
    delay (400);
    Serial.println("Turning Left!");

    analogWrite(6,0);
    analogWrite(9,0);
     //turn right
  } 
 void GoForward(int speed)
	{
    //int speed2 = 225;
		analogWrite(5,200);
		analogWrite(9,speed);
	}
void Stop()
	{
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(9,1);
    digitalWrite(10,1);
    delay(100);
		digitalWrite(5,0);
		digitalWrite(6,0);
		digitalWrite(9,0);
		digitalWrite(10,0);
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

void AvoidObs()
  {
    if (wallLeft == 0)
            {
              TurnLeft(100);
              //forward
            }
          else if(wallRight == 0)
            {
              TurnRight(100);
              //forward
            } 
  }
void SetWallFlags()
{
  //Serial.println(CheckServoDir(ServoPos));
  int wallDir = CheckServoDir(ServoPos);
  //GoForward(255);
  if(IsWall(SSMinDist) == true)
    {
      
      //if wall found set wall flags
      
	  
      if( wallDir == 1)
        {
          wallLeft = true;
		      currentWall = 1;
        }
      else if (wallDir == 2)
        {
		    	wallForward = true;
				  Stop();
		    	//stop
			    //if wall left == 0, turn left / if wallright == 0, turn right
				  
						
						TurnLeft(255);
						delay(500);
						
         /*
				else if(wallLeft == true and wallRight == false)
					{
						
						TurnRight(255);
						delay(1000);
						
					}
         */
          wallForward = false;
          
			//continue loop
        }
      if (wallDir == 3)
        {
          wallRight = true;
		  currentWall = 3;
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

        delay(200);
        
        
        //Serial.println(ServoPos);
        
        //delay(250);
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
        delay(200);
        
       // delay(250);  
        
    }  
    
    
}


  

void loop() 
{
	/*
    GoForward(255);
    delay(1000);
    TurnRight(255);
    delay(1000);
    GoForward(255);
    delay(1000);
    Stop();
    
    while(true);
	*/
    
   ServoSweep();
   GoForward(255);
   
   
   //myservo.write(0);
   Serial.println(hcsr04.distanceInMillimeters());
   
 
}
