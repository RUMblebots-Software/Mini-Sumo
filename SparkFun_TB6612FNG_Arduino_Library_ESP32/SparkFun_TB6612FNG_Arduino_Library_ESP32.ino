/******************************************************************************
TB6612.cpp
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.

Resources:
TB6612 SparkFun Library

Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/
class Motor{

  private:
    int In1;
    int In2;
    int PWM;
    int Standby;
    int Offset;
    int DEFAULTSPEED = 10;
  
  public:
    Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin)
    {
      In1 = In1pin;
      In2 = In2pin;
      PWM = PWMpin;
      Standby = STBYpin;
      Offset = offset;
      
      pinMode(In1, OUTPUT);
      pinMode(In2, OUTPUT);
      pinMode(PWM, OUTPUT);
      pinMode(Standby, OUTPUT);
    }

    void drive(int speed)
    {
      digitalWrite(Standby, HIGH);
      speed = speed * Offset;
      if (speed>=0) fwd(speed);
      else rev(-speed);
    }
    void drive(int speed, int duration)
    {
      drive(speed);
      delay(duration);
    }

    void fwd(int speed)
    {
       digitalWrite(In1, HIGH);
       digitalWrite(In2, LOW);
       ledcWrite(PWM, speed);
    
    }

    void rev(int speed)
    {
       digitalWrite(In1, LOW);
       digitalWrite(In2, HIGH);
       ledcWrite(PWM, speed);
    }

    void brake()
    {
       digitalWrite(In1, HIGH);
       digitalWrite(In2, HIGH);
       ledcWrite(PWM,0);
    }

    void standby()
    {
       digitalWrite(Standby, LOW);
    }

    void forward(Motor motor1, Motor motor2, int speed)
    {
      motor1.drive(speed);
      motor2.drive(speed);
    }
    
    void forward(Motor motor1, Motor motor2)
    {
      motor1.drive(DEFAULTSPEED);
      motor2.drive(DEFAULTSPEED);
    }


    void back(Motor motor1, Motor motor2, int speed)
    {
      int temp = abs(speed);
      motor1.drive(-temp);
      motor2.drive(-temp);
    }
    
    void back(Motor motor1, Motor motor2)
    {
      motor1.drive(-DEFAULTSPEED);
      motor2.drive(-DEFAULTSPEED);
    }
    
    void left(Motor left, Motor right, int speed)
    {
      int temp = abs(speed)/2;
      left.drive(-temp);
      right.drive(temp);
      
    }


    void right(Motor left, Motor right, int speed)
    {
      int temp = abs(speed)/2;
      left.drive(temp);
      right.drive(-temp);
      
    }
    
    void brake(Motor motor1, Motor motor2)
    {
      motor1.brake();
      motor2.brake();
    }
};


/******************************************************************************
TestRun.ino
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.

Resources:
TB6612 SparkFun Library

Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/


// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 17
#define AIN2 16
#define PWMA 5
#define STBY 21

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup()
{
 ledcSetup(0, 1000, 8);
 ledcAttachPin(PWMA, 0);
}


void loop()
{
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
   motor1.drive(255,1000);
   
}
