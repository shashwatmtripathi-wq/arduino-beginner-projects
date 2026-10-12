#include <LiquidCrystal.h>

int rs = 9;
int e = 8;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
  
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

int buzzPin = 7;
int upButton = 10 ;

int currentTime[4];
int alarmTime[4];

void presentTime(int *p) ;
void alertTime(int *a) ;
void displayCurrentTime(int *dc) ;
void displayAimedTime(int *da) ;
void updateTime(int array[4]) ;
void checkTime(int array1[4] , int array2[4]);

void setup() {
Serial.begin(9600);
lcd.begin(16,2);
pinMode(buzzPin , OUTPUT);
pinMode(upButton , INPUT_PULLUP);
presentTime(currentTime) ;
alertTime(alarmTime) ;

}

void loop() {
 delay(60000) ;
 updateTime(currentTime) ; 
 checkTime(currentTime , alarmTime) ;
}

void presentTime(int *p){
  int hourEntered ;
  int minEntered ; 
  Serial.println("Enter the Present Time  ");
  Serial.print("Current Hour (in hh) : ") ;
  while(Serial.available()==0){

  }
 
hourEntered = Serial.parseInt();
Serial.println(hourEntered);
while(Serial.available() > 0){   // flush trailing \r\n
  Serial.read();
}
  if(hourEntered>9){
    *p++ = hourEntered / 10 ;
    *p++ = hourEntered % 10 ;
  }else{
    *p++ = 0 ;
    *p++ = hourEntered ;
  }

  delay(2000); 
  
  Serial.print("Current min (in mm) : ") ;
  while(Serial.available()==0){

  }

minEntered = Serial.parseInt();
Serial.println(minEntered) ;
while(Serial.available() > 0){   // flush trailing \r\n
  Serial.read();
}  
Serial.println(" ");
  if(minEntered>9){
    *p++ = minEntered / 10 ;
    *p++ = minEntered % 10 ;
  }else{
    *p++ = 0 ;
    *p++ = minEntered ;
  } 
  delay(2000); 

  displayCurrentTime(p-4) ;
}

void displayCurrentTime(int *dc){
  lcd.setCursor(0,0);
  lcd.print("Time :");
lcd.setCursor(7,0);
     lcd.print(*dc);
     dc++ ;
  lcd.setCursor(8,0);
     lcd.print(*dc);
     dc++ ;
  lcd.setCursor(9,0);
     lcd.print(":");
  lcd.setCursor(10,0);
     lcd.print(*dc);
     dc++ ;
  lcd.setCursor(11,0);
     lcd.print(*dc);
} 

void alertTime(int *a){
int hourEntered ;
int minEntered ; 
  Serial.println("Enter the Alarm Time  ");
  Serial.print("Aimmed Hour (in hh) : ") ;
  while(Serial.available()==0){

  }

hourEntered = Serial.parseInt();
Serial.println(hourEntered);
while(Serial.available() > 0){   // flush trailing \r\n
  Serial.read();
} 
  if(hourEntered>9){
    *a++ = hourEntered / 10 ;
    *a++ = hourEntered % 10 ;
  }else{
    *a++ = 0 ;
    *a++ = hourEntered ;
  }

  delay(2000); 
  
  Serial.print("Aimed min (in mm) : ") ;
  while(Serial.available()==0){

  }

  minEntered = Serial.parseInt() ; 
  Serial.print(minEntered) ;
  if(minEntered>9){
    *a++ = minEntered / 10 ;
    *a++ = minEntered % 10 ;
  }else{
    *a++ = 0 ;
    *a++ = minEntered ;
  } 
  delay(2000); 

  displayAimedTime(a-4) ;
}

void displayAimedTime(int *da){
  lcd.setCursor(0,1);
  lcd.print("Alarm :");
    lcd.setCursor(8,1);
     lcd.print(*da);
     da++ ;
  lcd.setCursor(9,1);
     lcd.print(*da);
     da++ ;
  lcd.setCursor(10,1);
     lcd.print(":");
  lcd.setCursor(11,1);
     lcd.print(*da);
     da++ ;
  lcd.setCursor(12,1);
     lcd.print(*da);
}

void updateTime(int array[4]){
  if(array[3]<9){
    array[3]++ ;
  }else if(array[3]>=9 && array[2]<5){
    array[3] = 0 ;
    array[2] ++ ;
  }else if(array[3]>=9 && array[2]>= 5 && array[1]<9){
    array[3] = 0 ;
    array[2] = 0 ;
    array[1] ++ ; 
  }else if(array[3]>=9 && array[2]>=5 && array[1]>=9 && array[0]<2){
    array[3] = 0 ;
    array[2] = 0 ;
    array[1] = 0 ; 
    array[0] ++ ; 
  }else if(array[3]>=9 && array[2]>=5 && array[1]<4 && array[0]>=2){
    array[3] = 0 ;
    array[2] = 0 ;
    array[1] ++ ; 
    array[0] = 2 ;  
  }else if((array[3]>=9 && array[2]>=5 && array[1]>=4 && array[0]>=2) ){
    array[3] = 0 ;
    array[2] = 0 ;
    array[1] = 0 ; 
    array[0] = 0 ;  
  }
  if((array[0]==2 && array[1]==4)){
    array[3] = 0 ;
    array[2] = 0 ;
    array[1] = 0 ; 
    array[0] = 0 ;
  }
  lcd.setCursor(0,0);
  lcd.print("Time :");
  lcd.setCursor(7,0);
     lcd.print(array[0]);
  lcd.setCursor(8,0);
     lcd.print(array[1]);
  lcd.setCursor(9,0);
     lcd.print(":");
  lcd.setCursor(10,0);
     lcd.print(array[2]);
  lcd.setCursor(11,0);
     lcd.print(array[3]);
}

void checkTime(int array1[4] , int array2[4]){
  int count = 0 ;
  for(int i=0 ; i<4 ; i++){
    if(array1[i] == array2[i]){
      count++ ;
    }
  }
  if(count == 4){
    while(digitalRead(upButton)!=0){
      digitalWrite(buzzPin , HIGH);
      delay(500);
      digitalWrite(buzzPin , LOW);
      delay(500);
    }
  }
}