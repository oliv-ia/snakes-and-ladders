//dice.cpp
#include <iostream>
#include <cmath>
#include <string>
#include "Windows.h"
#include <time.h>
#include "dice.h"


//Member functions
// Constructor
// Sets number of faces to 6
dice::dice() 
{
	srand(time(NULL));
	number_of_faces = 6;
}

// Rolls dice
// Asks for user input to roll dice
int dice::roll() 
{
	COORD write_here{ 0,21 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), write_here);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "\033[A\033[2K";
	// Check valid input
	bool valid_roll = false;
	std::string if_roll;
	std::cout << "Please press 'r' to roll the dice: ";
	std::getline(std::cin, if_roll);
	while (!valid_roll) {
		std::cout << "\033[A\033[2K";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		if (if_roll == "r" || if_roll == "R") {
			// If valid input
			// Adds time delay to ensure new random number is generated
			Sleep(500);
			// Creates and returns random number between 1 and 6
			int roll_value = ((rand() % number_of_faces + 1) + (rand() % number_of_faces + 1)) % number_of_faces + 1;
			return roll_value;
			valid_roll = true;
		}else {
			// input invalid, asks again
			COORD write_here{ 0,21 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), write_here);
			std::cout << "\033[A\033[2K";
			std::cout << "Not quite what I asked for, please press 'r' to roll the dice: ";
			std::getline(std::cin, if_roll);
			valid_roll = false;
		}
	}
	
}

// Auto_rolls dice
int dice::auto_roll() 
{
	// Add time delay to ensure new random number is generated
	Sleep(500);
	// Creates and returns random number between 1 and 6
	int roll_value = rand() % number_of_faces + 1;
	return roll_value;
}