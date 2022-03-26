#include "NewPing.h"

#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define enginePowerLeft 9
#define enginePowerRight 3
#define colorDetectorA0 A5 
#define colorDetectorD0 8
#define frontEyeTrig 10
#define frontEyeEcho 11
#define leftEyeTrig A0
#define leftEyeEcho A1
#define rightEyeTrig A3
#define rightEyeEcho A2


int colorDetectorA0Value;
bool colorDetectorD0Value;

char receivedBluetooth = 0;

NewPing sonarFront(frontEyeTrig, frontEyeEcho, 400);
NewPing sonarLeft(leftEyeTrig, leftEyeEcho, 400);
NewPing sonarRight(rightEyeTrig, rightEyeEcho, 400);

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enginePowerLeft, OUTPUT);
  pinMode(enginePowerRight, OUTPUT);
  pinMode(frontEyeEcho, INPUT);
  pinMode(frontEyeTrig, OUTPUT);
  pinMode(frontEyeEcho, INPUT);
  pinMode(frontEyeTrig, OUTPUT);
  pinMode(rightEyeEcho, INPUT);
  pinMode(rightEyeTrig, OUTPUT);
  pinMode(leftEyeEcho, INPUT);
  pinMode(leftEyeTrig, OUTPUT);
  
  analogWrite(enginePowerLeft, 100);
  analogWrite(enginePowerRight, 100);

  // siyah nokta sensorü
  pinMode (colorDetectorA0, INPUT);
  pinMode (colorDetectorD0, INPUT);
  
  Serial.begin(9600);                                 
}

void loop() {

 colorDetectorA0Value = analogRead(colorDetectorA0); // reads the analog input from the IR distance sensor
 colorDetectorD0Value = digitalRead(colorDetectorD0);// reads the digital input from the IR distance sensor
 
 if(Serial.available() > 0)      // Bluetoothtan sadece veri geldiğinde okuma kodunu aktif eder:
 {
     receivedBluetooth = Serial.read();        // Bluetooth verisini okur ve receivedBluetooth değişkenine kaydeder
 }
if( receivedBluetooth == 'w' ){
    Serial.print("Emir (");
    Serial.print(receivedBluetooth);
    Serial.println("): Bir birim ileri.");
    // Bir birim ileri
    goForward();
 }else if(receivedBluetooth == 's' ){
    Serial.print("Emir (");
    Serial.print(receivedBluetooth);
    Serial.println("): Bir birim geri.");
    goBack();
 }else if(receivedBluetooth == 'a' ){
    Serial.print("Emir (");
    Serial.print(receivedBluetooth);
    Serial.println("): Sola dön." );
    turnLeft();
 }else if(receivedBluetooth == 'd' ){
    Serial.print("Emir (");
    Serial.print(receivedBluetooth);
    Serial.println("): Sağa dön." );
    turnRight();
 }else if(receivedBluetooth == 'p' ){
   Serial.print("Emir (");
   Serial.print(receivedBluetooth);
   Serial.println("): Algoritmayı başlat." );
 }else if(receivedBluetooth == 'x' ){
   Serial.print("Emir (");
   Serial.print(receivedBluetooth);
   Serial.println("): Algoritmayı durdur." );
   stopEngine();
 }else if(receivedBluetooth == 't' ){
   Serial.print("Emir (");
   Serial.print(receivedBluetooth);
   Serial.print("): Turn180" );
   turn180();
 }
 receivedBluetooth = 0;
 Serial.print("Floor : ");
 Serial.println(getFloorInfo(colorDetectorA0Value,colorDetectorD0Value));
 Serial.print(" -- DistanceFront : ");
 Serial.print(getDistanceFromFrontEye());
 Serial.print(" -- DistanceRight : ");
 Serial.print(getDistanceFromRightEye());
 Serial.print(" -- DistanceLeft : ");
 Serial.println(getDistanceFromLeftEye());
 delay(1000);
}
void goBack(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
  stopEngine();
}
void goForward(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500);
  stopEngine();
}
void turn180(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(1250);
  stopEngine();
}
void turnRight(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(600);
  stopEngine();
}
void turnLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(600);
  stopEngine();
}
void stopEngine(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
char getFloorInfo(int contrast, bool result){
   return (contrast>500 && result == 1)?'b':'w';
}
int getDistanceFromFrontEye(){
  return sonarFront.ping_cm();

}
int getDistanceFromRightEye(){
  return sonarRight.ping_cm();

}
int getDistanceFromLeftEye(){
  return sonarLeft.ping_cm();

}
