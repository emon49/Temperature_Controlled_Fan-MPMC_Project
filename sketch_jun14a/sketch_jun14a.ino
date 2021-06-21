#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int tempPin = A0; 
int fan = 11;
int buzzer = 13;   
int temp;
int tempMin = 30;
int tempMax = 50;
int fanSpeed;
int fanLCD;

void setup() {
pinMode(fan, OUTPUT);
pinMode(buzzer, OUTPUT);  
pinMode(tempPin, INPUT);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print(" WELCOME To Temp");
lcd.setCursor(0,1);
lcd.print("Control Fan System");
delay(2000);
lcd.clear();
}

void loop() {
  temp = readTemp();
  if((temp >= tempMin) && (temp <= tempMax)) {
       fanSpeed = map(temp, tempMin, tempMax, 32, 255);
       fanLCD = map(temp, tempMin, tempMax, 0, 100);
       analogWrite(fan, fanSpeed);
   } 
   if(temp < tempMin) {
    fanSpeed = 0;
    fanLCD = 0; 
    digitalWrite(fan, LOW);       
   } 
   
   if(temp > tempMax) {
    digitalWrite(fan, HIGH); 
    digitalWrite(buzzer, HIGH);
   } else {
     digitalWrite(buzzer, LOW); 
   }
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temp);
  lcd.write(223);
  lcd.print("C  ");
   
  lcd.setCursor(0,1);
  lcd.print("Fan Speed:");
  lcd.print(fanLCD);
  lcd.print("%   ");
  delay(200);
}

int readTemp() {
  temp = analogRead(tempPin);
  return temp * 0.48828125;
}
