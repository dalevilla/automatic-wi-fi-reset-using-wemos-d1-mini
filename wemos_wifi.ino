/*Copyright (c) 2022 xern-eaus

Permission is hereby granted, free of charge, to any person obtaining a copy of this hardware, software, and associated documentation files (the "Product"), to deal in the Product without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Product, and to permit persons to whom the Product is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Product.

THE PRODUCT IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE PRODUCT OR THE USE OR OTHER DEALINGS IN THE PRODUCT.
*/

#include <ESP8266WiFi.h>

//Wi-Fi info
#define WIFI_SSID "WIFI_SSID_HERE"
#define WIFI_PASS "WIFI_PASSWORD_HERE"

unsigned int relayPin = 12; //D6 on Wemos

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(relayPin, OUTPUT);

  //Init relay pin to high so the relay is closed (LED OFF)
  //just look at the LED indicator on the relay
  //if it is on, it means the normally-closed (NC) contacts are
  //open, thus no power to the Wi-FI router.
  //Do some minor testing on the relay first.
  digitalWrite(relayPin, HIGH);

  //Station mode
  WiFi.mode(WIFI_STA);

  //Disconnect first
  WiFi.disconnect();
  delay(100);
  
  //Connect to wifi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Connecting to: ");
  Serial.print(WIFI_SSID);

  //Repeat until wifi is connected, if not connected in
  //12 seconds, restart Wemos
  //12 seconds can be changed depending on how fast your 
  //Wemos connects on average
  int maxNotConnected = 0;
  
  while(WiFi.status() != WL_CONNECTED && maxNotConnected <= 12){
    delay(1000);
    Serial.print(WiFi.status());
    maxNotConnected++;

  }
  
  //Restart Wemos until it is connected to the Wi-Fi
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Device Failed to Connect... Restarting");
    ESP.restart();
  }

  //Print how long it took to connect for debugging
  Serial.println();
  Serial.print(maxNotConnected);

  //Connected
  Serial.println();
  Serial.print("Connected to IP Address: ");
  Serial.println();
  Serial.print(WiFi.localIP());
}

void loop(){
  wifiChecker();
  delay(2000);
}

void wifiChecker(){
  //Checks if wifi is still connected, if not, activate relay to reset wifi
  //wait 5s then reset to restart program

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("WiFi lost... Resetting WiFi");
    relayControl();
    delay(5000);
    ESP.restart();
  } 
}

void relayControl(){
  //LOW D6 pin to open circuit for 500ms, then close again

  digitalWrite(relayPin, LOW);
  delay(500);
  digitalWrite(relayPin, HIGH); 
}
