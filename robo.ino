#include <SoftwareSerial.h>
#include <RoboClaw.h>

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
// Left
int inPinL = 8;
// 45 Left
int inPinLM = 9;
// Straight
int inPinS = 10;
// 45 Right
int inPinRM = 11;
// Right
int inPinR =12;
int cValue;

bool casesLight[][] {
    {true, false, false, false},
    {false, true, false, false},
    {false, false, true, false},
    {false, false, false, true},

    {true, true, false, false},
    {false, false, true, true},
    {false, true, true, false},
    {true, false, false, true},
}

bool casesIR[][] {
    // Left
    //// -90
    {true, false, false, false, false},

    //// -77.5
    {true, true, false, false, false},
    {true, true, false, true, false},
    {true, true, false, false, true},

    //// -45
    {false, true, false, false, false},
    {true, true, true, false, true},
    {true, true, true, false, false},

    //// -22.5
    {false, true, true, false, false},
    {false, true, true, false, true},
    {true, true, true, true, false},

    // Forward
    {false, false, true, false, false},
    {true, true, true, true, true},
    {false, true, true, true, false},

    // Right
    //// 90
    {false, false, false, false, true},

    //// 77.5
    {false, false, false, true, true},
    {true, false, false, true, true},
    {false, true, false, true, true},

    //// 45
    {false, false, false, true, false},
    {false, false, true, true, true},
    {true, false, true, true, true},

    //// 22.5
    {false, true, true, true, true},
    {false, false, true, true, false},
    {true, false, true, true, false},

    // Faulty 
    {false, true, false, true, false},
    {true, false, false, false, true},
    {false, false, true, false, true},
    {true, true, false, true, true},
    {true, false, true, false, false},
    {true, false, false, true, false},
    {false, true, false, false, true},
 
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
    bool currentCaseL[] = {
        checkDir(inPinBL),
        checkDir(inPinFL), 
        checkDir(inPinFR),
        checkDir(inPinBR), 
    };
    for(int i = 0; i < 30; i++) {
        if(compareArr(currentCaseL, arr[i]) == true) {
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
    }
   
   bool currentCaseIR[] = {
       checkDir(inPinL),
       checkDir(inPinLM), 
       checkDir(inPinS),
       checkDir(inPinRM), 
       checkDir(inPinR)
   };
   
   for(int i = 0; i < 30; i++) {
       if(compareArr(currentCaseIR, arr[i]) == true) {
           cValue = i;
           break;
       }
   }
   
   switch(i) {
       case 0: 
           turn(-90);
           break;
       case 1: 
       case 2: 
       case 3: 
           turn(-77.5);
           break;
       case 4: 
       case 5: 
       case 6: 
           turn(-45);
           break;
       case 7: 
       case 8: 
       case 9: 
           turn(-22.5);
           break;
       case 10: 
       case 11: 
       case 12: 
           forward();
           break;
       case 13: 
           turn(90);
           break;
       case 14: 
       case 15: 
       case 16: 
           turn(77.5);
           break;
       case 17: 
       case 18: 
       case 19: 
           turn(45);
           break;
       case 20: 
       case 21: 
       case 22: 
           turn(22.5);
           break;
       default:
           forward(64);
           break;
   }
}

