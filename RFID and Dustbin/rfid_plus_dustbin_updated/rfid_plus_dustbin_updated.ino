#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo1; //define servo name
Servo myServo2;
Servo myServo3;

// twelve servo objects can be created on most boards
int IRSensor = 8; 
int pos = 0;    // variable to store the servo position
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

void ultraSoundSensor() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(1000);

   if(cm<=6){
    servoController2(); 
    }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void servoController() {
  for (pos = 180; pos >= 75; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 75; pos <= 180; pos += 1) { // goes from 180 degrees to 0 degrees
    myServo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void servoController2() {
  for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(2000);
  for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo3.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

//void setup(){
//  myservo.attach(9);
//  Serial.begin(9600); // Init Serial at 115200 Baud Rate.
//  Serial.println("Serial Working"); // Test to check if serial is working or not
//  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
//  
//}

void garbageBox(){
  ultraSoundSensor();
  int sensorStatus = digitalRead(IRSensor);
  if (sensorStatus == 1) // Check if the pin high or not
  {
    Serial.println("Motion Detected!"); // print Motion Detected! on the serial monitor window
    servoController();
  }
  else  {
    Serial.println("Motion Ended!"); // print Motion Ended! on the serial monitor window
  }
}









 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo1.attach(3); //servo pin
  myServo1.write(0); //servo start position
  Serial.println("Put your card to the reader...");
  Serial.println();
  myServo2.attach(5);
  myServo2.write(180); //servo start position

  myServo3.attach(2);
  myServo3.write(75);

  Serial.println("Serial Working"); // Test to check if serial is working or not
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  

}
void loop() 
{
  garbageBox();
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "F3 05 0E 2E") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    //delay(500);
    myServo1.write(75);

    delay(3000);
    myServo1.write(0);

  }
 
 else   {
    Serial.println(" Access denied");
//    digitalWrite(LED_R, HIGH);
////    tone(BUZZER, 300);
      delay(2000);
//    digitalWrite(LED_R, LOW);
////    noTone(BUZZER);
  }
}

