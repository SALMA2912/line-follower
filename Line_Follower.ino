#include <LiquidCrystal.h>
  const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
// Motor R
int MR = 3;
int in1 = 2;
int in2 = 4;

// Motor L
int ML = 6;
int in3 = 7;
int in4 = 5;

// speed 0 -> 255
int Mspeed1=130; // forward
int Mspeed2=130; // drifting

// line follower sensors
#define LFS1 11   // right sensor
#define LFS2 12  // central sensor
#define LFS3 8  // left sensor

// ultrasonic
#define echoPin 10
#define trigPin 9
long duration; 
int distance;


void setup()
{
  pinMode(MR, OUTPUT);
  pinMode(ML, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LFS1, INPUT);
  pinMode(LFS2, INPUT);
  pinMode(LFS3, INPUT);  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void Us_init()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
}

void Mood1() // stay forward
{ 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, Mspeed1);
  analogWrite(ML, Mspeed1);
}
void loop()
{
  int s1 = digitalRead(LFS1);
  int s2 = digitalRead(LFS2);
  int s3 = digitalRead(LFS3); 
  Us_init();
  if ( distance < 2){
  analogWrite(MR, 0);
  analogWrite(ML, 0);
  delay(3000);
  }
  if (s1 == LOW && s2 == HIGH && s3 == LOW){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, Mspeed1);
  analogWrite(ML, Mspeed1);
  }
  else if( s1 == HIGH && s2 == LOW && s3 == LOW){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(MR, Mspeed2);
  analogWrite(ML, Mspeed2);
  }
  else if( s1 == LOW && s2 == LOW && s3 == HIGH){
   digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(MR, Mspeed2);
  analogWrite(ML, Mspeed2);   
  }
  else if( s1 == HIGH && s2== HIGH && s3 == HIGH){
   analogWrite(MR, 0);
   analogWrite(ML, 0);
   delay(10000);
   Mood1();
  }
  else if( s1 == HIGH && s2 == LOW && s3 == HIGH){
   analogWrite(MR, 0);
   analogWrite(ML, 0);
   delay(5000);
  }
}
