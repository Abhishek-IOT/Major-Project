#include<Servo.h>
#include <Wire.h>


float temp;
int tempPin = 0;
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10];
Servo Myservo;
int pos;
void PhSensor(){
  for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);//Get 10 sample value from the sensor 
  delay(100);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];        //sort the analog from small to large
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;//convert the analog into millivolt
 float phValue = -5.70 * pHVol;//convert the millivolt into pH value
 Serial.print("pH Value = ");
 Serial.println(phValue);
 
 delay(10);

}
void Servo(){
  for(pos=0;pos<=180;pos++){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
  for(pos=180;pos>=0;pos--){
Myservo.write(pos);
delay(15);
}
  delay(1000);
  
}
void setup() {
  Myservo.attach(3);
   Serial.begin(9600);
}

void loop() {
   temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp = temp * 0.48828125;
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*C");
   Serial.println();
   delay(1000); // update sensor reading each one second
    PhSensor();
  Servo();
}
