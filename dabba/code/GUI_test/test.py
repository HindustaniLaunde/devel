#----------------------------------------------------------------------
import easygui
msg = "Enter your personal information"
title = "Credit Card Application"
fieldNames = ["Hour","Minute","Second","Date", "Month", "Year", "Remind me for",]
fieldValues = []  # we start with blanks for the values
fieldValues = easygui.multenterbox(msg,title, fieldNames)

# make sure that none of the fields was left blank
while 1:
    if fieldValues == None: break
    errmsg = ""
    for i in range(len(fieldNames)):
        if fieldValues[i].strip() == "":
            errmsg = errmsg + ('"%s" is a required field.' % fieldNames[i])
    if errmsg == "": break # no problems found
    fieldValues = easygui.multenterbox(errmsg, title, fieldNames, fieldValues)
st = ''
for value in fieldValues:
	st += value
	st += ':'
	
print st