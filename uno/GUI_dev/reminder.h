struct reminder
{
	int time[6];
	char* text;
}reminder0;




int check_reminder (void)
{
	int i = 0;
	if (reminder0.time[i] <= hour()){
		++i;
		if (reminder0.time[i] <= min()){
			++i;
			if (reminder0.time[i] <= second()){
				++i;
				if (reminder0.time[i] <= day()){
					++i;
					if (reminder0.time[i] <= month()){
						++i;
						if (reminder0.time[i] <= year()) ++i;}}}}}
	if (i == 6) {
		GLCD.ClearScreen();
		GLCD.SelectFont (System5x7);
        GLCD.CursorToXY(2,55);
        GLCD.print ("GOT IT");
		GLCD.CursorToXY(111,55);
		GLCD.print ("ZZZ");
		GLCD.CursorToXY(9,9);
		GLCD.SelectFont (fixednums8x16, BLACK);
		GLCD.print (reminder0.text)
		int menuBtn = digitalRead (menuButton);
		while (1) {
			if ((min() > reminder0.time[1] + 1) || digitalRead (menuButton)) break;
			if (digitalRead(navButtonUp)){
				reminder0.time[1] += 10;
				break;
			}
		}
	}
}
		