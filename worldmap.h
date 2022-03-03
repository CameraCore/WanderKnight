//This file is used for things regarding the world map, such as moving a player around
#include "bitmap.h"
#include "event.h"

using namespace std;

//A cell can contains a tile and the player object. Its color and function is based on the world map's bitmap
class Cell
{
	private:
		bool blocked = false;	//Information on whether the cell has a player or some other entity that cannot be passed through
		bool hasPlayer = false; //Tiles dont have players in them until they are stepped into
		string icon;	//The icon the cell will display on the world map
		uint32_t color;	//The color of the cell's icon

	public:

		void createCell(uint32_t input)
		{
			color = input;
			//A R G B
			if(color == 0x0000FF00)
				icon = "^";	//Tent - Starting location, should be green
			else if(color == 0x00FF0000)
				icon = "!";		//! - Enemy Encounter, should be red
			else if(color == 0x000000FF)
				icon = "?";		//? - Event, should be blue
			else if(color == 0x0000FFFF)
				icon = "\u265C";	//Tower - Shop, should be cyan
			else if(color == 0x00FF00FF)
				icon = "X";		//X - Boss, should be magenta
			else if(color == 0x00FFFF00)
				icon = "$";		//$ - Treasure, should be yellow
			else if(color == 0x00000000)
			{
				icon = " ";		// - A hole or wall, should be black
				blocked = true;
			}
			else if(color == 0x00FFFFFF)
				icon = ".";		//. - Walkable space, should be white

		
		}
		void display()
		{
			//It doesn't matter too much which color a cell is as long as it doesn't share
			//the color with another type of cell
			if(hasPlayer == true) //If a cell has a player, display them instead
				cout << "\033[1;32m@\033[0m";
			else
			{

				if(color == 0x0000FF00)
					cout << "\033[1;32m" << icon <<"\033[0m";
				else if(color == 0x00FF0000)
					cout << "\033[1;31m" << icon <<"\033[0m";
				else if(color == 0x000000FF)
					cout << "\033[1;34m" << icon <<"\033[0m";
				else if(color == 0x0000FFFF)
					cout << "\033[1;36m" << icon <<"\033[0m";
				else if(color == 0x00FF00FF)
					cout << "\033[1;35m" << icon <<"\033[0m";
				else if(color == 0x00FFFF00)
					cout << "\033[1;33m" << icon <<"\033[0m";
				else if(color == 0x00000000)
					cout << "\033[1;37m" << icon <<"\033[0m";
				else if(color == 0x00FFFFFF)
					cout << "\033[1;37m" << icon <<"\033[0m";
				
			}
			
		}
		//Checks the type of cell it is
		string checkType() {return icon;}
		//Checks if the cell is blocked
		bool checkBlocked() {return blocked;}

		//Setter functions
		void occupy() {hasPlayer = true;}
		void leave() {hasPlayer = false;}

		//A function to be specialized depending on what kind of cell it is
		void action(vector<shared_ptr<PartyMember>> & party, vector<shared_ptr<Item>> & bag, int maxb, int maxp, int & gold) 
		{
			//Examine Spawn
			if(icon == "^")
			{
				cout << "A tent set up near a strange patch of grass." << endl;
				if(bag.size() < 1)
				{
					cout << "You stock up on potions." << endl;
					shared_ptr<Item> pot (new HealthPotion("yeah"));
					bag.push_back(pot);
					pot.reset();

				}
				cin.ignore();
			}
			//Enemy Encounter
			else if(icon == "!")
			{
				//Fight!
				cout << "You fought a battle. " << endl;
				party.at(0).get()->getHit(2, true);
				party.at(0).get()->levelUp(10);

				//Clear the cell
				icon = ".";
				color = 0x00FFFFFF;
				cin.ignore();
			}
			//Treasure Encounter
			else if(icon == "$")
			{
				//Get the item
				rollChest(bag, gold, maxb, getRandom(100));

				//Clear the cell
				icon = ".";
				color = 0x00FFFFFF;

				cin.ignore();
			}
			//Event Encounter
			else if(icon == "?")
			{
				//Roll the event
				rollEvent(party, bag, gold, maxb, getRandom(5));

				//Clear the cell
				icon = ".";
				color = 0x00FFFFFF;
				cin.ignore();
			}
			//Shop Encounter
			else if(icon == "\u265C")
			{
				cout << "This shop is closed." << endl;
				cin.ignore();
			}
			else if(icon == "X")
			{
				if(party.at(0).get()->getStat("Level") < 3 )
					cout << "<== I'm not ready to be here yet." << endl;
				else
				{
					cout << "<== Prepare yourself..." << endl;
					rollEvent(party, bag, gold, maxb, 666);
				}
				cin.ignore();
			}
			//Blank Space
			else
			{
				cout << "There's nothing here." << endl;
				cin.ignore();
			}

		};
		//Returns the color of the cell
		uint32_t getColor() {return color;}
		//Returns whether player is in this cell
		bool checkForPlayer() {return hasPlayer;}

};
//The world map consists of a vector of cells, which do different things depending on what color the bitmap read in is
class Worldmap
{
	private:
		ifstream in;
		Bitmap image;
		ofstream out;

		vector<Cell> map;	//A vector containing every cell in the map
		int spawn;		//The index for which the spawn is located at
		int position;		//The index for the player's current position

		int width;		//Width of the map
		int height;		//Height of the map

	public:
		//Searches for a place to put the player
		int findSpawn()
		{
			bool spawnExists = false;
			int location;
			//Search the map until the end or until a spawn is located
			for(int i = 0; i < map.size() && !spawnExists; ++i)
			{
				if(map.at(i).checkType() == "^")
				{
					spawnExists = true;
					location = i;
				}
			}

			if(spawnExists == false){
				throw (Exception(" Invalid Bitmap file: There are no spawn points"));} //Spawn point not found
			else
				return location; 
		}
		//Returns the spawn index
		int getSpawn() {return spawn;};
		//Creates the map, using a bitmap file found in the folder
		void create(string file)
		{
			try
			{
			
				in.open(file, ios::binary);
				in >> image;
				in.close();
				width = image.getWidth();
				height = image.getHeight();

				//Convert the bitmap into the appropriate colors
				cellShade(image);


				//Load in the world map when the game is running
				for(int i = 0; i < image.getSize(); ++i)
				{
					Cell temp;
					temp.createCell(image.getColor(i));
					map.push_back(temp);
				}
				
				//Set the spawn to have the player
				map.at(findSpawn()).occupy();
				spawn, position = findSpawn();

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
		//You can only save on a blank tile, this is to prevent overwriting the tile information
		bool canSave()
		{
			if(map.at(position).getColor() == 0x00FFFFFF)
				return true;
			else
				return false;
		}
		void save()
		{
			try
			{
				//First, get the vector of cell data, we only need the color
				vector<uint32_t> copyVector;
				for(int i = 0; i < map.size(); ++i)
				{
					//If any previous spawn points are found, remove them
					if(map.at(i).checkType() == "^")
						copyVector.push_back(0x00FFFFFF);
					//Find the next place to spawn
					else if(map.at(i).checkForPlayer() == true)
						copyVector.push_back(0x0000FF00);
					else
						copyVector.push_back(map.at(i).getColor());
				}
				out.open("realm.bmp", ios::binary);
				update(image,copyVector);	
				out << image;
				out.close();
			}
			catch(Exception& x)
			{
				cout << "Error: an uncaught exception occured:" << x.getMessage()  << endl;
			}
			catch(...)
			{
				cout << "Error: an uncaught exception occured." << endl;
			}

		}
		//Tells every cell to display its contents
		void display()
		{
			//Push up previous screen, then add a top cover
			pushUp();
			for(int i = 0; i < width*2+2; ++i)
			{
					if(i == 0) cout << "\033[1;37m\u2554";
					else if(i == width*2+1) cout << "\u2557\033[0m";
					else cout << "\u2550";
			}
			cout << endl;
			for(int i = map.size()-1; i >= 0; --i)
			{
				//To keep track of which pixel we're displaying.
				//Since the console outputs from the top left to bottom right, we need to mirror
				//our output horrizontally
				
				//Puts a border before the first character on the row
				if((i % width) == width-1)
					cout << "\033[1;37m\u2551\033[0m";	

				//Zero offset, - current x position + the row we're on
				int x = (width - 1) - (i % width) + (width * (i/width)); 
				map.at(x).display();
				cout << " ";

				//This part enters a new line once we've reached the width of the image
				if((i % width) == 0)
				{

					cout << "\033[1;37m\u2551\n\033[0m";
				}
				
			}
			//Bottom cover of the map
			for(int i = 0; i < width*2+2; ++i)
			{
					if(i == 0) cout << "\033[1;37m\u255A";
					else if(i == width*2+1) cout << "\u255D\033[0m";
					else cout << "\u2550";
			}
			cout << endl;
		
		};
		//Moves the player across the map, but checks if they can first
		void move(string input)
		{
			if(input == "w") //UP
			{
				
				if(position + width > map.size())
				{
					//If we walk off the top of the map, come out at the bottom
					if(!map.at(0 + position % width).checkBlocked())
					{
						map.at(position).leave();
						position = 0 + (position % width);
						map.at(position).occupy();
					}
				}
				else
				{
					//Otherwise we just move up
					if(!map.at(position + width).checkBlocked())
					{
						map.at(position).leave();
						position = position + width;
						map.at(position).occupy();
					}
				}
				
			}
			else if(input == "s") //DOWN
			{
				
				if(position - width < 0)
				{
					//If we walk off the bottom of the map, come out at the top
					if(!map.at(map.size() - (width - position)).checkBlocked())
					{
						map.at(position).leave();
						position = map.size() - (width - position);
						map.at(position).occupy();
					}
				}
				else
				{
					//Otherwise we just move down
					if(!map.at(position - width).checkBlocked())
					{
						map.at(position).leave();
						position = position - width;
						map.at(position).occupy();
					}
				}
				
			}
			else if(input == "a") //LEFT
			{
				
				if((position%width) - 1 < 0)
				{
					//If we walk off the left of the map, come out at the right
					if(!map.at(position + (width - 1)).checkBlocked())
					{
						map.at(position).leave();
						position = position + (width - 1);
						map.at(position).occupy();
					}
				}
				else
				{
					//Otherwise we just move down
					if(!map.at(position - 1).checkBlocked())
					{
						map.at(position).leave();
						--position;
						map.at(position).occupy();
					}
				}
				
			}

			else if(input == "d") //RIGHT
			{
				if((position + 1) % width == 0)
				{
					//If we walk off the right of the map, come out at the left
					if(!map.at(position - width + 1).checkBlocked())
					{
						map.at(position).leave();
						position = position - width + 1;
						map.at(position).occupy();
					}
				}
				else
				{
					//Otherwise we just move down
					if(!map.at(position + 1).checkBlocked())
					{
						map.at(position).leave();
						++position;
						map.at(position).occupy();
					}
				}
				
			}
		}
		//Tells the cell that a player is entering it
		void action(vector<shared_ptr<PartyMember>> & party, vector<shared_ptr<Item>> & bag, int maxb, int maxp, int & gold)
		{
			map.at(position).action(party, bag, maxb, maxp, gold);
		}
};
