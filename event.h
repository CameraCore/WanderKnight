//This file is for story event cells
#include "party.h"

using namespace std;
void rollEvent(vector<shared_ptr<PartyMember>> & party, vector<shared_ptr<Item>> & bag, int & gold, int maxb, int roll)
{

	//Odd Signpost
	if(roll == 1)
	{
		pushUp();
		displayTextbox();
		cout << " [You come across a silly looking signpost] " << endl << endl
		     << " <== 'The person reading this is silly.' " << endl;
		displayTextbox();
		cout << "==> ";
		cin.ignore();

	}

	//Healing Springs
	else if(roll == 2)
	{
		pushUp();
		displayTextbox();
		cout << " [A rather magical spring stretches ahead of you.] " << endl << endl
		     << " [Taking a dip, you recover your Health] " << endl;
		displayTextbox();
		cout << "==> ";
		party.at(0).get()->getHit(-10, false);
		cin.ignore();

	}

	//Ancient Trap
	else if(roll == 3)
	{
		set<string> Question = {"1", "2"};
		Response input;

			do
			{
				pushUp();
				displayTextbox();
				cout << " [You activated an ancient trap!] " << endl << endl
				     << " [You can either shed a bit of blood, or lose a bit of your mind] " << endl;
				displayTextbox();
				choice(1,"[No pain, no gain.]");
				choice(2,"[Just a small headache.]");
				cout << "==> ";
				cin >> input;
				
				if(input.get() == "1")
				{
					pushUp();
					displayTextbox();
					cout << "[You casually brush past the spikes and blades, taking some damage.]" << endl;
					displayTextbox();

					party.at(0).get()->getHit(5,false);

				}
				if(input.get() == "2")
				{
					pushUp();
					displayTextbox();
					cout << "[You walk through the magical barrier, your body unharmed but your mind sustaining a migraine.]" << endl << endl;
					displayTextbox();

					party.at(0).get()->getSap(5);
				}


			
			}while(Question.find(input.get()) == Question.end());

	}

	//Fallen Hero
	else if(roll == 4)
	{
		set<string> Question = {"1", "2"};
		Response input;

			do
			{
				pushUp();
				displayTextbox();
				cout << " [You encounter the battered body of a fallen warrior] " << endl << endl
				     << " [Looks like they were recently defeated, their loot still intact] " << endl;
				displayTextbox();
				choice(1,"[Loot the body]");
				choice(2,"[Leave them be]");
				cout << "==> ";
				cin >> input;
				
				if(input.get() == "1")
				{
					pushUp();
					displayTextbox();
					cout << "<== Better take it before someone else does. " << endl;
					displayTextbox();
					roll = getRandom(100);
					if(roll >= 31)
					{	
						rollChest(bag, gold, maxb, getRandom(100));
					}
					else if(roll <= 30)	
					{
						pushUp();
						displayTextbox();
						cout << " 'H-hey what do you think you're doing?! I'm still alive!' " << endl << endl
						     << " [You quickly get away after getting struck by a heavy blow] " << endl;
						displayTextbox();

						party.at(0).get()->getHit(5,false);
					}


				}
				if(input.get() == "2")
				{
					pushUp();
					displayTextbox();
					cout << "<== They'll live. " << endl << endl;
					displayTextbox();
				}


			
			}while(Question.find(input.get()) == Question.end());

	}
		
	//Name Curse
	else if(roll == 5)
	{
		set<string> Question = {"1", "2"};
		Response input;

		if(party.at(0).get()->getName() != "???")
		{

			do
			{
				pushUp();
				displayTextbox();
				cout << " 'Hahaha! I am the great warlock Faloosjf'-Jfook! Bow down to me!' " << endl << endl
				     << " [This man is annoying, your fist is shaking with violent intent] " << endl;
				displayTextbox();

				choice(1,"[Punch him in the face]");
				choice(2,"[Punch yourself in the face]");
				cout << "==> ";
				cin >> input;
				
				if(input.get() == "1")
				{
					pushUp();
					displayTextbox();
					cout << " [You absolutely demlosh his nose] " << endl << endl
					     << " 'HW DRE YOU! I'LL MK SUR NOBDY REMMBRS YOUR NAME!' " << endl;
					displayTextbox();

					party.at(0).get()->setCombat("Name","???");
				}
				if(input.get() == "2")
				{
					pushUp();
					displayTextbox();
					cout << " [You punch yourself in the face] " << endl << endl
					     << " '...Well then. I uh... guess I'll be on my way...' " << endl;
					displayTextbox();

					party.at(0).get()->getHit(1,false);
				}


			
			}while(Question.find(input.get()) == Question.end());


		}
		else
		{
			cout << " 'Hmmm? You seem to lack a name, is it my doing?' " << endl;
		}

	}
		

	//FINAL BOSS
	else if(roll == 666)
	{
		set<string> Question = {"1", "2", "3"};
		Response input;
		bool prologue = false;

		if(party.at(0).get()->getName() == "He Ro")
		{
			do //PHASE 1.1
			{
				if(prologue == false)
				{
					pushUp();
					displayTextbox();
					cout << " [You meet a familiar figure, shrouded in shadows.] " << endl
					     << " 'So, you have finally arrived. Tell me " << party.at(0).get()->getName() << ", how many allies have you left to die?' " << endl;
						cin.ignore();

					cout << "<== I made it here on my own. " << endl;
						cin.ignore();
						
					cout << " 'Do not take me for a fool! Just because those battles were untold, does not mean I was oblivious to them.' " << endl;
						cin.ignore();

					cout << "<== What do you mean... " << endl;
						cin.ignore();

					cout << " [The figure step aside, their shadows dissipating to reveal-]" << endl
					     << "<== ! " << endl;
						cin.ignore();

					cout << " [A\033[1;34m Swordswoman,\033[0m" << 
						", a\033[1;31m Dragoon\033[0m" << 
						", and a\033[1;32m Hooded Archer\033[0m" << 
						", stand together, their gaze upon you burning with hatred] " << endl;

						cin.ignore();
					cout << " 'You threw them away when you sensed they were close to death. Just like you did to me!' " << endl << endl
					     << " 'However, I appeared before them to offer my hand, in turn the only thing I asked for was REVENGE' " << endl << endl
					     << " 'And now all of us will have a chance of beating you to near death!' " << endl;
						cin.ignore();
					prologue = true;
				}
				pushUp();
				displayTextbox();
				cout << " [The are closing in, what will you do?] " << endl << endl;
				displayTextbox();

				choice(1,"[Take down the\033[1;34m Swordswoman.\033[0m]");
				choice(2,"[Aim for the\033[1;31m Dragoon.\033[0m]");
				choice(3,"[Focus on the\033[1;32m Archer.\033[0m]");
				cout << "==> ";
				cin >> input;

				if(input.get() == "1")
				{
					cout << " [You try to overpower them, but she's considerably stronger than the last time you saw her.] " << endl
					     << " [The others press the attack, overwhelming you] " << endl << endl;
						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}
				else if(input.get() == "2")
				{
					cout << " [Despite having reach, she was no match for your speed.] " << endl
					     << " [You cut her down.] " << endl << endl;
						
					cin.ignore();
				}
				else if(input.get() == "3")
				{
					cout << " [You try your best to weave between his arrows, but his shots are relentless] " << endl
					     << " [You were mowed down before you could get to them] " << endl << endl;
						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}

			}while(Question.find(input.get()) == Question.end());

			do //PHASE 1.2
			{
				pushUp();
				displayTextbox();
				cout << " [You pick up the spear, putting away your sword. Who's next?] " << endl << endl;
				displayTextbox();

				choice(1,"[Take down the\033[1;34m Swordswoman.\033[0m]");
				choice(2,"[Focus on the\033[1;32m Archer.\033[0m]");
				choice(3,"[Confront the\033[1;35m Demon.\033[0m]");
				cout << "==> ";
				cin >> input;

				if(input.get() == "1")
				{
					cout << " [You should have known she would have no trouble getting past you.] " << endl
					     << " [She cuts YOU down.] " << endl << endl;
						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}
				else if(input.get() == "2")
				{
					cout << " [You are bombarded by a hail of arrows, but spin the spear fast enough to form a barrier against them.] " << endl
					     << " [Reaching them, you pin their body to the wall with a toss of your weapon.] " << endl << endl;
						
					cin.ignore();
				}
				else if(input.get() == "3")
				{
					cout << " [Jumping into the air, you use your ultimate technique.] " << endl
					     << " [Your foe merely turns into smoke as your attack connects. Their remaining allies make short work of you.] " << endl << endl;
						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}

			}while(Question.find(input.get()) == Question.end());

			do //PHASE 1.3
			{
				pushUp();
				displayTextbox();
				cout << " [Prying the bow from the man's dead hands, you spin around to aim at your next opponent] " << endl << endl;
				displayTextbox();

				choice(1,"[Take down the\033[1;34m Swordswoman.\033[0m]");
				choice(2,"[Confront the\033[1;35m Demon.\033[0m]");
				choice(3,"[Stand down, there has been enough bloodshed]");
				cout << "==> ";
				cin >> input;

				if(input.get() == "1")
				{
					cout << " [Arrow after arrow was sent their way, they look like nothing more than a pincushion.] " << endl
					     << " [Something is wrong though...] " << endl << endl;
					cin.ignore();

					cout << " [The corpses of the slain began to reanimate!] " << endl
					     << " 'Foolish mortal... Unlike you, I do not throw my friends away even if they are dead!' " << endl << endl;
					cin.ignore();

					cout << " [They got you surrounded again.] " << endl
					     << " [You feel your fatigue catching up to you...]" << endl << endl;
					cin.ignore();

						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}
				else if(input.get() == "2")
				{
					cout << " [You continuously shoot at the shadow, each time it seems that they are incapable of reforming] " << endl
					     << " [One arrow meets its mark, putting the demon to it's end.] " << endl
					     << " [The Swordswoman mysteriously falls down, lifeless.] " << endl << endl;
					cin.ignore();
				}
				else if(input.get() == "3")
				{
					cout << " [You drop your weapons, enouugh is enough.] " << endl
					     << " 'Thank you for making this easy on us. Now die.'  " << endl << endl;
						
					cout << "\033[1;31m[ You have died ]\033[0m" << endl; 

					cin.ignore();
					exit(0);
				}

			}while(Question.find(input.get()) == Question.end());

			cout << "<== Sorry, Vi Llain, but I must keep doing this until you have learned... " << endl;
						cin.ignore();

			cout << "[ \033[1;34mYou have won.\033[0m ]" << endl;
			cin.ignore();
			displayTitle();
			displayCredits();
			exit(0);


		}
		else
		{
			cout << "[ \033[1;34mYou have won.\033[0m ]" << endl;
			exit(0);
		}

	}


}
