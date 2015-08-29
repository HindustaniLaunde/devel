import urllib2
urllib2.install_opener(
    urllib2.build_opener(
        urllib2.ProxyHandler({'http': '127.0.0.1'})
    )
)
urllib2.urlopen('http://webmail.iitk.ac.in/')
