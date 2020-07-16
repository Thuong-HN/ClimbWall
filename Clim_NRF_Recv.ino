#include<Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define CE_PIN   7//Note
#define CSN_PIN 8
const uint64_t pipe = 0xE8E8F0F0E3LL;
RF24 radio(CE_PIN, CSN_PIN);
Servo ESC;
int packet_receive [5];
int set_point_forward,set_point_behind,set_point_right,set_point_left,set_point_gas;
int toogle, dem=1;
void setup() {
  Serial.begin(9600); 
  setup_rf();
  ESC.attach(9);//delay(50);
  ESC.writeMicroseconds(1000);
  //sTop();
}

void loop() {
  read_rf() ;

}
void setup_rf()//=============setup_RF=========================================
{
   radio.begin();
   radio.openReadingPipe(1,pipe);
   radio.startListening();   
}//=============end_setup_RF===================================================
void read_rf()//========read_RF=========================================
{
  if ( radio.available())
  { 
    radio.read(packet_receive,sizeof(packet_receive));

    set_point_forward=int(packet_receive[0]);
    set_point_behind=int(packet_receive[1]);
    set_point_left=int(packet_receive[2]);  
    set_point_right=int(packet_receive[3]  );  
    set_point_gas=int(packet_receive[4]);
//    Serial.print(set_point_forward);Serial.print('\t');
//    Serial.print(set_point_behind);  Serial.print('\t');
//    Serial.print(set_point_left); Serial.print('\t');
//    Serial.print(set_point_right);Serial.print('\t');
    Serial.print(set_point_gas);Serial.print('\t');
    if(set_point_forward == 1){
      forWard(); 
    }
    else if(set_point_behind == 1 ){
      beHind(); 
    }
    else if(set_point_left == 1){
      turnLeft(); 
      
    }
    else if(set_point_right == 1 ){
      turnRigh(); 
    }
    else sTop();

    if(set_point_gas==0){
      if(toogle==0){
      toogle=1;
      dem=-dem;
      }
    }
    else if(set_point_gas==1){
      if(toogle==1){
      toogle=0;     
      }
    }
    Serial.println(dem);
    if(dem==1){
      ESC.writeMicroseconds(1000);
     // toogle=0;
      Serial.println("Min");
    }
    else if(dem==-1){
      ESC.writeMicroseconds(2500);
      //dem=0;
      Serial.println("Max");
    }
//    else Serial.println("Max");ESC.writeMicroseconds(1200);
  //ESC.writeMicroseconds(1000);
  }

 // else ESC.writeMicroseconds(1000);sTop();toogle=0;
  
}//==============end_read_RF===========================================


 void forWard(void)  
{
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  analogWrite(6, 255);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  analogWrite(5, 255);
}
 void beHind(void)  
 {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  analogWrite(6, 255);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  analogWrite(5, 255);
}

 void sTop(void)  
 {
 analogWrite(6, 0);
 analogWrite(5, 0);
}
void turnLeft(void)  
{
  
  analogWrite(5, 0);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  analogWrite(6, 255);
}
void turnRigh(void)  
{
  analogWrite(6, 0);
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  analogWrite(5, 255);
}

