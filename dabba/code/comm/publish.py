#TODO: Get time from the internet and send it to the Arduino.

import paho.mqtt.client as mqtt
import time
import sys
import weather
import newpacket

reload(sys)
sys.setdefaultencoding("ISO-8859-1")
def on_connect (client, userdata, flags, rc):
	print("Connected with result code"+str(rc))
	client.publish("/topic/0", "hello World", 0, False)

def on_publish(client, userdata, msg):
	#print(msg.topic+" "+str(msg.payload))
	print "hi"

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    return

def loop():
	weather.get_weather()
	newpacket.packet()
	f=open("../../data/packet.dat","r")
	lines = f.readlines();
	weatherData=lines[0].split(",")
	lon=weatherData[0]
	lat=weatherData[1]
	getTime(lat,lon)
	f.close()
		
	client.publish("/topic/1",x)
	f=open("../../data/rss","r")
	for line in f:
		print line
		#client.publish("/topic/0",line)
	f.close()
	f=open("../../data/rss","w")
	f.close()
	

client= mqtt.Client()

client.on_connect = on_connect
#client.on_publish = on_publish
client.on_message = on_message
client.connect("192.168.0.108", 1883, 60)
client.subscribe("/topic/0");
x=0
client.loop_start()
while True:
	x +=1
	loop()
	time.sleep(10);
client.loop_end()
