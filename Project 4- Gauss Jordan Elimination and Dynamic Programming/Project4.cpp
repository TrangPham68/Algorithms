// Project4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Trang Pham and Andrew Descheneaux

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include "Precious.h"
#include <string>

using namespace std;

/*
print 2d vector 
part of debugging process to keep track of the matric
@param vector<vector<double>> a the 2d vector
@return void
*/
void print(vector<vector<double>> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << "\n";
		for (int j = 0; j < a.at(i).size(); j++)
		{
			cout << (a.at(i)).at(j) << " ";
		}

	}
	cout << "\n";
}

/*
print the solution given the ginal vector after using the Guass-Jordan Elimination
@param vector < vector<double>> b the 2d array with the not simplefy yet solution
@param vector<double> sol vector storing the real solution
@return return the solution vector
*/
vector<double> printSolution(vector < vector<double>> b, vector<double> sol)
{
	cout << "the solution is: \n";
	for (int i = 0; i < b.size(); i++)
	{
		sol.push_back((b.at(i)).at(b.size())/ (b.at(i)).at(i));  //add solution (value / pivot)
		cout << sol.at(i) << " ";
	}
	return sol;
}

/*
Apply Guass-Jordan Elimination to find the solution of a given system of equations
for this specific question (assume unique solutions)
@param vector<vector<double>> arr the 2d vector Ax with nxn real entries matrix
@param vector<double> ans b column matrix with n real entries
@param int n number of row
@return vector<double> the vector of the solution
*/

vector<double> findSolution(vector<vector<double>> arr, vector<double> ans, int n)
{
	vector <double> solution;
	for (int i = 0; i < n ; i++)
	{
		arr.at(i).push_back(ans.at(i));  //augmented the matrix
	}
	print(arr);

	//find bottom triangle
	for (int i = 0; i < n - 1; i++) //top down
	{
		int pivot = i;
		for (int j = i + 1; j < n ; j++)
		{
			if ((arr.at(j)).at(i) > (arr.at(pivot)).at(i))  //find the valuable matrix
				pivot = j;
		}
		for (int k = i; k < n+1; k++)
		{
			swap((arr.at(i)).at(k), (arr.at(pivot)).at(k));  //swap pivot row to the right position
		}
		for (int j = i + 1; j < n; j++)
		{
			//make bottom triangle of 0
			double tempbot = (arr.at(j)).at(i) / (arr.at(i)).at(i);
			for (int k = i; k < n + 1; k++)
			{
				(arr.at(j)).at(k) = (arr.at(j)).at(k) - (arr.at(i)).at(k) * tempbot;
				if (abs((arr.at(j)).at(k)) < 0.00000000001)  //if number is too small --> round to 0
				{
					(arr.at(j)).at(k) = 0;
				}
			}
		}
	}

	//find top triangle of 0
	for (int i = n-1; i >= 0; i--)  //go bottom up using the same logic but go backward
	{
		int pivot = i;
		for (int j = i-1; j >= 0; j--)
		{
			double temptop = (arr.at(j)).at(i) / (arr.at(i)).at(i);
			for (int k = i; k < n + 1; k++)
			{
				(arr.at(j)).at(k) = (arr.at(j)).at(k) - (arr.at(i)).at(k) * temptop;
				if (abs((arr.at(j)).at(k)) < 0.00000000001)
				{
					(arr.at(j)).at(k) = 0;
				}
				

			}
		}
		
	}

	cout << "\n" << "the RREF ver of the matrix is:";
	print(arr);
	cout << "\n";
	return printSolution(arr, solution);

}

Matrix initial[8][8], modified[8][8]; //Global variables initialized for the initial and modified matrices

void findPrecious() { //Finds the 'most precious path'
	for (int i = 6; i >= 0; i--) { //Starts at the 7th 'row' and finds the 'precious' path from that one to the 8th, then from the 6th to the 7th, etc.
		for (int j = 0; j < 8; j++) { //Goes through the columns regularly to find the most optimal way to get the 'precious' path
			int preciousValue = 0; //Used for storing the 'new' precious value
			Direction preciousD; //Used for storing the 'new' direction each time
			if (modified[i + 1][j].jewels > preciousValue) { //For going straight
				preciousValue = modified[i + 1][j].jewels;
				preciousD = Straight;
			}
			if (j != 7) { //For going right, also accounting for the farthest left value
				if (modified[i + 1][j + 1].jewels > preciousValue) {
					preciousValue = modified[i + 1][j + 1].jewels;
					preciousD = Right;
				}
			}
			if (j != 0) { //For going left, also accounting for the farthest left value
				if (modified[i + 1][j - 1].jewels > preciousValue) {
					preciousValue = modified[i + 1][j - 1].jewels;
					preciousD = Left;
				}
			}
			modified[i][j].jewels = preciousValue + initial[i][j].jewels; //Changes the modified value based on the initial and current 'precious' value
			modified[i][j].d = preciousD; //Adds a direction value for the 'precious' value
		}
	}
}

string printDirection(Direction dir) { //Prints out a direction taken
	string retVal = "Error";
	switch (dir) {
	case Left:
		retVal = "Left ";
		break;
	case Right:
		retVal = "Right ";
		break;
	case Straight:
		retVal = "Straight ";
		break;
	}
	return retVal;
}

void printPath() { //Prints out the highest value, 'vault', list of directions, etc
	int totalJewels = 0;
	int startingColumn;
	Direction currentDir;
	for (int i = 0; i < 8; i++) {
		if (modified[0][i].jewels > totalJewels) {
			totalJewels = modified[0][i].jewels;
			startingColumn = i + 1;
		}
	}

	cout << "Bilbo starts at Row 1, Vault " << startingColumn << "\n";
	cout << "Bilbo ends with " << totalJewels << " jewels\n";
	cout << "Bilbo's path is: \n";

	int column = startingColumn - 1;
	for (int i = 0; i < 7; i++) {
		cout << printDirection(modified[i][column].d) << "\n";
		switch (modified[i][column].d) {
		case Left:
			column = column - 1;
			break;
		case Right:
			column = column + 1;
			break;
		case Straight:
			break;
		}
	}

	cout << "Bilbo ends at Vault " << column + 1 << "\n";

}

void InitMatrices() { //Initializes two 2-D arrays, both having the initial values, but only one will be modified

	initial[0][0].jewels = 79;
	initial[0][1].jewels = 71;
	initial[0][2].jewels = 18;
	initial[0][3].jewels = 20;
	initial[0][4].jewels = 34;
	initial[0][5].jewels = 51;
	initial[0][6].jewels = 93;
	initial[0][7].jewels = 65;

	initial[1][0].jewels = 73;
	initial[1][1].jewels = 38;
	initial[1][2].jewels = 24;
	initial[1][3].jewels = 49;
	initial[1][4].jewels = 18;
	initial[1][5].jewels = 6;
	initial[1][6].jewels = 40;
	initial[1][7].jewels = 74;

	initial[2][0].jewels = 31;
	initial[2][1].jewels = 5;
	initial[2][2].jewels = 63;
	initial[2][3].jewels = 10;
	initial[2][4].jewels = 32;
	initial[2][5].jewels = 40;
	initial[2][6].jewels = 14;
	initial[2][7].jewels = 13;

	initial[3][0].jewels = 13;
	initial[3][1].jewels = 78;
	initial[3][2].jewels = 48;
	initial[3][3].jewels = 19;
	initial[3][4].jewels = 78;
	initial[3][5].jewels = 11;
	initial[3][6].jewels = 90;
	initial[3][7].jewels = 94;

	initial[4][0].jewels = 22;
	initial[4][1].jewels = 93;
	initial[4][2].jewels = 68;
	initial[4][3].jewels = 11;
	initial[4][4].jewels = 56;
	initial[4][5].jewels = 63;
	initial[4][6].jewels = 49;
	initial[4][7].jewels = 35;

	initial[5][0].jewels = 85;
	initial[5][1].jewels = 52;
	initial[5][2].jewels = 27;
	initial[5][3].jewels = 5;
	initial[5][4].jewels = 94;
	initial[5][5].jewels = 91;
	initial[5][6].jewels = 82;
	initial[5][7].jewels = 62;

	initial[6][0].jewels = 46;
	initial[6][1].jewels = 23;
	initial[6][2].jewels = 99;
	initial[6][3].jewels = 77;
	initial[6][4].jewels = 10;
	initial[6][5].jewels = 42;
	initial[6][6].jewels = 1;
	initial[6][7].jewels = 72;

	initial[7][0].jewels = 89;
	initial[7][1].jewels = 70;
	initial[7][2].jewels = 73;
	initial[7][3].jewels = 83;
	initial[7][4].jewels = 90;
	initial[7][5].jewels = 22;
	initial[7][6].jewels = 44;
	initial[7][7].jewels = 92;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			modified[i][j].jewels = initial[i][j].jewels;
		}
	}
}
int main()
{
    std::cout << "Hello World!\n";

	int A[3][4] = { {1,1,1,6}, {1,1,2,9}, {1,2,3,14} };

	int A2[3][4] = { {1,1,1,6},{1,1,2,9}, {2,2,3,15} };
	int n = 3;


	vector<vector<double>> arr = { {1,1,1,1,1,1,1,1},
								{1,2,1,1,1,1,2,1},
								{1,1,3,1,1,3,1,1},
								{1,1,1,4,4,1,1,1},
								{11,1,1,1,1,1,1,1},
								{1,1,1,1,-1,-1,-1,-1 },
								{ 1,2,3,4,5,6,7,8 },
								{ 1,-1,1,-1,1,-1,1,-1 }
	};  //2d vector
	vector<double> ans = { 0,0,0,0,20,34,-51,-6 };
	findSolution(arr, ans, 8);

	cout << "\n";
	cout << "\n";
	InitMatrices();
	findPrecious();
	printPath();
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
