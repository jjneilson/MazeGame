/*
 * Board.cpp
 *
 *  Created on: Sep 9, 2021
 *      Authors: John Neilson & Abhishek Kumar
 */
#include "Board.hpp"
#include <iostream>
using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;
	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size-1;

		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}
void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}


}

void Board::addFood() {
	if(level == 'e'){
		for(int i = 0; i < size; i++){
			board[(rand()%18)+1][(rand()%18)+1] = 'F';
		}
	}
	else if(level == 'm'){
		for(int i = 0; i < size-2; i++){
			board[(rand()%18)+1][(rand()%18)+1] = 'F';
		}
	}
	else{
		for(int i = 0; i < size-4; i++){
			board[(rand()%18)+1][(rand()%18)+1] = 'F';
		}
	}
}
void Board::addTraps() {
	int trapnum = 0;
	if(level == 'e'){
		trapnum = size-6;
	}
	else if(level == 'm'){
		trapnum = size-8;
	}
	else{
		trapnum = size-10;
	}
	for(int i = 0; i < trapnum; i++){
		board[(rand()%18)+1][(rand()%18)+1] = 'T';
	}
}

// fills entire board with space characters
void Board::boardConfig() {
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++)
			board[i][j] = ' ';
	} // board is filled with dummy characters
	int walls[10];
	for(int i=0;i<10;i++){
		walls[i] = rand()%size; //creating random indexes for the walls
	}
	int tempindex;
	for(int i=0;i<10;i++){
		tempindex=walls[i];
		if(i%2==1){ // filling in walls based on if i is odd or even
			for(int j=0;j<size;j+=rand()%5){
				board[j][tempindex] = '|';
			}
		}
		if(i%2==0){
			for(int j=0;j<size;j+=rand()%5){
					board[tempindex][j] = '-';
			}
		}
	}
	board[mydog.x][mydog.y] = 'D';
}

//prints the board starting from [0][0] to [20][20]
void Board::printBoard() {
	//top
	for(int i = 0; i < size-5; i++){
		cout<<" - ";
	}
	cout<<endl;
	//board itself
	for(int i=1;i<size-1;i++){
		if(i == startx){
			cout << "->";
		}
		else{
			cout<<"| ";
		}
		for(int j=0;j<size;j++){
			if(debug){
				cout << board[i][j] << " ";
			}
			else{
				if(board[i][j]=='T'){
					cout << "  ";
				}
				else{
					cout << board[i][j] << " ";
				}
			}
		}
		if(i == endx){
			cout << " ->";
		}
		else{
			cout<<" |";
		}
		cout<<endl;
	}
	//bottom
	for(int i = 0; i < size-5; i++){
		cout<<" - ";
	}
	cout<<endl;
}

//moves dog up, down, left, or right depending on input and further prompts depending on if coordinate contains a wall
bool Board::moveDog(char c) {
	board[mydog.x][mydog.y] = ' ';
	mydog.changeStrength(-2);
	char ans;
	if(c == 'r'){
		mydog.y++;
	}
	if(c == 'l'){
		mydog.y--;
	}
	if(c == 'u'){
		mydog.x--;
	}
	if(c == 'd'){
		mydog.x++;
	}

	if(board[mydog.x][mydog.y] == 'T'){
		mydog.changeStrength((-1)*((rand()%15)+2));
	}
	if(board[mydog.x][mydog.y] == 'F'){
		mydog.changeStrength(((rand()%15)+2));
	}

	if(mydog.y < 0){
		mydog.y++;
	}
	else if(mydog.y > size-1){
		mydog.y--;
	}
	else if(mydog.x > size-1){
		mydog.x--;
	}
	else if(mydog.x == 0){
		mydog.x++;
	}
	else if(board[mydog.x][mydog.y] == '|' || board[mydog.x][mydog.y] == '-'){
		cout << "Do you want to knock down that wall, it costs 6 strength?(y/n)"<<endl;
		cin >> ans;
		if(ans == 'y'){
			mydog.changeStrength(-6);
		}
		if(ans == 'n'){
			if(c == 'r'){
				mydog.y--;
			}
			if(c == 'l'){
				mydog.y++;
			}
			if(c == 'u'){
				mydog.x++;
			}

			if(c == 'd'){
				mydog.x--;
			}
		}
	}
	board[mydog.x][mydog.y] = 'D';
	if(mydog.x == endx && mydog.y == endy){
		mydog.won();
		return false;
	}
	if(!mydog.changeStrength(0)){
		return false;
	}
	return c;
}




