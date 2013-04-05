//Arduino Control

int incomingByte = 0;	// for incoming serial data
int lastByte = 0;
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int dirA = 12;
const int dirB = 13;

void setup()   {                
  // initialize the digital pin as an output:
  Serial.begin(9600);
  
//Setup Channel A
pinMode(dirA, OUTPUT); //Initiates Motor Channel A pin
pinMode(brakeA, OUTPUT); //Initiates Brake Channel A pin

//Setup Channel B
pinMode(dirB, OUTPUT); //Initiates Motor Channel A pin
pinMode(brakeB, OUTPUT); //Initiates Brake Channel A pin
}

// the loop() method runs over and over again,
// as long as the Arduino has power
void Move(int aDir,int bDir,int aSpeed=255,int bSpeed=255){
  //Motor A
  digitalWrite(dirA, aDir);  //Sets direction
  digitalWrite(brakeA, LOW);    //Removes break
  analogWrite(pwmA, aSpeed);  //Sets speed (max 255)
  
  //Motor B
  digitalWrite(dirB, bDir);  //Sets direction
  digitalWrite(brakeB, LOW);    //Removes break
  analogWrite(pwmB, bSpeed); //Sets speed (max 255)
}
void Turn(int turningDir, int pwm=255){
  //Motor A
  digitalWrite(dirA, turningDir);  //Sets direction
  digitalWrite(brakeA, LOW);
  analogWrite(pwmA, pwm);
  
  //Motor B
  digitalWrite(dirB, turningDir);  //Sets direction
  digitalWrite(brakeB, LOW);
  analogWrite(pwmB, pwm); //Sets speed (max 255)
}
void stopAll(){
  //Motor A
  digitalWrite(brakeA, HIGH);   //Enables break for MotorA
  analogWrite(pwmA, 0);
  //Motor B
  digitalWrite(brakeB, HIGH);   //Enables break for MotorB
  analogWrite(pwmB, 0);
}

void loop(){
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte != lastByte && incomingByte != 10) {
      Serial.println(incomingByte);
      lastByte = incomingByte;
      switch(incomingByte){
        case 48: Move(0,1);  //0
        case 49: Move(1,0);  //1
        case 50: Turn(1);    //2
        case 51: Turn(0);    //3
        case 52: stopAll();  //4
        break;
        case 53:              //5
          //ledStatus = digitalRead(inPin);
          //Serial.println(ledStatus);
          //ledStatus = !ledStatus;
          //digitalWrite(ledPin, ledStatus)
        break;
      }
    }
  }
}