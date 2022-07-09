This device resets the Wi-Fi router when internet connection is lost. Due to frequent disconnection (usually 2 to 3 times a day), it causes frustration to the users because they have to manually reset the router everytime the connection is lost (connection does not return automatically). The manual reset is done by unplugging and plugging the adapter or pressing the router's power button two times. The user has no remote access for resetting the router since when the internet is lost, router log-ins does not work. This means that the user will have to walk to the router often, disrupting work flow. Even if the log-in method works, it is better to automate the process so the users does not have to reset it manually.

Basically, this device automates the process of manual resetting whenever the internet connection is lost.

# Materials

### Wemos D1 Mini
 
 The controls of the project. It is connected to the Wi-Fi, and upon disconnection, activates the normally closed relay to reset the router.
  
### 5VDC Mechanical Relay
 
Any 5VDC relay can be used as long as its contact capacity is rated for the voltage and current of the Wi-Fi router. In this case, the rating for the router is 12V 2A, so the relay used is SRD-05VDC-SL-C, which can handle up to 7A 28VDC. Also, this relay already has a flyback diode. 
 
Note that 5VDC is used since Wemos D1 Mini works on 5V logic, i.e., you’ll need to step-up or step-down the voltage output of Wemos if the relay works on higher or lower voltage level respectively. It is also important to use a DC relay because AC relays cannot handle long exposure to arcing. 

### 5VDC Wall Adapter

Micro USB to power the Wemos.


  
# Methods

### Wiring
First is the electrical connections of the Wemos and the relay, pin 12 is used, which is pin D6 in Wemos. This is connected to the signal pin of the relay. Then, the Vcc of the relay is connected to the 5V pin of the Wemos, and their GND pins should be connected. However, it is safer to isolate the control and the relay by providing a separate Vcc supply to the relay and connecting it to its JD-Vcc pin. 

Shown below is a photo of a prototype, using LED as load for simplicity. Note that the Arduino UNO is only used to power the LED.

![image](https://user-images.githubusercontent.com/94373003/178096284-b3ca1203-6495-44c4-8052-d7857fc881c4.png)

Below is a better illustration of how to connect a relay from [1]. The input side shows the ground, 5V Vcc pin and the signal pin. This signal pin is the pin that should be connected to the pin 12 (D6) of Wemos. In the output side, NC means normally-closed, C is for common, and NO means normally-open. In the article, NC contact was used

![image](https://user-images.githubusercontent.com/94373003/178096306-933d699a-4953-4e8a-8e15-1dacca74fa46.png)


Photo from [1]

To connect the NC and C contacts of the relay to the router, the wires of the adapter were cut as shown in the photo below.

![image](https://user-images.githubusercontent.com/94373003/178096373-f3fcafb6-d416-4fe8-94cc-0bfd0f5f2191.png)



### Code

For the program, ESP8266WiFI library is included because Wemos uses ESP8266 Wi-Fi chip. Next is defining *WIFI_SSID* and *WIFI_PASS* which is the name and password of the Wi-FI respectively. Pin 12 is then assigned to relayPin for easy of programming.

```markdown
#include <ESP8266WiFi.h>
//wi-fi info
#define WIFI_SSID "WIFI_SSID_HERE"
#define WIFI_PASS "WIFI_PASSWORD_HERE"
		unsigned int relayPin = 12; //D6 on Wemos
```


Next is the setup() part in Arduino. *Serial.begin()* is for starting the serial monitor for debugging. We start with the relayPin (pin 12, D6) as high for reasons stated in comments of the code. In summary, the logic is inverse thus a high pin means the LED indicator of the relay is off, thus NC contact is closed.

Since the board will be connecting to a network and not as access point, the mode is set into station mode, by providing *WIFI_STA* as the argument to *WiFi.mode*. Then, disconnect any prior connections and begin connecting to the Wi-Fi, by providing *WIFI_SSID* and *WIFI_PASS*. Wemos then is delayed for 12 seconds so it can connect to the network. This value is obtained by trial and error during prototyping after performing multiple connection tests and recording the time it took to connect. This value could be lowered if the device you are using can connect faster.


```markdown
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
```

Once the board is connected, it proceeds to the main loop. This loop just uses function *wifiChecker()* which activates the relay (therefore resetting the router) and resets the board after five seconds if the Wi-Fi connection is lost. By resetting the board, the prior process in *setup()* repeats.


```markdown
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
```

Function *relayControl()* in *wifiChecker()* just sets *relayPin* to low to open the NC contacts.


```markdown
void relayControl(){
  //LOW D6 pin to open circuit for 500ms, then close again

  digitalWrite(relayPin, LOW);
  delay(500);
  digitalWrite(relayPin, HIGH); 
}
```

# References
[1] https://www.circuitbasics.com/setting-up-a-5v-relay-on-the-arduino/
