//piece.h
//header file containing the abstract base class for a tile, and the derived classes empty, snake and ladder
#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <cmath>

//Abstract tile base class
class tile
{
public:
	//Pure virtual functions
	tile() {}
	// Virtual destructor
	virtual ~tile() {}
	virtual int get_length() = 0;
};

// Derived empty class, inherits abstract tile base class
class empty : public tile
{
public:
	// Destructor
	~empty() {}
	// Access functions
	int get_length() { return 0; };
};

// Derived snake class, inherits abstract tile base class
class snake : public tile
{
private:
	int start_position{};
	int end_position{};
public:
	// Parameterised constructor, takes in start and end position
	snake(int start_pos, int end_pos);
	// Access functions
	int get_length() ;
};

// Derived ladder class, inherits abstract tile base class
class ladder : public tile
{
private:
	int start_position{};
	int end_position{};
public:
	// Parameterised constructor, takes in start and end position
	ladder(int start_pos, int end_pos);
	// Access functions
	int get_length();
};
#endif