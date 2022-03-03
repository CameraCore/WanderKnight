//This file is used for the naming menu
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//Gets a name string and checks what to do with that name
//Will return true for valid names and false for invalid ones.
bool checkName(string input)
{

	if(input.length() < 1)
	{
		cout << "<== Nothing was entered." << endl;
		cin.ignore();
		return false;
	}
	if(input.length() > 8)
	{
		cout << "<== That's too long." << endl;
		cin.ignore();
		return false;
	}
	if(input == "Vi Llain")
	{
		
		cout << "<== No." << endl;
		cin.ignore();
		exit(0);

	}

	//Quips on unique names
	if(input.length() == 1 || input == "Wander" || input == "Knight")
	{
		cout << "<== Not very creative huh?" << endl;
		cin.ignore();
	}
	if((input.find("1") != string::npos) || (input.find("2") != string::npos) || (input.find("3") != string::npos) || (input.find("4") != string::npos) || (input.find("5") != string::npos) ||
	   (input.find("6") != string::npos) || (input.find("7") != string::npos) || (input.find("8") != string::npos) || (input.find("9") != string::npos) || (input.find("0") != string::npos))	
	{
		cout << "<== Very strange to have a number in that name." << endl;
		cin.ignore();
		
	}
	if(input == "Link")
	{
		cout << "<== This is not my legend." << endl;
		cin.ignore();
	}
	if(input == "Cloud")
	{
		cout << "<== Big Sword Mode." << endl;
		cin.ignore();
	}
	if(input == "Exile")
	{
		cout << "<== I pave my own path." << endl;
		cin.ignore();
	}
	if(input == "Yasuo")
	{
		cout << "<== A wanderer isn't always lost." << endl;
		cin.ignore();
	}
	if(input == "Arthur")
	{
		cout << "<== This sword is only ordinary." << endl;
		cin.ignore();
	}
	if(input == "Preston")
	{
		cout << "<== Looking for my rival." << endl;
		cin.ignore();
	}
	if(input == "Sword")
	{
		cout << "<== I am a weapon." << endl;
		cin.ignore();
	}
	if(input == "Frisk")
	{
		cout << "<== There is no mercy here." << endl;
		cin.ignore();
	}
	if(input == "He Ro")
	{
		cout << "<== I remember now..." << endl;
		cin.ignore();
	}


	return true;
}
//Checks if a character is NOT digit
bool nondigit(char c)
{
	return !isdigit(c);
}
bool checkInput(string input)
{
	if(input.length() < 1 || input.length() > 1)
	{
		return false;
	}
	if(find_if(input.begin(), input.end(), nondigit) == input.end())
		return true;
}
