import paho.mqtt.client as mqtt

# MQTTブローカーの設定
mqtt_broker = "broker.emqx.io"
mqtt_port = 1883

# トピックとメッセージ
mqtt_topic = "KIT/move"
mqtt_message = "aiuo"

# MQTTクライアントの作成
client = mqtt.Client()

# MQTTブローカーに接続したときのコールバック
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker")
    else:
        print(f"Failed to connect, return code {rc}")

# MQTTブローカーにメッセージを送信したときのコールバック
def on_publish(client, userdata, mid):
    print(f"Message published (mid: {mid})")

# コールバック関数の設定
client.on_connect = on_connect
client.on_publish = on_publish

# MQTTブローカーに接続
client.connect(mqtt_broker, mqtt_port)

# メッセージをパブリッシュ
client.publish(mqtt_topic, mqtt_message)

# MQTTクライアントを維持するためにループを開始
client.loop_forever()
