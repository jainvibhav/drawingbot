#include <math.h>
#include<Servo.h>
#include<String.h>

int l1=45,l2=45,l3=40,distance,l12,l22,l32,serialdata,inbyte;
int x=0,y=0,a=4,x1,x2,y1,y2,b=8,c=11.5,d=80,e=9.5,h=74,dy,dx,r;
int del_l1,del_l2,del_l3;
int delta_step_count1,delta_step_count2,delta_step_count3;
void setup()
{
  // put your setup code here, to run once:
 
  Serial.begin(9600);
  pinMode(6,OUTPUT); // Enable
  pinMode(5,OUTPUT); // Step
  pinMode(4,OUTPUT); // Dir
  digitalWrite(6,LOW); // Set enable low
  pinMode(9,OUTPUT); // Enable
  pinMode(8,OUTPUT);
  // Step
  pinMode(7,OUTPUT); // Dir
  digitalWrite(9,LOW); // 
  pinMode(12,OUTPUT); // Enable
  pinMode(11,OUTPUT); // Step
  pinMode(10,OUTPUT); // Dir
  digitalWrite(12,LOW); // 
 
}

void loop() 
{ 
  digitalWrite(2,LOW); //pen down
  digitalWrite(3,LOW); 
  

  digitalWrite(6,LOW); // Set Enable low
  digitalWrite(9,LOW); // Set Enable low
  digitalWrite(12,LOW); // Set Enable low
 
  
  x1=(getSerial()*80)/644;

  y1=(getSerial()*74)/489;
//take x and y from java
  x=x1;
  y=y1;
if(x==-1 && y==-1)
  { 
  digitalWrite(2,LOW);//penup
  digitalWrite(3,HIGH);  
    adjustPosition();
    
  }
else

  {
  digitalWrite(2,HIGH); //pen down
  digitalWrite(3,LOW); 
  
  adjustPosition();
  
  
  
   }
}
  int getSerial()
  {
    serialdata=0;
    inbyte=Serial.read();
    while(inbyte!='\n' && inbyte!=' ')
    {
      if (inbyte>0)
      {
        serialdata=serialdata*10+inbyte-'0';
      }
       inbyte=Serial.read();
    }
    return serialdata;
  }
  void adjustPosition()
  {
    dx=abs(x2-x1);
    dy=abs(y2-y1);
    x2=x1;
    y2=y1;
    l12=l1;
    l22=l2;
    l32=l3;
    l1=sqrt(pow((x-b),2)+pow((y-a),2)+pow(c,2));
    l2=sqrt(pow((x+b-d),2)+pow((y-a),2)+pow(c,2));
    l3=sqrt(pow((x-0.5*d),2)+pow((y+e-h),2)+pow(c,2));
    del_l1=l12-l1;
    del_l2=l22-l2;
    del_l3=l32-l3;
    delta_step_count1=(del_l1/(r*1.8));
    delta_step_count2=(del_l2/(r*1.8));
    delta_step_count3=(del_l3/(r*1.8));

   while(delta_step_count1!=0 && delta_step_count2!=0 && delta_step_count3!=0)
  {
    if(delta_step_count1>0)
    {
        
          digitalWrite(4,HIGH); //direction high
           digitalWrite(5,HIGH); // Output high
           delay(10); // Wait
           digitalWrite(5,LOW); // Output low
           delay(100);
          delta_step_count1--;
      }
    else if(delta_step_count1<0)
    {
      
        digitalWrite(4,LOW); 
        digitalWrite(5,HIGH); // Output high
        delay(10); // Wait
        digitalWrite(5,LOW); // Output low
        delay(100);
        delta_step_count1++;
      
    }
    if(delta_step_count2>0)
    {
      
          digitalWrite(7,HIGH); 
          digitalWrite(8,HIGH); // Output high
          delay(10); // Wait
          digitalWrite(8,LOW); // Output low
          delay(100);
          delta_step_count2--;
    }
    else if(delta_step_count2<0)
    {  
        digitalWrite(7,LOW); 
        digitalWrite(8,HIGH); // Output high
        delay(10); // Wait
        digitalWrite(8,LOW); // Output low
        delay(100);  
        delta_step_count2++;
    }
    if(delta_step_count3>0)
    {
      
        digitalWrite(10,HIGH); 
        digitalWrite(11,HIGH); // Output high
        delay(10); // Wait
        digitalWrite(11,LOW); // Output low
        delay(100);
        delta_step_count3--;
    }
    else if(delta_step_count3<0)
    {
      
        digitalWrite(10,LOW); 
        digitalWrite(11,HIGH); // Output high
        delay(10); // Wait
        digitalWrite(11,LOW); // Output low
        delay(100);
        delta_step_count3++;
    }
  delay(500);
   }
  }
