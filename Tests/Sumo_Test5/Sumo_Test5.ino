
#include<xmotion.h>


#define RIGHT_FRONT_SENSOR A1
#define LEFT_FRONT_SENSOR A2
#define LEFT_LINE_SENSOR A7




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

void outputData() {
  Serial.print("Right Front Distance Sensor: ");
  Serial.print(get_Right_Front_Distance());
  Serial.println("cm");

  Serial.print("Average Right Front Distance: ");
  Serial.print(Average_Right_Front_Distance(50));
  Serial.println("cm");

  Serial.print("Left Front Distance Sensor: ");
  Serial.print(get_Left_Front_Distance());
  Serial.println("cm");

  Serial.print("Average Left Front Distance: ");
  Serial.print(Average_Left_Front_Distance(50));
  Serial.println("cm");
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

//// the loop routine runs over and over again forever:
void loop() {

  xmotion.Right0(30,100);
  while(Average_Left_Front_Distance(50) < 50 && Average_Right_Front_Distance(50) < 50) {
    xmotion.Forward(100,100);
  }


}
