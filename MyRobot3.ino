#include <AFMotor.h>   //Adafruit motor shield library
#include <Servo.h>     //Arduino Servo library
 
 //Create two motor objects for the robot.  Left motor and right motor.
AF_DCMotor motorL(1, MOTOR12_8KHZ);
AF_DCMotor motorR(4, MOTOR12_8KHZ);

//Declare pins for the ultrasonic sensor
int trigPin = A0;
int echoPin = A1;

//Create a servo motor object
Servo myservo;  // create servo object to control a servo 

                
//Varaibles to hold the left and right measured distance
int leftDistance = 0, rightDistance = 0;

void setup() {
  Serial.begin(57600);
  
  // Setup pins for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //set the speed of the motors
  motorL.setSpeed(200);
  motorR.setSpeed(200);
  
  //Initialize the servo with pin 9
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
  lookAhead();
  if(measureDistance() < 10)
  {
    stopMotor();
    lookLeft();
    leftDistance = measureDistance();
    delay(250);

    lookRight();
    rightDistance = measureDistance();
    delay(250);
    
    if (leftDistance < rightDistance)
    {
       goRight();
       delay(600);
    } 
    else
    {
       goLeft();
       delay(600);
    }
  }
  else{
      Serial.println("Go Forward");
      goFoward();
     delay(250);
  }
}

int measureDistance()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return (int)distance;
}

void lookLeft()
{
   myservo.write(30); 
}

void lookRight()
{
   myservo.write(150); 
}

void lookAhead()
{
   myservo.write(90); 
}

void goFoward()
{
  motorL.run(FORWARD);
  motorR.run(FORWARD);
}

void goRight()
{
  motorL.run(FORWARD);
  motorR.run(BACKWARD);
}

void goLeft()
{
  motorL.run(BACKWARD);
  motorR.run(FORWARD);
}

void goBackward()
{
  motorL.run(BACKWARD);
  motorR.run(BACKWARD);
}

void stopMotor()
{
  motorL.run(RELEASE);
  motorR.run(RELEASE);
}

