void setup() {
  Serial.begin(9600);
}
void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1024.0); // 0~5V 까지는 0~1023 수치로 나타냄
  Serial.println(voltage);
  delay(500);
}
