#include <Keypad.h>
#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
 
#define I2C_ADDR 0x27 //LCD i2c 
#define BUZZER_PIN 13 
 
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

 
virtuabotixRTC myRTC(2, 3, 4); //Wiring of the RTC (SCL,I/O,RST)
                               //If you change the wiring change the pins here also
 
 
const byte numRows= 4; 
const byte numCols= 4;

char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
 
 
byte rowPins[numRows] = {12,11,10,9}; //Rows 0 to 3 
byte colPins[numCols]= {8,7,6,5}; //Columns 0 to 3
 
int i1,i2,i3,i4;
char c1,c2,c3,c4;
char keypressed,keypressedx;
 
int A_hour=NULL;
int A_minute=NULL;
int B_hour=NULL;
int B_minute=NULL;
int C_hour=NULL;
int C_minute=NULL;
int AlarmIsActive1=NULL;
int AlarmIsActive2=NULL;
int AlarmIsActive3=NULL;
 

 
 
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
 
 
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.init();      
  lcd.backlight();  
                                                   
}
 
void loop() {     
 setAlarm();
}

void setAlarm(){
  while(keypressed == NO_KEY){ 
  keypressed = myKeypad.getKey();
  lcd.clear();
  myRTC.updateTime();
 
  if(myRTC.hours==A_hour && myRTC.minutes==A_minute && AlarmIsActive1==1){
    while(keypressedx == NO_KEY){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Medication Time!!!");  
    digitalWrite(BUZZER_PIN, HIGH);
    keypressedx = myKeypad.getKey();
    }
    if (keypressedx == 'D')
             {
              digitalWrite(BUZZER_PIN, LOW);
              lcd.clear();
              lcd.print("Alarm deactivated");
              AlarmIsActive1=0;
              keypressed=NO_KEY;
              delay(1000);
             }
  }

if(myRTC.hours==B_hour && myRTC.minutes==B_minute && AlarmIsActive2==1){
    while(keypressedx == NO_KEY){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Take your"); 
    lcd.setCursor(0,1);
    lcd.print("medicine");  
    digitalWrite(BUZZER_PIN, HIGH);
    keypressedx = myKeypad.getKey();
    }
    if (keypressedx == 'D')
             {
              digitalWrite(BUZZER_PIN, LOW);
              lcd.clear();
              lcd.print("Alarm deactivated");
              AlarmIsActive2=0;
              keypressed=NO_KEY;
              delay(1000);
             }
  }

  if(myRTC.hours==C_hour && myRTC.minutes==C_minute && AlarmIsActive3==1){
    while(keypressedx == NO_KEY){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Take your"); 
    lcd.setCursor(0,1);
    lcd.print("medicine");  
    digitalWrite(BUZZER_PIN, HIGH);
    keypressedx = myKeypad.getKey();
    }
    if (keypressedx == 'D')
             {
              digitalWrite(BUZZER_PIN, LOW);
              lcd.clear();
              lcd.print("Alarm deactivated");
              AlarmIsActive3=0;
              keypressed=NO_KEY;
              delay(1000);
             }
  }


  keypressedx = NO_KEY;
  lcd.setCursor(0,0);
  lcd.print(myRTC.dayofmonth);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.setCursor(0,1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  delay(300);
  }
 
 
         if (keypressed == '*') 
             {
              lcd.clear();
              lcd.print("     Setup");
             delay(1000);
              lcd.clear();
              lcd.print("Setup year");
              //The RTC virtuabotix library is already set to not accept strange time and dates (45/17/1990) (58:90:70), and old dates are considered as errors
             char keypressed2 = myKeypad.waitForKey();  
                    if (keypressed2 != NO_KEY && keypressed2 !='*' && keypressed2 !='#' && keypressed2 !='A' && keypressed2 !='B' && keypressed2 !='C' && keypressed2 !='D' )
                      {
                       c1 = keypressed2;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                 char      keypressed3 = myKeypad.waitForKey();
                    if (keypressed3 != NO_KEY && keypressed3 !='*' && keypressed3 !='#' && keypressed3 !='A' && keypressed3 !='B' && keypressed3 !='C' && keypressed3 !='D' )
                      {
                       c2 = keypressed3;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
                   char  keypressed4 = myKeypad.waitForKey();
                   if (keypressed4 != NO_KEY && keypressed4 !='*' && keypressed4 !='#' && keypressed4 !='A' && keypressed4 !='B' && keypressed4 !='C' && keypressed4 !='D' )
                      {
                       c3 = keypressed4;
                       lcd.setCursor(2, 1);
                       lcd.print(c3);
                       }
                   char   keypressed5 = myKeypad.waitForKey();
                   if (keypressed5 != NO_KEY && keypressed5 !='*' && keypressed5 !='#' && keypressed5 !='A' && keypressed5 !='B' && keypressed5 !='C' && keypressed5 !='D' )
                      {
                       c4 = keypressed5;
                       lcd.setCursor(3, 1);
                       lcd.print(c4);
                       }
 
                     i1=(c1-48)*1000;       
                     i2=(c2-48)*100;
                     i3=(c3-48)*10;
                     i4=c4-48;
                     int N_year=i1+i2+i3+i4;
                   delay(500);
                     lcd.clear();
                     lcd.print("Setup month");
 
                     char keypressed6 = myKeypad.waitForKey();  
                    if (keypressed6 != NO_KEY && keypressed6 !='*' && keypressed6 !='#' && keypressed6 !='A' && keypressed6 !='B' && keypressed6 !='C' && keypressed6 !='D' )
                      {
                       c1 = keypressed6;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed7 = myKeypad.waitForKey();
                    if (keypressed7 != NO_KEY && keypressed7 !='*' && keypressed7 !='#' && keypressed7 !='A' && keypressed7 !='B' && keypressed7 !='C' && keypressed7 !='D' )
                      {
                       c2 = keypressed7;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_month=i1+i2;
                     delay(500);
 
                     lcd.clear();
                     lcd.print("Setup Day");
                                      
                      char keypressed8 = myKeypad.waitForKey();  
                    if (keypressed8 != NO_KEY && keypressed8 !='*' && keypressed8 !='#' && keypressed8 !='A' && keypressed8 !='B' && keypressed8 !='C' && keypressed8 !='D' )
                      {
                        c1 = keypressed8;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                      char keypressed9 = myKeypad.waitForKey();
                    if (keypressed9 != NO_KEY && keypressed9 !='*' && keypressed9 !='#' && keypressed9 !='A' && keypressed9 !='B' && keypressed9 !='C' && keypressed9 !='D' )
                      {
                        c2 = keypressed9;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_day=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Setup hour");                   
                     char keypressed10 = myKeypad.waitForKey();  
                    if (keypressed10 != NO_KEY && keypressed10 !='*' && keypressed10 !='#' && keypressed10 !='A' && keypressed10 !='B' && keypressed10 !='C' && keypressed10 !='D' )
                      {
                       c1 = keypressed10;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed11 = myKeypad.waitForKey();
                    if (keypressed11 != NO_KEY && keypressed11 !='*' && keypressed11 !='#' && keypressed11 !='A' && keypressed11 !='B' && keypressed11 !='C' && keypressed11 !='D' )
                      {
                        c2 = keypressed11;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Setup minutes");
                    char keypressed12 = myKeypad.waitForKey();  
                    if (keypressed12 != NO_KEY && keypressed12 !='*' && keypressed12 !='#' && keypressed12 !='A' && keypressed12 !='B' && keypressed12 !='C' && keypressed12 !='D' )
                      {
                        c1 = keypressed12;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                   char    keypressed13 = myKeypad.waitForKey();
                    if (keypressed13 != NO_KEY && keypressed13 !='*' && keypressed13 !='#' && keypressed13 !='A' && keypressed13 !='B' && keypressed13 !='C' && keypressed13 !='D' )
                      {
                        c2 = keypressed13;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                    int N_minutes=i1+i2;
                    delay(500);
                     lcd.clear();
 
                    myRTC.setDS1302Time(1, N_minutes, N_hour, 1, N_day, N_month, N_year);
                    keypressed=NO_KEY;
              }
/////////////////////////////////////////Alarme setup/////////////////////////////////
              
             if (keypressed == 'A'){
              lcd.clear();
              lcd.print("Set Alarm A ");
              delay(1000);
              lcd.clear();
              lcd.print("Set alarm hour");
               
               char keypressed14 = myKeypad.waitForKey();  
                    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
                      {
                       c1 = keypressed14;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed15 = myKeypad.waitForKey();
                    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
                      {
                        c2 = keypressed15;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Set alarm minutes");
                      char keypressed16 = myKeypad.waitForKey();  
                    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
                      {
                       c1 = keypressed16;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed17 = myKeypad.waitForKey();
                    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
                      {
                        c2 = keypressed17;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     A_minute=i1+i2;
                    delay(500);
                     lcd.clear();
                    AlarmIsActive1=1;
                    keypressed=NO_KEY;
             }
              if (keypressed == 'B'){
              lcd.clear();
              lcd.print(" Set Alarm B ");
              delay(1000);
              lcd.clear();
              lcd.print("Set alarm hour");
               
               char keypressed14 = myKeypad.waitForKey();  
                    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
                      {
                       c1 = keypressed14;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed15 = myKeypad.waitForKey();
                    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
                      {
                        c2 = keypressed15;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     B_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Set alarm minutes");
                      char keypressed16 = myKeypad.waitForKey();  
                    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
                      {
                       c1 = keypressed16;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed17 = myKeypad.waitForKey();
                    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
                      {
                        c2 = keypressed17;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     B_minute=i1+i2;
                    delay(500);
                     lcd.clear();
                    AlarmIsActive2=1;
                    keypressed=NO_KEY;
             }
              if (keypressed == 'C'){
              lcd.clear();
              lcd.print(" Set Alarm C");
              delay(1000);
              lcd.clear();
              lcd.print("Set alarm hour");
               
               char keypressed14 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed14 != NO_KEY && keypressed14 !='*' && keypressed14 !='#' && keypressed14 !='A' && keypressed14 !='B' && keypressed14 !='C' && keypressed14 !='D' )
                      {
                       c1 = keypressed14;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed15 = myKeypad.waitForKey();
                    if (keypressed15 != NO_KEY && keypressed15 !='*' && keypressed15 !='#' && keypressed15 !='A' && keypressed15 !='B' && keypressed15 !='C' && keypressed15 !='D' )
                      {
                        c2 = keypressed15;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     B_hour=i1+i2;
                    delay(500);
                     lcd.clear();
                     lcd.print("Set alarm minutes");
                      char keypressed16 = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed16 != NO_KEY && keypressed16 !='*' && keypressed16 !='#' && keypressed16 !='A' && keypressed16 !='B' && keypressed16 !='C' && keypressed16 !='D' )
                      {
                       c1 = keypressed16;
                       lcd.setCursor(0, 1);
                       lcd.print(c1);
                       }
                    char   keypressed17 = myKeypad.waitForKey();
                    if (keypressed17 != NO_KEY && keypressed17 !='*' && keypressed17 !='#' && keypressed17 !='A' && keypressed17 !='B' && keypressed17 !='C' && keypressed17 !='D' )
                      {
                        c2 = keypressed17;
                       lcd.setCursor(1, 1);
                       lcd.print(c2);
                       }
 
 
                     i1=(c1-48)*10;
                     i2=c2-48;
                     C_minute=i1+i2;
                    delay(500);
                     lcd.clear();
                      AlarmIsActive3=1;
                      keypressed=NO_KEY;
             }
             else {
              myRTC.updateTime();
              keypressed=NO_KEY;
             }
}