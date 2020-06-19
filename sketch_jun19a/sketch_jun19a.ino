#include <Servo.h>

Servo myservo;
Servo myservo1;

int a1=0,a2=180,i;

void setup() {
    myservo.attach(9);
    myservo1.attach(10); 
    myservo.write(20);
    myservo1.write(180); 
    Serial.begin(9600);
    Serial.println();
}
void loop() {
   for (i=-20; i<=180 ; i=i+20) {
    a1=i;
    myservo.write(a1);
    delay(500);
  }
}

