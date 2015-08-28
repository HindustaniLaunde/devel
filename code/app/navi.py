import paho.mqtt.client as mqtt
def on_connect (client, userdata, flags, rc):
	print("Connected with result code"+str(rc))
	client.publish("/topic/0", "hello World", 0, False)

def on_publish(client, userdata, msg):
	print(msg.topic+" "+str(msg.payload))

client= mqtt.Client()

client.on_connect= on_connect
client.on_publish = on_publish

client.connect("172.20.185.147", 1883, 60)

client.loop_forever()
