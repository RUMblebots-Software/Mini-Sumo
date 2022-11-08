// UPRM RUMblebots Combact Robots Team
// Edimar Valentin Kery <edimar.valentin@upr.edu>

//These are the pins for the TB6612FNG Motor Driver 
#define STBY 0
#define PWMA 1
#define PWMB 4
#define AIN1 3
#define AIN2 2
#define BIN1 5
#define BIN2 6

//These are the pins for the Sharp GP2Y0A21YK0F Analog Distance Sensor
#define RIGHT_SENSOR A6
#define RIGHT_ANGLE_SENSOR A7
#define RIGHT_FRONT_SENSOR A3
#define LEFT_FRONT_SENSOR A2
#define LEFT_ANGLE_SENSOR A0
#define LEFT_SENSOR A1
#define BACK_SENSOR A10

//These are the pins for the Dual Micro Line Sensor ML2
#define RIGHT_LINE_SENSOR A8
#define LEFT_LINE_SENSOR A11
#define BACK_LINE_SENSOR A9


#include <Wire.h> // This library allows to communicate with I2C devices
#include <L3G.h> // This is a library interfaces with L3GD20H, L3GD20, and L3G4200D gyros on Pololu boards

L3G gyro; // Create the gyro object

// This functions read from the distance sensors and returns a float value representing centimeters
float getDistance(int sensor){
  return 65 * pow(analogRead(sensor) * 0.0048828125, -1.10);
}

//Sets both motors to go forward at x speed
void forward(int speed){
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
}

//Sets motors to stop and shuts down the motor driver. Use this whenever the sumo shouldn't move.
void stopMotors(){
  digitalWrite(STBY, LOW);
  
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

}

//Spins right at x speed and stops a y angle
void right(int speed, float angle){
  float Current_z_angle = 0.0f;
  unsigned long PrevTime = millis();
      digitalWrite(STBY, HIGH);
      
      speed = abs(speed)/2; // Motor1 + Motor 2 = Speed
  
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
     
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    
      analogWrite(PWMA, speed);
      analogWrite(PWMB, speed);
  
  while(Current_z_angle <= angle){
      Serial.println("Spinning");
      gyro.read();
      float DPS = (float)gyro.g.z * 0.00875; // Degrees Per Second
      
      unsigned long CurrentTime = millis();
      unsigned long DeltaTime = CurrentTime - PrevTime;
      PrevTime = CurrentTime;
    
      float Delta_z_angle = abs((DPS / 1000) * DeltaTime);
     
      Current_z_angle += Delta_z_angle;
      Serial.print("Z angle: ");
      Serial.println(Current_z_angle);
      Serial.print("Angle: ");
      Serial.println(angle);
  }
  stopMotors();
}

//Spins left at x speed and stops a y angle
void left(int speed, float angle){
  float Current_z_angle = 0.0f;
  unsigned long PrevTime = millis();
      digitalWrite(STBY, HIGH);
      
      speed = abs(speed)/2; // Motor1 + Motor 2 = Speed
  
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
     
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
    
      analogWrite(PWMA, speed);
      analogWrite(PWMB, speed);
  
  while(Current_z_angle <= angle){
      Serial.println("Spinning");
      gyro.read();
      float DPS = (float)gyro.g.z * 0.00875; // Degrees Per Second
      
      unsigned long CurrentTime = millis();
      unsigned long DeltaTime = CurrentTime - PrevTime;
      PrevTime = CurrentTime;
    
      float Delta_z_angle = abs((DPS / 1000) * DeltaTime);
     
      Current_z_angle += Delta_z_angle;
      Serial.print("Z angle: ");
      Serial.println(Current_z_angle);
      Serial.print("Angle: ");
      Serial.println(angle);
  }
  stopMotors();
}

//Sets motors to go back at x speed
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

  // Start communicating with the SDA (data line) and SCL (clock line) 

  //Initialze the gyro if found. If not, setup never finishes. 
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  if(analogRead(RIGHT_LINE_SENSOR) < 100 && analogRead(LEFT_LINE_SENSOR) < 100){
    forward(60);
  }
  else if(analogRead(RIGHT_LINE_SENSOR) > 100){
    stopMotors();
    left(255, 180);
  }
  else if(analogRead(LEFT_LINE_SENSOR) > 100){
    stopMotors();
    right(100, 180);
  }                                                                                                                                                                                            
}
