#include <SoftwareSerial.h>
#include "RoboClaw.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(0,1);	
RoboClaw roboclaw(&serial,10000);

#define address 0x80

// BL
int inPinBL = 4;
// 45 Left
int inPinBR = 5;
// Straight
int inPinFL = 6;
// 45 Right
int inPinFR = 7;

int cValue;

bool cases[][] {
    {true, false, false, false},
    {false, true, false, false},
    {false, false, true, false},
    {false, false, false, true},

    {true, true, false, false},
    {false, false, true, true},
    {false, true, true, false},
    {true, false, false, true},
        }

// Functions
bool checkDir(int inPut) {
    if(digitalRead(inPut) == LOW) {
        return true; 
    }
}

bool compareArr(int arr1[], arr2[]) {
    for(int i = 0; i < sizeof(arr1)/4; i++) {
        if(arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

void forward(int power) {
    roboclaw.ForwardM1(address, power);
    roboclaw.ForwardM2(address, power);
    delay(50);
}
void turn(int tTime, int tPower) {
    roboclaw.ForwardM1(address, tPower);
    roboclaw.ForwardM2(address, tPower);
    delay(tTime);
}

void setup() {
    roboclaw.begin(38400);;
  
    pinMode(inPin, INPUT);
    pinMode(led, OUTPUT);
}

void loop() {
   

    bool currentCase[] = {
        checkDir(inPinBL),
        checkDir(inPinFL), 
        checkDir(inPinFR),
        checkDir(inPinBR), 
    };
   
    for(int i = 0; i < 30; i++) {
        if(compareArr(currentCase, arr[i]) == true) {
            cValue = i;
            break;
        }
    }
   
    switch(i) {
        case 0: 
            roboclaw.ForwardM1(address, 127);
            roboclaw.ForwardM2(address, 64);
            delay(50);
            break;
        case 1: 
            roboclaw.ForwardM1(address, -127);
            roboclaw.ForwardM2(address, -64);
            delay(50);
            break;
        case 2: 
            roboclaw.ForwardM1(address, -64);
            roboclaw.ForwardM2(address, -127);
            delay(50);
            break;
        case 3: 
            roboclaw.ForwardM1(address, 64);
            roboclaw.ForwardM2(address, 127);
            delay(50);
            break;
        case 4: 
            roboclaw.ForwardM1(address, 127);
            roboclaw.ForwardM2(address, 64);
            delay(50);
            break;
        case 5: 
            roboclaw.ForwardM1(address, 64);
            roboclaw.ForwardM2(address, 127);
            delay(50);
            break;
        case 6: 
            roboclaw.ForwardM1(address, -127);
            roboclaw.ForwardM2(address, -127);
            delay(50);
            break;
        case 7: 
            roboclaw.ForwardM1(address, 127);
            roboclaw.ForwardM2(address, 127);
            delay(50);
            break;
        default:
            roboclaw.ForwardM1(address, 64);
            roboclaw.ForwardM2(address, 64);
            delay(50);
            break;
    }
}
