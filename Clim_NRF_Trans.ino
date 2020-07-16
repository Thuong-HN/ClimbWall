#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8
#define Y A0 // X
#define X A1 // Y
#define Gas 5



const uint64_t pipe = 0xE8E8F0F0E3LL;
RF24 radio(CE_PIN, CSN_PIN);

int gui[5];
int adc_x,adc_y,digital_gas;
int set_point_forward,set_point_behind,set_point_right,set_point_left,set_point_northeast,set_point_southeast,set_point_southwest,set_point_northwest;

void setup()
{
  //
  radio.begin();
  radio.openWritingPipe(pipe);
  Serial.begin(9600);
  pinMode(Gas, INPUT_PULLUP);
    
}

void loop()
{
  adc_x = analogRead(X);//gia tri o giua
  adc_y = analogRead(Y);
  digital_gas = digitalRead(Gas);
  Serial.print(adc_x);Serial.print('\t');
  Serial.print(adc_y);Serial.print('\t');
  //Serial.print(digital_gas);Serial.print('\t');
  
  
  if(adc_x>600){
    set_point_forward=1;
  }
  
  if(adc_x<400){
    set_point_behind=1;
  }
  
  if(adc_y>600){
    set_point_right=1;
  }
  
  if(adc_y<400){
    set_point_left=1;
  }
  
  gui[0] = set_point_forward;
  gui[1] = set_point_behind; 
  gui[2] = set_point_left;
  gui[3] = set_point_right;  
  gui[4] = digital_gas;
  radio.write(gui, sizeof(gui) );

 
 Serial.print(gui[0]);Serial.print('\t');
 Serial.print(gui[1]);  Serial.print('\t');
 Serial.print(gui[2]);Serial.print('\t');
 Serial.print(gui[3]);Serial.print('\t');
 Serial.println(gui[4]);
  set_point_forward=0;
  set_point_behind=0;
  set_point_left=0;
  set_point_right=0;
}


 

