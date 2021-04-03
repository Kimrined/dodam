#include <OneWire.h>  
#include <DallasTemperature.h>  
    
//DS18B20 온도 센서의 데이터선인 가운데 핀을 아두이노 3번에 연결합니다.   
#define ONE_WIRE_BUS 3  
    
//1-wire 디바이스와 통신하기 위한 준비  
OneWire oneWire(ONE_WIRE_BUS);  
    
// oneWire선언한 것을 sensors 선언시 참조함.  
DallasTemperature sensors(&oneWire);  
    
//다비아스 주소를 저장할 배열 선언  
DeviceAddress insideThermometer;  
    
    
void setup(void)  
{  
  //시리얼 포트 초기화  
  Serial.begin(9600);  
  Serial.println("Dallas Temperature IC Control Library Demo");  
    
  //1-wire 버스 초기화  
  sensors.begin();  
      
  //발견한 디바이스 갯수  
  Serial.print("Found ");  
  Serial.print(sensors.getDeviceCount(), DEC);  
  Serial.println(" devices.");  
    
  // parasite power 모드일 때에는  2핀(GND와 DQ 핀)만 연결하면 됨.  
  Serial.print("Parasite power is: ");   
  if (sensors.isParasitePowerMode()) Serial.println("ON");  
  else Serial.println("OFF");  
      
     
  //버스에서 첫번째 장치의 주소를 가져온다.  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");   
      
  //버스에서 발견한 첫번째 장치의 주소 출력  
  Serial.print("Device 0 Address: ");  
  printAddress(insideThermometer);  
  Serial.println();  
    
  //데이터시트에서 확인결과 9~12비트까지 설정 가능  
  sensors.setResolution(insideThermometer, 10);  
     
  Serial.print("Device 0 Resolution: ");  
  Serial.print(sensors.getResolution(insideThermometer), DEC);   
  Serial.println();  

  //아래는 RGB LED 코드 각 포트에서 출력
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}  
    
    
// 온도를 출력하는 함수  
void printTemperature(DeviceAddress deviceAddress)  
{  
  //섭씨 온도를 가져옴  
  float  tempC = sensors.getTempC(deviceAddress);  
      
  Serial.print("Temp C: ");  
  Serial.print(tempC);  
  Serial.print(" Temp F: ");  
      
  //화씨 온도로 변환  
  Serial.println(DallasTemperature::toFahrenheit(tempC));   
}  
    
//디바이스 주소를 출력하는 함수  
void printAddress(DeviceAddress deviceAddress)  
{  
  for (uint8_t i = 0; i < 8; i++)  
  {  
    if (deviceAddress[i] < 16) Serial.print("0");  
        Serial.print(deviceAddress[i], HEX);  
  }  
}  
    
    
void loop(void)  
{   
  Serial.print("Requesting temperatures...");  
  //sensors.requestTemperatures();   //연결되어 있는 전체 센서의 온도 값을 읽어옴  
  sensors.requestTemperaturesByIndex(0); //첫번째 센서의 온도값 읽어옴  
  Serial.println("DONE");  

  // RGB LED 코드, 빨>초>파 순서대로 불이 켜짐
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(500);

  digitalWrite(9,LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(500);

  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delay(500);
     
  //센서에서 읽어온 온도를 출력  
  printTemperature(insideThermometer);  
}  
