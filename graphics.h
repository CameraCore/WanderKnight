//This file is used to output the graphics
#include <iostream>
using namespace std;

	//1 is bold/bright
	//30 = black	34 = blue
	//31 = red	35 = magenta
	//32 = green	36 = cyan
	//33 = yellow	37 = white
	//\u2588 = Full shade
	//\u2583 = Dark shade
	//\u2582 = Medium shade
	//\u2591 = Light shade
	//
	//\u26FA = Tent
	//\u2764 = Full Heart
	//\u2665 = Heart, for Health
	//\u2660 = Spade, for Mana
	//\u2666 = Diamond, for Gold
	//\u2663 = Clubs, for Experience
	//\u265C = Rook, for towns maybe
	//! = enemy encounters
	//? = events
	//$ = treasure
	//\u2620 = boss tile
void pushUp()
{
	for(int i = 0; i < 60; ++i){cout << '\n';}
}
void displayTitle()
{
	pushUp();
	cout << endl
	     << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n"
	     << "\u2551\033[1;31m \u2588   \u2588  \u2588\u2588   \u2588\u2588  \u2588\u2588\u2588  \u2588\u2588\u2588\u2588 \u2588\u2588\u2588  \033[0m\u2551\n"
	     << "\u2551\033[1;31m \u2588 \u2588 \u2588	\u2588  \u2588 \u2588  \u2588 \u2588  \u2588 \u2588\u2588\u2588  \u2588  \u2588 \033[0m\u2551\n"
	     << "\u2551\033[1;31m \u2588 \u2588 \u2588	\u2588\u2588\u2588\u2588 \u2588  \u2588 \u2588  \u2588 \u2588    \u2588\u2588\u2588  \033[0m\u2551\n"
	     << "\u2551\033[1;31m \u2588\u2588\u2588\u2588\u2588 \u2588  \u2588 \u2588  \u2588 \u2588\u2588\u2588  \u2588\u2588\u2588\u2588 \u2588  \u2588 \033[0m\u2551\n"
	     << "\u2551\033[1;37m   \u2588  \u2588  \u2588\u2588  \u2588\u2588\u2588  \u2588\u2588\u2588 \u2588  \u2588 \u2588\u2588\u2588  \033[0m\u2551\n"
	     << "\u2551\033[1;37m   \u2588 \u2588  \u2588  \u2588  \u2588  \u2588    \u2588  \u2588  \u2588   \033[0m\u2551\n"
	     << "\u2551\033[1;37m   \u2588\u2588\u2588  \u2588  \u2588  \u2588  \u2588  \u2588 \u2588\u2588\u2588\u2588  \u2588   \033[0m\u2551\n"
	     << "\u2551\033[1;37m   \u2588  \u2588 \u2588  \u2588 \u2588\u2588\u2588  \u2588\u2588\u2588 \u2588  \u2588  \u2588   \033[0m\u2551\n"

	     << "\u255A\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255D\n" 
	     << "\tCameraCore (C) 2019"
	     << "\033[0m \n" <<endl;
}
void displayTitleOptions()
{
	cout << endl
	     << "\t\033[1;37m 1) New Game \033[0m\n\n" 
	     << "\t\033[1;37m 2) Load Game \033[0m\n\n" 
	     << "\t\033[1;37m 3) Quit \033[0m\n"  << endl;
}
void displayNamingScreen()
{
	cout << endl
	     << "\t\033[1;37m What is my name? \033[0m\n\n"
	     << "\t\033[1;37m _ _ _ _ _ _ _ _ \033[0m\n" << endl;
}
void displayOptions()
{
	cout << "\ne - enter\ti - inventory\t\no - options\tp - party" << endl;
}
void displayOptionsInner()
{
	cout << "\n1 - save\t2 - save/quit\n3 - quit\t4 - credits\n5 - back";
}
void displayTextbox()
{
	cout << endl
	     << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\n"
	     << endl;
}
void displayStat(int current, int max, string type)
{
	if(type == "HP")
		cout << "\033[1;31m\u2665\033[0m: [" << current << "/" << max << "] ";
	else if(type == "MP")
		cout << "\033[1;36m\u2660\033[0m: [" << current << "/" << max << "] ";
	else if(type == "GP")
		cout << "\033[1;33m\u2666\033[0m: [" << current << "] ";
	else if(type == "XP")
	{
		if(current < max) //Not Max Level
			cout << "\033[1;32m\u2663\033[0m: [" << current << "/" << max << "] ";
		else //Max level
			cout << "\033[1;32m\u2663\033[0m: [MAX]";

	}
	else
	{
		//Generally used to display a stat + bonus
		if(max > 0) //Positive Bonus
			cout << current << " \033[1;32m(+" << max << ")\033[0m";
		else if(max == 0) //No Bonus
			cout << current;
		else if(max < 0) //Negative Bonus
			cout << current << " \033[1;31m(" << max << ")\033[0m";
	}

}
//For events
void choice(int number, string text)
{
	cout << number << " -{ " << text << "\n\n";
}
void displayCredits()
{
	cout << endl
	     << "Programming \n CameraCore \n\n Design \n CameraCore \n\n A game made in 2019" << endl;
	cin.ignore();
}
