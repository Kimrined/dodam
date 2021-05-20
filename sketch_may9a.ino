void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT); // 4번 출력
}

void loop() {
    char a = 0;
    a = Serial.read();
    if(a == '1') { // 1을 입력했을 때 켜짐
      digitalWrite(4, HIGH);
      Serial.println("hiter On");
    }
    else if(a == '0') { // 0을 입력했을 때 꺼짐
      digitalWrite(4, LOW);
      Serial.print("Input data : ");
      Serial.println(a); // a의 값 출력
      Serial.println("hiter Off");
    }
    delay(500);
 }
