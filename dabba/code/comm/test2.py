from bs4 import BeautifulSoup
import mechanize
import cookielib
import json
from bs4 import BeautifulSoup
br=mechanize.Browser()
br.set_handle_robots(False)
cj = cookielib.LWPCookieJar()
br.set_cookiejar(cj)
br.addheaders=[("User-agent","Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko")]

time_table=br.retrieve("http://www.timeanddate.com/worldclock/india/kanpur")
fil=open(time_table[0],"r")
html=fil.read()

soup=BeautifulSoup(html)
x=soup.find_all("section",{"class":"bk-wc"})
y=x[0].find_all("div")
z=y[0].find_all("div")
a=z[0].find_all("span")
print a[0].text
