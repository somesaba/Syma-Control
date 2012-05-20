const int irLedPin = 12;
unsigned long lastSendTimeMs = 0;
int yaw = 0;
int pitch = 0;
int throttle = 127;
int yawCorrection = 0;

void setup() {
  //Serial.begin(115200);
  pinMode(irLedPin, OUTPUT);
}

void loop() {
  if(millis() - lastSendTimeMs >= 180) {
    lastSendTimeMs = millis();
    sendCommands();
    //unsigned long diff = millis() - lastSendTimeMs;
    //Serial.println(diff);
  }
}


void sendCommands() {
  sendStartSymbol();
  sendControl(yaw);
  sendControl(pitch);
  sendThrottle();
  sendControl(yawCorrection);
  sendEndSymbol();  
}

void sendThrottle() {
  sendOne();
  for(int i = 0; i < 7; i++) {
    if(bitRead(throttle, i) == 0) {
      sendZero();
    } else {
      sendOne();
    }
  }
}

void sendControl(int val) {
  sendZero();
  for(int i = 0; i < 7; i++) {
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
    delayMicroseconds(13);
    digitalWrite(irLedPin, LOW);
    delayMicroseconds(13);
  }
   delayMicroseconds(1998);
}

void sendEndSymbol() {
  setHigh300Ms();
}

void sendZero() {
  setHigh300Ms();
  delayMicroseconds(288);
}

void sendOne() {
  setHigh300Ms();
  delayMicroseconds(688);
}

void setHigh300Ms() {
  for(int i = 0; i < 12; i++) {
    digitalWrite(irLedPin, HIGH);
    delayMicroseconds(13);
    digitalWrite(irLedPin, LOW);
    delayMicroseconds(13);
  }
}
  
