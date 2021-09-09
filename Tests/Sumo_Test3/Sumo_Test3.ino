
#include<xmotion.h>



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  float sensorValueA = analogRead(A1) * 0.0048828125;
  float distanceA = 65 * pow(sensorValueA, -1.10);
  float sensorValueB = analogRead(A2) * 0.0048828125;
  float distanceB = 65 * pow(sensorValueB, -1.10);
  int lineA = analogRead(A4);
  Serial.print("A1: ");
  Serial.print(distanceA);
  Serial.println(" cm");
  Serial.print("A2: ");
  Serial.print(distanceB);
  Serial.println(" cm");
  Serial.print("Line: ");
  Serial.println(lineA);


  if(lineA > 700){
    xmotion.Right0(10, 100);
    while(distanceA < 50 && distanceB < 50){
      sensorValueA = analogRead(A1) * 0.0048828125;
      sensorValueB = analogRead(A2) * 0.0048828125;
      distanceA = 65 * pow(sensorValueA, -1.10);
      distanceB = 65 * pow(sensorValueB, -1.10);
      xmotion.Forward(10, 100);
    }
  }else{
    xmotion.StopMotors(100);
  }







//
//  if(lineA > 700){
//   xmotion.Forward(10, 100);
//  }else{
//    xmotion.Backward(10, 100);
//    delay(1000);
//    int r = random(1, 3);
//    while(lineA < 700){
//    if(r == 1){
//      xmotion.Right0(20,100);
//      Serial.print("Turning right");
//      delay(500);
//    }else{
//      xmotion.Left0(20, 100);
//      Serial.print("Turning left");
//      delay(500);
//    }
//    }
//  }


  
  delay(100);
}
