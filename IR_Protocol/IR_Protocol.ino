const int irLedPin = 3;
const int xpin = A5;
const int ypin = A3;
const int throttlePin = A7;

unsigned long lastSendTimeMs = 0;
int yaw = 63;
int pitch = 63;
int throttle = 127;
int yawCorrection = 63;

int prevX = 0;
int prevY = 0;
float alpha = .3;

void setup() {
  analogReference(EXTERNAL);
  //Serial.begin(115200);
  pinMode(irLedPin, OUTPUT);
  prevX = analogRead(xpin);
  delay(100);
  prevY = analogRead(ypin);

}

void loop() {

  while(millis() - lastSendTimeMs < 115) {
  }
  lastSendTimeMs = millis();
  sendCommands();
  //unsigned long now = millis();
  throttle = analogRead(throttlePin) / 8;
  delay(20);
  int x = (alpha*analogRead(xpin) + (1 - alpha)*prevX);
  prevX = x;
  pitch = 127 - (x - 454);
  delay(20);
  int y = (alpha*analogRead(ypin) + (1 - alpha)*prevY);
  prevY = y;
  yaw = 127 - (y - 454);
  delay(20);
}


void sendCommands() {
  sendStartSymbol();
  sendControl(yaw);
  sendControl(pitch);
  sendControl(throttle);
  sendControl(yawCorrection);
  sendEndSymbol();  
}

void sendControl(int val) {
  sendZero();
  for(int i = 6; i >= 0; i--) {
    if(bitRead(val, i) == 0) {
      sendZero();
    } else {
      sendOne();
    }
  }
}


//4000us
void sendStartSymbol() {
   for(int i = 0; i < 77; i++) {
    digitalWrite(irLedPin, HIGH);
    delayMicroseconds(6);
    digitalWrite(irLedPin, LOW);
    delayMicroseconds(6);
  }
   delayMicroseconds(1998);
}

void sendEndSymbol() {
  setHigh300us();
}

void sendZero() {
  setHigh300us();
  delayMicroseconds(300);
}

void sendOne() {
  setHigh300us();
  delayMicroseconds(695);
}

void setHigh300us() {
  for(int i = 0; i < 11; i++) {
    digitalWrite(irLedPin, HIGH);
    delayMicroseconds(6);
    digitalWrite(irLedPin, LOW);
    delayMicroseconds(6);
  } 
  digitalWrite(irLedPin, HIGH);
  delayMicroseconds(6);
  digitalWrite(irLedPin, LOW);
}
  
