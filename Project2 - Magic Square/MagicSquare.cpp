#include "MagicSquare.h"
#include <iostream>

using namespace N;
using namespace std;

int MagicSquare::magicSum(int n)
{
	return n * (pow(n, 2) + 1) / 2;
}

int MagicSquare::possibleCombination(int n)
{
	int sum = magicSum(n);
	int combination = 0;
	int *arr = new int[n];

	//when a combination is found
	if (sum == 0)
	{
		combination++;
	}

	return 1;

}

