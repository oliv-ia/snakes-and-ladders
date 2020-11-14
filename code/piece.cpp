#include <iostream>
#include <cmath>
#include "piece.h"

// Snake member functions
// Parameterised constructor, takes in integer start and end positions
snake::snake(int start_pos, int end_pos) : start_position{ start_pos }, end_position{ end_pos } {}

// Calculates length of snake, difference of the start and end positions
// Returns length
int snake::get_length() 
{
	return start_position - end_position;
}

// Ladder member functions
//Parameterised constructor, takes in integer start and end positions
ladder::ladder(int start_pos, int end_pos) : start_position{ start_pos }, end_position{ end_pos } {}

// Calculates length of ladder, difference of the end and start positions
// Returns length
int ladder::get_length() 
{
	return end_position - start_position;
}