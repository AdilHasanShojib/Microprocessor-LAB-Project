// int redLed1 = 3;
// int redLed2 = 4;
// int greenLed = 8;
int buzzer1 = 5; //PWM (~) pin
int buzzer2 = 6; //PWM (~) pin
// int gasPin = A0;
int gasPin = 8;
int flamePin = 9;
// Your threshold value
// int gasSensorThres = 400;
int waterPump = 3;

void setup() {
  // pinMode(redLed1, OUTPUT); 
  // pinMode(redLed2, OUTPUT);
  // pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  // pinMode(gasPin, INPUT);
  pinMode(gasPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(waterPump, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // int gasSensor = analogRead(gasPin);
  int flameSensor = digitalRead(flamePin);
  int gasSensor = digitalRead(gasPin);
 
  // Serial.print("gasPin Value: ");
  // Serial.println(gasSensor);
  Serial.print("gasPin Value: ");
  Serial.println(gasSensor);
  Serial.print("flamePin Value: ");
  Serial.println(flameSensor);

  delay(1000);
 
  if (gasSensor==LOW  && flameSensor==LOW){
  //  digitalWrite(redLed1, HIGH);
    tone(buzzer1, 5000); //the buzzer sound frequency at 5000 Hz
    // digitalWrite(redLed2, HIGH);
    tone(buzzer2, 5000); //the buzzer sound frequency at 5000 Hz
    // digitalWrite(greenLed, LOW);
    Serial.println("Fire and Smoke detected");
    digitalWrite(waterPump, LOW);

  }
   else if (gasSensor==LOW)
  {
    // digitalWrite(redLed1, HIGH);
    tone(buzzer1, 5000); //the buzzer sound frequency at 5000 Hz
    // digitalWrite(redLed2, LOW);
    noTone(buzzer2);
    // digitalWrite(greenLed, LOW);
    Serial.println("Smoke detected");
    digitalWrite(waterPump, HIGH);
  }
  else if (flameSensor==LOW){ // HIGH MEANS NO FLAME
    // digitalWrite(redLed1, LOW);
    noTone(buzzer1);
    // digitalWrite(redLed2, HIGH);
    tone(buzzer2, 5000); //the buzzer sound frequency at 5000 Hz
    // digitalWrite(greenLed, LOW);
    Serial.println("Fire detected");
    digitalWrite(waterPump, LOW);
  }
 
  else
  {
    // digitalWrite(redLed1, LOW);
    // digitalWrite(redLed2, LOW);
    noTone(buzzer1);
    noTone(buzzer2);
    // digitalWrite(greenLed, HIGH);
    Serial.println("You're Safe"); 
    digitalWrite(waterPump, HIGH); 
  }
} 



