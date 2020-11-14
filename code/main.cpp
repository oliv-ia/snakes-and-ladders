/*
Snakes and Ladders in C++ by Olivia Murray 11/05/2020
Game played by either two players or one player and a computer generated opponent
game prints a colured chequred board, with snake and ladder obstacles for the player to navigate
players move by rolling a dice
game is won when a player reaches the end of the board


*/

#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include <Windows.h>
#include <utility>
#include "piece.h"
#include "board.h"
#include "counter.h"
#include "dice.h"
#include "start_screen.h"


int main(){
	system("cls");
	// Start screen
	start_screen s1;
	s1.print_header();
	s1.print_snake_ascii(25, 3, 9);
	s1.print_ladder_ascii(40, 3, 10, 8);
	s1.print_snake_ascii(55, 3, 11);
	s1.print_ladder_ascii(70, 3, 12, 8);
	s1.print_snake_ascii(85, 3, 13);

    bool game_mode = s1.get_players();
	// Clers console
	system("cls");
	
	// Randomisation screen
	// Constructs board
	std::string y_or_n = "n";
	board b1;
	// Prints board, prints snakes, prints ladders
	b1.print_fancy();
	b1.print_snake();
	b1.print_ladder();
	// Prints ascii snakes and ladders
	s1.print_snake_ascii(45, 0, 10);
	s1.print_ladder_ascii(45, 7, 13, 8);
	s1.print_snake_ascii(45, 13, 10);

	// Print messge
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,22 });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	std::cout << "A random board has been generated. Press enter if you would like to play. " << std::endl;
	std::cout << "Press n to generate a new random board: ";

	std::getline(std::cin, y_or_n);
	// Randomisation loop
	while (y_or_n == "n") {
		// Loop generates random board until user input is not 'n'
		// Constructs board b2, assigns to board b1
		board b2;
		b1 = b2;
		b1.print_fancy();
		b1.print_snake();
		b1.print_ladder();
		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,22 });
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		std::cout << "A random board has been generated. Press enter if you would like to play. " << std::endl;
		std::cout << "Press n to generate a new random board: ";
		
		std::getline(std::cin, y_or_n);
		
	}
	// Clears console
	system("cls");

	// Game screen
	if (game_mode == 0) {
		std::string press_n = "n";
		while (press_n == "n") {
			system("cls");
			// Single player game
			// Get player and opponent information, construct player and oppoent
			std::pair <player, opponent> player_pair = s1.get_player_pair();
			player p1 = player_pair.first;
			opponent o1 = player_pair.second;
			// Print board, print snakes, print ladders
			b1.print_fancy();
			b1.print_snake();
			b1.print_ladder();
			// Print player and oppoenent
			b1.print_players(p1, o1, 3, 1, 3, 0);
			do {

				// While neither player or opponent has won
				// Move player, print player and opponent
				p1.move(b1, 2);
				b1.print_players(p1, o1, 3, 1, 3, 0);
				// Move opponent, print player and opponent
				// Print roll values
				o1.move(b1, 3);
				b1.print_players(p1, o1, 3, 1, 3, 0);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,22 });
				b1.print_roll_values(p1, o1, 1, 2);

			} while (!p1.has_won(b1) && !o1.has_won(b1));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,25 });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "Press 'n' to play this board again, press 's' to return to the start screen, press any other key to quit: ";
			std::getline(std::cin, press_n);
		}
		if (press_n == "s") {
			return main();
		}else {
			return 0;
		}
	}else {
		std::string press_n = "n";
		while (press_n == "n") {
			system("cls");
			// Multiplayer game
			// Get player information, construct players
			std::pair <player, player> multiplayer_pair = s1.get_multiplayer_pair();
			player p1 = multiplayer_pair.first;
			player p2 = multiplayer_pair.second;


			// Print board, print snakes, print ladders
			b1.print_fancy();
			b1.print_snake();
			b1.print_ladder();
			// Print both players
			b1.print_players(p1, p2, 3, 1, 3, 0);
			do {
				// While neither player has won
				// Move and print player 1
				// Print roll values
				p1.move(b1, 2);
				b1.print_players(p1, p2, 3, 1, 3, 0);
				b1.print_roll_values(p1, p2, 1, 2);
				// Move and print player two
				// Print roll values
				p2.move(b1, 3);
				b1.print_players(p1, p2, 3, 1, 3, 0);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,22 });
				b1.print_roll_values(p1, p2, 1, 2);

			} while (!p1.has_won(b1) && !p2.has_won(b1));
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,25 });
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << "Press 'n' to play this board again, press 's' to return to the start screen, press any other key to quit: ";
			std::getline(std::cin, press_n);
		}if (press_n == "s") {
			return main();
		}else {
			return 0;
		}
	}
	
}
	
	
