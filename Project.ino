#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DETECT 3 // Laser module
#define ACTION 5 // Buzzer
#define BUTTON1 7 // val1 -> 1번
#define BUTTON2 8 // val2 -> 2번
#define BUTTON3 9 // val3 -> 3번

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

    lcd.backlight();// I2C LCD의 백라이트 ON
  
  Serial.begin(9600); 
  lcd.setCursor(0,0);
  lcd.print("Welcome");  
  lcd.init();
}

void loop(){
    lcd.setCursor(0,0);
    lcd.print("1.L 2.R 3.C");
    int val1 = digitalRead(BUTTON1);
    int val3 = digitalRead(BUTTON3);
    int x =0, y=0;
    if(val1 == 1){
      but1 = 1;
    }
    if(val3 == 1){
      but3 = 1;
    }
    if(but1 == 1){
      but1=0;
      while(1){
        x = Laser(DETECT, ACTION);
        if(x)
          return;
      }
    }
    Total = 0;
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("1.L 2.R 3.C");

    if(but3 == 1){
      but3 = 0;
      while(1){
         y = Count();
         if(y){
          return;
         }
      }
    }
    lcd.init();
    delay(250);
    lcd.setCursor(0,0);
    lcd.print("1.L 2.R 3.C");
    delay(100);
}
int Laser(int a, int b){ 
      int detected = digitalRead(a);// read Laser sensor
      int val1 = digitalRead(BUTTON1);
      int val2 = digitalRead(BUTTON2);
      int val3 = digitalRead(BUTTON3);
      lcd.clear();
      if(val3 == 1){
        return 1;
      }
      if(val2 == 1){
        lcd.init();
        Total = 0;
      }
      lcd.setCursor(0,0);
      lcd.print("How many?"); 
      if( detected == HIGH)
      {
        lcd.setCursor(0,1); 
        lcd.print(Total);
        c = -1;
      }
      else{
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
  return 0;
}

int Count(){
    int val = digitalRead(BUTTON2);
    int val1 = digitalRead(BUTTON3);
    while(1){
      lcd.init();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("time is");
      lcd.setCursor(0,1);
      lcd.print(tm);
      tm--;
      if(tm < 0){
        lcd.init();
        lcd.setCursor(0,0);
        lcd.print("time over");
        tm = 30;
        delay(250);
        lcd.init();
        return 1;
      }
      else
        delay(200);
    }
    return 1;
}
