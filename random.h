//This file is used for randomly generating loot
#include "graphics.h"
#include <cstring>
#include <stdlib.h> //For rand and srand
#include <time.h> //For generating a seed
#include <memory>
#include <set>

using namespace std;

//Generates a pseudo random number up to a max
int getRandom(int max)
{
	//Make the seed
	srand(time(NULL));	

	return rand() % max + 1;
}
//This class asks for the user's response
//other classes may call this and then modify the contents of the response such as shortening it
class Response
{
	private:
		//For holding user responses
		string text;

		friend istream& operator>>(istream& in, Response& r)
		{
			string input;
			getline(in,input);
			r.text = input;
			return in;
		};
		friend ostream& operator<<(ostream& out, const Response& r)
		{
			cout << r.text;
			return out;
		};


	public:
		//Clears everything in the string for reuse
		void refresh(){	text.clear();};
		string get()	{return text;}
		void set(string toSet)	{text = toSet;}
		int length()	{return text.length();}
				
};
//Function for confirmation box
bool confirm(string text)
{
	Response playerInput;
	set<string> Question = {"y", "n"};

	do
	{
		cout << text << endl;
		cin >> playerInput;
		if(playerInput.get() == "y") return true;
		else if(playerInput.get() == "n") return false;

	}while(Question.find(playerInput.get()) == Question.end());

}

