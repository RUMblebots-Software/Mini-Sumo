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

bool is_Left_Line_Reading_Changed(float change_in_percent, float last_reading){
  float current_reading = get_Left_Line_Reading();
  float change = (abs(last_reading - current_reading)) / ((last_reading + current_reading)/2);
  change = change * 100;

  if(change >= change_in_percent){
    return true;
  }

  return false;
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

float last_left_line_reading;

void setup() {
  // initialize serial communication at 9600 bits per second:
  delay(2000);
  Serial.begin(9600);

  last_left_line_reading = get_Left_Line_Reading();
}

//// the loop routine runs over and over again forever:



void loop() {
  outputData();
  if(is_Left_Line_Reading_Changed(10, last_left_line_reading)){
      xmotion.Backward(30, 100);
      delay(500);
    }

  if(Average_Left_Front_Distance(20) < 80){
    xmotion.Left0(10, 100);
  }

  if(Average_Right_Front_Distance(20) < 80){
    xmotion.Right0(10, 100);
  }
   //xmotion.StopMotors(1);

  while(Average_Left_Front_Distance(20) < 80 && Average_Right_Front_Distance(20) < 80) {
    
    if(is_Left_Line_Reading_Changed(10, last_left_line_reading)){
      xmotion.Backward(30,100);
      delay(500);
    }
    else{
      xmotion.Forward(10,100);
    }
    
  }
  if(Average_Left_Front_Distance(20) > 50 && Average_Right_Front_Distance(20) > 50 && is_Left_Line_Reading_Changed(10, last_left_line_reading)){
    xmotion.StopMotors(100);
  }

  last_left_line_reading = get_Left_Line_Reading();
}
