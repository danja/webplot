#include <Arduino.h>
#include <ESP32Servo.h>

const int GPIO_PEN = 22;
const int GPIO_LEFT = 19;
const int GPIO_RIGHT = 23;

Servo servoPen;
Servo servoLeft;
Servo servoRight;

// Published values for SG90 servos; adjust if needed
const int minUs = 1000;
const int maxUs = 2000;

const int penMinUs = 0;
const int penMaxUs = 2000;

ESP32PWM pwm;

void setup()
{

  Serial.begin(115200);
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

  for (int pos = 0; pos <= 180; pos++)
  {
    Serial.println(pos);
    servoPen.write(pos);
    // servoLeft.write(pos);
    //  servoRight.write(pos);
    delay(100);
  }
}

void loop()
{
}