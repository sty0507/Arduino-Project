#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DETECT 3 // Laser module
#define ACTION 5 // Buzzer
#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 9

int but1=0, but2=0, but3=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

//보라색= A4, 파란색= A5
int c = 0, re = 0;
int Total = 0, count= 0;
int tm=30;

void setup(){
  pinMode(BUTTON1, INPUT);//개수 카운트
  pinMode(BUTTON2, INPUT);//초기화 및 나가기(메인 화면)
  pinMode(BUTTON3, INPUT);//시간 측정
  
  pinMode(DETECT, INPUT);
  pinMode(ACTION, OUTPUT);
  
  lcd.init();// I2C LCD를 초기화
  lcd.backlight();// I2C LCD의 백라이트 ON
  
  Serial.begin(9600); 
  lcd.setCursor(0,0);
  lcd.print("Welcome");  
}

void loop(){
  int val1 = digitalRead(BUTTON1);
  int val3 = digitalRead(BUTTON3);
  if(val1 = 0){
    but1 = 1;
  }
  Serial.print("but1: ");
  Serial.println(but1);
  if(val3 == 1){
    but3 == 1;
  }
  while(but1 == 1){
    Laser(DETECT, ACTION);
  }
  while(but3 == 0){
    Count();
  }
  delay(100);
}

void Reset_Total(){
  Total = 0;
  lcd.setCursor(0,1);
  lcd.print(Total);
  return;
}

void Reset_time(){
  tm = 0;
  lcd.setCursor(0,1);
  lcd.print(tm);
  return;
}

void Laser(int a, int b){
 
      int detected = digitalRead(a);// read Laser sensor
      int val2 = digitalRead(BUTTON2);
      int v = 0;
      if(val2 == 1){
        v = 1;
      }
      lcd.setCursor(0,0);
      lcd.print("How many?"); 
      if(v == 1){
        Reset_Total();
        return;
      }
      if( detected == HIGH)
      {
        //digitalWrite(b,HIGH);// set the buzzer ON 기본 
        lcd.setCursor(0,1); 
        lcd.print(Total);
        c = -1;
      }
      else{
        //digitalWrite(b,LOW); // Set the buzzer OFF 닿으면
        if(c == -1){
          delay(250);
          c = 1;
          Total++;
          lcd.setCursor(0,1);
          lcd.print(Total);
        }
      }
      delay(250);
      re = 1;
  return;
}

void Count(){
  int val = digitalRead(BUTTON2);
  int val1 = digitalRead(BUTTON3);
  if(val == HIGH){
    Reset_time();
  }
  if(val1 == HIGH){
    tm = tm + 30;
  }
  while(val == HIGH){
    lcd.setCursor(0,0);
    lcd.print("time is");
    lcd.setCursor(1,1);
    lcd.print(tm);
    tm--;
    if(tm < 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("time over");
      return;
    }
    delay(1000);
  }
  return;
}
