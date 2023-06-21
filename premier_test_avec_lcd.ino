#include <LiquidCrystal_I2C_Hangul.h>
#include <HCSR04.h>
#include <Servo.h>

UltraSonicDistanceSensor capE(D4, D3);
UltraSonicDistanceSensor capS(D6, D5);

   
LiquidCrystal_I2C_Hangul lcd(0x27,16,2);

bool v1 = false;
int Total = 5;
int Libre;


Servo servonaka;

void setup() {

 Serial.begin(9600);
 Libre = Total;
 lcd.init();
 lcd.backlight();
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("ISPM");
 lcd.setCursor(1,1);
 lcd.print("PARKING ESIIA");
 delay(2000);
 lcd.clear();
 lcd.setCursor(1,0);
 lcd.print("Total");
    lcd.setCursor(8,0);
    lcd.print("Libre");
    lcd.setCursor(1,1);
    lcd.print(Total);
    lcd.setCursor(8,1);
    lcd.print(Libre);
 servonaka.attach(D7);
 servonaka.write(0);
 

}

void loop() {
 if(capE.measureDistanceCm() < 10 && Libre > 0){
    if (Libre > 0){
      servonaka.write(100);
    } else {
       lcd.clear();
       lcd.setCursor(1,0);
       lcd.print("FENO IO");
       lcd.setCursor(1,1);
       lcd.print("BAINA A");
  }}
 if(capS.measureDistanceCm() < 10){
    servonaka.write(0);
    Libre -= 1;
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Total");
    lcd.setCursor(8,0);
    lcd.print("Libre");
    lcd.setCursor(1,1);
    lcd.print(Total);
    lcd.setCursor(8,1);
    lcd.print(Libre);    
  }
  //Serial.println(capE.measureDistanceCm());
  //Serial.println(capS.measureDistanceCm());
  

 /* switch(v1){
    case true : servonaka.write(100);break;
    case false : servonaka.write(0);break;
  }*/
  
while(capE.measureDistanceCm() < 10 || capS.measureDistanceCm() < 10){
  continue;
  
}
  delay(1000);
}