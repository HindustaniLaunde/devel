import easygui

def reminder_gui():
	#*****************************************************************************#
	msg = "Enter your personal information"
	title = "Credit Card Application"
	fieldNames = ["Hour","Minute","Second","Date", "Month", "Year", "Remind me for",]
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
		return ''
	for value in fieldValues:
		st += value
		st += ':'
	return st

#*****************************************************************************#
#*****************************************************************************#

def todo_template():
	template = ["LAB at ", "Call Home", "Complete Assignment", "Eat medicine"]
	reply = easygui.multchoicebox (msg='Pick one of the reminder Template.', title='Reminder Template', choices = template)
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
	reply = easygui.buttonbox(msg, title = "Smart Clock", choices=choices, image = "DBTech_Digital_Clock_Green.jpg")
	
	#*****************************************************************************#
	
	if reply == set_reminder:
		msg = "Reminder!"
		title = "Reminder"
		default = "Enter Reminder Text"
		#reply = easygui.enterbox(msg, title, default, strip = True)
		reply = reminder_gui()
		if reply:
			f = open ("reminder.txt", "w")
			f.write (reply)
			f.close
			continue
		
		else: continue
	
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
			open("TODO.txt", "w")
		reply = easygui.enterbox(msg, title, default, strip = True)
		if reply:
			f = open ("TODO.txt", "a")
			f.write (reply + "\n")
			f.close
			continue
		
		else: continue
	
	#*****************************************************************************#
	
	if reply == news:
		f = open("./dabba/data/rss", "r")
		easygui.textbox(msg='', title='News', text = f.read(), codebox=0)
		f.close
	
	#*****************************************************************************#
	
	if reply == close:
		break
