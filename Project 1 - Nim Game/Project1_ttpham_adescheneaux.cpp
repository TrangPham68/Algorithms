// Project1_ttpham_adescheneaux.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Algorithms
//Trang Pham and Andrew Descheneaux
//11/1/2019
//Homework 1

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdbool.h>

//#include "Board.h"
using namespace std;
int Computer;
int Player;

class Board {
private:
	int g = 3;  //number of green
	int y = 7;  //number of yellow
	int o = 5;  //number of orange
public:

	/*Take in a string of color name and return the number of the current number of that color
	@param string color
	@return int number of that color
	*/
	int getNum(string color)
	{
		if (color == "g") return g;
		else if (color == "y") return y;
		else return o;
	}

	/*A setter to set the number of color to the input number
	this function help update the color number after each move
	@param string color the color
	@param int move how many that got pick to be removed
	@return void
	*/
	void setColor(string color, int move)
	{
		if (color == "g")
		{
			g = g - move;
			if (g < 0) g = 0;
		}

		else if (color == "y") {
			y = y - move;
			if (y < 0) y = 0;
		}
		else
		{
			o = o - move;
			if (o < 0) o = 0;
		}
	}

	/*determine when the game is over
	when there is only one color left -->the next player is the winner
	@return bool if the game is over or not*/
	bool gameOver()
	{
		return g == 0 && y == 0 || g == 0 && o == 0 || y == 0 && o == 0;
	}

	/*Determine when the game is in the stage where there is nothing left
	@return bool true if nothing is left and false otherwise*/
	bool allZero()
	{
		return g == 0 && y == 0 && o == 0;
	}
};
/*A move is a struct that contain the color and the number of the markers of that color to remove in that move*/
struct move {
	string color;
	int num;
};

//display the current state of the game
void display(Board* nim)
{
	printf("current state of game: ");
	printf("green: %d yellow %d, orange: %d\n", nim->getNum("g"), nim->getNum("y"), nim->getNum("o"));
}


//find winner
void Winner(int turn)
{
	if (turn == Computer)
	{
		printf("Computer Won\n");
	}
	else
		printf("Human Won\n");
}


/*make a random move for the computer  when the level is easy
@param Board* nim pointer of the board
@param struct move* move pointer of the move struct
@return void
*/
void makeMove(Board* nim, struct move* moves) //A move is made
{
	//random move for now
	string validColor[3];  //a list of available color
	int i = 0;


	if (nim->getNum("g") > 0)
	{
		validColor[i] = "g";
		i++;
	}
	if (nim->getNum("y") > 0)
	{
		validColor[i] = "y";
		i++;
	}
	if (nim->getNum("0") > 0)
	{
		validColor[i] = "o";
		i++;
	}

	int color = (rand() % i); //pick a random color
	(*moves).color = validColor[color];
	(*moves).num = 1 + (rand() % nim->getNum(validColor[color])); //pick a random of number within the range of the available number
	nim->setColor(validColor[color], (*moves).num); //update the board
}

/*find the winning move for computer when the level is hard
@param board b the current board
@param bool& lost the reference of the boolean lost
@param bool& won the reference of the boolean won
@param strict move* moves the pointer to the move struct
@return return the board after the computer find and make a smart move
*/
Board findComputerMove(Board b, bool& lost, bool& won, struct move* moves) //The computer makes a move
{
	bool completeLoss = true; //True by default
	string cMove[3]; //Used to designate different colors to assign each move
	cMove[0] = "g";
	cMove[1] = "y";
	cMove[2] = "o";

	for (int c = 0; c < 3; c++) //Go through each color
	{
		for (int i = 1; i <= b.getNum(cMove[c]); i++) //Go through each possible move for each color
		{
			Board b2 = b; //Makes a new board , equal to the current one
			b2.setColor(cMove[c], i); //Makes a move using the new one
			if (b2.allZero() == true) //If the move leads to a win, return the board with that move made
			{
				won = true;
				lost = false;
				return b2;
			}
			if (b2.gameOver() == false) //If the move doesn't lead to a win, call the function again
			{
				bool opponentLost = false; //Changed in function depending on whether there was a win/loss
				bool opponentWon = true;
				findComputerMove(b2, opponentLost, opponentWon, moves); //Runs through the function again (and again and again) until a winning move is found, using the 'new' board with the move made
				if (opponentLost == true) //If the next move leads to a win, return the board
				{

					lost = false;
					won = true;
					return b2;
				}
				if (opponentWon == false) //If the opponent doesn't win, set completeLoss to false so it can continue
				{
					completeLoss = false;
				}
			}
		}
	}
	if (completeLoss == true) //If no possible move leads to a win, make a random move
	{
		lost = true;
		won = false;
		makeMove(&b, moves);
		return b;
	}
	else //If something unaccounted for happens, make a randomn move
	{
		lost = false;
		won = false;
		makeMove(&b, moves);
		return b;
	}
}
/*
check if the move is valid
@param board* nim pointer to the current board
@param string color the color of the move
@param int num the number of marker that picked to be removed
@return bool if the number of color is less of equal to the available number --> if the move is valid
*/
bool isValid(Board* nim, string color, int num)
{
	if (num > 0 && num <= nim->getNum(color))
		return true;
	return false;
}

/*
play the game
@param int turn the turn of either human or computer
@param level either hard or easy
@return void
*/
void game(int turn, int level)
{
	printf("Nim Starts!!!!!!");
	struct move moves;
	Board nim;

	while (nim.gameOver() == false) //if the game is not over yet, keep playing
	{
		display(&nim);

		if (turn == Computer) //computer move
		{
			if (level == 1) //hard level
			{
				bool won = false;
				bool loss = true;
				nim = findComputerMove(nim, won, loss, &moves);
			}
			else  //easy level
			{
				makeMove(&nim, &moves);
			}

			printf("\n");
			printf("Computer made a move\n");
			turn = Player;
		}
		else //human move
		{
			printf("\n");
			printf("Human made a move\n");
			printf("pick a color g for green, y for yellow and o for orange\n");
			int num;
			string color;
			cin >> color;
			if (!(color == "g" || color == "y" || color == "o"))
				printf("invalid input\n");
			else
			{
				printf("How many? (has to be less than or equal to the current stage)\n");
				cin >> num;
				if (isValid)
				{
					moves.color = color;
					moves.num = num;
					nim.setColor(color, num);
					turn = Computer;
				}
				else
					printf("invalid move\n");
			}

		}
	}

	display(&nim);
	Winner(turn);  //declare winner
}

//main function
int main()
{
	printf("What level of the game do you want to play? (e for easy and h for hard)");
	string level;
	int leveli;   //input level
	cin >> level;
	if (level == "h")
		leveli = 1;
	else
		leveli = 0;

	printf("Welcome to Nim! Do you want to make the first move? (y/n)\n");
	string turn;
	cin >> turn;   //input turn either play first or let computer play first
	if (turn == "y")
	{
		Player = 1;
		Computer = 0;
	}
	else
	{
		Computer = 1;
		Player = 0;
	}
	game(1, leveli);  //play game
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

