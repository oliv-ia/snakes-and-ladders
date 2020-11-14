//counter.h
//abstract base class representing a counter, and derived classes for player and computer opponent
#ifndef COUNTER_H
#define COUNTER_H

#include <iostream>
#include <cmath>
#include "board.h"

// Initialised board class for use in counter class
class board;

// Abstract counter base class 
class counter {

public:
	// Pure virtual functions
	// Virtual destructor
	virtual ~counter() {}
	// Virtual access functions
	virtual int get_position() const = 0;
	virtual std::string get_name() const = 0;
	virtual int get_previous_position() const = 0;
	virtual std::vector<int>  get_roll_values() const = 0;
	virtual bool has_won(const board b) = 0;
	virtual int move(const board & b, SHORT x) =0;
};

// Derived player class, inherits abstract counter base class
class player : public counter {
private:
	std::string name;
	int position;
	std::vector<int> player_roll_values;
	int previous_position{ -1 };
public:
	// Parameterised constructor, takes in string to set name
	player(std::string set_name);
	~player() {}
	int get_position() const;
	int get_previous_position() const;
	std::string get_name() const;
	std::vector<int>  get_roll_values() const;
	bool has_won(const board b);
	int move(const board & b, SHORT x);
};

// Derived opponent class, inherits abstract counter base class
class opponent : public counter {
private:
	std::string name = "opponent";
	int position;
	std::vector<int> opponent_roll_values;
	int previous_position{ -1 };
public:
	opponent();
	~opponent() {}
	int get_position() const;
	int get_previous_position() const;
	std::string get_name() const;
	std::vector<int>  get_roll_values() const;
	bool has_won(const board b);
	int move(const board& b, SHORT x);
};

#endif