// Get ESP8266 going with Arduino IDE
// send gps position over mqtt
#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "XXXXXXXXX"
#define wifi_password "YYYYYYYYY"

#define mqtt_server "test.mosquitto.org"
#define mqtt_user "your_username"
#define mqtt_password "your_password"


long lastMsg = 0;
WiFiClient espClient;
PubSubClient client(espClient);
TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // (Rx,Tx)(to be "crossed" for gps module)The serial connection to the GPS device
float latitude , longitude;
String  lat_str , lng_str, pos_str;

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you want to use a username and password, change next line to
    // if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data
    {
      long now = millis();
      if (gps.location.isValid()&& (now - lastMsg > 2000)) //check whether gps location is valid  and 2 sec has passed
      {
        lastMsg = now;
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
        pos_str = lat_str + "," + lng_str;
        Serial.println(pos_str);
        client.publish("eaaa/sensor/knn_pos", pos_str.c_str(), true);

      }
    }
}
