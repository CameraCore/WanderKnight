//This file is used for the equipment and items
#include "flavortext.h"

using namespace std;
//Items to be used from the inventory
class Item{
	private:
		string name;	//The item's name
	public:
		//The use of an item is determined by what it is
		virtual string use() {};
		virtual string get(){return name;}
};

//When used, heals the person who used it
class HealthPotion : public Item
{
	private:
		string name = "Health Potion";
	public:
		HealthPotion() {}
		HealthPotion(string message) {cout << "[ Acquired\033[1;31m Health Potion \033[0m ]" << endl;}	//Used when not just loading in
		string use()
		{
			cout << "You uncork the potion." << endl;
	       		cin.ignore();
			return name;
		};
		string get() {return name;}
};
class ManaPotion : public Item
{
	private:
		string name = "Mana Potion";
	public:
		ManaPotion() {}
		ManaPotion(string message) {cout << "[ Acquired\033[1;36m Mana Potion \033[0m ]" << endl;}	//Used when not just loading in
		string use()
		{
			cout << "You uncork the potion." << endl;
	       		cin.ignore();
			return name;
		};
		string get() {return name;}
};


//You can equip something to boost your stat and change how you attack in battle
class Equipment : public Item
{
	private:
		string _ID = "Genericequip";	//To reference when saving and loading
		string _Name = "Generic Equip";	//Name of equip
		string _Desc = "Description";	//Description of equip
		//STAT BONUSES
		int _HP = 0;	//Health Points
		int _MP = 0;	//Mana Points

		int _ATK = 0;	//Attack stat determines how much damage they can do in battle
		int _DEF = 0;	//Defense stat determines how much damage they can prevent in battle
		int _SPD = 0;	//Speed stat determines their priority in battle, and how much they can move
		int _MOV = 0;	//Points of movement during battle

	public:

		Equipment() {}
		Equipment(string type) {equip(type);}
		//Wielding an equip causes you to attack with it
		int attack() {};

		//Sets the properties of the Equipment depending on what it is
		void equip( string toEquip )
		{
			//Weapons
			//SWORDS
			if(toEquip == "Shortsword")
			{
				_ID = toEquip;
				_Name = "Short Sword";
				_Desc = "A basic, steel blade. \033[1;31m+1 ATK\033[0m";
				_ATK = 1;
			}
			if(toEquip == "Rapier")
			{

				_ID = toEquip;
				_Name = "Rapier";
				_Desc = "Lighter, but weaker";
				_ATK = 0;
				_SPD = 1;
			}
			
		
			//ARMOR
			if(toEquip == "Armornone")
			{
				_ID = toEquip;
				_Name = "None";
				_Desc = "No armor worn.";
			}
			if(toEquip == "Armorleather")
			{
				_ID = toEquip;
				_Name = "Leather Armor";
				_Desc = "Moderate protection, makes you quicker";
				_DEF = 2;
				_SPD = 1;

			}

		};
		string getName() {return _Name;}
		string getDesc() {return _Desc;}
		string getID()	 {return _ID;}

		//Gets one of the Equipment's stats
		int getStat(string type)
		{
			if(type == "HP")
				return _HP;
			if(type == "MP")
				return _MP;
			if(type == "ATK")
				return _ATK;
			if(type == "DEF")
				return _DEF;
			if(type == "SPD")
				return _SPD;
			if(type == "MOV")
				return _MOV;
		}
};
//Adds an item to a bag, depending on the argument supplied
void addItem( vector<shared_ptr<Item>> & bag, string toAdd )
{
	if(toAdd == "\r\nHealth Potion")
	{
		shared_ptr<Item> item (new HealthPotion);
		bag.push_back(item);
		item.reset();
	}
	else if(toAdd == "\r\nMana Potion")
	{
		shared_ptr<Item> item (new ManaPotion);
		bag.push_back(item);
		item.reset();
	}


}
//Drops loot based on what was rolled
void rollChest(vector<shared_ptr<Item>> & bag, int & gold, int maxb, int roll)
{
	//Chests always have gold, unless if I need to change it here
	if(roll > 0)
	{
		cout << "Found \033[1;33m 100 Gold.\033[0m" << endl;
		gold += 100;
	}
	//Check if bag is full if an item is going to be added
	if(bag.size() < maxb)
	{
		if(roll > 50 && roll <= 75)
		{
			cout << "Found a Health Potion." << endl;
			addItem(bag,"\r\nHealth Potion");

		}
		else
		{	
			cout << "Found a Mana Potion." << endl;
			addItem(bag,"\r\nMana Potion");
		}
	}
	else
	{
		cout << "[Your bag is full! You toss the item away.] " << endl;
			cin.ignore();
	}	
}
