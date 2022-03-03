//This file is used for the party members
#include "item.h"
using namespace std;

class PartyMember
{
	protected:
		string _Name;	//The party member's name
		string _Class;  //The party member's profession
		
		//STATS
		int _Level;	//The party member's level
		int _EXP;	//Experience gain towards a level up
		int _Level2;	//EXP needed to reach level 2
		int _Level3;	//EXP needed to reach level 3

		int _MaxHP;	//Maxmium Health Points
		int _MaxMP;	//Maximum Mana Points
		int _CurHP;	//Current HP
		int _CurMP;	//Current MP

		int _ATK;	//Attack stat determines how much damage they can do in battle
		int _DEF;	//Defense stat determines how much damage they can prevent in battle
		int _SPD;	//Speed stat determines their priority in battle, and how much they can move
		int _MOV;	//Points of movement during battle

		int _tATK;	//Attack bonus from buffs
		int _tDEF;	//Defense bonus from buffs
		int _tSPD;	//Speed bonus from buffs
		int _tMOV;	//Movement bonus from buffed speed

		//EQUIPMENT
		shared_ptr<Equipment> _weapon;	//What weapon the party member is holding
		shared_ptr<Equipment> _armor;	//What armor they are wearing

		//SKILLS
		string _skill1;		//Name of skill 1
		string _skill1D;	//Description of skill 1
		string _skill2;		//Name of skill 2
		string _skill2D;	//Description of skill 2
		string _skill3;		//Name of skill 3
		string _skill3D;	//Description of skill 3


		bool _unlock2;		//Checks if the party member has access to skill 2
		bool _unlock3;		//Checks if the party member has access to skill 3

	public:
		//COMBAT AND DAMAGE
		//Resets a party member's stats to their original values
		//Also recalculates their level
		virtual void refresh() {}

		//Unlocks skills and increase stats upon level up, numbers may differ between characters
		//Takes in exp gain and checks if we can level up.
		virtual void levelUp(int amount) {}

		//SKILLS
		//Abilities used in battle
		virtual void use_1() {}
		virtual void use_2() {}
		virtual void use_3() {}

		virtual bool checkDead(){}		
		virtual void getHit(int amount, bool pierce) {}
		virtual void getSap(int amount) {}

		//Shows the stats depending on how much info is needed
		virtual void getStats(string format){}

		//Getters
		virtual string getName() {}
		virtual string getClass() {}
		virtual int getStat(string type) {}
		virtual string getCombat(string type) {}

		//Setters
		virtual void setStat(string type, int value) {}
		virtual void setCombat(string type, string value) {}
		virtual void setEquip(string toSwap, Equipment onHand) { onHand.equip(toSwap); }


		//USE TABLE - Given an item, DO THIS
		virtual void take(string Item) {}

};

//The game ends if the main character dies
class Player : public PartyMember
{
	private:
		
	public:
		//Name taken when the Player is created
		Player(string name)
		{
			_Name = name;
			_Class = "Champ";
			_Level = 1;
			_EXP = 0;

			_Level2 = 10;
			_Level3 = 20;

			_MaxHP = 10;
			_MaxMP = 10;
			_CurHP = 10;
			_CurMP = 10;

			_ATK = 1;
			_DEF = 0;
			_SPD = 6;
			_MOV = _SPD/2;

			_tATK = 0;
			_tDEF = 0;
			_tSPD = 0;
			_tMOV = 0;

			//Equip starting weapons
			shared_ptr<Equipment> startingWeapon (new Equipment("Shortsword"));
			shared_ptr<Equipment> startingArmor (new Equipment("Armornone"));

			_weapon = startingWeapon;
			_armor = startingArmor;

			//Release these pointers after
			startingWeapon.reset();
			startingArmor.reset();

		 	_skill1	= "Battle Cry";
			_skill1D = "\033[1;31m+1 ATK\033[0m to nearby allies and self for 3 turns - \033[1;36m\u2660 3\033[0m";	
			_skill2  = "Recover";
			_skill2D = "\033[1;32mHeal 5 HP\033[0m to you or a target - \033[1;36m\u2660 5\033[0m";
			_skill3 = "Wander Lust";
			_skill3D = "Dash through a target, dealing \033[1;34mspeed\033[0m as damage. \033[1;34m+1 SPD\033[0m per use - \033[1;36m\u2660 7\033[0m";

			_unlock2 = false;
			_unlock3 = false;

		}

		//Unlocks skills and increase stats upon level up, numbers may differ between characters
		void levelUp(int expGain) 
		{
			_EXP += expGain;
			if(_EXP >= _Level2 && _Level < 2)
			{
				cout << "[" << _Name << " has leveled up!]" << endl
				     << "[Learned \033[1;33m" << _skill2 << "\033[0m!]" << endl;

				cin.ignore();
				++_Level; _EXP = 0; //Reset EXP
				_MaxHP = _MaxHP + 5;
				_CurHP = _MaxHP; //Fully Heal
				_MaxMP = _MaxMP + 2;
				_CurMP = _MaxMP; //Fully Fill

				_unlock2 = true;

			}
			if(_EXP >= _Level3 && _Level < 3)
			{
				cout << "[" << _Name << " has leveled up!]" << endl
				     << "[Learned \033[1;33m" << _skill3 << "\033[0m!]" << endl;
				
				cin.ignore();

				++_Level;	//EXP continues to accumulate in case I want to add more levels
				_MaxHP = _MaxHP + 5;
				_CurHP = _MaxHP; //Fully Heal
				_MaxMP = _MaxMP + 3;
				_CurMP = _MaxMP; //Fully Fill

				_unlock3 = true;
			}
		}

		//SKILLS
		//Abilities used in battle
		void use_1() {};
		void use_2() {};
		void use_3() {};

		//Get current health to check if dead
		bool checkDead() override
		{
			if(_CurHP <= 0)
				return true;
			else
				return false;
		}
		//When a member takes damage. Damage is reduced by natural, temporary, and equipment DEF
		//True damage ignores DEF
		void getHit(int amount, bool pierce) override
		{
			if(pierce == true)
				_CurHP -= amount;
			else
				_CurHP -= (amount - _DEF - _tDEF - _weapon.get()->getStat("DEF") - _armor.get()->getStat("DEF"));
		}
		//Lose Mana
		void getSap(int amount) override
		{
			_CurMP -= amount;
		}
		void refresh()
		{
			_tATK, _tDEF, _tSPD, _tMOV = 0;
			_MOV = (_SPD + _tSPD) / 2;
		}

		//Displaying details on the party screen
		void getStats(string format) override
		{
			if(format == "quick")
			{
				displayStat(_CurHP,_MaxHP, "HP"); cout << ' ';
				displayStat(_CurMP,_MaxMP, "MP"); cout << "\n\t";
				if(_Level == 1)
				{
					displayStat(_EXP,_Level2, "XP"); cout << ' ';
				}
				else if(_Level == 2)
				{
					displayStat(_EXP,_Level3, "XP"); cout << ' ';
				}
				else if(_Level == 3)
				{
					displayStat(_EXP, _EXP*2, "XP"); cout << ' ';
				}
			}
			else if(format == "long")
			{
				cout << "Name: " << _Name << "\tClass: " << _Class << '\n';
				cout << "Level: " << _Level << "\tEXP ";
				if(_Level == 1)
				{	displayStat(_EXP,_Level2, "XP"); cout << '\n';}
				else if(_Level == 2)
				{	displayStat(_EXP,_Level3, "XP"); cout << '\n';}
				else if(_Level == 3)
				{	cout << "MAX\n";}

				//General
				cout << "HP "; displayStat(_CurHP,_MaxHP, "HP"); cout << '\t';
				cout << "MP "; displayStat(_CurMP,_MaxMP, "MP"); cout << '\n';

				//Combat
				cout << "ATK: "; displayStat(_ATK,_weapon.get()->getStat("ATK")+_armor.get()->getStat("ATK"), "??"); cout << '\t';
				cout << "DEF: "; displayStat(_DEF,_weapon.get()->getStat("DEF")+_armor.get()->getStat("DEF"), "??"); cout << '\n';
				cout << "SPD: "; displayStat(_SPD,_weapon.get()->getStat("SPD")+_armor.get()->getStat("SPD"), "??"); cout << '\t';
				cout << "MOV: "; displayStat(_MOV,_weapon.get()->getStat("MOV")+_armor.get()->getStat("MOV"), "??"); cout << "\n\n";

				//Weapon and Skills
				cout << "Weapon: " << _weapon.get()->getName() << "\n\t" << _weapon.get()->getDesc() << '\n'
				     << "Armor: " << _armor.get()->getName() << "\n\t" << _armor.get()->getDesc() << "\n\n";

				cout << "Skill 1: " << _skill1 << "\n\t" << _skill1D << '\n';
				if(_unlock2 == true)
					cout << "Skill 2: " << _skill2 << "\n\t" << _skill2D << '\n';
				if(_unlock3 == true)
					cout << "Skill 3: " << _skill3 << "\n\t" << _skill3D <<'\n';
			}
			

		}

		//USE LIST - This character will do this when given an item
		virtual void take(string Item)
		{
			//Heals 5 HP
			if(Item == "Health Potion")
			{
				if(_CurHP == _MaxHP) //Full Health
					return;
				else if(_CurHP + 5 > _MaxHP) //No Overheal
					_CurHP = _MaxHP;
				else
					_CurHP += 5;
			}
			//Heals 5 MP
			if(Item == "Mana Potion")
			{
				if(_CurMP == _MaxMP) //Full Mana
					return;
				else if(_CurMP + 5 > _MaxMP) //No Overfill
					_CurMP = _MaxMP;
				else
					_CurMP += 5;
			}
		}
		//Getters
		string getName() {return _Name;}
		string getClass() {return _Class;}
		int getStat(string type)
		{
			if(type == "Level")
					return _Level;
			if(type == "EXP")
					return _EXP;
			if(type == "Level2")
					return _Level2;
			if(type == "Level3")
					return _Level3;

			if(type == "MaxHP")
					return _MaxHP;
			if(type == "MaxMP")
					return _MaxMP;
			if(type == "CurHP")
					return _CurHP;
			if(type == "CurMP")
					return _CurMP;

			if(type == "ATK")
					return _ATK;
			if(type == "DEF")
					return _DEF;
			if(type == "SPD")
					return _SPD;
			if(type == "MOV")
					return _MOV;
			if(type == "tATK")
					return _tATK;
			if(type == "tDEF")
					return _tDEF;
			if(type == "tSPD")
					return _tSPD;
			if(type == "tMOV")
					return _tMOV;
		}
		string getCombat(string type)
		{
			if(type == "weapon")
				return _weapon.get()->getID();
			if(type == "armor")
				return _armor.get()->getID();

			if(type == "skill1")
				return _skill1;
			if(type == "skill1D")
				return _skill1D;
			if(type == "skill2")
				return _skill2;
			if(type == "skill2D")
				return _skill2D;
			if(type == "skill3")
				return _skill2;
			if(type == "skill3D")
				return _skill2D;
			if(type == "lock2")
			{
				if(_unlock2 == false)
					return "f";
				else
					return "t";
			}
			if(type == "lock3")
			{
				if(_unlock3 == false)
					return "f";
				else
					return "t";
			}
		}
		//Setters
		void setStat ( string type, int value)
		{
			if(type == "Level")
				_Level = value;
			if(type == "EXP")
				_EXP = value;
			if(type == "Level2")
				_Level2 = value;
			if(type == "Level3")
				_Level3 = value;

			if(type == "MaxHP")
				_MaxHP = value;
			if(type == "MaxMP")
				_MaxMP = value;
			if(type == "CurHP")
				_CurHP = value;
			if(type == "CurMP")
				_CurMP = value;

			if(type == "ATK")
				_ATK = value;
			if(type == "DEF")
				_DEF = value;
			if(type == "SPD")
				_SPD = value;
			if(type == "MOV")
				_MOV = value;

			if(type == "tATK")
				_tATK = value;
			if(type == "tDEF")
				_tDEF = value;
			if(type == "tSPD")
				_tSPD = value;
			if(type == "tMOV")
				_tMOV = value;

		}
		void setCombat( string type, string value) 
		{
			if(type == "Name")
				_Name = value;
			if(type == "Class")

				_Class = value;
			if(type == "weapon")
				_weapon.get()->equip(value);
			if(type == "armor")
				_weapon.get()->equip(value);

			if(type == "skill1")
				_skill1 = value;
			if(type == "skill1D")
				_skill1D = value;
			if(type == "skill2")
				_skill2 = value;
			if(type == "skill2D")
				_skill2D = value;
			if(type == "skill3")
				_skill2 = value;
			if(type == "skill3D")
				_skill2D = value;
			if(type == "lock2")
			{
				if(value == "f")
					_unlock2 = false;
				else
					_unlock2 = true;
			}
			if(type == "lock3")
			{
				if(value == "f")
					_unlock3 = false;
				else
					_unlock3 = true;
			}

		}

};
