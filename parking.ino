//      ▲▲▲▲▲▲ CODE FINAL PARKING INTELLIGENT▼▼▼▼▼▼
#include <Wire.h>

#include <Servo.h>

#include <HCSR04.h>

#include <LiquidCrystal_I2C_Hangul.h>

UltraSonicDistanceSensor capE(D4, D3);
UltraSonicDistanceSensor capS(D6, D5);

LiquidCrystal_I2C_Hangul lcd(0x27,16,2);

Servo servonaka;

int Total = 5;
int Libre;
int pos = 0;
int f1 = 0;
int f2 = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("ISPM");
  lcd.setCursor(1,1);
  lcd.print("PARKING ESIIA");
  delay(2000);
  lcd.clear();
  servonaka.attach(D7);
  servonaka.write(0);
  
  Libre = Total;
}

void loop() {
  if(capE.measureDistanceCm() < 10 && f1==0 ){
    if(Libre>0){
      f1=1;
      if(f2==0){
        //servonaka.write(100);
        for(pos=0;pos<=100;pos+=5)
          servonaka.write(pos);
        Libre = Libre-1;
      }
    }else{
        lcd.setCursor(0,0);
        lcd.print("~PARKING PLEIN~");
        lcd.setCursor(0,1);
        lcd.print("~~PARKING FULL~~");
        while(capE.measureDistanceCm() < 10){
          continue;
        }
        delay(1000);
        lcd.clear();
      }
  }

  if(capS.measureDistanceCm() < 10 && f2==0 ){
      f2=1;
      if(f1==0){
        //servonaka.write(100);
        for(pos=0;pos<=100;pos+=5)
          servonaka.write(pos);
        Libre = Libre+1;
      }
    }
    if(f1==1 && f2==1){
      delay(1000);
      //servonaka.write(0);
      for(pos=100;pos>=0;pos-=5)
          servonaka.write(pos);
      f1=0;
      f2=0;
    }
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Total");
  lcd.setCursor(8,0);
  lcd.print("Libre");
  lcd.setCursor(1,1);
  lcd.print(Total);
  lcd.setCursor(8,1);
  lcd.print(Libre);
  delay(500);
  
}