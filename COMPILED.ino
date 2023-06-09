#include <Servo.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#define TRIGGER_PIN  11
#define ECHO_PIN     12
#define POT_PIN      A0
#define MAX_DISTANCE 20
#define D1           3
#define D2           4

int distancei,distancer,run_value;
int operate = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
//
void loop() {  
    if(digitalRead(2)==HIGH){                       // CODE TO LOWER THE JACK WHEN BUTTON ATTACHED AT BUTTON 2 IS PRESSED 
    myservo.write(180);
//    delay(5000);
    lcd.setCursor(0,0);
    lcd.print("PISTON UNLOCK  ");
    operate=1;
    delay(1000);
    }
    
    if(digitalRead(2)==LOW){                       // CODE TO LOWER THE JACK WHEN BUTTON ATTACHED AT BUTTON 2 IS PRESSED 
    myservo.write(0);
//    delay(5000);
    lcd.setCursor(0,0);
    lcd.print("CYLINDER LOCKED");
    delay(10000);
    operate=0;
    }

    if(operate == 1){
    for(int i=0;i<10;i++){  
    distancei = analogRead(POT_PIN);
    run_value = map(distancei, 0, 1023, 0, 15);
    lcd.setCursor(0,1);
    lcd.print("SET:  ");
    lcd.setCursor(4,1);
    lcd.print(run_value);
    delay(200);
    }
    distancer = sonar.ping_cm();
    lcd.setCursor(7,1);
    lcd.print("PAST=   ");
    lcd.setCursor(13,1);
    lcd.print(distancer);
    
    if(distancer < run_value){
    while(distancer < run_value){  
      lcd.setCursor(0,0);
      lcd.print("RAISING        ");
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      distancer = sonar.ping_cm();
      distancei = analogRead(POT_PIN);
      run_value = map(distancei, 0, 1023, 0, 16);
      lcd.setCursor(0,1);
      lcd.print("SET:  ");
      lcd.setCursor(4,1);
      lcd.print(run_value);
    }
      };
    if(distancer > run_value){
      lcd.setCursor(0,0);
      lcd.print("RAISED         ");
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      delay(1000);
      };
    }else{
      lcd.setCursor(0,1);
      lcd.print("UNLOCK CYLINDER..");
      delay(1000);
      };  
}
