#!/usr/bin/python

data = ["temp", "humidity", "name"]
def SHAS ():
			
	import fileinput, re
	for line in fileinput.input("../../data/weather.dat", inplace=True):
		print(line.replace(",", " , "))
	fileinput.close
	report = open ("../../data/weather.dat", "r")
	packet = open ("../../data/temp", "w")
	for line in report:
		for word in line.split():
			#print word
			for  match in data:
				if match+"\"" in word:
					packet.write (word + "\n")

	return


def packet ():
	SHAS()

	import fileinput
	for line in fileinput.input("../../data/temp", inplace = True):
		print(line.replace("\"main\":{", ""))

	fileinput.close


	for line in fileinput.input("../../data/temp", inplace = True):
		print(line.replace("\"main\":{", ""))

	f = open ("../../data/temp",'a')


	f.write ('$')
	f.close


	f = open ("../../data/temp", 'r')
	f.seek (0)
	c = f.read(1)
	a = ''
	type (a)
	type (c)
	while c != '$':
		if c == ":":
			c = f.read (1)
			while c != '\n':
				a += c
				c = f.read(1)
			a += ','
			c = f.read(1)
		if (c == '$'):
			break
		c = f.read (1)
	print a

	f.close

	packet = open ("../../data/packet.dat", 'w')

	packet.write (a)
	return