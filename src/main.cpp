#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



// ---------------REPLACE THE FOLLOWING PARAMATERS----------------------

char ssid[] = "SSID"; // Replace SSID with the name of your wifi network
char password[] = "Password"; // Replace Password with the password of your wifi network


String projectUrl = "/json-api/getIbleStats?id=ED5Z5LNKCW8HY2E"; // please refer to the readme file for directions on 










WiFiClientSecure client;
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
StaticJsonBuffer<200> jsonBuffer;
#define TEST_HOST "www.instructables.com"
void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

String getViewCount() {

  if (!client.connect(TEST_HOST, 443))
  {
    Serial.println(F("Connection failed"));
    return "0";
  }

  yield();

  client.print(F("GET "));
  client.print(projectUrl);
  client.println(F(" HTTP/1.1"));
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));
  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return "0";
  }


  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return "0";
  }
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    Serial.println("BAD");
  }

  String viewCountData  = "";


  while (client.available()) {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    viewCountData += c;
  }
  return viewCountData;
}

void loop() {
  String viewCountRawData = getViewCount();
  JsonObject& viewCountData = jsonBuffer.parseObject(viewCountRawData);

  int viewCount = viewCountData["views"];
  int favCount = viewCountData["favorites"];

  display.clearDisplay();

  display.setTextSize(2);             
  display.setTextColor(WHITE);       
  display.setCursor(0,0);             
  display.print("Tank Stats");

  display.setTextSize(2);           
  display.setTextColor(WHITE);       
  display.setCursor(0,20);         
  display.print("Views:");
  display.println(viewCount);
  
  display.setTextSize(2);             
  display.setCursor(0,42);      
  display.print("Favs:");
  display.println(favCount);

  display.display();
  delay(300000);

  ESP.restart();
}