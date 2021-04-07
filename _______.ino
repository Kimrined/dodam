int tmp = 0;

void setup() {
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tmp = 0.488155 * (analogRead(A0));
  if(tmp<20) {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
 if(tmp>=20 && tmp<=28) {
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);
  }
   if(tmp>28) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  Serial.println(tmp);
}
