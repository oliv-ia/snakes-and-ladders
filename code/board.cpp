//board.cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include "board.h"
#include "counter.h"
#include "piece.h"

// Member functions

// Parameterised constructor
// Creates vector of 100 empty tiles. Generates 20 random numbers and asignes to the start and finish position of 5 snakes and 5 ladders.
board::board() : board_vector{ 100,std::make_shared<empty>() } 
{
    // Seed random numbers
    srand(time(NULL));
    std::vector <int> low_position;
    std::vector <int> high_position;
    // Generates random number between 0 and 90 and pushes back onto vector
    int low_pos = rand() % 89 + 2;
    low_position.push_back(low_pos);
    // Does this 10 times, ignores numbers that have already been generated
    while (low_position.size() < 10) {
        int further_low_pos = rand() % 89 + 2;
        std::vector <int> ::iterator it;
        it = find(low_position.begin(), low_position.end(), further_low_pos);
        if (it == low_position.end()) {
            // Random number already in vector
            low_position.push_back(further_low_pos);
        }
    }
    // Generates further 10 random numbers between 10 and 99 and pushes back onto vector
    // Does this 10 times, ignores numbers that have already been generated here and above
    while (high_position.size() < 10) {
        int high_pos = rand() % 89 + 10;
        std::vector <int> ::iterator it;
        it = find(high_position.begin(), high_position.end(), high_pos);
        if (it == high_position.end()) {
            // Random number already in vector
            std::vector <int> ::iterator it_low;
            it_low = find(low_position.begin(), low_position.end(), high_pos);
            if (it_low == low_position.end()) {
                // Random number already in vector
                high_position.push_back(high_pos);
            }
        }
    }
    // Try and catch loop for handeling of out of range exeptions
    try {
        // Creates 5 snakes at position in board_vector determined by largest random at position i in low_position and high_position
        // Creates 5 ladders at position in board_vector determined by smallest random at position i in low_position and high_position
        for (int i{ 0 }; i < 10; i++) {
            if (i % 2 == 0) {
                if (high_position[i] > low_position[i]) {
                    board_vector[high_position[i]] = std::make_shared<snake>(high_position[i], low_position[i]);
                }else {
                    board_vector[low_position[i]] = std::make_shared<snake>(low_position[i], high_position[i]);
                }
            }else {
                if (high_position[i] < low_position[i]) {
                    board_vector[high_position[i]] = std::make_shared<ladder>(high_position[i], low_position[i]);
                }
                else {
                    board_vector[low_position[i]] = std::make_shared<ladder>(low_position[i], high_position[i]);
                }
            }
        }
    }
    catch (const std::out_of_range & oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

}

// Print functions
// Gets coordinates of position on representation of board from the position in board_vector
_COORD board::get_tile_coords(int array_pos) const
{
    int array_pos_div_ten{ array_pos / 10 };
    if ((array_pos_div_ten) % 2 == 0) {
        int X = 4 * (array_pos % 10);
        int Y = 2 * (9 - array_pos_div_ten);
        COORD pos{ X,Y };
        return pos;
    }else {
        int X = 4 * (9 - (array_pos % 10));
        int Y = 2 * (9 - array_pos_div_ten);
        COORD pos{ X,Y };
        return pos;
    }  
}

// Prints snakes
// Prints 'S' at start of snake, prints 's' at end of snake
// Each snake is colour coded
void board::print_snake() const 
{
    // Vector of colour codes
    std::vector<int> colour_ints{ {159,207,223,176,143} };
    int colour_counter{ 0 };
    for (int i{}; i < board_length(); i++) {
           
        if (is_snake(i)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour_ints[colour_counter]);
                COORD pos = get_tile_coords(i);
                pos.X += 2;
                pos.Y += 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                std::cout << "S";
                COORD pos_2 = get_tile_coords(i - length(i));
                pos_2.X += 2;
                pos_2.Y += 1;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos_2);
                std::cout << "s";
                colour_counter++;
            }
        }
    
}
// Prints ladders 
// Prints 'L' at start of ladder, prints 'l' at end of ladder
// Each ladder is colour coded
void board::print_ladder() const 
{
    std::vector<int> colour_ints{ {31,32,63,79,96} };
    int colour_counter{ 0 };
    for (int i{}; i < board_length(); i++) {
        
        if (is_ladder(i)) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour_ints[colour_counter]);
            COORD pos = get_tile_coords(i);
            pos.X += 2;
            pos.Y += 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
            std::cout << "L";
            COORD pos_2 = get_tile_coords(i + length(i));
            pos_2.X += 2;
            pos_2.Y += 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos_2);
            std::cout << "l";
            colour_counter++;
        }
    }
}

// Prints representation of board
// Prints 100 square tiles of alternating colours
// Prints the number of each tile in the top corner, this number corresponds to position of tiles in board_vector
void board::print_fancy() 
{
    // On snakes and ladders board, even and odd rows run in different directions
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0,0 });
        for (int i{ 10 }; i > 0; i--) {
            if (i % 2 == 0) {
                for (int j{}; j < 10; j++) {
                    if (j % 2 == 0) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                        if ((i) * 10 - j > 99) {
                            std::cout << (i) * 10 - j << " ";
                        }else {
                            std::cout << (i) * 10 - j << "  ";
                        }
                    }else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                        if ((i) * 10 - j > 99) {
                            std::cout << (i) * 10 - j << " ";
                        }else {
                            std::cout << (i) * 10 - j << "  ";
                        }
                    }
                }
                std::cout << std::endl;
                for (int j{}; j < 10; j++) {
                    if (j % 2 == 0) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                        std::cout << "    ";
                    }else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                        std::cout << "    ";
                    }
                }
                std::cout << std::endl;
            }else {
                for (int j{ 10 }; j > 0; j--) {
                    if (j % 2 == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                        if ((i) * 10 - j + 1 < 10) {
                            std::cout << (i) * 10 - j + 1 << "   ";
                        }else {
                            std::cout << (i) * 10 - j + 1 << "  ";
                        }
                    }else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                        if ((i) * 10 - j + 1 < 10) {
                            std::cout << (i) * 10 - j + 1 << "   ";
                        }else {
                            std::cout << (i) * 10 - j + 1 << "  ";
                        }
                    }
                }
                std::cout << std::endl;
                for (int j{}; j < 10; j++) {
                    if (j % 2 == 1) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                        std::cout << "    ";
                    }else {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                        std::cout << "    ";
                    }
                }
                std::cout << std::endl;
            }
        }
}

// Access functions
// Returns length of board-vector
int board::board_length() const 
{
	int board_length = board_vector.size();
	return board_length;	
}

// Returns true if board_vector element is the beginning of a ladder
bool board::is_ladder(int i) const 
{
	if (typeid(*board_vector[i]) == typeid(ladder)) {
		return true;
	}else {
		return false;
	}
}

// Returns true if board_vector element is the beginning of a snake
bool board::is_snake(int i) const 
{
	if (typeid(*board_vector[i]) == typeid(snake)) {
		return true;
	}else {
		return false;
	}
}

// Returns true if player is at the position of the board_vector element
bool board::is_player(int i, const player & p) const {
	if (p.get_position()-1 == i) {
		return true;
	}else {
		return false;
	}
}

// Returns true is opponent is at the position of the board_vector element
bool board::is_opponent(int i, const opponent& o)const 
{
	if (o.get_position()-1 == i) {
		return true;
	}else {
		return false;
	}
}

// Returns length of snake or ladder at board_vector element
int board::length(int i) const 
{
	return board_vector[i]->get_length();
}
