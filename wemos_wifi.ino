#include <ESP8266WiFi.h>

//wi-fi info
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
