#define leftTrigPin 2
#define leftEchoPin 3
#define middleTrigPin 4
#define middleEchoPin 5
#define rightTrigPin 6
#define rightEchoPin 7
#define leftSpeedPin 9
#define rightSpeedPin 10
#define leftDirectionPin1 8
#define leftDirectionPin2 11
#define rightDirectionPin1 12
#define rightDirectionPin2 13

#define turnSpeed 150 //speed of motors while turning, from 0 - 255, tho has to be atleast 70 in order for motors to move
#define driveSpeed 100 //speed of motors while driving forward 0 - 255, tho has to be atleast 70 in order for robot to move
#define sideWallDistance 5 //if distance to sidewall is lower than this, robot will try to fix the situation

long getDistance(int echo, int trig) { //returns the distance from sensor as centimeters
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void turnRight(){ // Turn right without moving forward

  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
 
  digitalWrite(leftDirectionPin1, HIGH);
  digitalWrite(leftDirectionPin2, LOW);
  digitalWrite(rightDirectionPin1, LOW);
  digitalWrite(rightDirectionPin2, HIGH);

  analogWrite(leftSpeedPin, turnSpeed);
  analogWrite(rightSpeedPin, turnSpeed);
 
}

void turnLeft(){ //Turn left without moving forward
  
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
 
  digitalWrite(leftDirectionPin1, LOW);
  digitalWrite(leftDirectionPin2, HIGH);
  digitalWrite(rightDirectionPin1, HIGH);
  digitalWrite(rightDirectionPin2, LOW);

  analogWrite(leftSpeedPin, turnSpeed);
  analogWrite(rightSpeedPin, turnSpeed);

}

void turnRightSlow(){ //Turn right while moving forward
 
  digitalWrite(leftDirectionPin1, HIGH);
  digitalWrite(leftDirectionPin2, LOW);
  digitalWrite(rightDirectionPin1, LOW);
  digitalWrite(rightDirectionPin2, HIGH);

  analogWrite(leftSpeedPin, 120);
  delay(20);
 
}

void turnLeftSlow(){ //Turn left while moving forward
 
  digitalWrite(leftDirectionPin1, LOW);
  digitalWrite(leftDirectionPin2, HIGH);
  digitalWrite(rightDirectionPin1, HIGH);
  digitalWrite(rightDirectionPin2, LOW);

  analogWrite(rightSpeedPin, 120);
  delay(20);

}

void drive(){ //Drive forward
 
  digitalWrite(leftDirectionPin1, HIGH);
  digitalWrite(leftDirectionPin2, LOW);
  digitalWrite(rightDirectionPin1, HIGH);
  digitalWrite(rightDirectionPin2, LOW);

  analogWrite(leftSpeedPin, driveSpeed);
  analogWrite(rightSpeedPin, driveSpeed);
}

void reverse(){ //Drive backwards

  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
 
  digitalWrite(leftDirectionPin1, LOW);
  digitalWrite(leftDirectionPin2, HIGH);
  digitalWrite(rightDirectionPin1, LOW);
  digitalWrite(rightDirectionPin2, HIGH);

  analogWrite(leftSpeedPin, driveSpeed);
  analogWrite(rightSpeedPin, driveSpeed);

  delay(20);
}


void setup() {
  Serial.begin (9600);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(middleTrigPin, OUTPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(middleEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
 
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(leftDirectionPin1, OUTPUT);
  pinMode(leftDirectionPin2, OUTPUT);
  pinMode(rightDirectionPin1, OUTPUT);
  pinMode(rightDirectionPin2, OUTPUT);
}

void loop() {
  long leftDistance = getDistance(leftEchoPin, leftTrigPin);
  long middleDistance = getDistance(middleEchoPin, middleTrigPin);
  long rightDistance = getDistance(rightEchoPin, rightTrigPin);

  if(middleDistance < 4){ // If distance in front of a robot is less than 4cm, reverse
    reverse();
  }else if(middleDistance < 10){       // If distance in front of a robot is more than 4cm
    if(leftDistance < rightDistance){  // but less than 10cm, measure distance on both sides 
      turnRight();                     // and turn to side which has more space
    }else{
      turnLeft();
    }
  } else {
    drive();                                          // If distance in front of a robot is more than 10cm, drive forward
    if(middleDistance < 15){                          // If distance in front of a robot is less than 15cm, check if we are too close the wall
      if(leftDistance < sideWallDistance){
        turnRightSlow();
      } else if(rightDistance < sideWallDistance){
        turnLeftSlow();
      }
    }
  }
  /*
  // For debugging purposes
  
  Serial.print("Left: ");
  Serial.println(leftDistance);

  Serial.print("Middle: ");
  Serial.println(middleDistance);

  Serial.print("Right: ");
  Serial.println(rightDistance);
*/
 
}
