#include <xmotion.h>
int motorL = 0;
int motorR = 0;
int sensorL = 0;
int sensorR = 0;
int sensorB = 0;
int distanceL = 0;
int distanceR = 0; 
int start = 0;
static bool isWaiting = true;
static bool isLooking = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(distanceL, INPUT);
  pinMode(distanceR, INPUT);
  pinMode(start, INPUT);
 

    while(isWaiting){
      if(digitalRead(start)){
        isWaiting = false;
        delay(5000);
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Read border sensor
  if(digitalRead(sensorL)){
    //Turn back and turn right
    xmotion.Backward(100, 500);
    xmotion.Right0(100, 500);
    }
  if(digitalRead(sensorR)){
      //Turn back and turn left 
    xmotion.Backward(100, 500);
    xmotion.Left0(100, 500);
    }
  if(digitalRead(sensorB)){
    xmotion.Forward(100, 500);
    } 
  //Nothing foung
  if(random(2) == 0 && isLooking){ // Turn right
    xmotion.Right0(100, random(1000));
  }else{ // Turn left
    xmotion.Left0(100, random(1000));
  }

  xmotion.Forward(100, 200);

  if(digitalRead(distanceL) || digitalRead(distanceR)){
    isLooking = false;
    xmotion.Forward(100, 500);
  }
  
  if(!digitalRead(distanceL) && !digitalRead(distanceR)){
     isLooking = true;
  }
}
