/*
 * MainGame.cpp
 *
 *  Created on: Sep 9, 2021
 *      Authors: John Neilson & Abhishek Kumar
 */
#include "Board.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;


int main() {
	srand(time(NULL));
	Board board('m',"fido", true);
	return 0;
}



