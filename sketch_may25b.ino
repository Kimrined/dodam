#include <OneWire.h>

int water = A1;              // 탁도 센서 A1 핀으로 연결
int temp = 2;                // 온도 센서 2번 핀으로 연결

OneWire ds(temp);


void setup(){
  Serial.begin(115200);

  pinMode(water, INPUT);       // 탁도 센서로 정보 입력 받음
  pinMode(4, OUTPUT);         // output으로 히터 출력 설정

}

void loop(){
  char a = 0;
  a = Serial.read();
  if(a == '1') { // 1을 입력했을 때 켜짐
    digitalWrite(4, HIGH);
    Serial.println("hiter On"); // 추후 주석 처리
  }
  else if(a == '0') { // 0을 입력했을 때 꺼짐
    digitalWrite(4, LOW);
    Serial.print("Input data : "); // 추후 주석처리
    Serial.println(a); // a의 값 출력, 추후 주석처리
    Serial.println("hiter Off"); // 추후 주석 처리
  }
  delay(500);
  
  float temp = getTemp();
  Serial.println(temp);
  int water = analogRead(A0);
  float voltage = water*(5.0/1024.0);

  Serial.println(voltage);
  delay(1000);
  
  int level = analogRead(A0);               // 수위 센서 A0 핀으로 연결
  Serial.println(level);
  delay(1000);
}

float getTemp(){                                   //온도 측정 후 반환하는 함수
 byte data[12];
 byte addr[8];
 if ( !ds.search(addr)) {
   ds.reset_search();
   return -1000;
 }
 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }
 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }
 ds.reset();
 ds.select(addr);
 ds.write(0x44,1);                                   
 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); 
 
 for (int i = 0; i < 9; i++) { 
  data[i] = ds.read();                                                          
 }
 
 ds.reset_search(); 
 byte MSB = data[1];
 byte LSB = data[0];
 float tempRead = ((MSB << 8) | LSB); 
 float TemperatureSum = tempRead / 16; 
 return TemperatureSum;                                                                    
}
