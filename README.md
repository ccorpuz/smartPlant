# smartPlant
Make a plant tweet the temperature and soil moisture using a DHT sensor and ThingSpeak.

Hardware involved:
- DHT11 sensor
- Arduino
- ESP8266 WiFi Module

### Relevant links:
https://thingspeak.com/

ESP Hardware setup:
http://rancidbacon.com/files/kiwicon8/ESP8266_WiFi_Module_Quick_Start_Guide_v_1.0.4.pdf

### tweet.ino
Contains some basic functions to tweet strings from an Arduino using the ESP Module and ThingSpeak API.
Uses SoftwareSerial library to simulate serial communication between the ESP Module and Arduino.
Requires: API Key from ThingTweet/ThingSpeak.

`SoftwareSerial esp(2,3)`
Sets up a SoftwareSerial object called esp on the arduino digital pins 2 and 3.

### connection()
Setting up the ESP Module and connecting to the WiFi.

`esp.println("Command");`
Sends commands to the esp

`AT+CIPMODE=0`
Setting CIPMODE to 0 (normal mode).

`AT+CWJAP=SSID,PASSWORD`
Connecting to the WiFi network with SSID and Password.

`AT+CIPMUX=1`
To enable multiple connections.

`AT+CIFSR`
To return the ESP's IP Address.

### readESP()
`while (esp.available()) {
    String inData = esp.readStringUntil('\n');
    Serial.println(inData);
  }`

Reading responses line by line from the ESP Module and printing to the Arduino serial monitor.

### tweeting(String tweet)
Tweets "tweet" through the ThingSpeak API.

`AT+CIPSTART="TCP","api.thingspeak.com",80`
Connects to the API using TCP protocol.

`AT+CIPSEND=LENGTHOFTEXT`
Getting ready to send text by telling the ESP how many characters to expect.

`if (esp.find(">")){
    esp.print(prep);
  }`

Sends the text when the esp prompts with '>'.

`AT+CIPCLOSE`
Close CIP connection.

### plantSensor.ino
Final setup with the DHT sensor.
