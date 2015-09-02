#include <espduino.h>
#include <mqtt.h>

ESP esp(&Serial, 4);
MQTT mqtt(&esp);

boolean wifiConnected = false;

void wifiCb(void* response)
{
  uint32_t status;
  RESPONSE res(response);

  if(res.getArgc() == 1) {
    res.popArgs((uint8_t*)&status, 4);
    if(status == STATION_GOT_IP) {
      mqtt.connect("192.168.0.108", 1883);
      wifiConnected = true;
    } else {
      wifiConnected = false;
      mqtt.disconnect();
    }
    
  }
}

void mqttConnected(void* response)
{
  mqtt.subscribe("/topic/0");
  mqtt.subscribe("/topic/1");
  mqtt.subscribe("/topic/2");
  mqtt.publish("/topic/0", "data0");
  digitalWrite(13,LOW);

}
void mqttDisconnected(void* response)
{
  digitalWrite(13,HIGH);
}
void mqttData(void* response)
{
  RESPONSE res(response);

  String topic = res.popString();
  
  String data = res.popString();
}
void mqttPublished(void* response)
{

}

void initMQTT(void)
{
  pinMode(13, OUTPUT);
  Serial.begin(19200);
  esp.enable();
  delay(500);
  esp.reset();
  delay(500);
  while (!esp.ready());

  if (!mqtt.begin("smartClock", "admin", "admin", 120, 1)) {
    while (1) {
      if (digitalRead(13) == HIGH)
        digitalWrite(13, LOW);
      else
        digitalWrite(13, HIGH);
      delay(1000);
    }
  }

  mqtt.lwt("/lwt", "offline");

  /*setup mqtt events */
  mqtt.connectedCb.attach(&mqttConnected);
  mqtt.disconnectedCb.attach(&mqttDisconnected);
  mqtt.publishedCb.attach(&mqttPublished);
  mqtt.dataCb.attach(&mqttData);

  /*setup wifi*/
  esp.wifiCb.attach(&wifiCb);

  esp.wifiConnect("What's in a name??", "tesLA999");
}

