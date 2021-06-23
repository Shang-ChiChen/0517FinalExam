#define B2 123
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 524
int buzzer = 14;

int latchPin = 10;
int clockPin = 12;
int dataPin = 11;

int btn_C4 = 9;
int btn_D4 = 8;
int btn_E4 = 7;
int btn_F4 = 6;
int btn_G4 = 5;
int btn_A4 =4;
int btn_B4 =3;
int btn_C5 =2;

long previousTime = 1,
     currentTime = 1;
int count=0;

int btnState[8]={1,1,1,1,1,1,1,1}, prevBtnState[8]={1,1,1,1,1,1,1,1};

int note[8]={C5,B4,A4,G4,F4,E4,D4,C4};

byte scan[8]={
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};

byte canvas[8]={0};

void draw(){
  for(int i = 0;i<8;i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, scan[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, canvas[i]);
    digitalWrite(latchPin,HIGH);
  }
}
void update(){
  for(int i=0;i<8;i++){
    btnState[i]=digitalRead(2+i);//btnState:0 down
    Serial.println(btnState[i]);
  	if(prevBtnState[i]==1 && btnState[i]==0){
      if(count==8){
        for(int j=0; j<8;j++){
          canvas[j]=0;
      	}
        count=0;
      }
      canvas[i]+=128/pow(2,(count));
      tone(buzzer,note[i]);
      count++;
 	 }
  	if(prevBtnState[i]==0 && btnState[i]==1){
      noTone(buzzer);
  	}
  	if(btnState[i]!=prevBtnState[i]){
      delay(35);
  	}
  	prevBtnState[i] = btnState[i];
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(btn_C4,INPUT_PULLUP); 
  pinMode(btn_D4,INPUT_PULLUP); 
  pinMode(btn_E4,INPUT_PULLUP); 
  pinMode(btn_F4,INPUT_PULLUP); 
  pinMode(btn_G4,INPUT_PULLUP); 
  pinMode(btn_A4,INPUT_PULLUP); 
  pinMode(btn_B4,INPUT_PULLUP); 
  pinMode(btn_C5,INPUT_PULLUP); 
  pinMode(buzzer,OUTPUT);
}
int n=0;
void loop(){
  update();
  draw();
  //delay(1000);
}
