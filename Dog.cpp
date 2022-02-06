/*
 * Dog.cpp
 *
 *  Created on: Sep 9, 2021
 *      Authors: John Neilson & Abhishek Kumar
 */

#include "Dog.hpp"
#include <iostream>
using namespace std;

//constructor	
Dog::Dog(string n){
	name = n;
	Dog();
}

//default constructor
Dog::Dog(){  
	strength = 50;
	x = 0;
	y = 0;
}

bool Dog::changeStrength(int amt){  //changes dog’s strength field
	strength += amt;
	cout<<" Strength: "<<strength<<endl;
	if(strength <= 0){
		die();
		return false;
	}else if(amt == 10000){
		won();
		return false;
	}
	return true;
}
void Dog::die(){  //die message when strength at or below 0
	cout << name + " has ran out of strength and died." <<endl;
}
void Dog::printDog(){  // prints out info about dog
	cout << name + " " << strength + " " <<  x + " " << y + " ";
}
void Dog::won(){ //won message for when dog is at end of evil forest
	cout << "Congratulations you have won and escaped the forest." << endl;
}
void Dog::reset(){  //resets dog for restarting a new game
	strength = 50;
	x = 0;
	y = 0;
}


