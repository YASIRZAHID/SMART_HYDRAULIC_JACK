// Analog Pin 4 - SDA
// Analog pin 5 - SCL

#include <servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#define TRIGGER_PIN  10
#define ECHO_PIN     13
#define MAX_DISTANCE 400
int distancei,distancer;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo mysevo;

void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  
  distancer = sonar.ping_cm();
  distancei = analogRead(A1);
  led_value = map(distancei, 0, 1023, 0, 255);
  if(distancer>2 && distancer<15){
    analogWrite(9, 255);
    delay(100);
    };
  if(distancer == distancei){
    analogWrite(9, 0);
    delay(100);
    };  
  
  if (distance >= 20 || distance <= 2) {       // CODE TO PRINT HEIGHT JACK REACHED
    lcd.setCursor(4,0);
    lcd.print("OUT OF RANGE");
  }
  else {
    lcd.setCursor(4,0);
    lcd.print("DISTANCE:    ");
    lcd.setCursor(4,1);
    lcd.print(distancer);
  }
  delay(50);
  
  if(digitalRead(2)==HIGH){                       // CODE TO LOWER THE JACK WHEN BUTTON ATTACHED AT BUTTON 2 IS PRESSED 
    myservo.write(180):
    lcd.setCursor(1,0);
    lcd.print("LOWERING JACK");
    delay(2000);
    }
}
