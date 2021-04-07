int tmp = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(2, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tmp = 0.488155 * analogRead(A0);
  if(tmp<24) {
    digitalWrite(2,HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  if(tmp>28) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  Serial.println(tmp);
}
