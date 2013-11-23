
int spin1 = 13;
int spin2 = 12;
int spin3 = 11;

int dataPinG = 10;
int dataPinB = 9;
int dataPinR = 8;

int row1 = 7;
int row2 = 6;
int row3 = 5;

int rowVal = 4;

int r = 0;
int g = 1;
int b = 1;

byte alpabet[][8] = { {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
                      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
                    };

byte frame[] = {0x00,0X00,0x00,0x00,0x00,0x00,0x00,0x00 };
byte frame1[] = {0x8F,0X70,0x01,0x30,0x03,0x00,0x00,0x00 };
unsigned long currentMillis = 0;
unsigned long prevMillis = 0;
int interval = 30;

void setup() {
  // put your setup code here, to run once:
 pinMode(spin1 , OUTPUT);
 pinMode(spin2 , OUTPUT);
 pinMode(spin3 , OUTPUT);
  pinMode(row1 , OUTPUT);
 pinMode(row2 , OUTPUT);
 pinMode(row3 , OUTPUT);
  pinMode(rowVal , OUTPUT);
  pinMode(dataPinR , OUTPUT);
  pinMode(dataPinG , OUTPUT);
  pinMode(dataPinB , OUTPUT);
  Serial.begin(9600);
  putByte(0x00, r, g, b, 1);
}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite( rowVal, HIGH);
  //putRow(3);
//putData(3, r, g,b, 1);
//putData(4, r, g,b, 1);
//putData(5, r, g,b, 1);
//putData(6, r, g,b, 1);
//putData(7, r, g,b, 7);
 byte frame1[] = {0x44,0X48,0x50,0x60,0x50,0x48,0x44,0x42 };
 byte frame2[] = {0xFF,0X18,0x18,0x18,0x18,0x18,0x18,0xFF };
 byte frame3[] = {0xc3,0X66,0x24,0x18,0x18,0x24,0x66,0xc3 };
 byte frame4[] = {0xFF,0Xc0,0xc0,0xF8,0xc0,0xc0,0xFF,0xFF };
 byte frame5[] = {0xc3,0X66,0x24,0x18,0x18,0x18,0x18,0x18 };
 byte frame6[] ={0xFF,0Xc0,0xc0,0xF8,0xc0,0xc0,0xFF,0xFF };
  byte frame7[] = {0x00,0X00,0x00,0x3e,0x3e,0x00,0x00,0x00 };
 
 invert(frame1);
 invert(frame2);
 invert(frame3);
 invert(frame4);
 invert(frame5);
 invert(frame6);
 
 append(frame1);
 append(frame2);
 append(frame3);
 append(frame4);
 append(frame5);
 append(frame6);
  append(frame7);
  
    if(b==0) {r=0; b=1; g = 1;} 
  else
  if(g==0) {b = 0; g = 1;}
  else
  if(r==0) { g= 0; r =1;}
 
}

void invert(byte b[]){
  byte temp[] = {0,0,0,0,0,0,0,0};
 for(int i =0;i< 8 ;i++){
   temp[i] = b[7-i];
 }
 for(int i =0;i< 8;i++){
   b[i] = temp[i];
 } 
}

void append(byte data[]) {
  currentMillis = millis();
  prevMillis = currentMillis; 
  byte shift[] = { 0,0,0,0,0,0,0,0};
  int k=0;
  while(k<9) {
     currentMillis = millis();
    if(currentMillis > (prevMillis + interval)) {
      for(int i =0;i<8; i++) {
       
        shift[i] = data[i] & 0x80;
        data[i] = data[i] << 1;
        frame[i] = frame[i] << 1;
        if(shift[i] > 0) {
          frame[i] = frame[i] | 1;
        } else {
         frame[i] = frame[i] | 0;
        }
     /*   byte c= frame[i];
         for(int i=0; i<8; i++) {  
          Serial.print(c%2);      // print the least significant bit
          c /= 2;                 // move to next significant bit
        }
         Serial.println();*/
      }
    //  Serial.println("============");
      k++;
      prevMillis = currentMillis;
    }
    printBuffer();
  }
}

void printBuffer(){
   for(int i =0;i<8;i++) {
     putByte(frame[i], r, g, b,i);           
   }
}
void putByte(byte byteData, byte r, byte g, byte b, byte rowData) {
  int temp =1;
  int value = 0;
  for(int i=0;i<8;i++){
     value = temp & byteData;
    
    if(value != 0) {
      putData(i, r, g,b, rowData);
    } 
    temp = temp << 1;
  }
  
}
  
void putRow(byte channel) {


}

void putData(byte channel,byte red, byte green, byte blue, byte row) {
  byte l0 = channel & 1;
  channel = channel>>1;
  byte l1 = channel & 1;
  channel = channel>>1;
  
  byte l2 = channel & 1;
  channel = channel>>1;
 
  digitalWrite( spin1, l0);
  digitalWrite( spin2, l1);
  digitalWrite( spin3, l2); 
   
  l0 = row & 1;
  row = row>>1;
  l1 = row & 1;
  row = row>>1;
  
  l2 = row & 1;

  digitalWrite( row1, l0);
  digitalWrite( row2, l1);
  digitalWrite( row3, l2);
  
  digitalWrite( dataPinR , red);
  digitalWrite( dataPinB , green);
  digitalWrite( dataPinG , blue);
  delay(1);
} 
