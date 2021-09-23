#include<xmotion.h>



#define RIGHT_FRONT_SENSOR A1
#define LEFT_FRONT_SENSOR A2
#define LEFT_LINE_SENSOR A5




float get_Right_Front_Distance() {
  return 65 * pow(analogRead(RIGHT_FRONT_SENSOR) * 0.0048828125, -1.10);
}

float get_Left_Front_Distance() {
  return 65 * pow(analogRead(LEFT_FRONT_SENSOR) * 0.0048828125, -1.10);
}

float get_Left_Line_Reading() {
  return analogRead(LEFT_LINE_SENSOR);
}


float Average_Right_Front_Distance(int sampleSize) {
  float sum = 0;
  for (int i = 0; i < sampleSize; i++) {
    sum = sum + get_Right_Front_Distance();
  }
  return sum / sampleSize;
}

float Average_Left_Front_Distance(int sampleSize) {
  float sum = 0;
  for (int i = 0; i < sampleSize; i++) {
    sum = sum + get_Left_Front_Distance();
  }
  return sum / sampleSize;
}

float Average_Left_Line_Reading(int sampleSize) {
  float sum = 0;
  for (int i = 0; i < sampleSize; i++) {
    sum = sum + get_Left_Line_Reading();
  }
  return sum / sampleSize;
}

void outputData() {
   Serial.print("Right Front Distance Sensor: ");
   Serial.print(get_Right_Front_Distance());
   Serial.println("cm");

   Serial.print("Average Right Front Distance: ");
   Serial.print(Average_Right_Front_Distance(20));
   Serial.println("cm");

   Serial.print("Left Front Distance Sensor: ");
   Serial.print(get_Left_Front_Distance());
   Serial.println("cm");

   Serial.print("Average Left Front Distance: ");
   Serial.print(Average_Left_Front_Distance(20));
   Serial.println("cm");

  Serial.print("Average Left Line Reading: ");
  Serial.print(Average_Left_Line_Reading(20));
  Serial.println(" ");
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  delay(2000);
  Serial.begin(9600);
  
}

//// the loop routine runs over and over again forever:
void loop() {
  outputData();
  if(Average_Left_Line_Reading(20) < 100){
      xmotion.Backward(30, 100);
      delay(100);
    }

  if(Average_Left_Front_Distance(20) < 80){
    xmotion.Left0(10, 100);
  }

  if(Average_Right_Front_Distance(20) < 80){
    xmotion.Right0(10, 100);
  }
   //xmotion.StopMotors(1);

  while(Average_Left_Front_Distance(20) < 80 && Average_Right_Front_Distance(20) < 80) {
    if(Average_Left_Line_Reading(20) > 300){
      xmotion.Forward(20, 100);
    }
    else if(Average_Left_Line_Reading(20) < 100){
      xmotion.Backward(30,100);
      delay(100);
    }
    
  }
  if(Average_Left_Front_Distance(20) > 50 && Average_Right_Front_Distance(20) > 50 && Average_Left_Line_Reading(20) > 100){
    xmotion.StopMotors(100);
  }
}
