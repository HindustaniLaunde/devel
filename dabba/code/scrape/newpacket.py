f = open ("../../data/packet.dat", 'r')
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

packet = open ("../../data/new_packet.dat", 'w')

packet.write (a)
