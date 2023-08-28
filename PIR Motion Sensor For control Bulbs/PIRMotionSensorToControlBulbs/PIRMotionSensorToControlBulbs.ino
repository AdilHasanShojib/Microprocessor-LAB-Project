// PIR sensor pin
const int pirPin = 4;  
const int ledPin = 13; // LED pin

void setup() {
  pinMode(pirPin, INPUT);  
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600); 
}

void loop() {
  // Read PIR sensor state
  int pirState = digitalRead(pirPin); 

  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);  
    Serial.println("Motion detected!");
    delay(1000);  
  } else {
    digitalWrite(ledPin, LOW);  
    Serial.println("Motion NOT detected!");
    delay(1000);  
  }
}