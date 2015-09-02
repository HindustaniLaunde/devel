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
