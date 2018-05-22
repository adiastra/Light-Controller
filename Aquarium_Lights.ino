/*
  Aquarium Lighting

  Cycles on and off 4 separate relays based on information from a real time clock.
  The real time clock in this case is a DS3231
  The relays are controling 2 LED light bars each with 3 modes (day/night/off).

  You have to set the time for the RTC using the commented out code in the setup section

  For this configuration relays 1 and 3 switch between two different modes on the light bar
  relays 3 and 4 turn off the bars and should be wired in series.  

  Written by: Alec DiAstra

*/
//Include RTC library 
#include <DS3231.h>

// Init the DS3231 RTC using the hardware interface
DS3231  rtc(A4, A5);

// Init a Time-data structure
Time  t;

//Setup output pins for relays
const int CH1 = A0 ; //assign pins outs, one for each channel
const int CH2 = A1 ;
const int CH3 = A2 ;
const int CH4 = A3 ;

//Setup light cycle for both bars
const int Bar1Morn = 6;      //Blue Lights only
const int Bar1Day = 7;     //all lights on 
const int Bar1Night = 18;   //Blue lights only
const int Bar1Off = 22;     //all ights off
const int Bar2Morn = 6;
const int Bar2Day = 8;
const int Bar2Night = 16;
const int Bar2Off = 21;






// the setup routine runs once when you press reset:
void setup() {
  //assign 
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);
  pinMode(CH4, OUTPUT);
  Serial.begin(115200);
  Serial.println("Setup complete");
  rtc.begin();
  

  //The following lines can be uncommented to set the date and time
  //rtc.setDOW(TUESDAY);     
  //rtc.setTime(7, 00, 00);     
  //rtc.setDate(3, 29, 2018);   

}

//the loop routine runs over and over again forever:
void loop() {

//Get time data from RTC and store in t
t = rtc.getTime();


//Bar 1
 if (t.hour >= Bar1Morn && t.hour < Bar1Day){
    digitalWrite(CH1, LOW);
    digitalWrite(CH3, HIGH);
    Serial.println("Bar 1 MORNING MODE");
  }

  else if (t.hour >= Bar1Day && t.hour < Bar1Night){
    digitalWrite(CH1, LOW);
    digitalWrite(CH3, LOW);
    Serial.println("Bar 1 DAY MODE");
  }
  else if (t.hour >= Bar1Night && t.hour < Bar1Off){
    digitalWrite(CH1, HIGH);
    digitalWrite(CH3, LOW);
    Serial.println("Bar 1 NIGHT MODE");
  }
   else if (t.hour >= Bar1Off || t.hour < Bar1Morn){
    digitalWrite(CH1, HIGH);
    digitalWrite(CH3, HIGH);
    Serial.println("Bar 1 OFF");
  }


//Bar 2
 if (t.hour >= Bar2Morn && t.hour < Bar2Day){
    digitalWrite(CH2, LOW);
    digitalWrite(CH4, HIGH);
    Serial.println("Bar 2 DAY MODE");
 }
  else if (t.hour >= Bar2Day && t.hour < Bar2Night){
    digitalWrite(CH2, LOW);
    digitalWrite(CH4, LOW);
    Serial.println("Bar 2 DAY MODE");
  }
   else if (t.hour >= Bar2Night && t.hour < Bar2Off){
    digitalWrite(CH2, HIGH);
    digitalWrite(CH4, LOW);
    Serial.println("Bar 2 NIGHT MODE");
  }
   else if (t.hour >= Bar2Off || t.hour < Bar2Morn){
    digitalWrite(CH2, HIGH);
    digitalWrite(CH4, HIGH);
    Serial.println("Bar 2 OFF");
  }
Serial.print("Time ");
Serial.print(t.hour);
Serial.print(":");
Serial.print(t.min);
Serial.print(" and ");
Serial.println(t.sec);
  //Wait 30 seconds and check again 
  delay (30000);


}






