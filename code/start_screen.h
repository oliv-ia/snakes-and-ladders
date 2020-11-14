//start_screen.h
#include <iostream>
#include <Windows.h>
#include <utility>
#include "counter.h"

class start_screen{
private:
	std::pair <player, opponent > player_pair;
	std::pair <player, player> multiplayer_pair;
	bool game_mode;
public:
	// Default constructor
	start_screen();
	// Print functions
	void print_header();
	void print_snake_ascii(SHORT x, SHORT y, int colour);
	void print_ladder_ascii(SHORT x, SHORT y, int colour, int shadow);
	// Access functions
	bool get_players();
	std::pair <player, opponent> get_player_pair();
	std::pair <player, player> get_multiplayer_pair();
};