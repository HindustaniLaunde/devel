#!/usr/bin/python

#import newpacket
def get_weather():
	import urllib2
	f = open ("../../data/current_city.dat", "r")
	city = f.readline()
	f.close()
	#print 	'http://api.openweathermap.org/data/2.5/weather?q='+city
	proxy = urllib2.ProxyHandler({'http': 'http://amanabt:IITKaat@vsnlproxy.iitk.ac.in:3128'})
	auth = urllib2.HTTPBasicAuthHandler()
	opener = urllib2.build_opener(proxy, auth, urllib2.HTTPHandler)
	urllib2.install_opener(opener)

	conn = urllib2.urlopen('http://api.openweathermap.org/data/2.5/weather?q='+city)
	report = conn.read()
	f = open ("../../data/weather.dat", "w")
	f.write (report)
	f.close
#	print newpacket.packet()
	return report



