
int rangeMax[18] = {700, 1300, 800, 1200, 1400, 2200, 900, 1700, 800, 2200, 1800, 800, 800, 1400, 2200, 2200, 1300, 800};
int rangeMin[18] = {1500, 2200, 2100, 1800, 2300, 700, 1700, 800, 2200, 1200, 900, 2100, 1400, 2100, 700, 1300, 2200, 2200};

int dir[18] = {1, 1, 1, 1, 1, -1, 1, -1, 1, -1, -1, 1, 1, 1, -1, -1, 1, 1};

int interval = 800;

int offsetMax[3] = {100, 20, 00};
int offsetMin[3] = {200, 20, 00};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 // Serial.println("#DISABLE"); 
}

String code;

int tripodmoves[6][6] = {
    {0, 100, 0, 100, 0, 100},
    {100, 0, 100, 0, 100, 0},
    {0, 100, 0, 100, 0, 100},
    {100, 0, 100, 0, 100, 0},
    {0, 100, 0, 100, 0, 100},
    {100, 0, 100, 0, 100, 0},  
};

int legLift[6][6] =  {{1,50,1,90, 1, 20},
                      {1,50,1,90, 1, 20},
                      {1,50,1,90, 1, 20},
                      {1,50,1,90, 1, 20},
                      {1,50,1,90, 1, 20},
                      {1,50,1,90, 1, 20}} ;
int legDrop[6][6] =  {{1,50,1,0, 1, 50},
                      {1,50,1,15, 1, 30},
                      {1,50,1,0, 1, 50},
                      {1,50,1,0, 1, 50},
                      {1,50,1,00, 1, 40},
                      {1,50,1,0, 1, 50}};
                      
int triLift[6][6] =  {{1,50,1,90, 1, 90},
                      {1,50,1,90, 1, 90},
                      {1,50,1,90, 1, 90},
                      {1,50,1,90, 1, 90},
                      {1,50,1,90, 1, 90},
                      {1,50,1,90, 1, 90}} ;
                      
int spinLift[6][6] =  {{1,80,1,90, 1, 90},
                      {1,80,1,90, 1, 90},
                      {1,80,1,90, 1, 90},
                      {1,80,1,90, 1, 90},
                      {1,80,1,90, 1, 90},
                      {1,80,1,90, 1, 90}} ;
 
 int spinDrop[6][6] =  {{1,30,1,0, 1, 50},
                      {1,30,1,15, 1, 30},
                      {1,30,1,0, 1, 50},
                      {1,30,1,0, 1, 50},
                      {1,30,1,00, 1, 40},
                      {1,30,1,0, 1, 50}};                     
int servoCode[18];
int servoSweep[18];
boolean relaxFlag = true;
boolean standFlag = 1;
 bool flag = false;
 bool tripodFlag = false;
 int tripodMoves = 0;
void loop() {

  if(relaxFlag) {
    relax();
  }
  stand();
  tripod();
}

void relax() {
  for(int i=0;i<6;i++) {
    setLegServos(i+1, legLift[i]);
  }
  flushCode();
  relaxFlag = false;
  delay(2000);
}

void stand() {
  if(standFlag < 2) {
   for(int i=0;i<6;i++) {
    setLegServos(i+1, legDrop[i]);
   }
   flushCode();
   standFlag ++;
  }
  //delay(2000);
}

void tripod() {
  
   for(int i=0;i<6;i++) {
    
      if(i%2 == 0 && !tripodFlag) {
        if(flag) {
         setLegServos(i+1, legDrop[i]);
        } else{
          setLegServos(i+1, triLift[i]);
        }      
      }
     
      if(i%2 != 0 && tripodFlag){
        if(flag) {
         setLegServos(i+1, legDrop[i]);
        } else{
          setLegServos(i+1, triLift[i]);
        }   
      }
  
   
  }
  flushCode();
  flag = !flag;
  tripodMoves++;
  if(tripodMoves ==2) {
    tripodMoves = 0;
    tripodFlag = !tripodFlag;
  } 
  delay(500);
}

void spin() {
  
   for(int i=0;i<6;i++) {
    
      if(i%2 == 0 && !tripodFlag) {
        if(flag) {
         setLegServos(i+1, legDrop[i]);
        } else{
          setLegServos(i+1, spinLift[i]);
        }      
      }
     
      if(i%2 != 0 && tripodFlag){
        if(flag) {
         setLegServos(i+1, legDrop[i]);
        } else{
          setLegServos(i+1, spinLift[i]);
        }   
      }
  
   
  }
  flushCode();
  flag = !flag;
  tripodMoves++;
  if(tripodMoves ==2) {
    tripodMoves = 0;
    tripodFlag = !tripodFlag;
  } 
  delay(2000);
}

// Right now considering linear motion only. NOOB
void setLeg(int leg, float pos) {
  int servo[3];
  int servoRange[3];
  int servoStart[3];
  int servoVal[3];
  pos = 100-pos;
  
  for(int i=0; i<3;i++) {
    servo[i] = 3*(leg-1) + i;
    servoStart[i] = rangeMax[servo[i]] + (dir[i] * offsetMax[i]);
    servoRange[i] =  abs((rangeMax[servo[i]] + (dir[i] * offsetMax[i]))   - (rangeMin[servo[i]] - (dir[i] * offsetMin[i])));
    servoVal[i] = servoStart[i] + (pos/100.0 * (float)servoRange[i]);
    servoCode[servo[i]] =  servoVal[i];
  }
    
}

// Right now considering linear motion only. NOOB
void setLegServos(int leg,  int pos[6]) {
  int servo[3];
  int servoRange[3];
  int servoStart[3];
  int servoVal[3];
  
  for(int i=0; i<3;i++) {
    servo[i] = 3*(leg-1) + i;
    servoStart[i] = rangeMax[servo[i]] + (dir[i] * offsetMax[i]);
    servoRange[i] =  abs((rangeMax[servo[i]] + (dir[i] * offsetMax[i]))   - (rangeMin[servo[i]] - (dir[i] * offsetMin[i])));
    servoVal[i] = servoStart[i] + dir[servo[i]] * ((100-pos[i*2+1])/100.0 * (float)servoRange[i]);
    if(pos[i*2] == 1) {
      servoCode[servo[i]] = servoVal[i];
    }
  }
    
}

// Right now considering linear motion only. NOOB
void adjustLegServos(int leg,  int pos[6]) {
  int servo[3];
  int servoRange[3];
  int servoStart[3];
  int servoVal[3];
  
  for(int i=0; i<3;i++) {
    servo[i] = 3*(leg-1) + i;
    servoStart[i] = rangeMax[servo[i]] + (dir[i] * offsetMax[i]);
    servoRange[i] =  abs((rangeMax[servo[i]] + (dir[i] * offsetMax[i]))   - (rangeMin[servo[i]] - (dir[i] * offsetMin[i])));
    servoVal[i] = servoStart[i] + dir[servo[i]] * ((100-pos[i*2+1])/100.0 * (float)servoRange[i]);
    if(pos[i*2] == 1) {
      servoSweep[servo[i]] = 100-pos[i*2+1];
      servoCode[servo[i]] = servoVal[i];
    }
  }
    
}
void addCode(int servo, int pwm) {
   if(servo > 0  && pwm >600 && pwm <2400 && servo <19 ) {
     for(int i=1;i<19;i++) {
       
     }
     Serial.print("#");
     Serial.print(servo);
     Serial.print("P"); 
     Serial.print(pwm);
   }
}

   void flushCode() { 
    for(int i=0;i<18;i++) {
       if( servoCode[i] >600 && servoCode[i] <2400 ) {
         Serial.print("#");
         Serial.print(i+1);
         Serial.print("P"); 
         Serial.print(servoCode[i]);
       }
     }
     Serial.print("T"); 
     Serial.println(interval);
     Serial.print(0x0d); Serial.print(0x0a);
     
}
