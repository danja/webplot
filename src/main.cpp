#include <Arduino.h>
#include <ESP32Servo.h>

#include <Point.h>
#include <FiveBar.h>

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

unsigned int pauseTime = 200;
FiveBar fb = FiveBar(9.6, 12.0, 12.0);
double crossSize = 0.5;

// 100,80
int offsetLeft = -80; // -54.0; // degrees off 90
int offsetRight = 65; // 51.0;

// forward declarations
void home();
void penUp();
void penDown();

void moveServos(float angleLeft, float angleRight);
void moveTo(double x, double y, boolean penDown);
void drawCross(double x, double y);

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

  // 120 degrees (60 in each direction)

  for (int i = -2; i < 10; i += 2.5)
  {
    for (int j = 12; j < 25; j += 2.5)
    {
      drawCross(i, j);
    }
  }

  /*
  penUp();
  moveTo(-2, 20, false);
  delay(1000);
  moveTo(9, 25, true);
  moveTo(9.5, 13, true);
  moveTo(-2, 14, true);
  penUp();
  drawCross(5, 13);
  penUp();
*/
}

void moveTo(double x, double y, boolean penDown)
{
  delay(pauseTime);
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);
  delay(pauseTime);
  Point p = Point(x, y);
  Point servos = fb.inverseKinematic(p);
  if ((servos.x == -1) && (servos.y == -1))
  {
    Serial.println("ERROR!");
    return;
  }

  if (penDown)
  {
    servoPen.write(PEN_DOWN);
  }
  else
  {
    servoPen.write(PEN_UP);
  }
  delay(pauseTime);
  moveServos(servos.x, servos.y);
  delay(pauseTime);
  Serial.print("angles ");
  Serial.print(servos.x);
  Serial.print(", ");
  Serial.println(servos.y);
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
double ease(double p)
{
  if (p < 0.5)
  {
    return 2 * p * p;
  }
  else
  {
    return (-2 * p * p) + (4 * p) - 1;
  }
}

void drawCross(double x, double y)
{
  moveTo(x - crossSize, y - crossSize, false);
  moveTo(x + crossSize, y + crossSize, true);
  moveTo(x - crossSize, y + crossSize, false);
  moveTo(x + crossSize, y - crossSize, true);
  penUp();
}

void loop()
{
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

void moveServos(float angleLeft, float angleRight)
{
  servoLeft.write(angleLeft + offsetLeft);
  servoRight.write(angleRight + offsetRight);
}
