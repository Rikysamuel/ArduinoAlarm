int led = 8;
String message = "11110000";

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i =0;i<message.length();i++){
    if (message.charAt(i)=='1'){ // if 1, then high-to-low
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led,LOW);
      delay(500);
    } else{  // if 0, then low-to-high
      digitalWrite(led, LOW);
      delay(500);
      digitalWrite(led,HIGH);
      delay(500);
    }
  }
}
