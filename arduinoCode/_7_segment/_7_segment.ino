#define data 2
#define clock 3
#define clr 4
#define disp1 5
#define disp2 6
#define ldr A0
#define interruptPin 9

const byte numbers[10] = {0b11111100,
                          0b01100000,
                          0b11011010,
                          0b11110010,
                          0b01100110,
                          0b10110110,
                          0b10111110,
                          0b11100000,
                          0b11111110,
                          0b11110110};
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
boolean alarmStart = false; 

void setup() {
  Serial.begin(9600);
  
  //set pins to output because they are addressed in the main loop
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(clr, OUTPUT);
  pinMode(disp1, OUTPUT);
  pinMode(disp2, OUTPUT);
  pinMode(interruptPin, OUTPUT);
  digitalWrite(interruptPin, HIGH);
  attachInterrupt(interruptPin, offAlarm, LOW);

  digitalWrite(clr, HIGH);
  inputString.reserve(200);
  
  delay(100);
}

void offAlarm()
{
  Serial.println("off");
}

int i = 20;
bool triggered;
int intensity = 0;
int timer = 10;
int threshold = 200;

void loop() {
  if (stringComplete) {
    Serial.println(inputString);
    if (inputString == "start") {
      alarmStart = true;
    }
    inputString = "";
    stringComplete = false;
  }
  
  if (alarmStart) {
    if (i==0) {
      Serial.println("off");
      alarmStart = false;
    }
    else if (alarmStart) {
      intensity = analogRead(ldr);
      Serial.println(intensity);
      
      if(intensity >= threshold){
        triggered = true;  
      }else{
        triggered = false;
      }
      
      if(triggered){
        if(i <= 0){
          triggered = false;
        }    
        i--; 
      }else{
        i = 20;
      }
    }
    for(int j = 0; j < timer; j++){
      displayDigits(i);    
      intensity = analogRead(ldr);    
    }
  }
} 

void allOff(){
  digitalWrite(disp1, LOW);
  digitalWrite(disp2, LOW); 
}

void displayFirstDigit(byte number){
  allOff();
  shiftOut(data, clock, LSBFIRST, number);
  digitalWrite(disp1, LOW);
  digitalWrite(disp2, HIGH);
  delay(10);
}

void displaySecondDigit(byte number){
  allOff();
  shiftOut(data, clock, LSBFIRST, number);
  digitalWrite(disp1, HIGH);
  digitalWrite(disp2, LOW);
  delay(10);
}

void displayDigits(int number){
  int d1, d2;
  
  if(number > 99){
    number = 99; 
  }
  if(number < 0){
    number = 0;
  }
  
  d1 = number / 10;
  d2 = number - (d1 * 10);
  
  displayFirstDigit(numbers[d1]);
  displaySecondDigit(numbers[d2]);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

