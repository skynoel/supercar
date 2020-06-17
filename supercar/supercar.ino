#include <AFMotor.h>
#include <IBusBM.h>
#include <Servo.h>
AF_DCMotor motorleft1(1);
AF_DCMotor motorleft2(2);
AF_DCMotor motorright1(4);
AF_DCMotor motorright2(3);
Servo myservo;
Servo myservo1;
double V1,V2,V3,V4;//motor speed
double x,y,a;
int a1,a2;
IBusBM IBus;    // IBus object
void setup() {
    myservo.attach(9);
    myservo1.attach(10);  
    Serial.begin(9600);
    Serial.println();
    IBus.begin(Serial2);
    motorleft1.run(RELEASE);
    motorleft2.run(RELEASE);
    motorright1.run(RELEASE);
    motorright2.run(RELEASE);
}
void loop() {
  int data[10];
  for (int i=0; i<10 ; i++) {
    data[i]=IBus.readChannel(i);
    Serial.print(data[i]);
    Serial.print(" ");
  }
    //接收資料和解析 END
    //Data: LY,LX,RY,RX,L2
    if(data[4]==1000){
      y=(float)map(data[2],1000,2000,-1000,1000)/1000;
      x=(float)map(data[3],1000,2000,-1000,1000)/1000;
      a=(float)map(data[0],1000,2000,-1000,1000)/1000;
    }else{
      y=(float)map(data[2],1000,2000,1000,-1000)/1000;
      x=(float)map(data[3],1000,2000,1000,-1000)/1000;
      a=(float)map(data[0],1000,2000,-1000,1000)/1000;
    }
    a1=map(data[6],1000,2000,0,160);
    if(data[9]==2000)
    {
      a2=160;
    }
    else
    {
      a2=0;
    }
    myservo.write(a1);
    myservo1.write(a2);
    Serial.print(y);
    Serial.print(" ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(a);
    Serial.print(" ");
    Serial.print(a1);
    Serial.print(" ");
    Serial.print(a2);
    Serial.print(" ");                            
    Serial.println();
    V1 = y - x + a;
    V2 = y + x - a;
    V3 = y - x - a;
    V4 = y + x + a;   
    motorR1speedcontrol(V1);
    motorR2speedcontrol(V4);
    motorL1speedcontrol(V2);
    motorL2speedcontrol(V3);
}
void motorL1speedcontrol(double s)
{
  if(s>0){
    motorleft1.run(FORWARD);
    motorleft1.setSpeed(s*250);
  }
    if(s==0){
    motorleft1.run(RELEASE);
  }
    if(s<0){
    motorleft1.run(BACKWARD);
    motorleft1.setSpeed(-s*250);
  }
}
void motorL2speedcontrol(double s)
{
  if(s>0){
    motorleft2.run(FORWARD);
    motorleft2.setSpeed(s*250);
  }
    if(s==0){
    motorleft2.run(RELEASE);
  }
    if(s<0){
    motorleft2.run(BACKWARD);
    motorleft2.setSpeed(-s*250);
  }
}
void motorR1speedcontrol(double s)
{
  if(s>0){
    motorright1.run(FORWARD);
    motorright1.setSpeed(s*250);
  }
    if(s==0){
    motorright1.run(RELEASE);
  }
    if(s<0){
    motorright1.run(BACKWARD);
    motorright1.setSpeed(-s*250);
  }
}
void motorR2speedcontrol(double s)
{
  if(s>0){
    motorright2.run(FORWARD);
    motorright2.setSpeed(s*250);
  }
    if(s==0){
    motorright2.run(RELEASE);
  }
    if(s<0){
    motorright2.run(BACKWARD);
    motorright2.setSpeed(-s*250);
  }
}
