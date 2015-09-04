import paho.mqtt.client as mqtt
import time
import sys
import weather
import newpacket
import  threading
reload(sys)
sys.setdefaultencoding("ISO-8859-1")

def message():
        easygui.msgbox("Computer synced with Smart Clock!", ok_button="OK!")
        return

def publishStartMessage():
        threading.Thread(target=message).start()
        return

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
	lines = f.readlines()
	f.close()
	weatherData=lines[0].split(",")
	lon=weatherData[0]
	lat=weatherData[1]
	time_packet = getTime(lat,lon)
	client.publish ("/topic/0", time_packet)
	
	#***************WEATHER*******************
	
	weather_packet = ''
	for i in range(2, len(weatherData) - 1): #Creating a # separated  string for sending.
		weather_packet += weatherData[i] + '#'
	client.publish ("/topic/1", weather_packet)
	
	#***************REMINDER*******************
	f = open("../../data/reminder.txt", "r")
	reminder = f.readlines()
	reminder_packet = reminder [0]
	client.publish ("/topic/2", reminder_packet)
	f.close
	
	#***************TO-DO*******************
	
	f = open("../../data/TODO.txt", "r")
	for todo in f:
		client.publish("/topic/3", todo)
	f.close
	
	#***************RSS*******************
	
	f = open("../../data/rss","r")
	for headline in f:
		client.publish("/topic/4",headline)
	f.close
	time.sleep(9)
	return

def publish():
	publishStartMessage()
	client= mqtt.Client()

	client.on_connect = on_connect
	#client.on_publish = on_publish
	client.on_message = on_message
	client.connect("192.168.0.111", 1883, 60)
	client.subscribe("/topic/0");
	x=0
	client.loop_start()
	while True:
		x +=1
		loop()
	client.loop_end()
