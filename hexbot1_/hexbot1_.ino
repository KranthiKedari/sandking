
int rangeMax[18] = {700, 1300, 800, 1200, 1400, 2200, 900, 1800, 800, 2200, 1800, 800, 1700, 1400, 2200, 2200, 1300, 800};
int rangeMin[18] = {1500, 2200, 2100, 1800, 2300, 700, 1700, 900, 2200, 1200, 900, 2100, 2200, 1800, 700, 1300, 2200, 2200};

int dir[18] = {1, 1, 1, 1, 1, -1, 1, -1, 1, -1, -1, 1, 1, 1, -1, -1, 1, 1};

int interval = 300;

int offsetMax[3] = {100, 100, 100};
int offsetMin[3] = {200, 200, 200};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 // Serial.println("#DISABLE"); 
}

String code;
void loop() {
  // put your main code here, to run repeatedly: 
  
  setLeg(1, 10);
  
  
}

void centerLeg(int leg) {
}

void liftLeg(int leg) {
  int servoa = 3*(leg-1) + 1;
  int servob = 3*(leg-1) + 2;
  int servoc = 3*(leg-1) + 3;
  
  int mid = abs((rangeMax[servoa - 1] - rangeMin[servoa - 1])/2);
  int servoaVal =  rangeMax[servoa - 1] + ( dir[servoa-1] * mid);
  int servobVal = rangeMax[servob - 1] + (dir[servob -1] * offsetMax[1]);
  int servocVal = rangeMax[servoc - 1] + (dir[servoc -1] * offsetMax[2]);
  
addCode(servoc, servocVal, interval);
addCode(servob, servobVal, interval);
addCode(servoa, servoaVal, interval);

  
  
}


// Right now considering linear motion only. NOOB
void setLeg(int leg, float pos) {
  int servo[3];
  int servoRange[3];
  int servoStart[3];
  int servoVal[3];
  
  for(int i=0; i<3;i++) {
    servo[i] = 3*(leg-1) + i;
    servoStart[i] = rangeMax[servo[i]] + (dir[i] * offsetMax[i]);
    servoRange[i] =  abs((rangeMax[servo[i]] + (dir[i] * offsetMax[i]))   - (rangeMin[servo[i]] - (dir[i] * offsetMin[i])));
    servoVal[i] = servoStart[i] + (pos/100.0 * (float)servoRange[i]);
    addCode(servo[i] + 1, servoVal[i]);
  }
    
}

void addCode(int servo, int pwm) {
   if(servo > 0  && pwm >600 && pwm <2400 && servo <19 ) {
     Serial.print("#");
     Serial.print(servo);
     Serial.print("P"); 
     Serial.print(pwm);
   }
}

void flushCode() {
     Serial.print("T"); 
     Serial.println(interval);
     Serial.print(0x0d); Serial.print(0x0a);
}
