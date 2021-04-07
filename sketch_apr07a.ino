int ledPin = 13;                // LED를 13번 핀으로 연결 
int sensor_in = 2;                 // 탁도 센서 2번 핀으로 연결

void setup(){
  //Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // output으로 LED 출력 설정
  pinMode(sensor_in, INPUT);       // 탁도 센서로 정보 입력 받음
}

void loop(){
  //int sensorValue = analogRead(A0);
  //float voltage = sensorValue*(5.0/1024.0);
  if(digitalRead(sensor_in)==LOW){       // 센서로 읽어들임
    digitalWrite(ledPin, HIGH);   // 센서가 탁한 물에 들어가면 LED 작동
  }
  else{
    digitalWrite(ledPin, LOW);    // 센서가 물에 들어면 LED 종료
  }

  //Serial.println(voltage);
  //delay(500);
}
