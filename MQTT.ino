#include <PubSubClient.h>
const char* mqtt_server = "116.203.60.216";
const char* MQTTPath = "Berlin/Christian/";
int mqttPort = 1883;
//const char* clientID = "1";
const char* MQTTUser     = "MQTTiot";
const char* MQTTPassword = "iot6812";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[150];
char topicChar[150];
int value = 0;
int reconnectCount = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();




}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected() && reconnectCount < 3) {
    reconnectCount++;
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTTUser,  MQTTPassword)) {
      Serial.println("connected");
      reconnectCount = 0;
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("DRAWIMAGE");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  reconnectCount = 0;
}

void initMQTT() {

  client.setServer( mqtt_server, mqttPort);
  client.setCallback(callback);
}

void handleMQTT() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

boolean sendMQTT() {
  boolean done = false;
  if (!client.connected()) {
    reconnect();
  }
  if (client.connected()) {
    String topic = MQTTPath;
    String values = "";
    for (int i = 0; i <= sensors.noOfMQTTValues; i++) {
      topic += sensors.header[i] + ";";
      values += sensors.measurement[i] + ";";
      //inputCount[i] = 0;
      sensors.measurement[i] = "0";
    }
    //String header[] = {"Temp", "Preasure", "Humidity", "Gas", "Light", "Volt", "PIR","Radar","Audio"};
    //String value[]  = { "0"  , "1",        "2",        "3",   "4"    , "5",    "6",   "7",   "8"    };

    Serial.print(topic);
    Serial.print(" Message: ");
    Serial.println(values);
    values.toCharArray(msg, values.length());
    topic.toCharArray(topicChar, topic.length());
    client.publish(topicChar, msg);
    done = true;
  }
  return done;
}

