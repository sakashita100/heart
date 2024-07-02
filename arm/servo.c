#include <WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// WiFiの設定　書き換えが必要
const char* ssid = "";
const char* password = "";

// MQTTブローカーの設定
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

Servo myservo1; // Servoオブジェクトを作成
Servo myservo2;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if(length == 4){
      myservo1.write(0); // ハグ
      myservo2.write(0);
      //digitalWrite(21, LOW);
    }
    else {
      myservo1.write(160);   // 戻る
      myservo2.write(160);
      //digitalWrite(21, HIGH);
    }
    Serial.println(length);
}


void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Subscriber")) {
      Serial.println("connected");
      client.subscribe("KIT/move");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(21, OUTPUT); // リレー操作
  myservo1.attach(32); // 13番ピンにサーボ制御線（黄色）を接続
  myservo2.attach(33);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
