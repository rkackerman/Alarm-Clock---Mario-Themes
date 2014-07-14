#include <Time.h>
#include <LiquidCrystal.h>
#include <pitches.h>
#define melodyPin 9
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensorPin = A0;
const int numReadings = 10;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

void setup(){
  lcd.begin(16,2);
  pinMode(sensorPin,INPUT);
  setTime(19, 07, 00, 16, 5, 2014);
  pinMode(9, OUTPUT);//buzzer
  pinMode(13, OUTPUT);//led indicator when singing a note
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}
void loop(){
  digitalWrite(13,LOW);
  if (month() == 1){
  lcd.print("January");
  }  
  if (month() == 2){
  lcd.print("February");
  }  
  if (month() == 3){
  lcd.print("March");
  }  
  if (month() == 4){
  lcd.print("April");
  }  
  if (month() == 5){
  lcd.print("May");
  }  
  if (month() == 6){
  lcd.print("June");
  }  
  if (month() == 7){
  lcd.print("July");
  }  
  if (month() == 8){
  lcd.print("August");
  }  
  if (month() == 9){
  lcd.print("September");
  }  
  if (month() == 10){
  lcd.print("October");
  }  
  if (month() == 11){
  lcd.print("November");
  }  
  if (month() == 12){
  lcd.print("December");
  }
  lcd.print(" ");
  lcd.print(day());
  lcd.print(", ");  
  lcd.print(year());
  lcd.setCursor(0,2);
  lcd.print(hourFormat12(),DEC);
  lcd.print(":");
  if (minute() < 10) {
    lcd.print("0");
  }
  lcd.print(minute(),DEC);
  lcd.print(" ");
  if (isAM() == 1){  
    lcd.print("AM");
  }
  if (isPM() == 1){
    lcd.print("PM");
  }
  delay(2500);
  lcd.clear();
    total = total - readings[index];
  readings[index] = analogRead(sensorPin);
  total = total + readings[index];
  index = index + 1;
  if (index >= numReadings) {
    index = 0; 
  }
  average = total / numReadings;
  float voltage = (average/1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  temperature = (temperature * 1.8) + 32.0;
  lcd.print("Current Temp:");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print(" F");
  delay(2500);
  lcd.clear();
  
  if(hour() == 19 && minute() == 9){
    lcd.print("Wake Up!");
    delay(2500);
    lcd.noDisplay();  
    sing(1);
    sing(1);
    sing(2);
    lcd.display();
    lcd.clear();
  }

}
int song = 0;
void sing(int s){      
   // iterate over the notes of the melody:
   song = s;
   if(song==2){
     Serial.println(" 'Underworld Theme'");
     int size = sizeof(underworld_melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/underworld_tempo[thisNote];

       buzz(melodyPin, underworld_melody[thisNote],noteDuration);
       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);

    }

   }else{

     Serial.println(" 'Mario Theme'");
     int size = sizeof(melody) / sizeof(int);
     for (int thisNote = 0; thisNote < size; thisNote++) {

       // to calculate the note duration, take one second
       // divided by the note type.
       //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
       int noteDuration = 1000/tempo[thisNote];

       buzz(melodyPin, melody[thisNote],noteDuration);
       // to distinguish the notes, set a minimum time between them.
       // the note's duration + 30% seems to work well:
       int pauseBetweenNotes = noteDuration * 1.30;
       delay(pauseBetweenNotes);

       // stop the tone playing:
       buzz(melodyPin, 0,noteDuration);
    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    digitalWrite(13,HIGH);
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    digitalWrite(13,LOW);
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
