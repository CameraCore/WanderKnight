//This header file contains menu functions
#include "names.h"
#include "worldmap.h"
using namespace std;

//This class holds many of the game's "global variables"
//This can be used to keep track of things such as steps and achievements
class Controller
{
	private:
		//NOTE: using shared pointers because it is expected we use the party and bag very often
		string playerName;			//The player's name
		vector<shared_ptr<PartyMember>> party;	//Contains the list of party members
		vector<shared_ptr<Item>> bag;		//Contains the list of items on hand
		shared_ptr<Worldmap> world;			//Points to the world
		int _Gold = 0;				//Money used to buy things
		int MAX_ITEM = 4;			//Maximum amount of items the bag can hold
		int MAX_PARTY = 1;		//Maximum amount of party members
		

	public:
		string getName() { return playerName; }
		//Sets the player's name
		void setName(string input) { playerName = input; }

		void setWorld( shared_ptr<Worldmap> toPoint)
		{
			world = toPoint;
		}
		//Check if the main character is still alive
		bool checkDead()
		{
			if(party.at(0).get()->checkDead() == true)
				return true;
		}
		//Display the main character's quick info
		void getInfo()
		{
			cout << party.at(0).get()->getName() << " || ";
			party.at(0).get()->getStats("quick");
			displayStat(_Gold,0,"GP");
		}
		
		//Sends the party to be changed
		vector<shared_ptr<PartyMember>> & send() {return party;}
		//Sends the inventory to be changed
		vector<shared_ptr<Item>> & deliver() {return bag;}
		//Gets the stats of the controller
		int getStat(string type)
		{
			if(type == "MAX_ITEM")
				return MAX_ITEM;
			if(type == "MAX_PARTY")
				return MAX_PARTY;
		}
		int & getGold()
		{
			return _Gold;
		}


		//Shows the current inventory
		void showBag()
		{
			if(bag.size() == 0)
				cout << "The bag is empty..." << endl;
			for(int i = 0; i < bag.size(); ++i)
			{
				//Get the address, then get the item's name
				cout << i+1 << " - " << bag.at(i).get()->get() << endl;
			}
			cout << "q - back" << endl;
		}
		//Uses an item from the bag
		void useBag(int toUse)
		{
			//FIRST, PICK AN ITEM
			Response playerInput;
			bool isUsed = false;	//To check if an item was successfully used.
			string toGive;		//Item to give

			//Only works if bag isn't empty and the input exists
			if(bag.empty() == false && (toUse > 0 && toUse <= bag.size()) )
			{
				toGive = bag.at(toUse-1).get()->use();
			}
			else
				return; //Return if the item doesn't exist
			
			//NEXT, GIVE THE ITEM TO A PARTY MEMBER
			do
			{
				world.get()->display();
				getInfo();
				displayTextbox();

				cout << "Who do you use it on?" << endl;
				showParty();
				cout << endl << "==> ";
				cin >> playerInput;
				if(playerInput.get() != "q" && checkInput(playerInput.get()) != false)
				{
					if(stoi(playerInput.get()) <= party.size())
					{
						cin.ignore();
						party.at(stoi(playerInput.get())-1).get()->take(toGive);
						isUsed = true;
					}
					
				}

			}while(playerInput.get() != "q" && isUsed == false);
			playerInput.refresh();


			//FINALLY, REMOVE THE ITEM FROM THE BAG IF IT WAS USED
			if(isUsed == true)
				bag.erase(bag.begin() + (toUse-1));

		}
		//Release shared pointers and clear the bag
		void dumpBag()
		{
			for(int i = 0; i < bag.size(); ++i)
			{
				bag.at(i).reset();
				bag.erase(bag.begin() + i);
			}
		}
		//Adds a member to the party
		void addParty(shared_ptr<PartyMember> toAdd, string name)
		{
			if(party.size() + 1 > MAX_PARTY)
				cout << "I have enough people to manage." << endl;
			else
			{
				cout << "[" << name << " has joined the party!]" << endl;
				party.push_back(toAdd);
			}

		}

		//Shows the current Party
		void showParty()
		{
			for(int i = 0; i < party.size(); ++ i)
			{
				//Get the address, then get the person's name
				cout << i+1 << " - " << party.at(i).get()->getName() << endl;
			}
			cout << "q - back" << endl;
		}
		//Checks the stats of a party member
		void checkParty(int toCheck)
		{
			//Only works if party isn't empty and the input exists
			if(party.empty() == false && (toCheck > 0 && toCheck <= party.size()) )
			{
				party.at(toCheck-1).get()->getStats("long");
			}
			else
				return;
		}
		//Release shared pointers and clear the bag
		void clearParty()
		{
			for(int i = 0; i < party.size(); ++i)
			{
				party.at(i).reset();
				party.erase(party.begin() + i);
			}
		}

		//Reads from a text file to fill in controller data
		void load()
		{
			try{
				string value; //Value read in
				string size; //Determining bag or party size
				ifstream in;

				in.open ("text.txt");
				if(in.is_open()){
					
					//Read in the party size, then create more members as necessary
					getline(in, size, '#');
					if(stoi(size) > 1)
					{
						for(int i = 0; i < stoi(size); ++i)
						{
							shared_ptr<Player> sideChar (new Player("sideChar"));
							addParty(sideChar,"sideChar");
							sideChar.reset();
						}
					}
					//Now read in party memberinfo
					for(int i = 0; i < party.size(); ++i)
					{
						getline(in, value, '#'); party.at(i).get()->setCombat("Name", value);
						setName(value);
						getline(in, value, '#'); party.at(i).get()->setCombat("Class", value);
						
						getline(in, value, '#'); party.at(i).get()->setStat("Level", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("EXO", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("Level2", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("Level3", stoi(value));
						
						getline(in, value, '#'); party.at(i).get()->setStat("MaxHP", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("MaxMP", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("CurHP", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("CurMP", stoi(value));
						
						getline(in, value, '#'); party.at(i).get()->setStat("ATK", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("DEF", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("SPD", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("MOV", stoi(value));
						
						getline(in, value, '#'); party.at(i).get()->setStat("tATK", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("tDEF", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("tSPD", stoi(value));
						getline(in, value, '#'); party.at(i).get()->setStat("tMOV", stoi(value));

						getline(in, value, '#'); party.at(i).get()->setCombat("weapon", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("armor", value);

						getline(in, value, '#'); party.at(i).get()->setCombat("skill1", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("skill1D", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("skill2", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("skill2D", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("skill3", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("skill3D", value);

						getline(in, value, '#'); party.at(i).get()->setCombat("lock2", value);
						getline(in, value, '#'); party.at(i).get()->setCombat("lock3", value);
					}
					getline(in, value, '#'); //End of party
					getline(in, value, '#'); _Gold = stoi(value);
					//Read in the inventory
					getline(in, size, '#'); 
					for(int i = 0; i < stoi(size); ++i)
					{
						getline(in, value, '#');
						addItem(bag,value);
					}

					in.close();
				}
				else
					cerr << "[ Unable to open file ]" << endl;
				
			}
			catch(Exception& x)
			{
				cout << "Error: an uncaught exception occured:" << x.getMessage()  << endl;
				exit(0);
			}
			catch(...)
			{
				cout << "Error: an uncaught exception occured." << endl;
				exit(0);
			}

		}
		//Puts all of the controller data into a txt
		void save()
		{
			try{
				ofstream out;

				out.open ("text.txt");
				if(out.is_open()){
					//Output the size to know how many party members to add when we load
					//Use '#' as a delimiter and "\r\n" for line breaks
					out << party.size() << '#' << "\r\n";
					//Save party contents
					for(int i = 0; i < party.size(); ++i)
					{
						out 
						    << party.at(i).get()->getName() << '#' << "\r\n" 
						    << party.at(i).get()->getClass() << '#' << "\r\n"
						    << party.at(i).get()->getStat("Level") << '#' << "\r\n"
						    << party.at(i).get()->getStat("EXP") << '#' << "\r\n"
						    << party.at(i).get()->getStat("Level2") << '#' << "\r\n"
						    << party.at(i).get()->getStat("Level3") << '#' << "\r\n"

						    << party.at(i).get()->getStat("MaxHP") << '#' << "\r\n"
						    << party.at(i).get()->getStat("MaxMP") << '#' << "\r\n"
						    << party.at(i).get()->getStat("CurHP") << '#' << "\r\n"
						    << party.at(i).get()->getStat("CurMP") << '#' << "\r\n"

						    << party.at(i).get()->getStat("ATK") << '#' << "\r\n"
						    << party.at(i).get()->getStat("DEF") << '#' << "\r\n"
						    << party.at(i).get()->getStat("MOV") << '#' << "\r\n"
						    << party.at(i).get()->getStat("SPD") << '#' << "\r\n"

						    << party.at(i).get()->getStat("tATK") << '#' << "\r\n"
						    << party.at(i).get()->getStat("tDEF") << '#' << "\r\n"
						    << party.at(i).get()->getStat("tMOV") << '#' << "\r\n"
						    << party.at(i).get()->getStat("tSPD") << '#' << "\r\n"

						    << party.at(i).get()->getCombat("weapon") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("armor") << '#' << "\r\n"

						    << party.at(i).get()->getCombat("skill1") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("skill1D") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("skill2") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("skill2D") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("skill3") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("skill3D") << '#' << "\r\n"

						    << party.at(i).get()->getCombat("lock2") << '#' << "\r\n"
						    << party.at(i).get()->getCombat("lock3") << '#' << "\r\n";
					}
					out << "-----END OF PARTY-----" << '#' << "\r\n";
					//Save gold
					out << _Gold << '#' << "\r\n";

					//Save bag contents
					out << bag.size() << '#' << "\r\n";
					for(int i = 0; i < bag.size(); ++i)
					{
						out << bag.at(i).get()->get() << '#' << "\r\n";
					}
					out << "-----END OF BAG-----" << '#' << "\r\n";
					out.close();
				}
				else
					cerr << "[ Unable to open file ]" << endl;
			}
			catch(Exception& x)
			{
				cout << "Error: an uncaught exception occured:" << x.getMessage()  << endl;
				exit(0);
			}
			catch(...)
			{
				cout << "Error: an uncaught exception occured." << endl;
				exit(0);
			}

		}


};

//This class opens up the naming menu
class Namemenu
{
	public:
		
		//Continuously asks for a name until valid
		string input()
		{
			Response playerInput;
			do{
				displayTitle();
				displayNamingScreen();
				displayTextbox();
				cout << "==> ";
				cin >> playerInput;
			
			}while(checkName(playerInput.get()) == false);
			return playerInput.get();
		}

};

//This menu comes up while on the world map
//It will display the world, quickstats/options, and a dialogue box
class Worldmenu
{
	private:
		bool GameOver = false;

	public:
		//The while loop that keeps the game running as long as the player doesn't quit or die
		//Takes the control object and the map to load
		void run(shared_ptr<Controller> remote, string mapLoad, string dataLoad)
	       	{
			//Set up the controls
			shared_ptr<Controller> control (remote);
			shared_ptr<Worldmap> world (new Worldmap);
			control.get()->setWorld (world);
			world.get()->create(mapLoad);

			//Load the main character
			shared_ptr<Player> mainChar (new Player(control.get()->getName()));
			control.get()->addParty(mainChar, control.get()->getName());


			//If this isn't a new game
			if(dataLoad != "default")
			{
				control.get()->load();
			}

			Response playerInput;
			do{

				//MAP
				world.get()->display();
				//HUD
				control.get()->getInfo();

				displayOptions();
				displayTextbox();
				//Check if the player has moved to do travel text
				if(playerInput.get() == "w" ||playerInput.get() == "a" || playerInput.get() == "s" || playerInput.get() == "d")
					travelText();

				cout << endl << "==> ";
				cin >> playerInput;
				//Player decides to move
				if(playerInput.get() == "w" ||playerInput.get() == "a" || playerInput.get() == "s" || playerInput.get() == "d")
				{
					world.get()->move(playerInput.get());
				}
				//Player enters the cell
				else if(playerInput.get() == "e")
					//Send the party and inventory in case it needs to be changed
					world.get()->action(control.get()->send(), control.get()->deliver(),control.get()->getStat("MAX_ITEM"),control.get()->getStat("MAX_PARTY"),control.get()->getGold());

				//Player goes to options
				else if(playerInput.get() == "o")
				{
					set<string> Option = {"1", "2", "3", "4"};
					do
					{
						world.get()->display();
						control.get()->getInfo();
						displayOptionsInner();
						displayTextbox();
						cout << endl << "==> ";
						cin >> playerInput;
						if(playerInput.get() == "1") //Save Game
						{
							if(world.get()->canSave() == true)
							{
								cout << "[The game was saved. ]" << endl;
								control.get()->save();
								world.get()->save();
								cin.ignore();
							}
							else
							{
								cout << "[You cannot save here. ]" << endl;
								cin.ignore();
							}
						}
						else if(playerInput.get() == "2") //Save and Quit
						{

							if(world.get()->canSave() == true)
							{
								cout << "[The game was saved. ]" << endl;
								control.get()->save();
								world.get()->save();
								cin.ignore();

								cout << "[Closing the game... ]" << endl;
								control.get()->dumpBag();
								control.get()->clearParty();
								mainChar.reset();
								exit(0);
							}
							else
							{	
								cout << "[You cannot save here. ]" << endl;
								cin.ignore();
							}
						}
						else if(playerInput.get() == "3") //Quit
						{
							if(confirm("[Quit without saving? (y/n) ]") == true)
							{
								cout << "[Closing the game... ]" << endl;
								control.get()->dumpBag();
								control.get()->clearParty();
								mainChar.reset();
								exit(0);
							}
						}
						else if(playerInput.get() == "4")
							displayCredits();
							
					//Repeat if invalid response, or chose to go back
					}while(Option.find(playerInput.get()) == Option.end() && playerInput.get() != "5");

				}
				//Player goes to inventory
				else if(playerInput.get() == "i")
				{
					do
					{
						world.get()->display();
						control.get()->getInfo();
						displayTextbox();
						control.get()->showBag();

						cout << endl << "==> ";
						cin >> playerInput;
						if(playerInput.get() != "q" && checkInput(playerInput.get()) != false )
							control.get()->useBag(stoi(playerInput.get()));

					}while(playerInput.get() != "q");
					playerInput.refresh();
				}
				//Player goes to the party screen
				else if(playerInput.get() == "p")
				{
					do
					{
						world.get()->display();
						control.get()->getInfo();
						displayTextbox();
						control.get()->showParty();

						cout << endl << "==> ";
						cin >> playerInput;
						if(playerInput.get() != "q" && checkInput(playerInput.get()) != false )
						{
							control.get()->checkParty(stoi(playerInput.get()));	
							cout << "[Enter to continue]" << endl;
							cin.ignore();
						}

					}while(playerInput.get() != "q");
					playerInput.refresh();
				}
				
				if(control.get()->checkDead() == true)
					GameOver = true;
			}while(playerInput.get() != "q" && GameOver != true);
			if(GameOver == true)
				cout << "\033[1;31m[ You have died ]\033[0m" << endl; 
			//Deallocate
			mainChar.reset();
			control.get()->dumpBag();
			control.get()->clearParty();

		};


};

//This menu comes up whenever the program starts
class Startmenu
{
	private:

	public:
		//This function brings up the start menu
		void startGame()
		{
			set<string> Question = {"1", "2", "3"};

			shared_ptr<Controller> control (new Controller);
			Response playerInput;
			Namemenu namingMenu;
			Worldmenu worldingMenu;
			
			//Keep asking until we get a valid response
			do
			{
				playerInput.refresh();
				displayTitle();
				displayTitleOptions();
				displayTextbox();
				cout << "==> ";
				cin >> playerInput;
				if(playerInput.get() == "1")
				{
					control.get()->setName(namingMenu.input());
					displayTitle();
					displayTextbox();
					//The game is now running, hand over the controls to the game
					//so that the game can update globals
					worldingMenu.run(control, "world.bmp", "default");
				}
				else if(playerInput.get() == "2")
				{
					string data;
					string map;

						cout << "[Specify the map to load. ]" << endl;
						cin >> playerInput;
						map = playerInput.get();
						playerInput.refresh();

						cout << "[Specify the text file to load. ]" << endl;
						cin >> playerInput;
						data = playerInput.get();
						playerInput.refresh();

						worldingMenu.run(control, map, data);

				}
				else if(playerInput.get() == "3")
				{
					cout << "[Closing the game... ]" << endl;
				}

			}while(Question.find(playerInput.get()) == Question.end());

		}
};

