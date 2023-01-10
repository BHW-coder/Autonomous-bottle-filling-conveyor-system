#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
RFID rfid(SS_PIN, RST_PIN);
#include <Servo.h>
#define echoPin 5// attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
Servo myservo;
//#include <Servo.h> // include servo library to use its related functions
#define Servo_PWM 7 // A descriptive name for D7 pin of Arduino to provide PWM signal
Servo MG995_Servo;  // Define an instance of of Servo with the name of "MG995_Servo"
  

// create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position


String rfidCard;
int RelayPin = 3;
int RelayPin2 = 2;
int RelayPin3 = 8;
int count = 0;
int ir = 6;
int val = 0;
int LED = 7;
void setup() {

  pinMode(RelayPin, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(ir, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println(" Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
  Serial.begin(9600); // Initialize UART with 9600 Baud rate
  //MG995_Servo.attach(Servo_PWM);  // Connect D6 of Arduino with PWM signal pin of servo motor
  digitalWrite(RelayPin, HIGH);
  digitalWrite(RelayPin2, HIGH);
  delay(3000);
  myservo.attach(7);
  pinMode(trigPin, OUTPUT);      // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);      // Sets the echoPin as an INPUT
  Serial.begin(9600);          // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); 
  pinMode(LED_BUILTIN, OUTPUT);// print some text in Serial Monitor
  //Serial.println("with Arduino UNO R3");
}

void loop() {

  if (rfid.isCard()) {
    if (rfid.readCardSerial())
      delay(250); {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println("Card Accepted");
      if (rfidCard == "179 19 251 22") {
        Serial.println("Harish");
        count++;
        Serial.println(count);
        digitalWrite(LED_BUILTIN, LOW);
      }
      else {
        Serial.println("Card Rejected");
        //digitalWrite(8,LOW);
      }
      } 
  }    
  val = digitalRead(ir);

  Serial.println(count);
  if (count % 2 == 1)
  {

    if (val == LOW)
    {
      digitalWrite(RelayPin3, HIGH);
      delay(2000);
      digitalWrite(RelayPin3, LOW);
      //delay(2000);
    }
    //digitalWrite(RelayPin3,LOW);
    //delay(3000);
    //digitalWrite(8, HIGH);
    digitalWrite(RelayPin, LOW);
    digitalWrite(RelayPin2, LOW);
    delay(2300);
    digitalWrite(RelayPin, HIGH);
    digitalWrite(RelayPin2, HIGH);
    delay(2000);
    Serial.println("a");

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    /*digitalWrite(RelayPin, LOW);
    digitalWrite(RelayPin2, LOW);
    delay(2100);
    digitalWrite(RelayPin, HIGH);
    digitalWrite(RelayPin2, HIGH);
    delay(2100);
    Serial.println("servo check");*/

    if (!( distance <= 8 && distance >= 3 ))
    {
      digitalWrite(LED,LOW);
      Serial.println("Product Rejected");
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      //delay(1000);
      //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      //delay(1000);
      Serial.println("0");// You can display on the serial the signal value
      MG995_Servo.write(0); //Turn clockwise at high speed
      delay(1000);
      MG995_Servo.detach();//Stop. You can use deatch function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
      delay(1500);
      MG995_Servo.attach(Servo_PWM);//Always use attach function after detach to re-connect your servo with the board
      Serial.println("0");//Turn left high speed
      MG995_Servo.write(180);
      delay(1000);
      MG995_Servo.detach();//Stop
      delay(1500);
      MG995_Servo.attach(Servo_PWM);

     /* for (pos = 0; pos <= 180; pos += 90) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);
        // tell servo to go to position in variable 'pos'

        delay(150);
        }// waits 15 ms for the servo to reach the position
        for (pos = 180; pos >= 0; pos -= 90)
        { // goes from 180 degrees to 0 degrees
        myservo.write(pos);
        // tell servo to go to position in variable 'pos'

        delay(150);// waits 15 ms for the servo to reach the position
        }*/
    }
    else if(distance <= 8 && distance >= 3 )
    {
     digitalWrite(LED,LOW);
      Serial.println("Product Accepted");
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000); 
    }
  }

  else if (count % 2 != 1)
  {

    digitalWrite(LED, LOW);
    digitalWrite(RelayPin3, LOW);
    digitalWrite(RelayPin, HIGH);
    digitalWrite(RelayPin2, HIGH);
    delay(1500);
    Serial.println("Conveyor STOPPED");
  }


  rfid.halt();    
}
