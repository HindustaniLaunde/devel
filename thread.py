import threading
import test

threading.Thread(target=test.test).start()

print "main window started"
