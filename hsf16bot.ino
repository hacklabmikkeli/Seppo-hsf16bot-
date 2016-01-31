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

#define turnSpeed 80
#define driveSpeed 65
#define sideWallDistance 5

long getDistance(int echo, int trig) {
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

void turnRight(int turnDelay){

  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
  
  digitalWrite(leftDirectionPin1, HIGH);
  digitalWrite(leftDirectionPin2, LOW);
  digitalWrite(rightDirectionPin1, LOW);
  digitalWrite(rightDirectionPin2, HIGH);

  analogWrite(leftSpeedPin, turnSpeed);
  analogWrite(rightSpeedPin, turnSpeed);

  delay(turnDelay);
  
}

void turnLeft(int turnDelay){
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
  
  digitalWrite(leftDirectionPin1, LOW);
  digitalWrite(leftDirectionPin2, HIGH);
  digitalWrite(rightDirectionPin1, HIGH);
  digitalWrite(rightDirectionPin2, LOW);

  analogWrite(leftSpeedPin, turnSpeed);
  analogWrite(rightSpeedPin, turnSpeed);

  delay(turnDelay);

}

void drive(long frontDistance){
  
  digitalWrite(leftDirectionPin1, HIGH);
  digitalWrite(leftDirectionPin2, LOW);
  digitalWrite(rightDirectionPin1, HIGH);
  digitalWrite(rightDirectionPin2, LOW);

  if(frontDistance < 25){
    analogWrite(leftSpeedPin, 70);
    analogWrite(rightSpeedPin, 70);
  }else if(frontDistance < 35){
    analogWrite(leftSpeedPin, 80);
    analogWrite(rightSpeedPin, 80);
  }else if(frontDistance < 45){
    analogWrite(leftSpeedPin, 90);
    analogWrite(rightSpeedPin, 90);
  }else if(frontDistance < 60){
    analogWrite(leftSpeedPin, 100);
    analogWrite(rightSpeedPin, 100);
  }else{
    analogWrite(leftSpeedPin, 110);
    analogWrite(rightSpeedPin, 110);
  }

}

void reverse(){

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
  delay(2);
  long middleDistance = getDistance(middleEchoPin, middleTrigPin);
  delay(2);
  long rightDistance = getDistance(rightEchoPin, rightTrigPin);
  delay(2);

  if(middleDistance < 4){
    reverse();
  }else if(middleDistance < 20){
    if(leftDistance > 21){
      turnLeft(50);
    }else if(rightDistance > 10){
      turnRight(50);
    }else{
      if(leftDistance > 10){
        turnLeft(50);
      }else{
        reverse();
      }
    }
  } else {
    if(leftDistance < sideWallDistance){
      turnRight(3);
    } else if(rightDistance < sideWallDistance){
      turnLeft(3);
    }else{
      drive(middleDistance);
    }
  } 
}
