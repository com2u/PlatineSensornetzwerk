//#include <WiFi.h>
#include <ESP8266WiFi.h>
//#include "..\..\Credentials\Credentials.h"

char* ssid[] =     { "ArcorSS-B87638", "ArcorWirelessLan","HHLink","HessCom2u", "NETGEAR35", "Com2u.de.WLAN2", "muccc.legacy-2.4GHz", "muenchen.freifunk.net",  "Cafeteria","ArcorSS-B87638" };
char* password[] = { "SOMMERREGEN05","SOMMERREGEN05","SOMMERREGEN05","SOMMERREGEN05", "smilingtree251", "SOMMERREGEN05", "haileris"           , ""                     ,  "$eidenader", "SOMMERREGEN05"};



//generate unique name from MAC addr
String macToStr(const uint8_t* mac){
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5){
      result += ':';
    }
  }
  return result;
}




void initWIFI() {
  /*
  ssid = credentials_ssid;
  password = credentials_password;
  */
  //connect to WiFi
  int networkNo = 0;
  int retries = 12;
  int retry = 0;
  //attempt to connect to the wifi if connection is lost
  if (WiFi.status() != WL_CONNECTED) {

    // Try several WIFI Networks
    for (networkNo = 0; networkNo < 10; networkNo++) {
      Serial.print("Connecting ");
      Serial.print(networkNo);
      Serial.print(" of ");
      Serial.print(sizeof(ssid));
      Serial.print(" to ");
      Serial.println(credentials_ssid[networkNo]);
      delay(100);
      WiFi.begin(credentials_ssid[networkNo], credentials_password[networkNo]);
        String clientName;
      clientName += "SensorBoard-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);
      // WiFi.setHostname("clientName");
      for (retry = 0; retry < retries; retry++) {
        if (WiFi.status() == WL_CONNECTED) {
          break;
        } else {
          Serial.print(".");
          delay(1000);
        }
      }
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected");
        break;
      }
      /*
      Serial.println("Try another AP");
      WiFi.mode(WIFI_OFF);
      delay(2000);
      WiFi.mode(WIFI_STA);
      */
    }
  }
  // Create Acces Point when no WIFI found
  /*
  if (retry == retries) {
    Serial.println(WiFi.softAP("ESPsoftAP_01") ? "Ready" : "Failed!");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
  }
  */
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
