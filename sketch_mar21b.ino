void setup() {
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(0);
  float volt = val*5.0/1024;
  float temp = volt*100;
  Serial.println(temp);
  delay(1000);

}
