#pragma once

enum Direction { //Direction 'types' created to signify which direction is taken
	Left,
	Straight,
	Right
};

struct Matrix { //A matrix that can have both an int and a direction in a single 'location'
	int jewels;
	Direction d;
};