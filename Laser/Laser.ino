#define BUTTON 7
#define BUTTON1 8

int but1=0, but2=0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int val1 = digitalRead(BUTTON);
  int val2 = digitalRead(BUTTON1);
  Serial.print("val1: ");
  Serial.println(val1);
  if(val1 == 1){
    but1 = 1;
  }
  if(val2 == 1){
    but1 = 0;
  }
  if(but1 == 1){
    lcd();
  }
  Serial.print("but1: ");
  Serial.println(but1);
  delay(100);
}

void lcd(){
  Serial.print("Come on!");
  int a = 1;
  int val1 = digitalRead(BUTTON);
  if(val1 == 1){
    a = 0;
  }
  if(a == 0){
    return;
  }
}
