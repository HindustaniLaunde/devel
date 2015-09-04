#https://maps.googleapis.com/maps/api/timezone/xml?location=39.60,-119.68&timestamp=1331161200&key=AIzaSyC0fpj5-IdgdfMRiSOpggo49Jv0xlel1Sw
def getTime(lat,lon):
	import urllib2
	proxy = urllib2.ProxyHandler({'http': 'http://amanabt:IITKaat@vsnlproxy.iitk.ac.in:3128'})
	auth = urllib2.HTTPBasicAuthHandler()
	opener = urllib2.build_opener(proxy, auth, urllib2.HTTPHandler)
	urllib2.install_opener(opener)

	conn = urllib2.urlopen("https://maps.googleapis.com/maps/api/timezone/xml?location="+lat+","+lon+"&timestamp=1331161200&key=AIzaSyC0fpj5-IdgdfMRiSOpggo49Jv0xlel1Sw")
	report = conn.read()
	f = open("timetz.dat", "w")
	f.write (report)
	print report
	import os
	bashcommand0 = "export GMT"
	bashcommand1 = "date +%s > ~/devel/dabba/code/comm/timestamp"
	#bashcommand2 = "cp ~/devel/dabba/code/comm/timetz.dat ~/devel/dabba/code/comm/timezone.dat"
	os.system(bashcommand0)
	os.system(bashcommand1)
	#os.system(bashcommand2)
	f.seek(0)
	f.close
	f = open("timetz.dat", "r")
	line1 = ''
	for line in f:
		if "raw_offset" in line:
			line1 = line
			break
	f.close
	f = open("timestamp", "r")
	timestamp = int (f.read())
	
	import re
	data = re.search(r"\d+(\.\d+)?", line1)
	offset = float(data.group(0))
	import datetime
	current_time = datetime.datetime.fromtimestamp(int(timestamp + offset)).strftime('%Y,%m,%d,%H,%M,%S')
#	print current_time
	return current_time

print getTime("25.25","87")
