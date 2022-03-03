//This file is used for random messages during travel
#include "random.h"
using namespace std;

void travelText()
{
	//
	int dialogue = getRandom(100);

	//Weather
	if(dialogue == 81)
	{
		cout << "The wind is howling..." << endl;
	}
	if(dialogue == 82)
	{
		cout << "Clear skies today." << endl;
	}
	if(dialogue == 83)
	{
		cout << "The sun is shining intensely." << endl;
	}
	if(dialogue == 84)
	{
		cout << "There is a slight drizzle." << endl;
	}
	if(dialogue == 85)
	{
		cout << "A crackle of thunder in the distance..." << endl;
	}
	if(dialogue == 86)
	{
		cout << "The rain is pouring." << endl;
	}
	if(dialogue == 87)
	{
		cout << "Dense fog, but still manageable." << endl;
	}
	if(dialogue == 88)
	{
		cout << "What a terrible night." << endl;
	}
	if(dialogue == 89)
	{
		cout << "The birds are singing." << endl;
	}
	if(dialogue == 90)
	{
		cout << "Feeling some slight tremors." << endl;
	}

	//Other
	if(dialogue == 91)
	{
		cout << "Thinking about food." << endl;
	}
	if(dialogue == 92)
	{
		cout << "A field of swords." << endl;
	}
	if(dialogue == 93)
	{
		cout << "A scream echoes in the distance." << endl;
	}
	if(dialogue == 94)
	{
		cout << "Some bones belonging to a massive beast." << endl;
	}
	if(dialogue == 95)
	{
		cout << "A murder of crows flies past." << endl;
	}
	if(dialogue == 96)
	{
		cout << "Taking a break." << endl;
	}
	if(dialogue == 97)
	{
		cout << "Daydreaming..." << endl;
	}
	if(dialogue == 98)
	{
		cout << "A sprawlling meadow." << endl;
	}
	if(dialogue == 99)
	{
		cout << "A lakeside view." << endl;
	}
	if(dialogue == 100)
	{
		cout << "..." << endl;
	}




	//80% Chance of nothing happening
	if(dialogue <= 80)
	{
		cout << "" << endl;
	}


}
