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
FiveBar fb = FiveBar(9.6, 12, 12);
double crossSize = 1;

int offsetLeft = -32; // degrees off 90
int offsetRight = 40;

// forward declarations
void home();
void penUp();
void penDown();
void drawCross(double x, double y);
void moveTo(double x, double y, boolean penDown);

void moveServos(float angleLeft, float angleRight);
//static double easeInOut(double t, double b, double c, double d);
void testK();

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

  //  moveServos(90 - 32, 90 + 42);

  /*
  delay(2000);
  drawCross(5, 0);

  delay(2000);
  drawCross(5, 22);

  delay(2000);
  drawCross(-12, 12);

  delay(2000);
  drawCross(-10, 19);

  delay(2000);
  drawCross(22, 12);

  delay(2000);
  drawCross(15, 20);
*/

  /*
  for (int i = -10; i < 40; i += 5)
  {
    for (int j = -30; j < 50; j += 5)
    {
      drawCross(i, j);
    }
  }
*/
  int x = 5;
  for (int y = -30; y < 50; y += 5)
  {
    drawCross(x, y);
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);
  }

  penUp();
}
/*
  Point p1, p2, servos1, servos2;

  for (int i = 0; i < 100; i++)
  {
    Serial.println("===================");
    penUp();
    int x1 = rand() % 30 - 10;
    int y1 = rand() % 20;
    int x2 = rand() % 30 - 10;
    int y2 = rand() % 20;
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(x2);
    Serial.println(y2);
    Serial.println("-----------------------");
    p1 = Point(x1, y1);
    p2 = Point(x1, y1);
    servos1 = fb.inverseKinematic(p1);
    servos2 = fb.inverseKinematic(p2);
    Serial.println(servos1.x);
    Serial.println(servos1.y);
    Serial.println(servos2.x);
    Serial.println(servos2.y);
    int d = 400;

    if ((servos1.x != -1) && (servos1.y != -1) && (servos2.x != -1) && (servos2.y != -1))
    {
      penUp();
      delay(d);
      servoLeft.write(servos1.x);
      servoRight.write(servos1.y);
      delay(d);
      penDown();
      delay(d);
      servoLeft.write(servos2.x);
      servoRight.write(servos2.y);
      delay(d);
    }
    else
    {
      Serial.println("Error!");
    }
  }
  penUp();
*/

/*
left ~140...180
right 0..40?
*/

void moveTo(double x, double y, boolean penDown)
{
  delay(pauseTime);
  Point p = Point(x, y);
  Point servos = fb.inverseKinematic(p);
  if ((servos.x == -1) && (servos.y == -1))
  {
    return;
  }
  //  Serial.print(x);
  //  Serial.print(", ");
  //  Serial.println(y);

  if (penDown)
  {
    servoPen.write(PEN_DOWN);
  }
  else
  {
    servoPen.write(PEN_UP);
  }
  delay(pauseTime);
  servoLeft.write(servos.x + offsetLeft);
  servoRight.write(servos.y + offsetRight);
  delay(pauseTime);
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

void left(int angle)
{
  int current = servoLeft.read();
  angle = 180 - angle;
}

void moveServos(float angleLeft, float angleRight)
{
  servoLeft.write(angleLeft);
  servoRight.write(angleRight);
}

void testK()
{
  double x = 5;
  double y = 15;

  FiveBar fb = FiveBar(10, 10, 10);

  Point pen = Point(5, 15);
  Point servos = fb.inverseKinematic(pen);

  // Left = 109.32629508411303
  // Right = 70.67370491588697
  Serial.println("===================");
  Serial.print(servos.x);
  Serial.println("------");
  Serial.print(servos.y);
  Serial.println("===================");
}
