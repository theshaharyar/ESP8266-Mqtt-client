#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include <ArduinoJson.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

const char* ssid = "AVEROS 2.4G";
const char* password =  "averos6754";
const char* mqttServer = "mq01.averos.com";
const int mqttPort = 1883;
const char* mqttUser = "averos";
const char* mqttPassword = "[mqAverosMQ6754]";
int Relay = D3;
int wifi_led = 2;
int buzzer = D4;



WiFiClient espClient;
PubSubClient client(espClient);
SSD1306  display(0x3c, D1, D2);
//SSD1306  display(0x3c, 5, 4);
void setup() {
  pinMode(wifi_led, OUTPUT);
  pinMode(Relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  //digitalWrite(wifi_led, LOW);
  digitalWrite(buzzer, LOW);
  Serial.begin(115200);
  display.init();
  delay(100);

  
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi network");
  display.clear();
  display.drawString(0, 0, "Connecting WiFi");
  display.display();
  int progresspointer = 1;
  
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    
    display.drawString(progresspointer, 20, ".");
    display.display();
    progresspointer = progresspointer + 3;
      
    digitalWrite(wifi_led, !digitalRead(wifi_led));
    delay(250);
  }

  digitalWrite(wifi_led, HIGH);
  Serial.println("Connected to WiFi network");
  display.clear();
  display.drawString(0, 0, "WiFi Connected");
  display.display();
  delay(1000);
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT");
    display.clear();
    display.drawString(0, 0, "Connecting to \nMQTT Broker");
    display.display();
    delay(500);
    if (client.connect("/saudistartup", mqttUser, mqttPassword )) {

      Serial.println("connected");
      display.clear();
      display.drawString(0, 0, "MQTT Connected");
      display.display();
      delay(1000);
    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      display.clear();
      display.drawString(0, 0, "Network error");
      display.display();
      delay(2000);

    }
  }

  client.publish("/saudistartup", "Hello from ESP8266");
  client.subscribe("/saudistartup");

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("payload: ");
  Serial.print(length);
  // Conver the incoming byte array to a string
  payload[length] = '\0'; // Null terminator used to terminate the char array
  String message = (char*)payload;


  Serial.print("\nMessage arrived on topic: ");
  Serial.println(topic);

  Serial.print("MessageObject: ");
  Serial.println(message);

  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(message);

  if (!root.success())
  {
    Serial.print("parseObject(");
    Serial.print(message);
    Serial.println(") failed");
    return;

  }
  else
  {
    String LED_Control = root["Criteria"];
    //String tagNum = root["SerialNumber"];
    //Serial.println(tagNum);

    if (LED_Control == "IN") 
    {
      
      digitalWrite(wifi_led, LOW);
      Serial.println("Action: LED ON");
      display.setFont(ArialMT_Plain_24);
      display.clear();
      display.drawString(5, 2, "ACCESS\nGRANTED");
      display.display();
    }
    else if (LED_Control == "OUT") 
    {
      digitalWrite(wifi_led, HIGH);
      Serial.println("Action: LED OFF");
      display.setFont(ArialMT_Plain_24);
      display.clear();
      display.drawString(5, 2, "ACCESS\nREWOKED");
      display.display();
    }
  }

   
  Serial.println("-----------------------");

}

void loop() {
  client.loop();
}
