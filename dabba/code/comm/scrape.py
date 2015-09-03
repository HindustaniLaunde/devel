#!/usr/bin/python

def scrape ():
	import urllib2

	proxy = urllib2.ProxyHandler({'http': 'http://amanabt:IITKaat@vsnlproxy.iitk.ac.in:3128'})
	auth = urllib2.HTTPBasicAuthHandler()
	opener = urllib2.build_opener(proxy, auth, urllib2.HTTPHandler)
	urllib2.install_opener(opener)

	conn = urllib2.urlopen('http://api.openweathermap.org/data/2.5/weather?q=Kanpur')
	report = conn.read()
	f = open ("../../data/weather.dat", "w")
	f.write (report)
	f.close
	return
