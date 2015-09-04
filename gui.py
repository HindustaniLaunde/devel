import easygui

def rem_template():
	template = ["LAB at ", "Call Home", "Complete Assignment", "Eat medicine"]
	reply = easygui.multchoicebox (msg='Pick one of the reminder Template.', title='Reminder Template', choices = template)
	return reply

msg   = "Team Electro Welcomes You!"
set_reminder = "Set Reminder"
todo = "Add To-Do"
news = "News"
close = "Close"
choices = [set_reminder, todo, news, close]
while True:
	reply = easygui.buttonbox(msg, title = "Smart Clock", choices=choices, image = "DBTech_Digital_Clock_Green.jpg")
	
	if reply == set_reminder:
		
		msg = "Reminder!"
		title = "Reminder"
		
		ynreply = easygui.ynbox(msg='Do you want to choose from reminder template?', title=' ', choices=('Yes', 'No'), image=None)
		if  ynreply == 1:
			default = rem_template()

		else:
			default = "Enter Reminder Text"

		
		reply = easygui.enterbox(msg, title, default, strip = True)
		if reply:
			f = open ("reminder.txt", "w")
			f.write (reply)
			f.close
			continue
		
		else: continue
	if reply == news:
		f = open("./dabba/data/rss", "r")
		easygui.textbox(msg='', title='News', text = f.read(), codebox=0)
		f.close
	if reply == close:
		break
