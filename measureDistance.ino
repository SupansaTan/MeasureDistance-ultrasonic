#include <TM1637Display.h>

/* ultrasonic */
#define TRIG 10
#define ECHO 9

/* seven segment */
#define CLK 4
#define DIO 3
TM1637Display display(CLK,DIO);

/* LED */ 
#define RED 5
#define YELLOW 6
#define GREEN 7

// set pin
int button = 2;

const uint8_t PLAY[] = {B01110011, B00111000, B01011111, B01101110};
const uint8_t ERR[] = {B01111001, B01111001, B01110111, B01000000};

void setup() {
  //pinMode(button, INPUT);
  Serial.begin(9600);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  display.setBrightness(4);
  display.setSegments(PLAY);
  delay(80);
}

void loop() {
  long duration, cm;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  duration = pulseIn(ECHO, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  display.showNumberDec(cm);
  showLED(cm);
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(300);
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void showLED(int distance){
  if(distance <= 5){ 
    // lowest is 2
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
  }
  else if(distance > 5 && distance <= 20){
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
  }
  else if(distance > 20 && distance <= 400){
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);
  }
  else {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    display.setSegments(ERR);
  }
}
