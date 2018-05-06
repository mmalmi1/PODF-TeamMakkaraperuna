//outputs
int ServoPin = 11;
int Motor1In1 = 5;
int Motor1In2 = 6;
int Motor2In1 = 9;
int Motor2In1 = 10;
int InfSensorEcho = 3;
//inputs
int InfSensorTrig = 2;
int ButtonIn = 13;
int InfFork1 =  5;
int InfFork1 =  6;



 



void setup()
	{
		for(int i=0;i<=6;i++)
		{
			pinMode(i, OUTPUT);
			
		}
		for(int i=0;i<=4;i++)
		{
			pinMode(i, INPUT);
			
		}
		
	}
	
	
	