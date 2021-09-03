/*This example reads XMotion's Bottom Analog inputs
   There are A1 - A2 - A4 - A5
   Can be developed for other XMotion element readings
   www.Jsumo.com/xmotion
*/

#include<xmotion.h>



void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  float sensorValue = analogRead(A1) * 0.0048828125;
  float distance = 65 * pow(sensorValue, -1.10);
  if(distance < 20){
    xmotion.Backward(20, 250);
  }else{
    xmotion.StopMotors(100);
  }
  Serial.print("A1: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);
}
