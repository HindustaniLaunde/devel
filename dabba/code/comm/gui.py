import easygui
import threading
import publish

def reminder_gui():
	#*****************************************************************************#
	msg = "Enter Data for Reminder"
	title = "SmartClock v1.0"
	fieldNames = ["Hour","Minute","Second","Day (in DD)", "Month (in MM)", "Year ( in YYYY)", "Remind me to"]
	fieldValues = []  # we start with blanks for the values
	fieldValues = easygui.multenterbox(msg,title, fieldNames)
	while 1:
		if fieldValues == None: break
		errmsg = ""
		for i in range(len(fieldNames)):
			if fieldValues[i].strip() == "":
				errmsg = errmsg + ('"%s" is a required field.' % fieldNames[i])
		if errmsg == "": break # no problems found
		fieldValues = easygui.multenterbox(errmsg, title, fieldNames, fieldValues)

	st = ''
	if fieldValues == None:
		return 0
	
	for value in fieldValues:
		st += value + ":"
	f = open ("../../data/reminder.txt", "w")
	f.write (st+'\n')
	f.close
	return 1

#*****************************************************************************#
#*****************************************************************************#

def todo_template():
	template = ["Lab at ", "Call Home at ", "Complete Assignment by ", "Eat medicine at", "Extra class at", "Meeting at","Football Match at","Cricket match at","Return library book by"]
	reply = easygui.multchoicebox (msg='Pick one of the reminder templates.', title='Reminder Templates', choices = template)
	return reply

def city_list():
	f = open ("../../data/cities.dat", "r")
	city_list = f.readlines()
	reply = easygui.multchoicebox (msg='Choose City.', title='City List', choices = city_list)
	f.close
	return reply

def todo_():
	#reply = easygui.enterbox(msg = "TO-DO", title = "TO-DO", default = '', strip = True)
	
	#print reply
	#f = open ("../../data/TODO.txt", "w")
	#f.write (reply + "\n")
	#f.close
	ynreply = easygui.ynbox(msg = 'Do you want to choose from TODO template?', title = 'Please Answer', choices = ('Yes', 'No'), image = None)
	if  ynreply == 1:
		default = todo_template()

	else:
		default = "Enter TODO Text"

	ynreply = easygui.ynbox(msg='Do you want to reset the TODO file?', title='Please Answer', choices=('Yes', 'No'), image=None)
	rw = ''
	if ynreply == 1:
		rw = "w"
	else: rw = "a"
	#fieldNames = ["TO-DO"]
	#fieldValues = []  # we start with blanks for the values
	while True:
		#fieldValues = easygui.enterbox(msg,fieldNames[0], fieldNames)
		reply = easygui.enterbox("Enter TO-DO", "Smart Clock v1.0", default, strip = True)
		if reply:
			f = open ("../../data/TODO.txt", rw)
			f.write (reply + "\n")
			f.close
			ynreply = easygui.ynbox(msg = 'Sure To Save?', title = 'Please Answer', choices = ('Yes', 'No'), image = None)
			if ynreply == 1:
				break
		else: break

def change_city_gui():
	ynreply = easygui.ynbox(msg='Do you want to Choose From the Listof Cities?', title='Choose', choices=('Yes', 'No'), image=None)
	if  ynreply == 1:
		default = city_list()
	
	else:
		default = "Kanpur"

	reply = easygui.enterbox ("Change City", "Smart Clock v1.0", default, strip = True)
	if reply:
		f = open ("../../data/current_city.dat", "w")
		f.write (reply)
		f.close
	return
#*****************************************************************************#
#*****************************************************************************#
#threading.Thread(target=publish.publish).start()
msg   = "Team Electro Welcomes You!"
set_reminder = "Set Reminder"
todo = "Add To-Do"
news = "News"
change_city = "Change City"
close = "Close"
choices = [set_reminder, todo, news, change_city, close]
reply = easygui.buttonbox(msg, title = "Smart Clock", choices=choices, image = "./mauryans.gif")
while True:
	
	#*****************************************************************************#
	
	if reply == set_reminder:
		#reply = easygui.enterbox(msg, title, default, strip = True)
		reminder_gui()
	
	#*****************************************************************************#
	
	if reply == todo:
				
		#ynreply = easygui.ynbox(msg = 'Do you want to choose from TODO template?', title = 'Please Answer', choices = ('Yes', 'No'), image = None)
		#if  ynreply == 1:
			#default = todo_template()

		#else:
			#default = "Enter TODO Text"

		#ynreply = easygui.ynbox(msg='Do you want to reset the TODO file?', title='Please Answer', choices=('Yes', 'No'), image=None)
		#rw = ''
		#if ynreply == 1:
			#rw = "w"
		#else: rw = "a"
		##fieldNames = ["TO-DO"]
		##fieldValues = []  # we start with blanks for the values
		#while True:
			##fieldValues = easygui.enterbox(msg,fieldNames[0], fieldNames)
			#reply = easygui.enterbox("Enter TO-DO", "Smart Clock v1.0", default, strip = True)
			#if reply:
				#f = open ("../../data/TODO.txt", rw)
				#f.write (reply + "\n")
				#f.close
				#ynreply = easygui.ynbox(msg = 'Sure To Save?', title = 'Please Answer', choices = ('Yes', 'No'), image = None)
				#if ynreply == 1:
					#break
			#else: break
		#*****************************************************************************#
		#else: continue
		#reply = easygui.enterbox(msg = "TO-DO", title = "TO-DO", default = '', strip = True)
		#print reply
		#f = open ("../../data/TODO.txt", "w")
		#f.write (reply + "\n")
		#f.close
		#else: continue
		todo_()
	#*****************************************************************************#
	
	if reply == news:
		f = open("../../data/rss", "r")
		easygui.textbox(msg='', title='News', text = f.read(), codebox=0)
		f.close
	
	if reply == change_city:
		
		#ynreply = easygui.ynbox(msg='Do you want to Choose From the Listof Cities?', title='Choose', choices=('Yes', 'No'), image=None)
		#if  ynreply == 1:
			#default = city_list()
		
		#else:
			#default = "Kanpur"

		#reply = easygui.enterbox (msg, title, default, strip = True)
		#if reply:
			#f = open ("../../data/current_city.dat", "w")
			#f.write (reply)
			#f.close
			#continue
			change_city_gui()
	#*****************************************************************************#
	
	if reply == close:
		break
	reply = easygui.buttonbox(msg, title = "Smart Clock", choices=choices, image = "./mauryans.gif")
