#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>  
const byte RX = 3;         
const byte TX = 2;          
 
SoftwareSerial mySerial = SoftwareSerial(RX,TX); 
 
 
SerialCommand sCmd(mySerial); 
 
int red = 4, blue = 5; 
int lightsensor = 6;
int lpower = 7;
const unsigned long chu_ky_lenh = 2000UL;
void setup() {
 
  Serial.begin(57600);

  mySerial.begin(57600);
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(lightsensor,INPUT);
  pinMode(lpower,OUTPUT);
  digitalWrite(lpower,HIGH);
  sCmd.addCommand("LED",led); 
  sCmd.addCommand("LIGHT",light_detect);
  Serial.println("Da san sang nhan lenh");
}

unsigned long chu_ky=0;
void loop() {
  if(millis() - chu_ky >chu_ky_lenh){
    chu_ky=millis();
    light_detect();
    }
  sCmd.readSerial();
}
 

void led() {
  Serial.println("LED");
  char *json = sCmd.next(); 
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; 
  JsonObject& root = jsonBuffer.parseObject(json);
  int redStatus = root["led"][0];  
  int blueStatus = root["led"][1];
  int sensorStatus = root["led"][2];
 
  Serial.print(F("redStatus"));
  Serial.println(redStatus); 
  Serial.print(F("blueStatus"));
  Serial.println(blueStatus);
  Serial.print(F("sensorStatus"));
  Serial.println(sensorStatus);
////
  StaticJsonBuffer<200> jsonBuffer2; 
  JsonObject& root2 = jsonBuffer2.createObject();
  root2["redStatus"] = redStatus;
  root2["blueStatus"] = blueStatus;
  root2["sensorStatus"]= sensorStatus;
  JsonArray& data = root2.createNestedArray("data");
  data.add(redStatus);
  data.add(blueStatus);
  data.add(sensorStatus);
  
  mySerial.print("LED_STATUS");
  mySerial.print('\r');
  root2.printTo(mySerial);
  mySerial.print('\r');
  root2.printTo(Serial);
  
  digitalWrite(red,redStatus);
  digitalWrite(blue,blueStatus);
  digitalWrite(lpower,sensorStatus);
}
void light_detect(){
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["digital"]=digitalRead(lightsensor);
    root["message"]=digitalRead(lightsensor) ?"Khong co anh sang":"Co anh sang";

    mySerial.print("LIGHT");
    mySerial.print('\r');
    root.printTo(mySerial);
    mySerial.print('\r');
  }
