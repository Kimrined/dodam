#include <OneWire.h>

int sensor_in = A1;                 // 탁도 센서 A0 핀으로 연결
int DS18S20_Pin = 2;                // 온도 센서 2번 핀으로 연결

OneWire ds(DS18S20_Pin);

void setup(){
  Serial.begin(9600);

  pinMode(sensor_in, INPUT);       // 탁도 센서로 정보 입력 받음
  pinMode(13, OUTPUT);  // output으로 LED 출력 설정
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop(){  
  float temperature = getTemp();
  Serial.println(temperature);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue*(5.0/1024.0);
  
  if(temperature<20){       // 온도 센서로 읽어들임
    digitalWrite(11, HIGH);   // 온도가 20도 미만이면 B LED 작동
  }
  else{
    digitalWrite(11, LOW);    // 아니면 B LED 종료
  }
  if(temperature>=20 && temperature<=28){       // 온도 센서로 읽어들임
    digitalWrite(12, HIGH);   // 온도가 20이상 28도 이하면 G LED 작동
  }
  else{
    digitalWrite(12, LOW);    // 아니면 LED 종료
  }
  if(temperature>28){       // 온도 센서로 읽어들임
    digitalWrite(13, HIGH);   // 온도가 28도 초과면 LED 작동
  }
  else{
    digitalWrite(13, LOW);    // 아니면 LED 종료
  }

  Serial.println(voltage);
  delay(2000);
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
