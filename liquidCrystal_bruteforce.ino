const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

int i;
int iVoltage;
int c1iVoltage;
int c2iVoltage;
int c3iVoltage;
int c4iVoltage;
float fVoltage;

void setup(){
  Serial.begin(9600);
  pinMode(RS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
  //Set Enable 0
  digitalWrite(EN, 0);
  //delay before send
  delay(15);
  //send command 0x30 delay 20ms for 3 times
  //RS DB7 DB6 DB5 DB4
  //0   0   0   1   1
  for(i = 0; i < 3; i++){
  digitalWrite(EN, 1);  
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 1);
  delay(20);
  digitalWrite(EN, 0);
  }
  //Function set
  
  //set interface data lengeth 4 bit
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);
  delay(20);
  digitalWrite(EN, 0);
  
  //set interface data lengeth 4 bit
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 1);
  digitalWrite(D4, 0);// DL : 4bits / 8bits
  delay(20);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 1);//set number display line (DB7): 0 ( 1 line ) 1 ( 2 lines)
  digitalWrite(D6, 1);//set display font type (DB6): 0 ( 5x8 dots ) 1 ( 5x11 dots )
  digitalWrite(D5, 0);// D5 **
  digitalWrite(D4, 0);// D4 **
  delay(20);
  digitalWrite(EN, 0);
  
  //Display on/off control
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  delay(20);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 1);//D3
  digitalWrite(D6, 1);//Set Display (D2)
  digitalWrite(D5, 0);//Set Cursor (D1)
  digitalWrite(D4, 0);//Set Blinking of cursor (D0)
  delay(20);
  digitalWrite(EN, 0);
  
  //Clear Display
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  delay(20);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);//D3
  digitalWrite(D6, 0);//D2
  digitalWrite(D5, 0);//D1
  digitalWrite(D4, 1);//D0
  delay(20);
  digitalWrite(EN, 0);
  
  //Entry mode set
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  delay(20);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);//D3
  digitalWrite(D6, 1);//D2
  digitalWrite(D5, 1);//D1 I/D=0 means the cursor position is decremented (moves right to left). 
                        // I/D=1 means the cursor position is incremented (moves left to right).
  digitalWrite(D4, 0);//D0 S=0 means normal operation, the display remains still, and the cursor moves.
                         //S=1 means the display moves with the cursor.
  delay(20);
  digitalWrite(EN, 0);
}

void cleary(void){
//Clear Display
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);
  digitalWrite(D6, 0);
  digitalWrite(D5, 0);
  digitalWrite(D4, 0);
  delay(1000);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 0);
  digitalWrite(D7, 0);//D3
  digitalWrite(D6, 0);//D2
  digitalWrite(D5, 0);//D1
  digitalWrite(D4, 1);//D0
  delay(1000);
  digitalWrite(EN, 0);
}

char convertInttoChar(int iNum){
 switch(iNum){
   case 0: return '0';
   case 1: return '1';
   case 2: return '2';
   case 3: return '3';
   case 4: return '4';
   case 5: return '5';
   case 6: return '6';
   case 7: return '7';
   case 8: return '8';
   case 9: return '9';

 } 
}

void convertChartoBit(char cC){
boolean bD7;
boolean bD6;
boolean bD5;
boolean bD4;
boolean bD3;
boolean bD2;
boolean bD1;
boolean bD0;

 bD7 = cC&0b10000000;
 bD6 = cC&0b01000000;
 bD5 = cC&0b00100000;
 bD4 = cC&0b00010000;
 bD3 = cC&0b00001000;
 bD2 = cC&0b00000100;
 bD1 = cC&0b00000010;
 bD0 = cC&0b00000001;
 
  digitalWrite(EN, 1);
  digitalWrite(RS, 1);
  digitalWrite(D7, bD7);
  digitalWrite(D6, bD6);
  digitalWrite(D5, bD5);
  digitalWrite(D4, bD4);
  delay(5);
  digitalWrite(EN, 0);
  
  digitalWrite(EN, 1);
  digitalWrite(RS, 1);
  digitalWrite(D7, bD3);//D3
  digitalWrite(D6, bD2);//D2
  digitalWrite(D5, bD1);//D1
  digitalWrite(D4, bD0);//D0
  delay(5);
  digitalWrite(EN, 0);
}

void loop(){
  iVoltage = analogRead(A0);

  convertChartoBit('S');
  convertChartoBit('e');
  convertChartoBit('n');
  convertChartoBit('s');
  convertChartoBit('o');
  convertChartoBit('r');
  convertChartoBit(':');

  convertChartoBit(convertInttoChar(iVoltage/1000));
  convertChartoBit(convertInttoChar(iVoltage%1000 /100));
  convertChartoBit(convertInttoChar(iVoltage%100 /10));
  convertChartoBit(convertInttoChar(iVoltage%10));
  for( i = 0 ; i < 29 ; i++)
  convertChartoBit(' ');
  
  fVoltage = iVoltage/1023.0 * 5.0;
  
  convertChartoBit('V');
  convertChartoBit('o');
  convertChartoBit('l');
  convertChartoBit('t');
  convertChartoBit('a');
  convertChartoBit('g');
  convertChartoBit('e');
  convertChartoBit(':');
  convertChartoBit(convertInttoChar(fVoltage));
  convertChartoBit('.');
  convertChartoBit(convertInttoChar(int(fVoltage*10)%10));
  convertChartoBit(convertInttoChar(int(fVoltage*100)%10));
  for( i = 0 ; i < 28 ; i++)
  convertChartoBit(' ');
  

}
