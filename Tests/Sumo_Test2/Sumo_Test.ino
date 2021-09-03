#include <xmotion.h>

void setup() {
  // put your setup code here, to run once:
  delay(10000);

}

void loop(){
  xmotion.Forward(20, 250);
  delay(3000);
  xmotion.Backward(20, 250);
  delay(3000);
}
