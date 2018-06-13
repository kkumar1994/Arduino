#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
#include "index.h"
 
//SSID and passwrd of your WiFi router
const char* ssid = "lol";
const char* passwrd = "123456789";
 
ESP8266WebServer server(80); //Server on port 80
 
void root() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, passwrd);     //Connect to your WiFi router
  Serial.println("");
 
  // Connection time
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Waiting for connection");
  }
 
  //Display IP
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", root);      
 
  server.begin();                  //Server initialization
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();          //Handle client requests
}
