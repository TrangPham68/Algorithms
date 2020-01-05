#include <iostream>
#include "Board.h"


Board::Board(int dimensions, int* queens) {
	m_dimensions = dimensions;
	positions = new int[dimensions * dimensions];
	for (int i = 0; i < dimensions * dimensions; i++) {
		positions[i] = 0;
	}
	for (int j = 0; j < dimensions; j++) {
		int row = j;
		if (queens[j] != 0) {
			int column = queens[j] - 1;
			positions[(row * dimensions) + column] = 1;
		}
	}
}

int Board::at(int row, int column) {
	if (row < 0 || column < 0)
		return 0;
	if (row >= m_dimensions || column >= m_dimensions)
		return 0;
	return positions[(row * m_dimensions) + column];
}


bool Board::isLegal() {
	for (int i = 0; i < m_dimensions; i++) {
		for (int j = 0; j < m_dimensions; j++) {
			if (at(i, j) == 1) {
				if (attacked(i, j) == true)
					return false;
			}
		}
	}
	return true;
}

bool Board::attacked(int row, int column) {
	//check row
	for (int i = 0; i < m_dimensions; i++) {
		if ((at(i, column) == 1) && (i != row))
			return true;
	}

	//check column
	for (int i = 0; i < m_dimensions; i++) {
		if ((at(row, i) == 1) && (i != column))
			return true;
	}

	//check lower diagonal
	for (int i = row + 1; i < m_dimensions; i++) {
		int c = column + i - row;
		int c2 = column - i + row;
		if (at(i, c) == 1)
			return true;
		if (at(i, c2) == 1)
			return true;
	}
	//check upper diagonal
	for (int i = row - 1; i >= 0; i--) {
		int c = column + row - i;
		int c2 = column - row + i;
		if (at(i, c) == 1)
			return true;
		if (at(i, c2) == 1)
			return true;
	}
	return false;
}

int Board::lastQueenRow(int& column) {
	for (int i = m_dimensions; i >= 0; i--) {
		for (int j = m_dimensions; j >= 0; j--)
			if (at(i, j) == 1) {
				column = j;
				return i;
			}
	}
	return -1;
}

void Board::moveQueen() {
	int column = 0;
	int row = lastQueenRow(column);

	if (isLegal() == true && row != (m_dimensions - 1)) {
		positions[((row + 1) * m_dimensions)] = 1;
		return;
	}
	while (row >= 0) {
		positions[(row * m_dimensions) + column] = 0;
		if ((column + 1) != m_dimensions) {
			positions[(row * m_dimensions) + column + 1] = 1;
			return;
		}
		else {
			row = lastQueenRow(column);
		}
	}
}

int* Board::getQueens() {
	int* queens = new int[m_dimensions];
	for (int i = 0; i < m_dimensions; i++)
		queens[i] = 0;
	for (int j = 0; j < m_dimensions; j++) {
		for (int k = 0; k < m_dimensions; k++) {
			if (at(j, k) == 1)
				queens[j] = k + 1;
		}
	}
	return queens;
}

Board::~Board() {
	delete[] positions;
}



