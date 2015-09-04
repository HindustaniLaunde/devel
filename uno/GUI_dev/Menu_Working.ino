#include <glcd.h>
#include "fonts/allFonts.h"
#include "bitmaps/allBitmaps.h"
#include<Time.h>

#define menuButton 2           
#define exitButton 12           

unsigned int menuVal = 0;          
unsigned int subMenuVal = 0;      

#define btnTime 300                  // for debouncing of button

//Sizes for analog clock pointers
#define RSEC 19
#define RMIN 15
#define RHOUR 10
#define ClockCenterX 25

//int getSubMenuVal(void);

void setup()
{  
  pinMode(A5,INPUT);
  setTime(4,42,00,3,9,15);
  GLCD.Init(NON_INVERTED);                   
  GLCD.SelectFont(System5x7);
  //BootScreen();  
  pinMode(menuButton, INPUT);             
  digitalWrite(menuButton, LOW);            
  
  pinMode(exitButton, INPUT);             
  digitalWrite(exitButton, LOW);            
   
  mainProgram();                            // initalize MAIN SCREEN...
}

void loop()
{
  if (menuVal == 0 && subMenuVal == 0) 
  {
   DisplayClock(); 
  }
  if (menuVal == 1 && subMenuVal <= 4) 
  {
   GLCD.ClearScreen();
   mainMenuProgram();   
  }
  if (menuVal == 2)                    
  {
     GLCD.ClearScreen();
     systemResetProgram();
  }
  if (menuVal == 3)                   
  {
    displayWeatherScreen();
  }
  if (menuVal ==4 )                    
  {
   displayNewsScreen();
  } 
  if (menuVal == 5)                    
  {
    aboutUsScreen();
  }
  
}

void DisplayClock()
{
    char x, y;
    unsigned char dy  = 5;
    GLCD.ClearScreen();
    mainProgram();
    GLCD.DrawLine(54,0,54,63,BLACK);
        
    //The digitalClock
    GLCD.SelectFont(fixednums8x16, BLACK);  
    GLCD.GotoXY(56,0);	
    if (hour() < 10)
    GLCD.print('0');
    GLCD.print(hour());
    GLCD.print(':');
    if (minute() < 10)
	GLCD.print('0');
    GLCD.print(minute());
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
  if(day()<10) 
    GLCD.print("0");
  GLCD.print(day());//date
  GLCD.print("/");
  if(month()<10) 
    GLCD.print("0");
  GLCD.print(month());//mon
  GLCD.print("/");
  if(year()<10) 
    GLCD.print("0");
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
    unsigned long currentTime=millis();
    unsigned long delta=0;
    delta=0;
    while(delta<995)
    {
      if(digitalRead(menuButton)==HIGH)
      {
        menuVal=1;
        delay(btnTime);
       break;
      }
      delta=millis()-currentTime;
    }
}
void mainProgram()
{ 
        GLCD.SelectFont(System5x7);
        GLCD.FillRect(0,54,54,8,BLACK);  // "MENU" text
        GLCD.CursorToXY(2,55);
        GLCD.SetFontColor( WHITE); 
        GLCD.print("MENU");
        // GLCD.DefineArea(55,54,127,63);
        //GLCD.CursorToXY(56,56);
        //GLCD.SetTextMode(SCROLL_UP);
        //GLCD.print("SHYAM");
        
        //GLCD.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ*%ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

void mainMenuProgram()
{ 
  Serial.print("menu\n");
  subMenuVal=getSubMenuVal();
  GLCD.DrawLine(0,52,127,52);
  GLCD.CursorToXY(2,55);
  GLCD.Puts("ENTER");
  GLCD.CursorToXY(109,55);
  GLCD.Puts("ESC");

  if (subMenuVal == 1) 
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("->SYSTEM RESET");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  Current News");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  Weather");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("  About Us");
  }
  
  if (subMenuVal == 2)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("  SYSTEM RESET");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("->Current News");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  Weather");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("  About Us");
   
  }
  
  if (subMenuVal == 3)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("  SYSTEM RESET");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  Current News");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("->Weather");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("  About Us");
  }
  
  if (subMenuVal == 4)
  {
    GLCD.CursorToXY(2,2);
    GLCD.Puts("  SYSTEM RESET");
    GLCD.CursorToXY(2,11);
    GLCD.Puts("  Current News");
    GLCD.CursorToXY(2,20);
    GLCD.Puts("  Weather");
    GLCD.CursorToXY(2,29);
    GLCD.Puts("->About Us");
   }
   int previousSubMenuVal=subMenuVal;
  while(1)
  {
    subMenuVal=getSubMenuVal();
    if(previousSubMenuVal!=subMenuVal)
      break;
    int menuBtn = digitalRead(menuButton);
    int exitBtn = digitalRead(exitButton);
  
    if (exitBtn == HIGH) // exits menu screen back to MAIN PROGRAM.
    {
      menuVal = 0;
      subMenuVal = 0;
      GLCD.ClearScreen();
      mainProgram();
      delay(btnTime);
      break;
    }
    if (menuBtn == HIGH && subMenuVal == 1) 
    {
      menuVal = 2;
      GLCD.ClearScreen();
      systemResetProgram();
      delay(btnTime);
      break;
    }
    if (menuBtn == HIGH && subMenuVal == 2) 
    {
      menuVal = 3;
      GLCD.ClearScreen();
      delay(btnTime);
      break;
    }
    if (menuBtn == HIGH && subMenuVal == 3) 
    {
      menuVal = 4;
      GLCD.ClearScreen();
      delay(btnTime);
      break;
    }
    if (menuBtn == HIGH && subMenuVal == 4)
    {
      menuVal = 5;
      GLCD.ClearScreen();
      delay(btnTime);
      break;
    }
  }
}

// this program checks button states while on the SYSTEM RESET SCREEN.

void displayWeatherScreen(void)
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

void displayNewsScreen(void)
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
void aboutUsScreen()
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
  GLCD.CursorToXY(2,55);
  GLCD.Puts("YES");
  GLCD.CursorToXY(115,55); 
  GLCD.Puts("NO");
  
  while(1)
  {
    int menuBtn = digitalRead(menuButton);
    int exitBtn = digitalRead(exitButton);
    if (menuBtn == HIGH)
    {
      GLCD.ClearScreen();
      performSystemReset();
      delay(btnTime);
      break;
    }
    if (exitBtn == HIGH)
    {
      menuVal = 1;
      GLCD.ClearScreen();
      mainMenuProgram();
      delay(btnTime);
      break;
    }
  }
}

// delay times can be changed to adjust reset times. The dalays are purely for feel and are actually unnecessary. 
void performSystemReset()
{
  menuVal = 0;
  subMenuVal = 0;
  
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
    
  BootScreen();
  delay(2000); // holds boot screen image for 3 seconds.
  GLCD.ClearScreen(); 
  mainProgram();
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
