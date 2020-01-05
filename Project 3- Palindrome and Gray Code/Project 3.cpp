// Project 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Palindromes, Inversions, and binary reflected gray code
//11/16/2019

#include <iostream>
#include <string>
#include<vector>
using namespace std;



string stringConverter(string &str)
{
	int size = str.length();
	int i = size;
	while (i >= 0)
	{
			//remove space and punctuation
			if (isspace(str[i]) || ispunct(str[i]))
			{
				str.erase(str.begin() + i);
				i++;
			}
			i--;
	}
	return str;
} 

bool palindromecheck(string& str)
{
	bool palindrome = true;
	//ignore white space and punctuation

	str = stringConverter(str);

	
	//search for palindrome
	int size = str.length();
	printf("the size here is %d \n", size);
	for (int i = 0; i < size / 2; i++)
	{
		if (tolower(str.at(i)) != tolower(str.at(size-i-1))) //case insensitive
		{
			palindrome = false;
			printf("It is not a palindrome!\n");
			printf("\n");
			return palindrome;

		}
	}
	if (palindrome == true)
	{
		printf("it is a palindrome!\n");
		printf("\n");
	}
	return palindrome;
}

//bubble sort
//inversion using bubble sort
//running time O(n^2)
int easyInversionCount(int arr[], int size)
{
	int counter = 0;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i; j < size; j++)
		{
			if (arr[i] > arr[j])
			{
				counter++;
			}
		}
	}
	printf("easy Inversion: there are %d inversions from array \n", counter);
	return counter;
}

//merge sort
//finding inversions using merge sort logic
//running time O(nlogn)
int fastInversionCount(int count[], int size)
{
	int inversions = 0;
	int c, temp;
	if (size > 2) {
		inversions += fastInversionCount(&count[0], size / 2);
		inversions += fastInversionCount(&count[size / 2], size - size / 2);
		for (int i = size / 2; i < size; i++) {
			c = i - 1;
			while (i > 0 && count[c] > count[i]) {
				temp = count[c];
				count[c] = count[i];
				count[i] = temp;
				i--;
				c--;
				inversions++;
			}
		}
	}
	else if (size <= 1)
		return 0;
	else {
		if (count[0] > count[1]) {
			temp = count[0];
			count[0] = count[1];
			count[1] = temp;
			return 1;
		}
		else
			return 0;
	}

	printf("fast Inversion: there are %d inversions from array \n", inversions);
	return inversions;

}

//gray code displayer 
//param int n order of n
vector<string> brgc(int n) {
	vector<string> str;
		//printf("gray code for %d \n", n);
	if (n == 1) {
		str.push_back("0");
		str.push_back("1");
		//return str;
	}
	else {
		
		vector<string> l1 = brgc(n - 1);   //generate l1 list using recursion
		vector<string> l2;

		for (int i = 0; i < l1.size(); i++) { //add in reverse order and add 0 in front
			str.push_back("0" + l1.at(i));
		}

		for (int i = l1.size() - 1; i >= 0; i--) {
			l2.push_back("1" + l1.at(i));  //aff 1 in front of the second half
		}
		for (int i = 0; i < l2.size(); i++)
		{
			str.push_back(l2.at(i));   //append to str list
		}
	
	}
	return str;
}

// rhythm abacabadabacaba....
// find order of children in photo using gray code patern
//find the action of mvoing in and out of the children (flipping point)
vector<string> graycodeisfun(int n, vector<string> child, vector<string> &move)
{
	vector<string> str;
	//printf("gray code for %d \n", n);
	if (n == 1) 
	{
		str.push_back(" ");
		//return str;
	}
	else 
	{
		//child.pop_back();
		vector<string> l1 = graycodeisfun(n - 1, child, move);
		vector<string> l2;

		for (int i = 0; i < l1.size(); i++) 
		{
			str.push_back(l1.at(i));
			//cout << l1.at(i) << "\n";
			
		}

		for (int i = l1.size() - 1; i >= 0; i--) {
			l2.push_back(child.at(n-2) + l1.at(i));

			if (i == l1.size()-1) 
			{
			
				move.push_back(child.at(n - 2));  //add child in aka the 1 in gray code in the left

				if (move.size() == 2)
				{
					move.push_back(move.at(0));
				}
				
				else if (move.size() > 2)
				{
					int size = move.size();
					for (int pos = 0; pos < size-1; pos++)
					{
						move.push_back(move.at(pos));
					}
				}
				
			}


		}
		for (int i = 0; i < l2.size(); i++)
		{
			str.push_back(l2.at(i));
		}

	}
	return str;
}


	int main()
	{
		//check palindrome
		string a = "Helleh";
		string b = "Never odd or even";
		string c = "Able was I ere I saw Elba";
		string d = "A man, a plan, a canal: Panama!";
		cout << a;
		palindromecheck(a);
		cout << "\n";
		cout << b;
		palindromecheck(b);
		cout << "\n";
		cout << c;
		palindromecheck(c);
		cout << "\n";
		cout << d;
		palindromecheck(d);
		cout << "\n";

		//check inversions
		int arr[3] = { 3,2,1 };
		easyInversionCount(arr, 3); //later, change this to input
		fastInversionCount(arr, 3);

		//gray code
		//brgc(2);
		//cout << "\n";

		cout << "\n";
		vector<string> arr1 = { " Alice ", " Bob ", " Chris ", " Dylan "};

		vector<string> gray;
		gray = brgc(4);
		printf("gray code of order 4: \n");
		for (int i = 0; i < gray.size(); i++)
		{
			
			cout <<gray.at(i) << "\n";
		}

		vector<string> grayy;
		grayy = brgc(3);
		printf("gray code of order 3: \n");
		for (int i = 0; i < grayy.size(); i++)
		{
			
			cout << grayy.at(i) << "\n";
		}

		vector<string> gray2;
		vector<string> move;
		printf("Child(ren) in photo order of: \n");
		gray2 = graycodeisfun(5, arr1, move);
		for (int j = 0; j < gray2.size(); j++)
		{
			cout << j<< ". " << gray2.at(j) << "\n";
		}

		printf("Moved in order of (action) :\n");
		for (int j = 0; j < move.size(); j++)
		{
			cout << move.at(j) << "\n";
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
