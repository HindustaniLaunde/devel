def rss():
	import subprocess
	bashcommand = "rsstail -u  http://feeds.reuters.com/reuters/INtopNews >> ../../data/rss"
	
	process = subprocess.Popen (bashcommand.split(), stdout = subprocess.PIPE)
	output = process.communicate()[0]
	return
	
rss()
