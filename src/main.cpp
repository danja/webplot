#include <Arduino.h>
#include <ESP32Servo.h>

const int GPIO_PEN = 22;
const int GPIO_LEFT = 19;
const int GPIO_RIGHT = 23;

const int PEN_DOWN = 180;
const int PEN_UP = 0;

Servo servoPen;
Servo servoLeft;
Servo servoRight;

// Published values for SG90 servos; adjust if needed
const int minUs = 1000;
const int maxUs = 2000;

const int penMinUs = 1000;
const int penMaxUs = 2000;

const int slowFactor = 0.01;

ESP32PWM pwm;

// forward declarations
void home();
void penUp();
void penDown();
void moveServos(int angleLeft, int angleRight);
static float easeInOut(float t, float b, float c, float d);

void setup()
{

  Serial.begin(9600);
  Serial.println("Starting..");
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  // ESP32PWM::allocateTimer(3);

  servoPen.setPeriodHertz(50);   // Standard 50hz servo
  servoLeft.setPeriodHertz(50);  // Standard 50hz servo
  servoRight.setPeriodHertz(50); // Standard 50hz servo

  servoPen.attach(GPIO_PEN, penMinUs, penMaxUs);
  servoLeft.attach(GPIO_LEFT, minUs, maxUs);
  servoRight.attach(GPIO_RIGHT, minUs, maxUs);

  /*
  for (int pos = 0; pos <= 180; pos++)
  {
    Serial.println(pos);
    //  servoPen.write(pos);
    // servoLeft.write(pos);
    //  servoRight.write(pos);
    penUp();
    delay(2000);
  }
*/
  penUp();
}

int servo = 0;

/*
left ~140...180
right 0..40?
*/

void loop()
{
  for (int pos = 85; pos <= 95; pos++)
  {
    // servoLeft.write(180 - pos);

    // servoRight.write(90);
    Serial.println(pos);
    //  servoPen.write(pos);
    // servoRight.write(180 - pos);
    //  servoRight.write(pos);
    // penUp();
    delay(1000);
  }
  /*
  if (Serial.available() > 0)
  {
    // read the incoming string:
    String incomingString = Serial.readString();
    Serial.println(incomingString);

    if (servo == 0)
    {
      Serial.print("Left : " + incomingString);
      servoLeft.write(incomingString.toInt());
      servo = 1;
    }
    else
    {
      Serial.print("Right : " + incomingString);
      servoRight.write(incomingString.toInt());
      servo = 0;
    }
  }
  delay(200);
*/
}

void penDown()
{
  servoPen.write(PEN_DOWN);
}

void penUp()
{
  servoPen.write(PEN_UP);
}

void left(int angle)
{
  int current = servoLeft.read();
  angle = 180 - angle;
}

void moveServos(int angleLeft, int angleRight)
{
}
