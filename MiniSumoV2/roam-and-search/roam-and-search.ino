// Edimar Valentin Kery <edimar.valentin@upr.edu>

#define STBY 0
#define PWMA 1
#define PWMB 4
#define AIN1 3
#define AIN2 2
#define BIN1 5
#define BIN2 6

#define RIGHT_SENSOR A6
#define RIGHT_ANGLE_SENSOR A7
#define RIGHT_FRONT_SENSOR A3
#define LEFT_FRONT_SENSOR A2
#define LEFT_ANGLE_SENSOR A0
#define LEFT_SENSOR A1
#define BACK_SENSOR A10

#define RIGHT_LINE_SENSOR A8
#define LEFT_LINE_SENSOR A11
#define BACK_LINE_SENSOR A9


#include <Wire.h>
#include <L3G.h>

L3G gyro;


float getDistance(int sensor){
  return 65 * pow(analogRead(sensor) * 0.0048828125, -1.10);
}


void right(int speed){
  digitalWrite(STBY, HIGH);
  speed = abs(speed)/2; // Motor1 + Motor 2 = Speed
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}

void left(int speed){
  digitalWrite(STBY, HIGH);
  speed = abs(speed)/2; // Motor1 + Motor 2 = Speed
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
 
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}

void foward(int speed){
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
 
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}

void stopMotors(){
  digitalWrite(STBY, LOW);
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

}

void reverse(int speed){
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}


//const float GYRO-DPS-PER-LSB = 0.00875;
unsigned long PrevTime;
float Current_z_angle = 0.0f;
float Target_angle;
bool Target_angle_set = false;

void turn(int speed, float angle){
  if(!Target_angle_set){
      Target_angle = Current_z_angle + angle;
      Target_angle_set = true;
  }

  if(angle > 0){
    left(speed);
    if(Current_z_angle >= Target_angle){
      stopMotors();
      Target_angle_set = false;
      Target_angle = 0;
      delay(1000);
    }
  }else{
    right(speed);
      if(Current_z_angle <= Target_angle){
      stopMotors();
      Target_angle_set = false;
      Target_angle = 0;
      delay(1000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(RIGHT_ANGLE_SENSOR, INPUT);
  pinMode(RIGHT_FRONT_SENSOR, INPUT);
  pinMode(LEFT_FRONT_SENSOR, INPUT);
  pinMode(LEFT_ANGLE_SENSOR, INPUT);
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(BACK_SENSOR, INPUT);

  pinMode(RIGHT_LINE_SENSOR, INPUT);
  pinMode(LEFT_LINE_SENSOR, INPUT);
  pinMode(BACK_LINE_SENSOR, INPUT);

  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
  unsigned long PrevTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print("Left Sensor: ");
//  Serial.print(getDistance(LEFT_SENSOR));
//  Serial.println("cm \n");  
//  
//  Serial.print("Left Front Sensor: ");
//  Serial.print(getDistance(LEFT_FRONT_SENSOR));
//  Serial.println("cm \n"); 
//  
//  Serial.print("Left Angle Sensor: ");
//  Serial.print(getDistance(LEFT_ANGLE_SENSOR));
//  Serial.println("cm \n"); 
//  
//  Serial.print("Right Front Sensor: ");
//  Serial.print(getDistance(RIGHT_FRONT_SENSOR));
//  Serial.println("cm \n"); 
//  
//  Serial.print("Right Angle Sensor: ");
//  Serial.print(getDistance(RIGHT_ANGLE_SENSOR));
//  Serial.println("cm \n"); 
//  
//  Serial.print("Right Sensor: ");
//  Serial.print(getDistance(RIGHT_SENSOR));
//  Serial.println("cm \n"); 
//
//  Serial.print("Back Sensor: ");
//  Serial.print(getDistance(BACK_SENSOR));
//  Serial.println("cm \n"); 

//  Serial.print("Right Line Sensor: ");
//  Serial.println(analogRead(RIGHT_LINE_SENSOR));
//  
//  Serial.print("Left Line Sensor: ");
//  Serial.println(analogRead(LEFT_LINE_SENSOR));
//
//  Serial.print("Back Line Sensor: ");
//  Serial.println(analogRead(BACK_LINE_SENSOR));

  gyro.read();
  float DPS = (float)gyro.g.z * 0.00875; // Degrees Per Second
  
  unsigned long CurrentTime = millis();
  unsigned long DeltaTime = CurrentTime - PrevTime;
  PrevTime = CurrentTime;

  float Delta_z_angle = (DPS / 1000) * DeltaTime;

  turn(60, 90);
 
  Current_z_angle += Delta_z_angle;
  Serial.print("Angle: ");
  Serial.println(Current_z_angle);
  Serial.print("Target: ");
  Serial.println(Target_angle);
}
