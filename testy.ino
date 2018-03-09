int lRPWM_Output = 0; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int lLPWM_Output = 1; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

int rRPWM_Output = 2; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int rLPWM_Output = 3; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)


void lFBward(int power) {
    if (power < 512)
  {
    // reverse rotation
    int reversePWM = -(power - 511) / 2;
    analogWrite(lLPWM_Output, 0);
    analogWrite(lRPWM_Output, reversePWM);
  }
  else
  {
    // forward rotation
    int forwardPWM = (power - 512) / 2;
    analogWrite(lLPWM_Output, forwardPWM);
    analogWrite(lRPWM_Output, 0);
  }
}

void rFBward(int power) {
    if (power < 512)
  {
    // reverse rotation
    int reversePWM = -(power - 511) / 2;
    analogWrite(rLPWM_Output, 0);
    analogWrite(rRPWM_Output, reversePWM);
  }
  else
  {
    // forward rotation
    int forwardPWM = (power - 512) / 2;
    analogWrite(rLPWM_Output, forwardPWM);
    analogWrite(rRPWM_Output, 0);
  }
}

void turn(int power, int t) {
  lFBward(power);
  rFBward(power);
  delay(t);
}
   
void setup() {
  pinMode(lRPWM_Output, OUTPUT);
  pinMode(lLPWM_Output, OUTPUT);
  pinMode(rRPWM_Output, OUTPUT);
  pinMode(rLPWM_Output, OUTPUT);

  lFBward(600);
  rFBward(600);
  delay(1000);
  lFBward(512);
  rFBward(512);
}
 
void loop() { 
  // sensor value is in the range 0 to 1023
  // the lower half of it we use for reverse rotation; the upper half for forward rotation
}
