#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <SerialCommand.h>  
 
extern "C" {
 
  #include "user_interface.h"
}
 
 
const byte RX = 5;
const byte TX = 4;
 
SoftwareSerial mySerial (RX,TX);
SerialCommand sCmd(mySerial);

SocketIOClient client;
const char* ssid = "Oreo";          
const char* password = "0312621105";  
char host[] = "192.168.43.230";  
int port = 8080;                 
char namespace_esp8266[]="esp8266"; 
extern String RID;
extern String Rfull;
 
 
void setup()
{
    Serial.begin(57600);
    mySerial.begin(57600);
    delay(10);
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
    WiFi.begin(ssid,password);
    
   
    while (WiFi.status() != WL_CONNECTED) { 
        
        delay(500);
        Serial.print('.');
    }
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());

    if (!client.connect(host, port,namespace_esp8266)) {
        Serial.println(F("Ket noi den socket server that bai!"));
        return;
        }
//        } ​
    sCmd.addDefaultHandler(defaultCommand);
    Serial.println("Da san sang nhan lenh");
   
}
 
void loop()
{ 
    if (client.monitor()){
        mySerial.print(RID);    
        mySerial.print('\r');
        mySerial.print(Rfull);     
        mySerial.print('\r');
        Serial.print(RID);
        Serial.print(' ');
        Serial.println(Rfull);
        uint32_t free = system_get_free_heap_size();
        Serial.println(free);
    }
//
    if (!client.connected()){      
      client.reconnect(host,port,namespace_esp8266);}
      sCmd.readSerial();
}

void defaultCommand(String command) {
  char *json = sCmd.next();
  client.send(command, (String) json);
  
  Serial.print(command);
  Serial.print(' ');
  Serial.println(json);
}
