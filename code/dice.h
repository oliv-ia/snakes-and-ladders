//dice.h
#ifndef DICE_H
#define DICE_H
#include <iostream>
#include <cmath>
class dice
{
private:
	int number_of_faces{};
	int roll_value{};
public:
	// Constructor and destructor
	dice();
	~dice() {};
	int roll();
	int auto_roll();

};
#endif