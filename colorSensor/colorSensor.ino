#include <Servo.h>

Servo pickServo;

Servo dropServo;


#define S0 4 

#define S1 5

#define S2 7

#define S3 6

#define sensorOut 8    

int frequency = 0;
int pos=0;
int color=0;


int detectColor() {

  // activating red photodiodes to read

  digitalWrite(S2, LOW);

  digitalWrite(S3, LOW);

  frequency = pulseIn(sensorOut, LOW);

  int R = frequency;

  Serial.print("Red = ");

  Serial.print(frequency);//printing RED color frequency

  Serial.print("   ");

  delay(50);


   // activating blue photodiodes to read

  digitalWrite(S2, LOW);

  digitalWrite(S3, HIGH);

  frequency = pulseIn(sensorOut, LOW);

  int B = frequency;

  Serial.print("Blue = ");

  Serial.print(frequency);

  Serial.println("   ");

  

  // activating green photodiodes to read

  digitalWrite(S2, HIGH);

  digitalWrite(S3, HIGH);

  // Reading the output frequency

  frequency = pulseIn(sensorOut, LOW);

  int G = frequency;

  Serial.print("Green = ");

  Serial.print(frequency);

  Serial.print("   ");

  delay(50);


  delay(50);


//Readings are different for different setup

//change the readings according your project and readings detected

  if(R<200 & R>130 & G<480 & G>420 & B < 400 & B > 320){

    color = 1; // Red

    Serial.print("Detected Color is = ");

    Serial.println("RED");

  }

  // if(G<25 & G>22 & B<22 &B>19){

  //   color = 2; // Orange

  //     Serial.println("Orange  ");

  // }

  // if(R<2100 & R>1700 & G<1700 & G>1200 & B < 1700 & B > 1100){

  //   color = 3; // Green

  //     Serial.print("Detected Color is = ");

  //   Serial.println("GREEN");

  // }

  if(R<220 & R>180 & G<320 & G>280 & B < 400 & B > 350){

    color = 2; // Yellow

       Serial.print("Detected Color is = ");

    Serial.println("YELLOW");

  }

  if (R<500 & R>400 & G<520 & G>420 & B < 350 & B > 300){

    color = 3; // Blue

     Serial.print("Detected Color is = ");

    Serial.println("BLUE");

  }

  return color;  

}


void setup() {

  pinMode(S0, OUTPUT);

  pinMode(S1, OUTPUT);

  pinMode(S2, OUTPUT);

  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);


  //frequency-scaling to 20% selected

  digitalWrite(S0, LOW);

  digitalWrite(S1, HIGH);


  pickServo.attach(9);

  dropServo.attach(10);


  Serial.begin(9600);

}


void loop() {

  //initial position of servo motor

  // pickServo.write(180);

  // delay(600);

  

  // for(int i = 180; i > 50; i--) {

  //   pickServo.write(i);

  //   delay(2);

  // }

  for (pos = 0; pos <= 170; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    pickServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  delay(3000);
  for (pos = 170; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    pickServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);  
    if(pos ==70){
      for(int i=0;i<20;i++)
      color = detectColor(); 
      
  switch (color) {

    case 1:
    dropServo.write(40);
    break;
    case 2:

    dropServo.write(80);

    break;
    case 3:

    dropServo.write(140);

    break;
    case 4:

    dropServo.write(140);

    break;
    case 5:

    dropServo.write(170);

    break;
    case 0:

    break;

  }

     color=0;
      delay(10000);
      
    }
            
  }


}




// #include <Servo.h>

// Servo myservo;  // create servo object to control a servo
// // twelve servo objects can be created on most boards

// int pos = 0;    // variable to store the servo position

// void setup() {
//   myservo.attach(10);  // attaches the servo on pin 9 to the servo object
// }

// void loop() {
//   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//     // in steps of 1 degree
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);                       // waits 15ms for the servo to reach the position
//   }
//   delay(3000);
//   for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     delay(15);  
//                        // waits 15ms for the servo to reach the position
//   }
// }
