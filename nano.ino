#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>
SoftwareSerial n(D6,D5);
float vol = 0;
float speed1;
float time1;
String str;
char ch;
void setup() {
 Serial.begin(9600);
 n.begin(9600);
 
 WiFi.begin("SRIDHARREDDY-PC_Network","o08w-g83k-2zys");
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin("sample-77337.firebaseio.com","6Edeo64CdLSytwUOM5t9nHmzaQxhhkL3dHIJiimO");
  
}

void loop() {
  ch = n.read();

if(n.available() > 0)
{
  if(ch == 'v')
  {
  str = n.readStringUntil('\n');
    vol = str.toFloat();
    Serial.print("Vol = ");
    Serial.println(vol);
    Firebase.setFloat("number",vol);
  }
  else if(ch == 's')
  {
    str = n.readStringUntil('\n');
    speed1 = str.toInt();
    Serial.print("Speed = ");
    Serial.println(speed1);
    Firebase.setFloat("Speed",speed1);
  }
  else if(ch == 't')
  {
    str = n.readStringUntil('\n');
    time1 = str.toFloat();
    Serial.print("Time = ");
    Serial.println(time1);
    Firebase.setFloat("Time",time1);
  }
}

 
}
