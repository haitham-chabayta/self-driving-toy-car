#include <LiquidCrystal.h> 

LiquidCrystal lcd(12,11, 5,4,3,2); 
 enum{Idle, MotorF, TurnLeft, TurnRight,Stop};
 int DCMotor1F = A1, DCMotor2F = A3, DCMotor1B = A0, DCMotor2B = A2;
 int trig = 8;
 int echo1 = A4, echo2 = A5;
 int PB = 6;
 int current;
 int distance1, distance2;
 long StartTime;
 long CurrentTime;
 int ElapsedTime;
 int RedLED = 10, GreenLED = 9;
 int StopsCount;

void setup() {
   
   lcd.begin(16,2); 
   pinMode(RedLED,OUTPUT);
   pinMode(GreenLED,OUTPUT);
   pinMode(DCMotor1F, OUTPUT);
   pinMode(DCMotor2F, OUTPUT);
   pinMode(DCMotor1B, OUTPUT);
   pinMode(DCMotor2B, OUTPUT);
   pinMode(trig, OUTPUT);
   pinMode(echo1,INPUT);
   pinMode(echo2,INPUT);
   pinMode(PB,INPUT_PULLUP);
   StopsCount = 0;
   current = Idle;
   
 }

void loop() {


   switch(current){

    case Idle:
     
     lcd.setCursor(0,0 ); 
     lcd.print("    Stand By"); 
     
     digitalWrite(RedLED,HIGH);
     digitalWrite(GreenLED,LOW);
     
     digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);  
     digitalWrite(DCMotor1B, LOW);
     digitalWrite(DCMotor2B, LOW);
        
     if(digitalRead(PB)== 0 ){
     StartTime = millis(); 
     current = MotorF;
     }
     
     break;

    case MotorF:

    lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("  Clear ahead!"); 
     
     digitalWrite(RedLED,LOW);
     digitalWrite(GreenLED,HIGH);
     
     digitalWrite(DCMotor1F, HIGH);
     digitalWrite(DCMotor2F, HIGH);
     digitalWrite(DCMotor1B, LOW);
     digitalWrite(DCMotor2B, LOW);

    distance1 = calculateDistance();
    distance2 = calculateDistance2();


     if (distance1 <= 30 && distance1 !=0)
       current = TurnRight;
       
     if (distance2 <= 30 && distance2 != 0)
       current = TurnLeft;                                                                                         

    
     if(digitalRead(PB)== 0 ){
     current = Stop;
     
     }

    break;   

    case TurnLeft: 
     
     StopsCount++; 
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("  Caution!!!"); 

    digitalWrite(RedLED,HIGH);
     digitalWrite(GreenLED,LOW);
     
     digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);
     digitalWrite(DCMotor1B, LOW);
     digitalWrite(DCMotor2B, LOW);

    delay(1000);

    lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("   Turning Left!!"); 

    digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);
     digitalWrite(DCMotor1B, HIGH);
     digitalWrite(DCMotor2B, HIGH);
     
     delay(350);
     
     digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, HIGH);
     digitalWrite(DCMotor1B, HIGH);
     digitalWrite(DCMotor2B, LOW);

    delay(150);
     
     if(digitalRead(PB)== 0 ){
       current = Stop;
     }
     current = MotorF;

    break;

  case TurnRight: 


     StopsCount++; 
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("  Caution!!!"); 

    digitalWrite(RedLED,HIGH);
     digitalWrite(GreenLED,LOW);

    digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);
     digitalWrite(DCMotor1B, LOW);
     digitalWrite(DCMotor2B, LOW);

    delay(1000);

    lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("   Turning Right!!"); 

    digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);
     digitalWrite(DCMotor1B, HIGH);
     digitalWrite(DCMotor2B, HIGH);

    delay(350);
     
     digitalWrite(DCMotor1F,HIGH);
     digitalWrite(DCMotor2F,LOW);
     digitalWrite(DCMotor1B,LOW);
     digitalWrite(DCMotor2B,HIGH);

    delay(150);

    if(digitalRead(PB)== 0 ){
     current = Stop;
     
     }

    current = MotorF;

    break;

    case Stop:

    
     CurrentTime = millis();
     
     digitalWrite(RedLED,HIGH);
     digitalWrite(GreenLED,LOW);

    digitalWrite(DCMotor1F, LOW);
     digitalWrite(DCMotor2F, LOW);
     digitalWrite(DCMotor1B, LOW);
     digitalWrite(DCMotor2B, LOW);

     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("   Stopping!!");
     
     delay(2000);

    CalculateTimeAndDistance();

    break;
  
   }
   }

void CalculateTimeAndDistance(){

    int TimeMicro = (CurrentTime - StartTime);
     ElapsedTime = TimeMicro/1000;
     int TimeStationary = StopsCount;
     int TimeMoving = ElapsedTime-TimeStationary;
     int distanceTraveled = TimeMoving*0.8; //Speed of the car is 0.8 m/s
     
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Elapsed Time: ");
     lcd.print(ElapsedTime);
     lcd.print("s");
     lcd.setCursor(0,1); 
     lcd.print("Distance: ");
     lcd.print(distanceTraveled);
     lcd.print("m");
     
     delay(50000);

  
 }

float calculateDistance2() {
   
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);
 float duration = pulseIn(echo2, HIGH);
 float distanceA= duration*0.034/2;

return distanceA;

 }

float calculateDistance() {
   
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);
 float duration = pulseIn(echo1, HIGH);
 float distanceB= duration*0.034/2;

return distanceB;

 }
