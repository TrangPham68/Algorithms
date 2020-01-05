// Homework5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Question 1,2,3
/*struct for the hash Entry 
each hashEntre has its own hashCode aka hashing Value
                           hashAddress
                           word aka hash word
                           frequency of collision (from same hash address)
*/
struct hashEntre{
	int hashCode;
	int hashAddress;
	int frequency;
	string word;
};


/*
find hash value of the word using given formula
@param string a the word to find hash
@param int h initial hash value
@param int C (set as 123)
@param int m max(set as 1000)
@return int the hashing value of the word
*/
int hashing(string a, int h, int C, int m)
{
	for (int i = 0; i < a.length(); i++)
	{
		char ch = a[i];
		h = (h * C + int(ch)) % m;
	}
	return h;
}


/*
parse the string to ignore all spaces and punctuations
@param string str the string to parse
@return string the parsed string with only characters and no space or punctuations
*/
string parseString(string str)
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


/*
insert hashEntre to the hashtable is the hashEntre.word does not exist in the table yet
if collision happens, keep ascending address by one till find an empty spot
@param hashEntre* hashtable the pointer to the hashtable
@param hashEntre a entre to add in 
@return int return 1 if insert success, 0 otherwise
*/
void insert(hashEntre* hashtable, hashEntre a, int m)
{
	//check if word is already in there

	for (int i = 0; i < 1000; i++)
	{
		if (hashtable[i].word == a.word)
		{
			return; //if word already exit --> return and not add into the hashtable
		}
	}
	//if nothing is in that position yet
	if (hashtable[a.hashAddress].hashCode == -1)
	{
		hashtable[a.hashAddress] = a;  //insert
	}
	else
	{
		if (a.hashCode == hashtable[a.hashAddress].hashCode)
		{
			hashtable[a.hashAddress].frequency += 1;
		}
		a.hashAddress += 1;  //ascending the address by one
		if (a.hashAddress >= m-1)
		{
			a.hashAddress = 0;  //if got to the end, loop back to the beginning
		}
		insert(hashtable, a, m);
	}
}

//question 4
int readFile(int*& matrix) {
	ifstream myfile;
	myfile.open("C:\\Users\\Trang Pham\\Downloads\\test.txt");
	int graphSize;
	myfile >> graphSize;
	matrix = new int[graphSize * graphSize];
	for (int i = 0; i < graphSize * graphSize; i++) {
		myfile >> matrix[i];
	}
	myfile.close();
	//cout << graphSize << "\n";
	return graphSize;
}

struct Node {
	int distance;
	bool visited;
	vector <Node> neighbor;
};

int nextNode(int startNode, Node* nodes, int graphSize) {
	int minDistance = 100000000;
	int currentNode = -1;
	for (int i = 0; i < graphSize; i++) {
		if (nodes[i].visited == false) {
			if (nodes[i].distance <= minDistance && nodes[i].distance != -1) {
				minDistance = nodes[i].distance;
				currentNode = i;
			}
		}
	}
	return currentNode;
}

/*
find the shortest path from the given sources node and store it back the the nodes list
*/
void Djikstra(Node* nodes, int* matrix, int graphSize, int startNode) {
	int currentNode = startNode;
	nodes[startNode].visited = true;
	nodes[startNode].distance = 0;
	cout << "this is the path of currentNode -> nextNode " << "\n";
	while (currentNode != -1 ) {
		int rowStart = graphSize * currentNode;
		nodes[currentNode].visited = true;
		for (int i = 0; i < graphSize; i++) {
			if (matrix[i + rowStart] != 0) {
				if (nodes[i].distance > (matrix[i + rowStart] + nodes[currentNode].distance) ||
					nodes[i].distance == -1) {
					nodes[i].distance = matrix[i + rowStart] + nodes[currentNode].distance;
				}

			}
		}
		cout << currentNode << " ";

		currentNode = nextNode(startNode, nodes, graphSize);
		cout << currentNode << endl;
	}
}


int main()
{
	fstream myFile;
	string filename, word;
	int m = 1000;
	int C = 123;
	int counter = 0;

	hashEntre hashTable[1000]; //make a list of 1000 slots
	//initialize the spot by filling it up with nonValid value
	for (int i = 0; i < m; i++)
	{
		hashTable[i].hashCode = -1;
		hashTable[i].word = "";
		hashTable[i].hashAddress = i;
		hashTable[i].frequency = 0;
	}

	//read file
	filename = "C:\\Users\\Trang Pham\\Downloads\\Raven.txt";
	myFile.open(filename.c_str());
	
	if (!myFile)
	{

		cerr << "unable to open file";
		exit(1);
	}
	else
	{

		while (myFile >> word)
		{
			int h = 0;
			hashEntre temp;
			word = parseString(word);
			temp.word = word;
			temp.hashCode = hashing(word, h, C, m);
			temp.hashAddress = temp.hashCode;
			temp.frequency = 0;
			insert(hashTable, temp, m);

		}

		int longEmpty = -1;
		int emptyAdd = -1;
		int longCluster = -1;
		int clusterAdd = -1;
		int mostFrequen = -1; 
		int frequenAdd = -1;
		int furthestLen = -1;
		string far;
		int farAdd = -1;
		int loopCluster = 0;

		int tempCluster = 0;
		int tempClusterAdd = 0;
		int tempEmpty = 0;
		int tempEmptyAdd = 0;
		int length = 0;
		cout << "\nThe map is : \n";
		cout << "\tADDRESS\tWORD\t\tVALUE\n";

		for (int i = 0; i < m; i++) {
			if (hashTable[i].hashCode != -1) //non-empty
			{
				counter++;
				if (tempEmpty > longEmpty)
				{  //update and find the longest empty are and address
					emptyAdd = tempEmptyAdd; 
					longEmpty = tempEmpty;
				}
				tempEmpty = 0;
				if (tempCluster == 0)
				{
					tempClusterAdd = hashTable[i].hashAddress;
				}
				tempCluster++;
				cout <<counter<< '\t'<<hashTable[i].hashAddress
					<< '\t' << hashTable[i].word;
				if (hashTable[i].word.length() > 7)
				{
					cout << '\t' << hashTable[i].hashCode << '\n';
				}
				else
				{
					cout << '\t' << '\t' << hashTable[i].hashCode << '\n';
				}

				if (hashTable[i].frequency > mostFrequen)
				{
					//update the address that has greatest number of dinstinc words
					mostFrequen = hashTable[i].frequency;
					frequenAdd = i;
				}

				if (hashTable[i].hashCode > hashTable[i].hashAddress)
				{
					//distance from value to address of hashEntre that loop back to the beginning
					length = m - hashTable[i].hashCode + hashTable[i].hashAddress;
				}
				else
					length = hashTable[i].hashAddress - hashTable[i].hashCode;

				if (length > furthestLen)
				{
					//dintance form value to address
					furthestLen = length;
					far = hashTable[i].word;
					farAdd = i;
				}

				if (i == m - 1 && tempCluster!=0)
				{
					if (tempCluster + loopCluster > longCluster)
					{
						longCluster = tempCluster + loopCluster;
						clusterAdd = tempClusterAdd;
					}
				}

			}
			else  //empty
			{
				if (longCluster == -1)
				{
					loopCluster = tempCluster;
				}
				if (tempCluster > longCluster)
				{ //update and find the longest cluster area and address
					clusterAdd = tempClusterAdd;
					longCluster = tempCluster;
				}
				tempCluster = 0;
				if (tempEmpty == 0)
				{
					tempEmptyAdd = hashTable[i].hashAddress;
				}
				tempEmpty++;
			}

		}
		cout << endl;

		cout << "The # of non empty addresses are " << counter << "\n";
		cout << "The load factor (alpha) is " << (double)counter / m << endl;
		cout << "The longest empty area is " << longEmpty << " and it starts at address " << emptyAdd << endl;
		cout << "The longest cluster area is " << longCluster << " and it starts at address " << clusterAdd << endl;
		cout << "The hash Address that has the greatest number of distinct words is " << frequenAdd << " with the number of collision(including the word itself) " << mostFrequen +1 << endl;
		cout << "the word that is furthest from it actual value is " << far << " which is at " <<farAdd<< " and is "<< furthestLen << " unit from its value/actual address" << endl;

	}

	cout << "\n";
	
	int again = 1;
	while (again == 1)
	{
		int start;
		int end;
		cout << "What Node do you want to start? (0:A, 1:J, M:2, 3:R, 4:K, 5:S, 6:I, 7:N, 8:T, 9:D)";
		cin >> start;
		cout << "What Node do you want to end? (0:A, 1:J, M:2, 3:R, 4:K, 5:S, 6:I, 7:N, 8:T, 9:D)";
		cin >> end;

		int* matrix;
		int nodeNumber = readFile(matrix);
		Node* nodes = new Node[nodeNumber];
		for (int i = 0; i < nodeNumber; i++) {
			nodes[i].distance = -1;
			nodes[i].visited = false;
		}

		Djikstra(nodes, matrix, nodeNumber, start);

		for (int i = 0; i < nodeNumber; i++) {
			cout << "Node " << i << " : " << nodes[i].distance << endl;
		}
		cout << "the shortest path length from " << start << " to " << end << " is " << nodes[end].distance << endl;
		cout << "\n";
		cout << "If you want to try again, enter 1, else 0"<<endl;
		cin >> again;
		delete matrix;
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
