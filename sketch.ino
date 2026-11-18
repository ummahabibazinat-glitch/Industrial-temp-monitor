#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Pin configuration
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define BUTTON_PIN 18
#define LED_PIN 23

// WiFi configuration
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT configuration
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "industrial/monitor/temperature";

WiFiClient espClient;
PubSubClient mqttClient(espClient);
DHT dht(DHT_PIN, DHT_TYPE);

// Timing
unsigned long previousSensorTime = 0;
unsigned long previousWiFiTime = 0;
unsigned long previousMQTTTime = 0;
unsigned long previousButtonTime = 0;

const unsigned long sensorInterval = 2000;
const unsigned long reconnectInterval = 5000;
const unsigned long debounceDelay = 30;

// Button and fan
bool fanState = false;
bool lastReading = LOW;
bool buttonState = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);

  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  mqttClient.setServer(mqtt_server, mqtt_port);

  Serial.println("Industrial Temperature Monitor");
  Serial.println("System Started");
}

void checkButton() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    previousButtonTime = millis();
    lastReading = reading;
  }

  if (millis() - previousButtonTime >= debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        fanState = !fanState;

        digitalWrite(LED_PIN, fanState ? HIGH : LOW);

        Serial.print("Fan Status: ");
        Serial.println(fanState ? "ON" : "OFF");
      }
    }
  }
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    if (millis() - previousWiFiTime >= reconnectInterval) {
      previousWiFiTime = millis();
      WiFi.begin(ssid, password);
      Serial.println("WiFi reconnecting...");
    }
  }
}

void checkMQTT() {
  if (WiFi.status() == WL_CONNECTED && !mqttClient.connected()) {
    if (millis() - previousMQTTTime >= reconnectInterval) {
      previousMQTTTime = millis();

      String clientId = "ESP32Monitor_";
      clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("MQTT Connected!");
      } else {
        Serial.print("MQTT connection failed: ");
        Serial.println(mqttClient.state());
      }
    }
  }

  if (mqttClient.connected()) {
    mqttClient.loop();
  }
}

void readAndPublishData() {
  if (millis() - previousSensorTime >= sensorInterval) {
    previousSensorTime = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT22 Sensor Error!");
      return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    if (mqttClient.connected()) {
      String data = "{";
      data += "\"temperature\":";
      data += String(temperature, 1);
      data += ",\"humidity\":";
      data += String(humidity, 1);
      data += "}";

      if (mqttClient.publish(mqtt_topic, data.c_str())) {
        Serial.println("Data Published Successfully!");
      } else {
        Serial.println("Publish Failed!");
      }
    } else {
      Serial.println("MQTT Offline");
    }
  }
}

void loop() {
  checkButton();
  checkWiFi();
  checkMQTT();
  readAndPublishData();
}
