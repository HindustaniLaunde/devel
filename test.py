import easygui
import threading
def message():
	easygui.msgbox("Backup complete!", ok_button="Good job!")
	return
def test():
	threading.Thread(target=message).start()
	print  "testStarted"

test()
