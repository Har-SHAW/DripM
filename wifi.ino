#include <Servo.h>
#include<Metro.h>
#include<SoftwareSerial.h>
Servo servo;
SoftwareSerial node(5,6);
Metro voltime = Metro(4000);
#define totvol 80
int inputPin = 2;
int inputPin1 = 4;
int dripper = 7;
int dval = 0;
int count = 0;
int con = 1;
float vol = 0;
float amount = 0;
float time1;
int prev = 0;
void setup() {
pinMode(dripper,INPUT);
pinMode(inputPin1,INPUT);
pinMode(inputPin,INPUT);
node.begin(9600);
Serial.begin(9600);
servo.attach(3);
servo.write(180);
}
void pass(char ch,float b)
{
  String str = String(b);
  int len = str.length() + 1;
  char a[5];
  str.toCharArray(a,len);
  node.write(ch);
  node.write(a);
  node.write('\n'); 
}
void loop() 
{

 if (digitalRead(inputPin) == HIGH)
   { 
      servo.write(180);               
            
   } 
   else 
   { 
      servo.write(90);
   }
 
   /*if (digitalRead(inputPin1) == HIGH)
   {
      digitalWrite(ledPin, HIGH); // turn LED OFF   
   } 
   else 
   { 
      digitalWrite(ledPin, LOW); // turn LED ON
    
}*/
   dval = digitalRead(dripper);
   if (dval == LOW&&con == 1)
   { 
    count++;
    vol = ((float)count)/20;
    Serial.print(count);
    Serial.print(" - ");
    Serial.print(vol);
    Serial.println("ml");
    if((int)vol == vol)
    {
      pass('v',vol);
    }
    con = 0;
    }
   if (dval == HIGH&&con == 0)
   {
    con = 1;
   } 
   if(voltime.check() == 1)
   {
    amount = (((float)(count - prev))/20)*15;
    time1 = ((float)totvol-vol)/amount;
    Serial.print(amount);
    Serial.print("ml/min      time left to empty bottle :");
    Serial.print(time1);
    Serial.println("min");
    pass('s',amount);
    prev = count;
    pass('t',time1);
   }
} 
