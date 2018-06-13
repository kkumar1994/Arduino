
#include <WiFi.h>
#include <PubSubClient.h>  //MQTT LIBRARY FOR PUBLISHING AND SUBSCRIBING
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

const char* ssid = "LOL";
const char* password = "1234";

// Add your MQTT Broker IP address, example: here i used mosquitto
const char* MQTT_SERVER_IP = "192.168.1.4";

WiFiClient ESP_CLIENT;
PubSubClient client(ESP_CLIENT);
long lastMsg = 0;
char msg[50];
int value = 0;

Adafruit_BME280 bme; 
float temperature = 0;
float humidity = 0;

const int led = 4;

void setup() {
  Serial.begin(115200);  
  if (!bme.begin(0x76)) {
    Serial.println("BME280 sensor unavailable!");
    while (1);
  }
  setup_wifi();
  client.setServer(MQTT_SERVER_IP, 1883); //1883 is the port number
  client.setCallback(callback);

  pinMode(led, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // Connect to WiFi
  Serial.println();
  Serial.print("Waiting");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "Bedroomlight") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(led, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(led, LOW);
    }
  }
}

void reconnect() {
  // IF connection is lost reconnect again
  while (!client.connected()) {
    Serial.print("....");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe to the topic
      client.subscribe("Bedroomlight");
    } else {
      Serial.print("failed");
      Serial.print(client.state());
      Serial.println(" Retrying");
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    temperature = bme.readTemperature();   
    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("temperature", tempString);

    humidity = bme.readHumidity();
    
    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("humidity", humString);
  }
}
