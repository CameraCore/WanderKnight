#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << endl << "usage:\n"
             << "wanderknight option\n"
             << "options:\n"
             << "  -r run\n" << endl;

        return 0;
    }
	cout << endl;
        string flag(argv[1]);
	Startmenu start;

	if(flag == "-r"s)
	{
		start.startGame();
	}
	
	cout << endl;


    return 0;
}

