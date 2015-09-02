#include <glcd.h> 
#include "fonts/Verdana_digits_24.h"
#include "fonts/SystemFont5x7.h"   // system font
//#include "ArduinoIcon.h"     // bitmap  
#include<Time.h>

//Sizes for analog clock pointers
#define RSEC 28
#define RMIN 20
#define RHOUR 15

void setup(){
  GLCD.Init(NON_INVERTED);   // initialise the library
  GLCD.ClearScreen();  
  //GLCD.DrawBitmap(ArduinoIcon, 32,0, BLACK); //draw the bitmap at the given x,y position
  delay(3000);
  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7);       // select fixed width system font 
}
void loop(){ 
  
        GLCD.ClearScreen();
        char x, y;	
	unsigned char hour = random(0,12);
    	unsigned char min  = random(0,60);
	unsigned char sec  = random(0,60);
	unsigned char day  = 3 ;
	unsigned char date  = 1;
	unsigned char month  = 9;
	unsigned char year  = 15;
        GLCD.DrawLine(64,0,64,63,BLACK);
//Digital Clock
        GLCD.SelectFont(Verdana24, BLACK);
	GLCD.GotoXY(65,0);	
        //Hour
	if (hour < 10)
		GLCD.print('0');
	GLCD.print(hour);
	//Minute
	GLCD.print(':');
	if (min < 10)
		GLCD.print('0');
	GLCD.print(min);
	//Seconds
	GLCD.print(':');
	if (sec < 10)
		GLCD.print('0');
	GLCD.print(sec);
				
//Analog clock
	GLCD.DrawCircle(32,32,30,BLACK);
	//Second hand
	x = RSEC * sin(sec*PI/30);
	y = RSEC * cos(sec*PI/30);
	GLCD.DrawLine(32,32,32+x,32-y, BLACK);
	//Minute hand
	x = RMIN * sin(min*PI/30);
	y = RMIN * cos(min*PI/30);
	GLCD.DrawLine(32,32,32+x,32-y, BLACK);
	//Hour hand
	x = RHOUR * sin((hour>11?hour-11:hour)*PI/6);
	y = RHOUR * cos((hour>11?hour-11:hour)*PI/6);
	GLCD.DrawLine(32,32,32+x,32-y, BLACK);
//Clock Over....
//Alarm Section
	GLCD.DrawRoundRect(65, 28, 52, 30, 10, BLACK); 
	GLCD.GotoXY(75,40);
	GLCD.print("Alarm:");	
	GLCD.print("To Do:");
//Week Day, Day/Month/Year
	GLCD.GotoXY(38,25);
	GLCD.SelectFont(System5x7, BLACK);
	
//Day of Week
	switch(day){
		case 1:
			GLCD.print("SUN");
			break;
		case 2:
			GLCD.print("MON");
			break;
		case 3:
			GLCD.print("TUE");
			break;
		case 4:
			GLCD.print("WED");
			break;
		case 5:
			GLCD.print("THU");
			break;
		case 6:
			GLCD.print("FRI");
			break;
		default:
			GLCD.print("SAT");
	}
	GLCD.print(" ");
//Date Section
	if(date<10) GLCD.print("0");
	GLCD.print(date);//date
	GLCD.print("/");
	if(month<10) GLCD.print("0");
	GLCD.print(month);//month
	GLCD.print("/20");
	if(year<10) GLCD.print("0");
	GLCD.print(year); //year
 }
