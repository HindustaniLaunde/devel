/*If the Arduino's LED blinks every 1 second, then mqtt connection has failed
 * If the LED is LOW, then the arduino is succesfully connected to 192.168.0.108
 * Else, it curently disconnected.
 */
#include <espduino.h>

extern boolean wifiConnected;
extern ESP esp;
void setup()
{
 initMQTT();
}

void loop() {
  esp.process();
  if (wifiConnected) {

  }
}
