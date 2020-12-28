/*
  recieved data to motors
*/

#include <Servo.h>
// create servo object to control servos
Servo sm00;   
Servo sm01;  
Servo sm02;
Servo sm03;
Servo sm04;
Servo sm05;
Servo sm06;
Servo sm07;
Servo sm08;
Servo sm09;
Servo sm10;
Servo sm11;
Servo sm12;
Servo sm13;
Servo sm14;
Servo sm15;

// variable to store the servo position
int pos00 = 0;
int pos01 = 0;
int pos02 = 0;
int pos03 = 0;
int pos04 = 0;
int pos05 = 0;
int pos06 = 0;
int pos07 = 0;
int pos08 = 0;
int pos09 = 0;
int pos10 = 0;
int pos11 = 0;
int pos12 = 0;
int pos13 = 0;
int pos14 = 0;
int pos15 = 0;

// new data flag
int newData = 0;

// to save bits of received bytes
int m00 = 0;
int m01 = 0;
int m02 = 0;
int m03 = 0;
int m04 = 0;
int m05 = 0;
int m06 = 0;
int m07 = 0;
int m08 = 0;
int m09 = 0;
int m10 = 0;
int m11 = 0;
int m12 = 0;
int m13 = 0;
int m14 = 0;
int m15 = 0;

// motors status
int stat00 = 0;
int stat01 = 0;
int stat02 = 0;
int stat03 = 0;
int stat04 = 0;
int stat05 = 0;
int stat06 = 0;
int stat07 = 0;
int stat08 = 0;
int stat09 = 0;
int stat10 = 0;
int stat11 = 0;
int stat12 = 0;
int stat13 = 0;
int stat14 = 0;
int stat15 = 0;

// data storage
const byte numBytes = 2;
byte receivedBytes[numBytes];

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino is ready!");
  
  // attach servos on pins 38~53 to servo objects
  sm00.attach(38);
  sm01.attach(39);
  sm02.attach(40);
  sm03.attach(41);
  sm04.attach(42);
  sm05.attach(43);
  sm06.attach(44);
  sm07.attach(45);
  sm08.attach(46);
  sm09.attach(47);
  sm10.attach(48);
  sm11.attach(49);
  sm12.attach(50);
  sm13.attach(51);
  sm14.attach(52);
  sm15.attach(53);

  // set servos initial position
  sm00.write(0);
  sm01.write(0);
  sm02.write(0);
  sm03.write(0);
  sm04.write(0);
  sm05.write(0);
  sm06.write(0);
  sm07.write(0);
  sm08.write(0);
  sm09.write(0);
  sm10.write(0);
  sm11.write(0);
  sm12.write(0);
  sm13.write(0);
  sm14.write(0);
  sm15.write(0);
}

void loop() {
    recvBytes();
    
    if (newData == 1) // call the function only if new data received
      controlMotors();
    else if (newData == 0)
      asm("nop");
}

void recvBytes() {
  // receive 2 bytes (16 bits) from serial port
  // each bit shows the status of one motor
  // read data from serial port
  // Need to set it only when there is new information coming
  //receivedBytes[0] = ;
  //receivedBytes[1] = ;
  // set newData flag to 1 if new data received
}

void controlMotors() {
  // extract the status of each motor from received bytes 
  m00 = bitRead(receivedBytes[0],0);
  m01 = bitRead(receivedBytes[0],1);
  m02 = bitRead(receivedBytes[0],2);
  m03 = bitRead(receivedBytes[0],3);
  m04 = bitRead(receivedBytes[0],4);
  m05 = bitRead(receivedBytes[0],5);
  m06 = bitRead(receivedBytes[0],6);
  m07 = bitRead(receivedBytes[1],7);
  m08 = bitRead(receivedBytes[1],0);
  m09 = bitRead(receivedBytes[1],1);
  m10 = bitRead(receivedBytes[1],2);
  m11 = bitRead(receivedBytes[1],3);
  m12 = bitRead(receivedBytes[1],4);
  m13 = bitRead(receivedBytes[1],5);
  m14 = bitRead(receivedBytes[1],6);
  m15 = bitRead(receivedBytes[1],7);
  
  // motor 0
  if (m00 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat00 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat00 == 0){
        for (pos00 = 0; pos00 <= 180; pos00 += 1){sm00.write(pos00);}
        stat00 = 1; }} // motor is up, change its status to 1
  else if (m00 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat00 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat00 == 1){
        for (pos00 = 180; pos00 >= 0; pos00 -= 1) {sm00.write(pos00);}
        stat00 = 0; }} // motor is down, change its status to 0

  // motor 1
  if (m01 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat01 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat01 == 0){
        for (pos01 = 0; pos01 <= 180; pos01 += 1){sm01.write(pos01);}
        stat01 = 1; }} // motor is up, change its status to 1
  else if (m01 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat01 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat01 == 1){
        for (pos01 = 180; pos01 >= 0; pos01 -= 1) {sm01.write(pos01);}
        stat01 = 0; }} // motor is down, change its status to 0
  
  // motor 2
  if (m02 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat02 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat02 == 0){
        for (pos02 = 0; pos02 <= 180; pos02 += 1){sm02.write(pos02);}
        stat02 = 1; }} // motor is up, change its status to 1
  else if (m02 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat02 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat02 == 1){
        for (pos02 = 180; pos02 >= 0; pos02 -= 1) {sm02.write(pos02);}
        stat02 = 0; }} // motor is down, change its status to 0
  
  // motor 3
  if (m03 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat03 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat03 == 0){
        for (pos03 = 0; pos03 <= 180; pos03 += 1){sm03.write(pos03);}
        stat03 = 1; }} // motor is up, change its status to 1
  else if (m03 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat03 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat03 == 1){
        for (pos03 = 180; pos03 >= 0; pos03 -= 1) {sm03.write(pos03);}
        stat03 = 0; }} // motor is down, change its status to 0
  
  // motor 4
  if (m04 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat04 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat04 == 0){
        for (pos04 = 0; pos04 <= 180; pos04 += 1){sm04.write(pos04);}
        stat04 = 1; }} // motor is up, change its status to 1
  else if (m04 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat04 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat04 == 1){
        for (pos04 = 180; pos04 >= 0; pos04 -= 1) {sm04.write(pos04);}
        stat04 = 0; }} // motor is down, change its status to 0

  // motor 5
  if (m05 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat05 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat05 == 0){
        for (pos05 = 0; pos05 <= 180; pos05 += 1){sm05.write(pos05);}
        stat05 = 1; }} // motor is up, change its status to 1
  else if (m05 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat05 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat05 == 1){
        for (pos05 = 180; pos05 >= 0; pos05 -= 1) {sm05.write(pos05);}
        stat05 = 0; }} // motor is down, change its status to 0

  // motor 6
  if (m06 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat06 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat06 == 0){
        for (pos06 = 0; pos06 <= 180; pos06 += 1){sm06.write(pos06);}
        stat06 = 1; }} // motor is up, change its status to 1
  else if (m06 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat06 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat06 == 1){
        for (pos06 = 180; pos06 >= 0; pos06 -= 1) {sm06.write(pos06);}
        stat06 = 0; }} // motor is down, change its status to 0

  // motor 7
  if (m07 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat07 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat07 == 0){
        for (pos07 = 0; pos07 <= 180; pos07 += 1){sm07.write(pos07);}
        stat07 = 1; }} // motor is up, change its status to 1
  else if (m07 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat07 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat07 == 1){
        for (pos07 = 180; pos07 >= 0; pos07 -= 1) {sm07.write(pos07);}
        stat07 = 0; }} // motor is down, change its status to 0

  // motor 8
  if (m08 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat08 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat08 == 0){
        for (pos08 = 0; pos08 <= 180; pos08 += 1){sm08.write(pos08);}
        stat08 = 1; }} // motor is up, change its status to 1
  else if (m08 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat08 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat08 == 1){
        for (pos08 = 180; pos08 >= 0; pos08 -= 1) {sm08.write(pos08);}
        stat08 = 0; }} // motor is down, change its status to 0

  // motor 9
  if (m09 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat09 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat09 == 0){
        for (pos09 = 0; pos09 <= 180; pos09 += 1){sm09.write(pos09);}
        stat09 = 1; }} // motor is up, change its status to 1
  else if (m09 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat09 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat09 == 1){
        for (pos09 = 180; pos09 >= 0; pos09 -= 1) {sm09.write(pos09);}
        stat09 = 0; }} // motor is down, change its status to 0

  // motor 10
  if (m10 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat10 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat10 == 0){
        for (pos10 = 0; pos10 <= 180; pos10 += 1){sm10.write(pos10);}
        stat10 = 1; }} // motor is up, change its status to 1
  else if (m10 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat10 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat10 == 1){
        for (pos10 = 180; pos10 >= 0; pos10 -= 1) {sm10.write(pos10);}
        stat10 = 0; }} // motor is down, change its status to 0

  // motor 11
  if (m11 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat11 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat11 == 0){
        for (pos11 = 0; pos11 <= 180; pos11 += 1){sm11.write(pos11);}
        stat11 = 1; }} // motor is up, change its status to 1
  else if (m11 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat11 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat11 == 1){
        for (pos11 = 180; pos11 >= 0; pos11 -= 1) {sm11.write(pos11);}
        stat11 = 0; }} // motor is down, change its status to 0

  // motor 12
  if (m12 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat12 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat12 == 0){
        for (pos12 = 0; pos12 <= 180; pos12 += 1){sm12.write(pos12);}
        stat12 = 1; }} // motor is up, change its status to 1
  else if (m12 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat12 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat12 == 1){
        for (pos12 = 180; pos12 >= 0; pos12 -= 1) {sm12.write(pos12);}
        stat12 = 0; }} // motor is down, change its status to 0

  // motor 13
  if (m13 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat13 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat13 == 0){
        for (pos13 = 0; pos13 <= 180; pos13 += 1){sm13.write(pos13);}
        stat13 = 1; }} // motor is up, change its status to 1
  else if (m13 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat13 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat13 == 1){
        for (pos13 = 180; pos13 >= 0; pos13 -= 1) {sm13.write(pos13);}
        stat13 = 0; }} // motor is down, change its status to 0

  // motor 14
  if (m14 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat14 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat14 == 0){
        for (pos14 = 0; pos14 <= 180; pos14 += 1){sm14.write(pos14);}
        stat14 = 1; }} // motor is up, change its status to 1
  else if (m14 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat14 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat14 == 1){
        for (pos14 = 180; pos14 >= 0; pos14 -= 1) {sm14.write(pos14);}
        stat14 = 0; }} // motor is down, change its status to 0

  // motor 15
  if (m15 == 1){
    // activate the block
    // turn on the led
    // push the cube up
    if (stat15 == 1) // if it is already up do nothing
        asm("nop");
    else if (stat15 == 0){
        for (pos15 = 0; pos15 <= 180; pos15 += 1){sm15.write(pos15);}
        stat15 = 1; }} // motor is up, change its status to 1
  else if (m15 == 0) {
    // deactivate the block
    // turn off the led
    // pull the cube down
    if (stat15 == 0) // if it is already down do nothing
        asm("nop");
    else if (stat15 == 1){
        for (pos15 = 180; pos15 >= 0; pos15 -= 1) {sm15.write(pos15);}
        stat15 = 0; }} // motor is down, change its status to 0

}
