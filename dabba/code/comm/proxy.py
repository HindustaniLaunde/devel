import urllib2

proxy = urllib2.ProxyHandler({'http': 'http://username:password@vsnlproxy.iitk.ac.in:3128'})
auth = urllib2.HTTPBasicAuthHandler()
opener = urllib2.build_opener(proxy, auth, urllib2.HTTPHandler)
urllib2.install_opener(opener)

conn = urllib2.urlopen('http://api.openweathermap.org/data/2.5/weather?q=Kanpur')
return_str = conn.read()
print return_str
