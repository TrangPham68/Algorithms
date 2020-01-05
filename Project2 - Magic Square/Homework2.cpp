// Homework2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Trang Pham
//Andrew Descheneaux

#include <iostream>
#include <time.h>
#include <vector>


using namespace std;

/*problem 1
R(n) = (3^n+1) -1
Order of growth O(3^n) 
*/
int non_recursive(int n) {
	return pow(3, n + 1) - 1;
}

// Lucas number
//lucas invent the tower of Hanoi puzzle
// known for the cannonball problem
int lucas(int n)
{
	int result;
	if (n == 0)
	{
		result = 2;
	}
	else if (n == 1)
	{

		result = 1;
	}
	else
	{
		result = lucas(n - 1) + lucas(n - 2);
	}
	return result;
}

/*problem 4
Magic square has the size of  (nxn)
contain number from 1 - n^2
the magic sum = n(n^2+1)/2
*/

//combination of 4 elements combination
int combination(int a[], int n, int sum)
{
	int count = 0;

	for (int f = 0; f < n-3; f++)
	{
		for (int s = f+1; s < n-2; s++)
		{
			for (int t = s+1; t< n-1 ; t++ )
			{
				for (int fo = t+1; fo < n; fo++)
				{
					if (a[f] + a[s] + a[t] + a[fo] == sum)
					{
						std::cout << a[f] << " " << a[s] << " " << a[t] << " " << a[fo] << "\n";
						count++;
					}
				}
			}
		}
	}
	return count;
}


//int count;
int combination2(int magicSquare[],int squareSize, int currentSum, int target, int start, int resultSize, int& count)
{
	int result = 0;

	for (int i = start; i < squareSize; i++)
	{
		if (magicSquare[i] < (target - currentSum))// if the sum is less than the target and can add another value
		{
			//result[resultSize - i] = array[i];
			combination2(magicSquare, squareSize, currentSum + magicSquare[i], target, i + 1, resultSize + 1, count);

		}
		else if (magicSquare[i] == (target - currentSum))  //if sum add the next value == sum
		{
			//result[resultSize - 1] = array[i];
			result = magicSquare[i];
			count++;
			
		}//cout << "cout for " << resultSize << " " << count << endl;
			//int* remaining = array[i + 1:]; can start for loop from i
		//return count + combination2(array, n-1, sum + array[i], target, i);
	}

	return count;

}

int main()
{

	clock_t t;
	int result;
	float before;
	float after;
	float ratio =-1;


	for (int i = 0; i < 30; i++)
	{

		t = clock();
		result = lucas(i);
		t =(clock() - t);

		std::cout <<result<< "\n";
		std::cout << "the time is: "<<((float)t) / CLOCKS_PER_SEC << "\n";

		if (i == 0)
		{
			before = ((float)t) / CLOCKS_PER_SEC;
		}
		else if (i == 1)
		{
			after = ((float)t) / CLOCKS_PER_SEC;
			ratio = after / before;
		}
		
		else
		{
			before = after;
			after = ((float)t) / CLOCKS_PER_SEC;
			ratio = after / before;
		}

		std::cout << "the ratio is of  L(n+1)/L(n)" << ratio << "\n";
	}
	
	//the growth time is at 0 for the first few n (n <20ish)
	//but after that the ratio appear to be roughly (1.4,2) --> avg = 1.61 which is a golden ratio and is also fibonacci rate of growth in time
	//in other word, the big O is 1.61^n or can be said to be 2^n

	//question 4
	int magicSquare[16] = {1,14,14,4,11,7,6,9,8,10,10,5,13,2,3,15};
	int sum = 33; 
	int size = 16;
	int count = 0;


	std::cout << "the amount of combinations of 4 elements that add up to 33 is "<<combination(magicSquare, size, sum) <<endl;
	cout << "The amount of combinations that has sum = 33 is "<<combination2(magicSquare, size, 0, sum, 0, 0, count)<<endl;

	for (int i = 0; i < 132; i++)
	{
		int count2 = 0;
		cout << "the combination to get " << i << " is " << combination2(magicSquare, size, 0, i, 0, 0, count2) << endl;
	}

	cout << "the sum that has the largest combinations is 66 which is 2 times 33 (with 1364 combinations). WOW" << endl;
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
