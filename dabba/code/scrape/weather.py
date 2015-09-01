from sets import Set
searchterms = Set(['\"temp\"'])

#def words(fileobj):
	#for line in fileobj:
		#for word in line.split():
			#yield word



#with open("weather.dat") as weather:
	#temp = words(weather)
	#for word in weather:
		#if word in searchterms:
			#break

def words(fileobj):
    for line in fileobj:
        for word in line.split():
            print word, '\n'
            yield word


with open("../../data/weather.dat") as wordfile:
    wordgen = words(wordfile)
    for word in wordgen:
        if word in searchterms:   # searchterms should be a set() to make this fast
            print word
    else:
        word = None               # makes sure word is None if the word wasn't found

#    foundwords = [word, next(wordgen, None), next(wordgen, None)]
#    print foundwords

