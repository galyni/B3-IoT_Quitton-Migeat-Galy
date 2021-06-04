#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "CC C T-O"; // Enter your WiFi name
const char* password =  "gnocchis"; // Enter WiFi password
const char* mqttServer = "192.168.43.172";
const int mqttPort = 1883;
/*
const char* mqttUser = "otfxknod";
const char* mqttPassword = "nSuUc1dDLygF";
*/

int inputPin = D0;
int buzzerPin = D1;
int pirState = LOW;
int val = 0; 
int currentValue = 0;

String isSensorActive = "false"; 
String isBuzzerActive = "false";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  
  pinMode(inputPin, INPUT);
  pinMode(buzzerPin, INPUT);
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client")) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }

  // Pou le capteur
  client.publish("sensor", "Capteur ok"); //Topic name
  client.subscribe("sensor");

  // Pour le buzzer
  client.publish("alarm", "Buzzer ok"); //Topic name
  client.subscribe("alarm");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  if(strcmp(topic, "sensor") == 0){
    String temp = "";
    Serial.print("Message:");
  
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      temp += (char)payload[i];
    }

    if(temp == "true" || temp == "false"){
      isSensorActive = temp;
      if(temp == "false"){
        isBuzzerActive = temp;
        val = 0;
      }
    }
  }
  else if(strcmp(topic, "alarm") == 0){
    String temp = "";
    Serial.print("Message:");
  
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      temp += (char)payload[i];
    }

    if(temp == "true" || temp == "false"){
      isBuzzerActive = temp;
      if(temp == "false"){
        isSensorActive = "true";
      }
    }
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();

  if(client.connected()){
    if(isSensorActive == "true"){
      val = digitalRead(inputPin);
      Serial.println(val);
      if(val != currentValue){
        currentValue = val;
        client.publish("motion", (val ? "true" : "false"));
        Serial.println(val ? "true" : "false");

        if(val == 1){
          isBuzzerActive = "true";
        }
      }
      delay(400);
    }
    if(isBuzzerActive == "true"){
      isSensorActive = "false";
      val = 0;
      playMusic();
    }
  }
}

void playMusic(){
  tone(buzzerPin,500,100);
  delay(20);
  tone(buzzerPin,600,100);
  delay(150);
};

void playMusicMario(){
      tone(buzzerPin,660,100);
      delay(150);
      tone(buzzerPin,660,100);
      delay(300);
      tone(buzzerPin,660,100);
      delay(300);
      tone(buzzerPin,510,100);
      delay(100);
      tone(buzzerPin,660,100);
      delay(300);
      tone(buzzerPin,770,100);
      delay(550);
      tone(buzzerPin,380,100);
      delay(575);
      
      tone(buzzerPin,510,100);
      delay(450);
      tone(buzzerPin,380,100);
      delay(400);
      tone(buzzerPin,320,100);
      delay(500);
      tone(buzzerPin,440,100);
      delay(300);
      tone(buzzerPin,480,80);
      delay(330);
      tone(buzzerPin,450,100);
      delay(150);
      tone(buzzerPin,430,100);
      delay(300);
      tone(buzzerPin,380,100);
      delay(200);
      tone(buzzerPin,660,80);
      delay(200);
      tone(buzzerPin,760,50);
      delay(150);
      tone(buzzerPin,860,100);
      delay(300);
      tone(buzzerPin,700,80);
      delay(150);
      tone(buzzerPin,760,50);
      delay(350);
      tone(buzzerPin,660,80);
      delay(300);
      tone(buzzerPin,520,80);
      delay(150);
      tone(buzzerPin,580,80);
      delay(150);
      tone(buzzerPin,480,80);
      delay(500);
};
