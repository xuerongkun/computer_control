#include <Arduino.h>
#include <U8x8lib.h>
#include "DHTesp.h" 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "ssio.h"

SoftwareSerial ESPserial(12,13); 
SoftwareSerial DT(4, 5); 
DHTesp dht;

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 10, /* data=*/ 0, /* reset=*/ U8X8_PIN_NONE);         // Digispark ATTiny85
void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  dht.setup(14, DHTesp::DHT11); // Connect DHT sensor to GPIO 17
  Serial.begin(9600);
  ESPserial.begin(115200); 
  DT.begin(115200);
  
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_8x13_1x2_r);
  u8x8.drawString(0,0,"Robot condition:");

  //DIS4000mm();//测距量程设置为4.0m
  DIS1300mm();//测距量程设置为1.3m
  delay(2000);
  //outputTIME10S();//设置输出间隔时间10S
  //outputTIME2S();//设置输出间隔时间2S
  //outputTIME500MS();//设置输出间隔时间500MS
  outputTIME100MS();//设置输出间隔时间100MS
  delay(2000);
  JZJZ();//设置为加载校准模式
  delay(2000);
  modRST();//重启

  offset();//校准
  xtalk();//
}

void loop(void)
{ 
  if (DT.available() > 6){
    char a = DT.read();
    if(a != 0x01)
      return;
    byte Buf[6];
    DT.readBytes(Buf, 6);
    for (int i = 0; i < 6; i++){
      if (Buf[i] < 0x10)
        Serial.print("0x0");
      else
        Serial.print("0x");
      Serial.print(Buf[i], HEX);
    }
    if (Buf[2] == 0xFF){
      Serial.println("Distance:");
      Serial.println("invalid");
      return;
    }   
    float distance = Buf[2] * 256 + Buf[3];
    Serial.println("Distance:");
    Serial.print(distance);
    if (distance <100){
      digitalWrite(LED_BUILTIN, LOW);
      }
     else{
      digitalWrite(LED_BUILTIN, HIGH);
      }
    char displaybuf1[32];
    sprintf(displaybuf1,"DIStance: %.1f",distance);
    u8x8.drawString(0,2,displaybuf1);
    Serial.print("mm");
  }
  char displaybuf[32];
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  sprintf(displaybuf,"RH: %.1f T: %.1f",humidity,temperature);
  u8x8.drawString(0,4,displaybuf);
  if (ESPserial.available() == 5) {
    for (int i = 0 ; i <= 4; i++) {
      uart_cmd[i] =  char(ESPserial.read());
    }
    if (uart_cmd[0] == 0xaa && uart_cmd[1] == 0x55 && uart_cmd[3] == 0x55 && uart_cmd[4] == 0xaa) {
     //Serial.print("check!");
     //Serial.print(uart_cmd[2], HEX);
     // client.publish("/smart-light/cmd", String(uart_cmd[2]));
    }
    if (uart_cmd[2] == 0x01) {
      u8x8.drawString(0, 6, "GO GO GO!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (uart_cmd[2] == 0x02) {
      u8x8.drawString(0, 6, "BACK BACK!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (uart_cmd[2] == 0x03) {
      u8x8.drawString(0, 6, "STOP STOP!");
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if (uart_cmd[2] == 0x05) {
      u8x8.drawString(0, 6, "LEFT LEFT!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
    else if (uart_cmd[2] == 0x04) {
      u8x8.drawString(0, 6, "RIGHT RIGHT!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      u8x8.drawString(0, 6, "WATING WATING!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  delay(500);
}


//*********************SYS系统设置*************************//
//*******offset偏移校准函数
void offset()
{
  for (int i = 0; i < 8; i++)
    DT.write(SYSCMD[0][i]);
}
//*******xtalk串扰校准函数
void xtalk()
{
  for (int i = 0; i < 8; i++)
    DT.write(SYSCMD[1][i]);
}
//*********是/否 加载校准
void JZJZ()//加载校准
{
  for (int i = 0; i < 8; i++)
    DT.write(SYSCMD[2][i]);
}
//*********测距模块重启函数
void modRST()//测距模块重启
{
  for (int i = 0; i < 8; i++)
    DT.write(SYSCMD[8][i]);
}
//*********************设置连续输出时间间隔函数集*************************//
void outputTIME100MS()//输出时间间隔100ms
{
  for (int i = 0; i < 8; i++)
    DT.write(timeCMD[0][i]);
}
void outputTIME500MS()//输出时间间隔500ms
{
  for (int i = 0; i < 8; i++)
    DT.write(timeCMD[1][i]);
}
void outputTIME2S()//输出时间间隔2s
{
  for (int i = 0; i < 8; i++)
    DT.write(timeCMD[2][i]);
}
void outputTIME10S()//输出时间间隔10s
{
  for (int i = 0; i < 8; i++)
    DT.write(timeCMD[3][i]);
}
//**********************测距距离（量程）模式选择函数***************************//
void DIS1300mm()//测距量程设置为1.3m
{
  for (int i = 0; i < 8; i++)
    DT.write(distanceCMD[0][i]);
}

void DIS4000mm()//测距量程设置为4m
{
  for (int i = 0; i < 8; i++)
    DT.write(distanceCMD[1][i]);
}
