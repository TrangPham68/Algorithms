#pragma once
class Board {
	int m_dimensions;
	int* positions;

public:
	/*
	Constructor
	Create board with certaint n dimentions and int pointer to queen array
	*/
	Board(int dimensions, int* queens);

	/*
	destructor of the board
	*/
	~Board();

	/*
	determine if there is a queen at a given space
	*/
	int at(int row, int column);

	/*
	determine if the board is legal or not
	return true if the board is legal and no queens attacking each other
	return false otherwise
	*/
	bool isLegal();

	/*
	check to see if a queen at position (row, col) is being attacked by other queen or not
	return if the queen is being attacked vertically, horizontally(don't really need to check), or diagnolly
	*/
	bool attacked(int row, int column);

	/*
	find the row with the last queen
	*/
	int lastQueenRow(int& column);

	/*
	move the queen to get next position based on the current board
	*/
	void moveQueen();

	/*
	get the current array of queens
	*/
	int* getQueens();

};