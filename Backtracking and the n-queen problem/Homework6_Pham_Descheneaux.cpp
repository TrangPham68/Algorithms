// Homework 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Board.h"

using namespace std;

/*
print board in form of array
@param int*board pointer to the board array
@param int n the size of the array
@return void
*/
void simplePrint(int* board, int n)
{

	for (int i = 0; i < n; i++)
	{
		cout << board[i] << " ";
	}
	cout << endl;
}

/*
check to see if the board is full (filled with non-zero)
@param int*board pointer to the board array
@param int n the size of the array
@return true if the board is full and false otherwise
*/
bool isFull(int* board, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (board[i] == 0)
		{
			return false;
		}
	}
	return true;
}

/*
check to see if the board is empty (filled with 0)
@param int*board pointer to the board array
@param int n the size of the array
@return true if the board is empty and false otherwise
*/
bool isEmpty(int* board, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (board[i] != 0)
		{
			return false;
		}
	}
	return true;
}

/*
check to see if the board is legal aka if no queen can attack each other
@param int*queen pointer to the board array
@param int dimensions the size/dimension of the array
@return true the board does not violate the queen rule and false otherwise
*/
bool isLegalPosition(int* queens, int dimensions) {
	Board filledBoard(dimensions, queens);
	return filledBoard.isLegal();
}

/*
find the next legal position/board of the board 
@param int*queen pointer to the board array
@param int dimensions the size/dimension of the array
@return int* the next legal board
*/
int* nextLegalPosition(int* queens, int dimensions) {
	Board filledBoard(dimensions, queens);
	filledBoard.moveQueen();
	if (filledBoard.isLegal() == true) {
		return filledBoard.getQueens();
	}
	else
		return nextLegalPosition(filledBoard.getQueens(), dimensions);
}

//print board in 2d array form 
void printBoard(int* board, int n)
{
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (j != board[i - 1])
			{
				cout << " - ";
			}
			else
			{
				cout << " 1 ";
			}
		}
		cout << endl;
	}
	cout << "\n";
}


/*
find the first solution of a given n x n board
@param int n the dimensions of the board
@param int*a the pointer to the board
@return int* return the pointer to a after getting the solution
*/
int* findFirstSolution(int n, int* a)
{
	a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		a[i] = 0;
	}

	while (isFull(a, n) == false)
	{
		a = nextLegalPosition(a, n);
	}
	
	return a;
}

/*
count all solutions for n queens problem
@param int n the dimensions of the board as in n x n board
@param int* a the initial array pointer
@return int number of solutions for a given dimensions
*/
int findAllSolutions(int n, int* a)
{
	a = (int*)malloc(n * sizeof(int));
	bool done = false;
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		a[i] = 0;
	}

	while (isEmpty(a, n) == false || done == false)
	{
		a = nextLegalPosition(a, n);
		done = true;
		while (isFull(a, n) == false && isEmpty(a,n) == false)
		{

			a = nextLegalPosition(a, n);
		}
		if (isEmpty(a, n) == false)
		{
			//simplePrint(a, n);  //can print out all too if we want to
			count++;	
		}
		
	}
	delete[] a; //attemp to deallocate memory
	return count;
}


int main()
{
	int board1[] = { 1,6,8,3,7,4,2,5 };
	int board2[] = { 1,6,8,3,7,0,0,0 };
	int board3[] = { 1,6,8,3,5,0,0,0 };

	int case1[] = { 1,6,8,3,5,0,0,0 };
	int case2[] = { 1,6,8,3,7,0,0,0 };
	int case3[] = { 1,6,8,3,7,4,2,5 };
	int n = 8;

	cout << isLegalPosition(board1, n) << endl;
	cout << isLegalPosition(board2, n) << endl;
	cout << isLegalPosition(board3, n) << endl;

	cout << "to check for legal position, from the queen position, we can track up and down vertically and diangonally"<<endl;
	cout << "and if we detect any queen on the way (compare the position of otehr queen with the tracked position), then it is not legal" << endl;
	cout << endl;
	cout << "The next legal position will add queen to the next rank if the current board is legal"<<endl;
	cout << "if the board is not legal, the next legal board can be the current board with different last queen of the board"<<endl;
	cout << endl;
	cout << "if the board is full and is legal, we will backtrack till we find the next legal position"<<endl;
	cout << endl;
	cout << "A solution is when there is n queens on a nxn dimensions board where no queens attack each other"<<endl;
	cout << endl;
	cout << "We all want to increase efficiency because the code get really slow after a certain n which proves the exponential growth of the n-queens problem"<<endl;
	cout << "test nextLegalPosition for case1" << endl;

	printBoard(case1, n);
	printBoard(nextLegalPosition(case1, n), n);
	cout << "test nextLegalPosition for case2" << endl;
	printBoard(case2, n);
	printBoard(nextLegalPosition(case2, n), n);
	cout << "test nextLegalPosition for case3" << endl;
	printBoard(case3, n);
	printBoard(nextLegalPosition(case3, n), n);

	
	int* pointer = NULL;
	//find first solution of n queens problem, expect to be able to displat from n=4 to n=30
	//however currently can only print the till n=19 before the program crashs with bad memory allocation???????
	for (int i = 4; i <= 15; i++)
	{
		cout << "First Solution for n=" << i << endl;
		simplePrint(findFirstSolution(i, pointer), i);
		cout << endl;
		free (pointer);
	}
	

	//Count and find all solution for n queens problem, expect to be able to count to n =15
	//however currently can only print till n=11 before crashing becasue of the same reason
	for (int i = 4; i <= 12; i++)
	{
		cout << "The are "<< findAllSolutions(i, pointer) <<" solutions for " << i<< " queens problem"<<endl;
		delete[] pointer;  //attemp to free memory
	}
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
