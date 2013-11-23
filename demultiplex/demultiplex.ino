
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
}

void loop() {
  // put your main code here, to run repeatedly: 
digitalWrite( rowVal, HIGH);
  //putRow(3);
  for(int j = 0; j< 8;j++) {
  for(int i =0; i< 8;i++) {
   
   putData(i, r, g,b, j);
   delay(10);
   putData(8-i, b, r,g, j);
   delay(40);
  }
  }
  //delay(10);
  if(b==0) {r=0; b=1; g = 1;} 
  else
  if(g==0) {b = 0; g = 1;}
  else
  if(r==0) { g= 0; r =1;}
  
}

void putByte(byte byteData) {
  
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
} 
