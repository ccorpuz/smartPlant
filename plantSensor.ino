#include <dht.h>
#include <SoftwareSerial.h>
//Setting up Software Serial
SoftwareSerial esp(2, 3);
dht DHT;
#define DHT11_PIN 7
//API Key from ThingTweet
String apiKey = "APIKEY123";
String network = "\"SSID\"";
String password = "\"PasSWorD\"";

const int mSensor = 0;

void setup() {
  Serial.begin(9600);
  esp.begin(9600);

  //Set up WiFi connection
  connection();
  delay(1000);
  //tweet("test connection");

}

void loop() {
  String moisture ="";
  if (getMoisture() < 150) {
    tweet("Thanks for pouring excessive water :)");
  }

  if (getMoisture() > 151 && getMoisture() < 350) {
    tweet("Thanks for watering me");
  }

  if (getMoisture() > 350) {
    tweet("I need a drink");
  }
  
  tweet(getTnH());
  delay(120000);
}

int getMoisture() {
  //670 default, 120 wet
  int reading = analogRead(mSensor);
  delay(300);
  return reading;
}

String getTnH() {
  int chk = DHT.read11(DHT11_PIN);
  String TnH = "The temperature is ";
  TnH += DHT.temperature;
  TnH += " and the humidity is ";
  TnH += DHT.humidity;
  delay(1000);
  return TnH;
}

void connection() {
  Serial.println("Changing CIPMODE");
  esp.println("AT+CIPMODE=0");
  delay(750);
  readESP();
  delay(750);

  Serial.println("Connecting to WIFI...");
  //CHANGE SSID AND PW HERE
  esp.println("AT+CWJAP=" + network + "," + password);
  delay(2000);
  readESP();
  delay(4000);

  esp.println("AT+CIPMUX=0");
  delay(750);
  readESP();
  delay(500);

  Serial.println("Getting esp IP Address...");
  esp.println("AT+CIFSR");
  delay(1000);
  readESP();
  delay(1000);

}

void readESP() {
  while (esp.available()) {
    String inData = esp.readStringUntil('\n');
    Serial.println(inData);
  }
}

void tweet(String thetweet) {
  //TCP Connection
  Serial.println("Tweeting...");
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "api.thingspeak.com";
  cmd += "\",80";
  esp.println(cmd);
  readESP();
  delay(1000);

  //CIPSEND prep
  String prep = "GET /apps/thingtweet/1/statuses/update?api_key=";
  prep += apiKey;
  prep += "&status=";
  prep += thetweet;
  prep += "\r\n\r\n";

  //send data
  cmd = "AT+CIPSEND=";
  cmd += String(prep.length());
  esp.println(cmd);

  if (esp.find(">")) {
    esp.print(prep);
  }

  readESP();
  delay(3000);
  esp.println("AT+CIPCLOSE");
  readESP();

  delay(7000);
}
