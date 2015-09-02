#!/usr/bin/python

def rss():
	import os
	bashcommand = "rsstail -u http://feeds.reuters.com/reuters/INtopNews > ../../data/rss"
	os.system(bashcommand)
	return
