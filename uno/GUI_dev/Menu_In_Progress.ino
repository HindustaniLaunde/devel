#include <glcd.h>
#include "fonts/allFonts.h"
#include "bitmaps/allBitmaps.h"

#include<Time.h>
const int binPins[] = {50,51,52,53};  // sets BINARY OUTPUT pins, (MIDI Channel selection via 4-bit binary output).
const int navButtonUp = 0;          // sets NAVIGATION UP pin.
const int navButtonDown =1;        // sets NAVIGATION DOWN pin.
const int menuButton = 2;           // sets MENU pin...
const int exitButton = 3;           // sets EXIT pin....


unsigned int menuVal = 0;           // sets inital MENU values - used to determine menu states.
unsigned int subMenuVal = 0;        // sets inital SUBMENU values = used to determine submenu states.
unsigned int midiVal = 1;           // sets inital MIDI CHANNEL Value.
unsigned int dispVal = 0;           // sets DISPLAY Value, (used for adjusting display parameters).

int btnTime = 300;                  // minimum delay between button presses or while button is held down.

//Sizes for analog clock pointers
#define RSEC 19
#define RMIN 15
#define RHOUR 10
#define ClockCenterX 25
char x, y;
	
unsigned char dy  = 5;

void setup()
{
  setTime(12,11,00,3,9,15);
  GLCD.Init(NON_INVERTED);                   
                         
  GLCD.SelectFont(System5x7);
  //BootScreen();  
  for (int index = 0; index < 4; index++)    // sets all BINARY output pins as OUTPUT
  {
    pinMode(binPins[index], OUTPUT);
  }
  pinMode(navButtonUp, INPUT);            
  digitalWrite(navButtonUp, LOW);           
  
  pinMode(navButtonDown, INPUT);          
  digitalWrite(navButtonDown, LOW);         
   
  pinMode(menuButton, INPUT);             
  digitalWrite(menuButton, LOW);            
  
  pinMode(exitButton, INPUT);             
  digitalWrite(exitButton, LOW);            
   
 // mainProgram();                            // initalize MAIN SCREEN...
}

void loop() // check button states/menu values before performing any functions
{
  if (menuVal == 0 && subMenuVal == 0) // MAIN SCREEN
  {
    mainProgramButtonState();
  }
  if (menuVal == 1 && subMenuVal <= 4) // MAIN MENU
  {
   // menuProgramButtonState();         
  }
  if (menuVal == 2)                    // SYSTEM RESET
  {
    systemResetButtonState();
  }
//  if (menuVal == 3)                    // DISPLAY OPTIONS
//  {
//    dispProgramButtonState();
//  }
  if (menuVal ==4 )                    // SYSTEM SETTINGS
  {
   systemSettingsButtonState();
  } 
  if (menuVal == 5)                    // SOFTWARE VERSION
  {
    aboutSystemButtonState();
  }

  DisplayClock();
  
}

void DisplayClock(){
        GLCD.ClearScreen();
        
        mainProgram();
        
        GLCD.DrawLine(54,0,54,63,BLACK);
        
//Digital Clock
        GLCD.SelectFont(fixednums8x16, BLACK);
	GLCD.GotoXY(56,0);	
        //Hour
	if (hour() < 10)
		GLCD.print('0');
	GLCD.print(hour());
	//Minute
	GLCD.print(':');
	if (minute() < 10)
		GLCD.print('0');
	GLCD.print(minute());
	//Seconds
	GLCD.print(':');
	if (second() < 10)
		GLCD.print('0');
	GLCD.print(second());
				
//Analog clock
        
	GLCD.DrawCircle(ClockCenterX,ClockCenterX,20,BLACK);
	//Second hand
	x = RSEC * sin(second()*PI/30);
	y = RSEC * cos(second()*PI/30);
	GLCD.DrawLine(ClockCenterX,ClockCenterX,ClockCenterX+x,ClockCenterX-y, BLACK);
	//Minute hand
	x = RMIN * sin(minute()*PI/30);
	y = RMIN * cos(minute()*PI/30);
	GLCD.DrawLine(ClockCenterX,ClockCenterX,ClockCenterX+x,ClockCenterX-y, BLACK);
	//Hour hand
	x = RHOUR * sin((hour()>11?hour()-12:hour())*PI/6);
	y = RHOUR * cos((hour()>11?hour()-12:hour())*PI/6);
	GLCD.DrawLine(ClockCenterX,ClockCenterX,ClockCenterX+x,ClockCenterX-y, BLACK);
        
        
//Clock Over....
//Alarm Section
GLCD.SelectFont(System5x7);
	//GLCD.DrawRoundRect(65, 28, 52, 30, 10, BLACK); 
	GLCD.GotoXY(65,40);
	GLCD.print("AL:");
        GLCD.GotoXY(65,48);	
	GLCD.print("TD:");
//Week dy, dy/mon/yr
	GLCD.GotoXY(65,18);
	GLCD.SelectFont(System5x7, BLACK);
	//Date Section
	if(day()<10) GLCD.print("0");
	GLCD.print(day());//date
	GLCD.print("/");
	if(month()<10) GLCD.print("0");
	GLCD.print(month());//mon
	GLCD.print("/");
	if(year()<10) GLCD.print("0");
	GLCD.print(year()); //yr 
GLCD.DrawLine(54,36,127,36,BLACK);
GLCD.GotoXY(65,28);
//dy of Week
	switch(dy){
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
delay(1000);
}

// this runs the main program screen, shows current MIDI channel, (updates based on "mainProgramButtonState()"), MIDI CC information, and MIDI in/out activity.

void mainProgram()
{ 
        GLCD.SelectFont(System5x7);
        GLCD.FillRect(0,54,54,8,BLACK);  // "MENU" text
        GLCD.CursorToXY(2,55); 
        GLCD.print("MENU");
//       GLCD.DefineArea(54,54,127,63);
//        GLCD.CursorToXY(2,56);
//        GLCD.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ*%ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

// this program shows main menu screen, and selectable items based on up or down button selection within the menuButtonState() program.
void mainMenuProgram()
{ 
  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7);
  GLCD.CursorToXY(2,2);
  GLCD.Puts("  RESTART CLOCK");
  GLCD.CursorToXY(2,11);
  GLCD.Puts("  WEATHER");
  GLCD.CursorToXY(2,20);
  GLCD.Puts("  Button 1");
  GLCD.CursorToXY(2,29);
  GLCD.Puts("  ABOUT US");
  
  GLCD.DrawLine(0,52,127,52);
  GLCD.CursorToXY(2,55);
  GLCD.Puts("ENTER");
  GLCD.CursorToXY(109,55);
  GLCD.Puts("ESC");
  
  // Displays selected menu items according to subMenuVal. The menuButtonState() program checks button presses of the UP and DOWN navigation buttons, and changes
  // menuVal (DOWN Button increments menuVal by 1, and UP Button decrements menuVal by 1, each press). This takes menuVal and displays which item is selected. 
  if (subMenuVal == 1) 
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("->RESTART CLOCK");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  WEATHER");
  }
  
  if (subMenuVal == 2)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("  RESTART CLOCK");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("->WEATHER");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  Button 1");
  }
  
  if (subMenuVal == 3)
  {
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  WEATHER");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("->Button 1");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("  ABOUT US");
  }
  
  if (subMenuVal == 4)
  {
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  Button 1");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("->ABOUT US");
  }
}

/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void mainProgramButtonState()
{
  int upBtn = digitalRead(navButtonUp);
  int downBtn = digitalRead(navButtonDown);
  int menuBtn = digitalRead(menuButton);
  
  if (upBtn == HIGH && midiVal <= 15) // changes MIDI channel value incrementally.
  {
    midiVal = (midiVal += 1);
    selectMidiChannel();
    mainProgram();
    delay(btnTime);
  }
  if (downBtn == HIGH && midiVal > 1) // changes MIDI channel value decrementally.
  {
    midiVal = (midiVal -= 1);
    mainProgram();
    selectMidiChannel();
    delay(btnTime);
  }
  if (menuBtn == HIGH) // enters into menu program 
  {
    menuVal = 1;
    subMenuVal = 1;
    GLCD.ClearScreen();
    mainMenuProgram();
    delay(btnTime);
  }
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


// this program checks button states while in the MAIN MENU SCREEN.

void menuProgramButtonState()
{
  int upBtn = digitalRead(navButtonUp);
  int downBtn = digitalRead(navButtonDown);
  int menuBtn = digitalRead(menuButton);
  int exitBtn = digitalRead(exitButton);
  
  if (upBtn == HIGH && subMenuVal > 1) // scrolls up to select MENU items.
  {
    subMenuVal = (subMenuVal -= 1);
    mainMenuProgram();
    delay(btnTime);
  }
  if (downBtn == HIGH && subMenuVal <= 3) // scrolls down to select MENU items.
  {
    subMenuVal = (subMenuVal += 1);
    mainMenuProgram();
    delay(btnTime);
  }
  if (exitBtn == HIGH) // exits menu screen back to MAIN PROGRAM.
  {
    menuVal = 0;
    subMenuVal = 0;
    GLCD.ClearScreen();
    mainProgram();
    delay(btnTime);
  }
  if (menuBtn == HIGH && subMenuVal == 1) // enters SYSTEM RESET screen when SYSTEM RESET is selected and ENTER button is pressed.
  {
    menuVal = 2;
    GLCD.ClearScreen();
    systemResetProgram();
    delay(btnTime);
  }
  if (menuBtn == HIGH && subMenuVal == 2) // enters DISPLAY ADJUSTMENT screen when DISPLAY OPTIONS is selected and ENTER button is pressed.
  {
    menuVal = 3;
    GLCD.ClearScreen();
    //dispAdjustProgram();
    delay(btnTime);
  }
  if (menuBtn == HIGH && subMenuVal == 3) // enters SYSTEM OPTIONS MENU screen when SYSTEM OPTIONS is selected and ENTER button is pressed.
  {
    menuVal = 4;
    subMenuVal = 5;
    GLCD.ClearScreen();
    systemSettingsProgram();
    delay(btnTime);
  }
  if (menuBtn == HIGH && subMenuVal == 4) // enters SYSTEM INFORMATION screen when SOFTWARE VERSION is selected and ENTER button is pressed.
  {
    menuVal = 5;
    GLCD.ClearScreen();
    aboutSystemSoftware();
    delay(btnTime);
  }
    
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// this program checks button states while on the SYSTEM RESET SCREEN.

void systemResetButtonState()
{
  int menuBtn = digitalRead(menuButton);
  int exitBtn = digitalRead(exitButton);
  
  if (menuBtn == HIGH)
  {
    GLCD.ClearScreen();
    performSystemReset();
    delay(btnTime);
  }
  if (exitBtn == HIGH)
  {
    menuVal = 1;
    GLCD.ClearScreen();
    mainMenuProgram();
    delay(btnTime);
  }
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void systemSettingsButtonState()
{
  int exitBtn = digitalRead(exitButton);
  int upBtn = digitalRead(navButtonUp);
  int downBtn = digitalRead(navButtonDown);
  //int leftBtn = digitalRead(navButtonLeft);
  //int rightBtn = digitalRead(navButtonRight);
  
  if (downBtn == HIGH && subMenuVal >= 5 && subMenuVal <= 6)
  {
    subMenuVal = (subMenuVal + 1);
    systemSettingsProgram();
    delay(btnTime);
  }
  if (upBtn == HIGH && subMenuVal <= 7 && subMenuVal >= 6)
  {
    subMenuVal = (subMenuVal - 1);
    systemSettingsProgram();
    delay(btnTime);
  }
  if (exitBtn == HIGH)
  {
    menuVal = 1;
    subMenuVal = 3;
    GLCD.ClearScreen();
    mainMenuProgram();
    delay(btnTime);
  }
}

////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


// this program checks button states while on the DISPLAY OPTIONS SCREEN.

//void dispProgramButtonState()
//{
//}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


void aboutSystemButtonState()
{
  int exitBtn = digitalRead(exitButton);
  
  if (exitBtn == HIGH)
  {
    menuVal = 1;
    GLCD.ClearScreen();
    mainMenuProgram();
    delay(btnTime);
  }
}
////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


// SYSTEM RESET screen.

void systemResetProgram() 
{
  GLCD.CursorToXY(28,5);
  GLCD.Puts("SYSTEM RESET");
  GLCD.DrawRect(25,2,76,13);
  GLCD.DrawLine(26,16,102,16);
  GLCD.DrawLine(102,3,102,16);
    
  GLCD.CursorToXY(25,38);
  GLCD.Puts("ARE YOU SURE?");
      
  GLCD.DrawLine(0,52,127,52);
  GLCD.CursorToXY(2,55); // Text for MENU text...
  GLCD.Puts("YES");
  GLCD.CursorToXY(115,55); // Text for ESC text...
  GLCD.Puts("NO");
}
/////////////////////////////////////////////////////////////////////////

// performs SYSTEM RESET.

void performSystemReset()
{
  menuVal = 0;
  subMenuVal = 0;
  midiVal = 1;
  dispVal = 0;  
  selectMidiChannel();
  
  GLCD.CursorToXY(35,20);
  GLCD.Puts("SYSTEM IS");
  GLCD.CursorToXY(35,29);
  GLCD.Puts("RESETTING");
  delay(1000);
  GLCD.CursorToXY(35,29);
  GLCD.Puts("RESETTING.");
  delay(1000);
  GLCD.CursorToXY(35,29);
  GLCD.Puts("RESETTING..");
  delay(1000);
  GLCD.ClearScreen();
  GLCD.CursorToXY(40,20);
  GLCD.Puts("COMPLETE");
  delay(2000);
  // delay times can be changed to adjust reset times. The dalays are purely for feel and are actually unnecessary. 
   
  BootScreen();
  delay(2000); // holds boot screen image for 3 seconds.
  GLCD.ClearScreen(); 
  mainProgram(); // returns to MAIN PROGRAM
}
//////////////////////////////////////////////////////////////////////////////////////////////////

// displays SYSTEM SETTINGS menu

void systemSettingsProgram()
{
  GLCD.CursorToXY(2,2);
  GLCD.Puts("  Button  ");
  GLCD.CursorToXY(2,11);
  GLCD.Puts("  menu item 1");
  GLCD.CursorToXY(2,20);
  GLCD.Puts("  menu item 2");
  
  GLCD.DrawLine(0,52,127,52);
  GLCD.CursorToXY(2,55);
  GLCD.Puts("ENTER");
  GLCD.CursorToXY(109,55);
  GLCD.Puts("ESC");
  
  if (subMenuVal == 5)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("->Button");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  menu item 1");
  }
  if (subMenuVal == 6)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("  Button  ");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("->menu item 1");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  menu item 2");
  }
  if (subMenuVal == 7)
  {
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  menu item 1");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("->menu item 2");
  }
}
    
    
    ///////////////////////////////////////////////////////////////////////
    
   // shows current Firmware Version.

void aboutSystemSoftware()
{
  GLCD.CursorToXY(13,2);
  GLCD.Puts("CPU Interface");
  GLCD.CursorToXY(31,11);
  //GLCD.Puts(softwareVersion); // "softwareVersion" text is determined in beginning of sketch.
  GLCD.CursorToXY(10,29);
  GLCD.Puts("Powered by Arduino");
    
  GLCD.DrawLine(0,52,127,52);
  GLCD.CursorToXY(115,55); 
  GLCD.Puts("OK");
}

////////////////////////////////////////////////////////////////////////////////////////

// outputs 4-bit binary - sets MIDI channel selection output pins accordingly, (refer to the Highly Liquid MIDI CPU Hardware manual, pg. 10, fig. 7.0).

void selectMidiChannel() 
{
  if (midiVal == 1)
  {
    setBinPins(LOW, LOW, LOW, LOW);
  }
  if (midiVal == 2)
  {
    setBinPins(HIGH, LOW, LOW, LOW);
  }
  if (midiVal == 3)
  {
    setBinPins(LOW, HIGH, LOW, LOW);
  }
  if (midiVal == 4)
  {
    setBinPins(HIGH, HIGH, LOW, LOW);
  }
  if (midiVal == 5)
  {
    setBinPins(LOW, LOW, HIGH, LOW);
  }
  if (midiVal == 6)
  {
    setBinPins(HIGH, LOW, HIGH, LOW);
  }
  if (midiVal == 7)
  {
    setBinPins(LOW, HIGH, HIGH, LOW);
  }
  if (midiVal == 8)
  {
    setBinPins(HIGH, HIGH, HIGH, LOW);
  }
  if (midiVal == 9)
  {
    setBinPins(LOW, LOW, LOW, HIGH);
  }
  if (midiVal == 10)
  {
    setBinPins(HIGH, LOW, LOW, HIGH);
  }  
  if (midiVal == 11)
  {
    setBinPins(LOW, HIGH, LOW, HIGH);
  }
  if (midiVal == 12)
  {
    setBinPins(HIGH, HIGH, LOW, HIGH);
  }
  if (midiVal == 13)
  {
    setBinPins(LOW, LOW, HIGH, HIGH);
  }
  if (midiVal == 14)
  {
    setBinPins(HIGH, LOW, HIGH, HIGH);
  }
  if (midiVal == 15)
  {
    setBinPins(LOW, HIGH, HIGH, HIGH);
  }
  if (midiVal == 16)
  {
    setBinPins(HIGH, HIGH, HIGH, HIGH);
  }
}

////////////////////////////////////////////////////////////////////
// sets binPins according to program above, selectMidiChannel()

void setBinPins(int bin1, int bin2, int bin4, int bin8)
{
 digitalWrite(binPins[0], bin1);
 digitalWrite(binPins[1], bin2);
 digitalWrite(binPins[2], bin4);
 digitalWrite(binPins[3], bin8);
}

void BootScreen(){
  GLCD.ClearScreen(); 
  //GLCD.DrawRoundRect(0,0,64,128, 10, BLACK);  
  GLCD.SelectFont(System5x7);
  
  GLCD.DrawBitmap(Arduino, 0,0, BLACK);
  delay(1000);
  
  GLCD.ClearScreen();
  GLCD.GotoXY(5,1);
  GLCD.Puts("Team Electro \n Presents...");
  GLCD.GotoXY(30,35);
  for (int i = 0; i < 15; ++i) 
  {
    delay(250);
    GLCD.print("#");
  }
  
  GLCD.ClearScreen();
  //GLCD.DrawRoundRect(0,0,64,128, 10, BLACK); 
  GLCD.GotoXY(10,1);
  GLCD.Puts("\n An IOT Clock ");
  delay(500);
  GLCD.GotoXY(30,1);
  GLCD.Puts("Based on Arduino and Espduino.. ");
  delay(1000);
  
  
  GLCD.ClearScreen();
}
