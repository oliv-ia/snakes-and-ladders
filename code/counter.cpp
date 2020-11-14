//counter.cpp
#include <iostream>
#include <cmath>
#include <string>
#include "counter.h"
#include "dice.h"
#include "board.h"
#include "piece.h"

// Member functions for derived class
// Parameterised constructor, takes in string and sets the name of the player
// Sets position to 0
player::player(std::string set_name)
{
	name = set_name;
	position = 0;
}

// Returns position, adjusts for vector starting at 0
int player::get_position() const
{
	return position + 1;
}

// Returns previous position
int player::get_previous_position() const 
{
	return previous_position;
}

// Returns player name
std::string player::get_name() const 
{
	return name;
}

// Returns vector of roll values
std::vector<int>  player::get_roll_values() const 
{
	return player_roll_values;
}

// Returns true if player has reached end of board, returns false if not
bool player::has_won(const board b) 
{


	if (get_position() >= b.board_length()) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 45,6 });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		std::cout << "Congratulations " << get_name() << " ! You won! " << std::endl;
		
		return true;
		
	}else {
		return false;
	};
}

// Moves player
// Returns new position
int player::move(const board & b, SHORT x) 
{	
	// Creates and rolls dice, adds value to player_roll_value vector
	dice d1;
	int player_roll_value = d1.roll();
	player_roll_values.push_back(player_roll_value);
	// Sets previous position to position, then adds roll value to position
	previous_position = position;
	position = position + player_roll_value;
	
	// Only needs to move if the player is not at the end of the board
	if (position < b.board_length()) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,20 + x });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		if (b.is_ladder(position)) {
			// If position element of board_array is ladder, print message and add length of ladder to position
			// Return new position
			// Clears console line
			std::cout << "\033[A\033[2K";
			std::cout << get_name() <<" landed on a ladder! ";
			return position = position + b.length(position);
		}else if (b.is_snake(position)) {
			// If position element of board_array is snake, print message and minus length of snake to position
			// Return new position
			std::cout << "\033[A\033[2K";
			std::cout << get_name() << " landed on a snake. ";
			return position = position - b.length(position);
		}else {
			// Return new position
			// Clears console line
			std::cout << "\033[A\033[2K";
			return position;
		}
	}
	// If the player has passed the end of the board, set position to 99 so they print at the end
	else {
		position = 99;
		return position;
	}
	return position;
}


//Member functions for opponent
//Default constructor, sets position to 0
opponent::opponent() {
	position = 0;
}

// Returns position, adjusts for vector starting at 0
int opponent::get_position() const 
{
	return position +1;
}

// Returns previous position
int opponent::get_previous_position() const 
{
	return previous_position;
}

// Returns opponent name
std::string opponent::get_name() const 
{
	return name;
}

// Returns vector of roll values
std::vector<int>  opponent::get_roll_values() const 
{
	return opponent_roll_values;
}

// Returns true if opponent has reached the end of the board, returns false if not
bool opponent::has_won(const board b) {
	
	if (get_position() >= b.board_length()) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 45,6 });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		std::cout << "Unfortunately, your opponent has beaten you to the end of the board" << std::endl;
		
		return true;
		
	}else{
	   return false;
	};	
}

// Moves opponent
// Returns new position
int opponent::move(const board & b, SHORT x) {
	// Creates and auto_rolls dice, adds value to opponent_roll_value vector
		dice d2;
		int opponent_roll_value = d2.auto_roll();
		opponent_roll_values.push_back(opponent_roll_value);
		// Sets previous position to position, then adds roll value to position
		previous_position = position;
		position = position + opponent_roll_value;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		if (position < b.board_length()) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,20 + x });
			if (b.is_ladder(position)) {
				// If position element of board_array is ladder, print message and add length of ladder to position
			    // Return new position
				// Clears console line
				std::cout << "\033[A\033[2K";
				std::cout << get_name() << " landed on a ladder. ";
				return position = position + b.length(position);
			}else if (b.is_snake(position)) {
				// If position element of board_array is snake, print message and minus length of snake to position
			    // Return new position
				// Clears console line
				std::cout << "\033[A\033[2K";
				std::cout << get_name()<< " landed on a snake. ";
				return position = position - b.length(position);
			}else {
				// Returns new position
				// Clears console line
				std::cout << "\033[A\033[2K";
				return position;
			}
		}
		else {
			position = 99;
			return position;
		}
		return position;
		
}


