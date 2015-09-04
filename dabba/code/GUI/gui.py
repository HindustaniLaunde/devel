import easygui

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


#*****************************************************************************#
#*****************************************************************************#


msg   = "Team Electro Welcomes You!"
set_reminder = "Set Reminder"
todo = "Add To-Do"
news = "News"
close = "Close"
choices = [set_reminder, todo, news, close]
while True:
	reply = easygui.buttonbox(msg, title = "Smart Clock", choices=choices, image = "./mauryans.gif")
	
	#*****************************************************************************#
	
	if reply == set_reminder:
		#reply = easygui.enterbox(msg, title, default, strip = True)
		reminder_gui()
	
	#*****************************************************************************#
	
	if reply == todo:
		
		msg = "TO-DO!"
		title = "TO-DO"
		
		ynreply = easygui.ynbox(msg='Do you want to choose from TODO template?', title='Please Answer', choices=('Yes', 'No'), image=None)
		if  ynreply == 1:
			default = todo_template()
		
		else:
			default = "Enter TODO Text"
		
		ynreply = easygui.ynbox(msg='Do you want to reset the TODO file?', title='Please Answer', choices=('Yes', 'No'), image=None)
		if ynreply == 1:
			open("../../data/TODO.txt", "w")
		reply = easygui.enterbox(msg, title, default, strip = True)
		if reply:
			f = open ("../../data/TODO.txt", "a")
			f.write (reply + "\n")
			f.close
			continue
		
		#else: continue
	
	#*****************************************************************************#
	
	if reply == news:
		f = open("../../data/rss", "r")
		easygui.textbox(msg='', title='News', text = f.read(), codebox=0)
		f.close
	
	#*****************************************************************************#
	
	if reply == close:
		break
