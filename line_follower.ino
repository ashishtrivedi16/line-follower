/*This is a simple line follower robot which uses 3 IR sensors to detect a black line.
 * The whole project is built using the following - 
 * #Arduino Uno rev3 board
 * #An arduino motor sheild which is used to control 2 DC geared motors (12V, 300rpm,300mA) 
 * #3 IR sensor module connected to analog pins(they can be also used to get digital input
 * Arduino board and motor sheild are powered seperately from different sources
 * Arduino board gets a input from a 9V batter from either the DC input jack(better option because of protection diode) or the Vin pin
 * Don't forget to remove the jumper when using seperate power supplies
 * Motor sheild is powered by a battery of 1.5V cells (12V total) using the EXT_PWR pins on the sheild.
 * The chassis is made using acrylic plexiglass sheets with two decks for the boards and battery seperately
 * Author : Ashish Trivedi
 */

#include <AFMotor.h> // this file uses the adafruit motor shield library

AF_DCMotor m_l(1,MOTOR12_64KHZ); // Channels 2 at 64KHZ frequency
AF_DCMotor m_r(4,MOTOR34_64KHZ); // Channels 4 at 64KHZ frequency


#define W 70  // constants defined for sensors
#define D 900
#define MAX 255  // constants defined for motor speed control
#define MOD 200
#define MIN 100

  int s_l,s_r,s_m; //gets sensor readings

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);  
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  Serial.println("Pins initialized");
  
  // turn on motor
  m_l.setSpeed(255); // m_l: left motor, m_r: right motor
  m_r.setSpeed(255);
  m_l.run(RELEASE);
  m_r.run(RELEASE);

  Serial.println("Motors initialized");
}

void loop() {
  
  s_r = analogRead(A0); // s_r: right sensor, s_m: middle sensor, s_l: left sensor 
  s_m = analogRead(A1);
  s_l = analogRead(A2);

  
  Serial.print(s_r);
  Serial.print("\t");
  Serial.print(s_m);
  Serial.print("\t");
  Serial.print(s_l);
  Serial.print("\n");
  delay(0);


    if( (s_r < W) && (s_m < W) && (s_l < W) ){ // when all sensors are on white area
      m_l.setSpeed(MIN);
      m_r.setSpeed(MIN);
      Serial.println("Put me down!! :D");
    }
    else if( (s_r < W) && (s_m > D) && (s_l < W) ){ // when middle sensor is on dark area
      m_l.setSpeed(MAX);
      m_r.setSpeed(MAX); 
      Serial.println("I'm going straight!!");
    }
    else if( (s_r > D) && (s_m < W) && (s_l < W) ){ // when right sensor is on dark area
      m_l.setSpeed(MAX);
      m_r.setSpeed(MOD);
      Serial.println("Whoo i'm going right!!");
    }
    else if( (s_r < W) && (s_m < W) && (s_l > D)){  // when left sensor is on dark area
      m_l.setSpeed(MOD);
      m_r.setSpeed(MAX);
      Serial.println("Whoo i'm going left!!");
    }
    else if( (s_r > D) && (s_m > D) && (s_l > D) ){ // when all sensors are on dark area
      m_l.setSpeed(MIN);
      m_r.setSpeed(MIN);
      Serial.println("Where am i? -_- -_-");
    }
    delay(50);  // delay added to increase/decrease senstivity of the robot
   
}
