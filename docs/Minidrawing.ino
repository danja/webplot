#include <Servo.h>

Servo servo1;  
Servo servo2;  
Servo servoup;  
boolean stringComplete = false;
String inputString;
double rotate1;
double rotate2;
int updown;

double servo1Langle;
double servo2Langle;
double s1diff;
double s2diff;
double s1step;
double s2step;
int msdelay=3;

String Splitstr;
int findcomma;
int previouscomma;

int divby=50;

int pos;
int penpos;


//Variables for trignomentry
float baselen=4.5;
float arm1len=3.0;
float arm2len=6.0;
float selx;
float sely;
float pi=3.14159;

float baslenmid= baselen / 2;
float topstart= 3;
float arm3lens1;
float arm3lens2;

float S1angle;
float S2angle;

float C1angle;
float C2angle;

float S1Totangle;
float S2Totangle;
      
float initialangle=60;

void setup() {
  servo1.attach(5);
  servo2.attach(6);
  servoup.attach(9);
  delay(100);
  servo1Langle=120;
  servo2Langle=60;
  servo1.write(servo1Langle); 
  servo2.write(servo2Langle);
  servoup.write(10);
  //servoup.write(110);        
  penpos=0;
  Serial.begin(9600);
}

void loop() {
  if(stringComplete == true)
  {
    findcomma=0;
    previouscomma=0;
    findcomma=inputString.indexOf(",",findcomma);
    if (findcomma>0)
    {
      Splitstr=inputString.substring(0,findcomma);
      rotate1=Splitstr.toDouble();
    }
    previouscomma=findcomma+1;
    inputString = inputString.substring(previouscomma);

    findcomma=0;
    findcomma=inputString.indexOf(",",findcomma);
    if (findcomma>0)
    {
      Splitstr=inputString.substring(0,findcomma);
      rotate2=Splitstr.toDouble();
    }

    previouscomma=findcomma+1;
    inputString = inputString.substring(previouscomma);

    findcomma=0;
    findcomma=inputString.indexOf(",",findcomma);
    if (findcomma>0)
    {
      Splitstr=inputString.substring(0,findcomma);
      updown=Splitstr.toInt();
    }
      selx=(rotate1/divby)+baslenmid;
      sely=(rotate2/divby)+topstart;
      anglecalc();
      S1Totangle=S1Totangle-initialangle;
      S2Totangle=180-(S2Totangle-initialangle);
    
      if(S1Totangle>=0 and S1Totangle<=180)
      {
        if(S2Totangle>=0 and S2Totangle<=180)
        {
          s1diff=servo1Langle-S1Totangle;
          s2diff=servo2Langle-S2Totangle;
          if(abs(s1diff)>abs(s2diff))
          {
            s1step=s1diff/abs(s1diff);
            s2step=s2diff/abs(s1diff);
//            Serial.print(s1step);
//            Serial.print("#####");
//            Serial.println(s2step);                                                          
            for (pos = 0; pos <= abs(s1diff); pos += 1) { 
              servo1Langle=servo1Langle-s1step;
              servo2Langle=servo2Langle-s2step;
              servo1.write(servo1Langle); 
              servo2.write(servo2Langle);                      
//              Serial.print(servo1Langle);
//              Serial.print("##");
//              Serial.println(servo2Langle);
              delay(msdelay);                       
            }            
//            Serial.print(S1Totangle);
//            Serial.print("##");
//            Serial.println(S2Totangle);            
            servo1.write(S1Totangle); 
            servo2.write(S2Totangle);                                  
          }
          else if(abs(s2diff)>0)
          {
            s1step=s1diff/abs(s2diff);
            s2step=s2diff/abs(s2diff);            
//              Serial.print(s1step);
//              Serial.print("*****");
//              Serial.println(s2step);                                              
            for (pos = 0; pos <= abs(s2diff); pos += 1) { 
              servo1Langle=servo1Langle-s1step;
              servo2Langle=servo2Langle-s2step;
              servo1.write(servo1Langle); 
              servo2.write(servo2Langle);  
//              Serial.print(servo1Langle);
//              Serial.print("-");
//              Serial.println(servo2Langle);                                  
              delay(msdelay);                       
            }                        
//            Serial.print(S1Totangle);
//            Serial.print("-");
//            Serial.println(S2Totangle);                        
            servo1.write(S1Totangle); 
            servo2.write(S2Totangle); 
                                             
          }
          servo1Langle=S1Totangle;
          servo2Langle=S2Totangle;
          if(updown!=penpos)
          {
            penpos=updown;
            penupdown();
          }
        }
      }
      else
      {
        if (penpos==1)
        {
            penpos=0;      
            penupdown();
        }
      }

      
    Serial.print("N");
    inputString="";
    stringComplete = false;
  }
}

void penupdown()
{
    if (penpos==1)
    {
        for (pos = 10; pos <= 110; pos += 1) { 
          servoup.write(pos);              
          delay(msdelay);                       
        }
    }
    else
    { 
        for (pos = 110; pos >10 ; pos -= 1) { 
          servoup.write(pos);              
          delay(msdelay);                       
        }
    }            
}

void anglecalc()
{
  arm3lens1 = sqrt((pow((selx - 0), 2)) + (pow((sely - 0), 2)));
  arm3lens2 = sqrt((pow((selx - baselen), 2)) + (pow((sely - 0), 2)));
  
  S1angle=findangle(arm1len, arm3lens1, arm2len);
  S2angle = findangle(arm1len, arm3lens2, arm2len);
  C1angle = findangle(baselen, arm3lens1, arm3lens2);
  C2angle = findangle(baselen, arm3lens2, arm3lens1);

  S1Totangle = round((S1angle + C1angle)*100)/100.00;
  S2Totangle = round((S2angle + C2angle)*100)/100.00;
  
}
float findangle(float opp,float adj,float hyp)
{
  float Scal;
  float Scal2;
  Scal2 = (pow(opp, 2) + pow(adj, 2) - pow(hyp, 2)) / (2.0 * opp * adj);
  Scal = acos(Scal2);
  Scal =findangle(Scal);
  return Scal;
}
float findangle(float radians)
{
  float degree;
  degree = radians * (180 / pi);
  return degree;
}
void serialEvent() {
 while (Serial.available()) {
    char inChar = (char)Serial.read();   
    if (inChar == 'R') {
      stringComplete = true;
     }
     else
     {
      inputString += inChar; 
     }
  }    
}
