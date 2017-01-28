#include <LiquidCrystal.h>

#define SENSOR_PIN A1
#define BUZZER_PIN 3
#define MAX_TEMP 27.0
#define MIN_TEMP 25.0

int pin11 = 11;
int pin12 = 12;

LiquidCrystal lcd(4, 5, 6, 7, 8, 9); // Creating an LCD object

// declaring global variable which are essential for operation time
unsigned long start = 0, finish = 0, elapsed = 0, operationTime = 0;
float tempMax = 0;
int flag=0;
/*  flipping of a number is needed to calculate time correctly.  
 *  it prevents start & finish to override & only calculates
 *  elapsed time when both start & finish were calculated.
 */
 
 int tmpmin=0;
 int tmpmax=0;
unsigned short flip = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initializing LCD object by specifying 16x2 display
  lcd.clear();      // Clearing the display
  pinMode(SENSOR_PIN, INPUT);  // sensor pin as input pin      
  pinMode(BUZZER_PIN, OUTPUT); // buzzer pin as output pin
  pinMode(10,INPUT_PULLUP);
   pinMode(pin11, OUTPUT);
   pinMode(pin12, OUTPUT);
}

void loop() {
  //Serial.println(start);
  float tempCurrent = readTemp(); // read current temp
  if (tempCurrent > MAX_TEMP) {    // when current tempearture greater than Max_TEMP
       // buzz the buzzer 
    if (flip == 0) {                 // when flip isn't flipped
      start = millis()/1000;      // start time
      flag=0;    
     Serial.println(start);
      //Serial.println(flag);
    }
    
    //if( (start + 10) >= (millis()/1000)){
    tone(BUZZER_PIN, 1300, 1400);
    //}
    //digitalWrite(pin11,LOW);
    analogWrite(pin12,255);
    flip = 1;                      // flip the number
  }
  else if (tempCurrent < MIN_TEMP) { // when current temperature less than MIN_TEMP
        // buzz the buzzer
        if(flag==0){
        // Serial.println(flag);
        finish=millis()/1000;
        flag=1;
        
        }
    if (flip == 1) {                // when flip is flipped
      finish = millis()/1000;            // finish time
      elapsed = finish - start;     // time needed
      operationTime += elapsed;     // add to operation time
      setTimeElements();            // set the time elements to default
    }
    digitalWrite(pin12,LOW);
    //if( (finish + 10) >= (millis()/1000) ){
    tone(BUZZER_PIN, 2500, 500); 
    //}
  }
else if(tempCurrent < MAX_TEMP && tempCurrent > MIN_TEMP)  
{
 finish = millis()/1000;
 //digitalWrite(pin11,LOW);
    digitalWrite(pin12,LOW);
}
  if(digitalRead(10)==LOW)
  {
    //finish = millis()/1000;            // finish time
      elapsed = millis()/1000- start;     // time needed
      operationTime += elapsed;
      Serial.println("Time difference :");
    Serial.println(elapsed);
    Serial.println("Total operation Time :");
    Serial.println(operationTime);
    //digitalWrite(pin11,LOW);
    digitalWrite(pin12,LOW);
  }
  if(digitalRead(10)==HIGH)
  {
    //Serial.println("push button off");
  }
  if (tempCurrent > tempMax) {
    tempMax = tempCurrent;
  }
  lcd.setCursor(0, 0);
  lcd.print("Max_Temp:");
  lcd.print(tempMax);
  lcd.setCursor(0,1);
   lcd.print("CT:");
  lcd.print(tempCurrent);
  lcd.print(" T:");
  lcd.print(operationTime);
  
  //serial print secttion
  //Serial.setCursor(0, 0);
  Serial.print("Max_Temp:");
  Serial.print(tempMax);
  //Serial.setCursor(0,1);
   Serial.print(" Current Temperature : ");
  Serial.print(tempCurrent);
  Serial.print(" Total Operation Time : ");
  Serial.println(operationTime);
  delay(1000);
}

// Creating a function to read temp
float readTemp() {
  int reading = analogRead(SENSOR_PIN);
  float tempC = (5.0 * reading * 100.0) / 1024;
  return tempC;
}

// Creating a function to set the time elements
void setTimeElements() {
  flip = 0;
  start = 0;
  //finish = 0;
  elapsed = 0;
}

