/* vim: set syntax=cpp: */
/* ======================================================================
 
 Copyright: Scott Penrose 2011 - scottp@dd.com.au http://scott.dd.com.au/
 https://github.com/scottp/TrafficLights
 http://scott.dd.com.au/wiki/Traffic_Lights
 
 License: Creative Commons Attribution-ShareAlike
 https://creativecommons.org/licenses/by-sa/2.5/
 
 Birthday lights
 
 Basic:
 	On/Off and delay
 
 Speed change:
 
 Change pattern
 
 Analogue Hit it
  
 BUTTON to Change Program ?
 
 */

// ======================================================================

#define BASIC
// #define SERIAL

#define PINOFFSET 2
#define PINMAX 7
#define PINSWITCH1 8
#define PINSWITCH2 9
#define PINPOT 2
#define delayShort 1
#define delayMedium 2
#define delayLong 4

#define red1 0
#define yellow1 1
#define green1 2
#define red2 3
#define yellow2 4
#define green2 5

// ======================================================================
void setup() { 
  // Outputs
  for (int i = 0; i < PINMAX; i++)
    pinMode(i + PINOFFSET, OUTPUT);
    
  // Inputs
  pinMode(PINSWITCH1, INPUT);  
  digitalWrite(PINSWITCH1, HIGH);   
  pinMode(PINSWITCH2, INPUT);  
  digitalWrite(PINSWITCH2, HIGH);   

#ifdef SERIAL
  // Serial
  Serial.begin(9600);
  Serial.println("Birthday lights starting");
#endif
}


// ======================================================================
int sequence = 0;
void loop() {
  if (digitalRead(PINSWITCH1) == LOW){
    basicTraffic();
  }
  else if (digitalRead(PINSWITCH2) == LOW) {
    switch(sequence) {
      case 0:
        basicOnOff();
        break;
      case 1:
        basicRun();
        break;
      case 2:
        basicTogether();
        break;
      case 3:
        basicFlash();
        break;
      case 4:
        basicLeftRight();
        break;
      default:
        sequence = -1;
        break;
    }
    sequence++;
  }
  else {
    basicLeftRight();
  }
}

void doDelay(int factor) {
  int val;
  val = analogRead(PINPOT);
  // val range is 0 to 1000
  // factor is 1, 2, 4
  delay(factor * ((val * 1.5) + 200));
}

// ======================================================================
void lightOn(int l) {
#ifdef SERIAL
  Serial.print("ON: ");
  Serial.print(l);
#endif
  digitalWrite(l + PINOFFSET, LOW);
}

void lightOff(int l) {
#ifdef SERIAL
  Serial.print("off: ");
  Serial.print(l);
#endif
  digitalWrite(l + PINOFFSET, HIGH);
}

void allOff() {
  for (int i = 0; i <= PINMAX; i++)
    lightOff(i);
}

// ======================================================================
void basicRun() {
  allOff();
  for (int i = 0; i < 6; i++) {
    lightOn(i);
    doDelay(delayMedium);
    lightOff(i);
  }
}

// ======================================================================
void basicTogether() {
  allOff();
  for (int i = 0; i < 3; i++) {
    lightOn(i);
    lightOn(i + 3);
    doDelay(delayMedium);
    lightOff(i);
    lightOff(i + 3);
  }
}

// ======================================================================
void basicOnOff() {
  allOff();
  for (int i = 0; i < 3; i++) {
    lightOn(i);
    lightOn(i + 3);
    doDelay(delayMedium);
  }
  for (int i = 0; i < 3; i++) {
    lightOff(i);
    lightOff(i + 3);
    doDelay(delayMedium);
  }
}

// ======================================================================
void basicFlash() {
  allOff();
  for (int i = 0; i < 6; i++) {
    for (int y = 0; y < 1; y++) {
      lightOn(i);
      doDelay(delayShort);
      lightOff(i);
      doDelay(delayShort);
    }
  }
}

// ======================================================================
void basicLeftRight() {
  allOff();
  for (int i = 0; i < 3; i++) {
      lightOn(0);
      lightOn(1);
      lightOn(2);
      lightOff(3);
      lightOff(4);
      lightOff(5);
      doDelay(delayShort);
      lightOff(0);
      lightOff(1);
      lightOff(2);
      lightOn(3);
      lightOn(4);
      lightOn(5);
      doDelay(delayShort);
  }
}

// ======================================================================
void basicTraffic() {
  allOff();

  // Red      Green
  lightOn(red1);
  lightOn(green2);
  doDelay(delayLong*2);

  // Red      Yellow
  lightOff(green2);
  lightOn(yellow2);
  doDelay(delayMedium);

  // Red      Red
  lightOff(yellow2);
  lightOn(red2);
  doDelay(delayShort);

  // Green    Red
  lightOff(red1);
  lightOn(green1);
  doDelay(delayLong *2);

  // Yellow    Red
  lightOff(green1);
  lightOn(yellow1);
  doDelay(delayMedium);

  // Red      Red
  lightOff(yellow1);
  lightOn(red1);
  doDelay(delayShort);

  // Turn them off to finish
  lightOff(red1);
  lightOff(red2);
}



