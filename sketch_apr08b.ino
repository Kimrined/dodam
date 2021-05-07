#include <OneWire.h>

int sensor_in = A1;                 // 탁도 센서 A0 핀으로 연결
int DS18S20_Pin = 2;                // 온도 센서 2번 핀으로 연결

OneWire ds(DS18S20_Pin);

void setup(){
  Serial.begin(9600);

  pinMode(sensor_in, INPUT);       // 탁도 센서로 정보 입력 받음
}

void loop(){  
  float temperature = getTemp();
  Serial.println(temperature);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue*(5.0/1024.0);

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
