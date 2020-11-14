//start_screen.cpp
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <utility>
#include "start_screen.h"
#include "counter.h"

// Member functions for start_screen

// Constructor
start_screen::start_screen() : player_pair{ std::make_pair(player(""),opponent()) }, multiplayer_pair{ std::make_pair(player(""), player("")) }, game_mode{ 0 }{}

// Print functions
// Prints header in ascii characters
void start_screen::print_header() 
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,10 });
    std::cout << "                  _                               _   _           _     _              " << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,11 });
    std::cout << "  ___ _ __   __ _| | _____  ___    __ _ _ __   __| | | | __ _  __| | __| | ___ _ __ ___ " << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,12 });
    std::cout << " / __| '_ \\ / _` | |/ / _ \\/ __|  / _` | '_ \\ / _` | | |/ _` |/ _` |/ _` |/ _ \\ '__/ __|" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,13 });
    std::cout << " \\__ \\ | | | (_| |   <  __/\\__ \\ | (_| | | | | (_| | | | (_| | (_| | (_| |  __/ |  \\__ \\" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 17,14 });
    std::cout << " |___/_| |_|\\__,_|_|\\_\\___||___/  \\__,_|_| |_|\\__,_| |_|\\__,_|\\__,_|\\__,_|\\___|_|  |___/" << std::endl;
    std::cout << std::endl;
}

// Prints snake in scii characters
// Takes in coordinates and colour
void start_screen::print_snake_ascii(SHORT x, SHORT y, int colour) 
{
    COORD pos{ x,y };
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    std::cout << "   oo_    " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 1 });
    std::cout << "  /  _)-< " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 2 });
    std::cout << "  \__ `.  " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 3 });
    std::cout << "     `. | " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 4 });
    std::cout << "     _| | " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 5 });
    std::cout << "  ,-'   | " << std::endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 6 });
    std::cout << " (_..--'  " << std::endl;
}

// Prints ladder in ascii characters
// Takes in coordinates, colour and shadow colour
void start_screen::print_ladder_ascii(SHORT x, SHORT y, int colour, int shadow) 
{
    COORD pos{ x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y });
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    std::cout << "|____|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/____/ " << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 1 });
    std::cout << "|____"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/____/" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 2 });
    std::cout << "|___"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour); std::cout << "|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "___/" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 3 });
    std::cout << "|__"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour); std::cout << "_|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "__/" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 4 });
    std::cout << "|_"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour); std::cout << "__|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "_/" << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ x, y + 5 });
    std::cout << "|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour); std::cout << "___|"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shadow); std::cout << "/" << std::endl;
}

// Access functions

// Gets player information
// Sets game_mode
// Constructs players and opponents
bool start_screen::get_players() 
{
    // Checks for valid input
    bool valid_input = false;
    while (!valid_input) {
        std::string  number_of_players_string;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 37,18 });
        std::cout << "\33[2K";
        std::cout << "Please enter number of players (1 or 2): ";
        std::getline(std::cin, number_of_players_string);
        std::istringstream number_of_players_stream;
        int number_of_players;
        number_of_players_stream.str(number_of_players_string);
        number_of_players_stream >> number_of_players;
        // If fails, continue with loop
        if (number_of_players_stream.fail()) continue;
        if (number_of_players == 1 || number_of_players == 2) {
            // If valid input
            if (number_of_players == 1) {
                // Single player game
                // Prints message, allows player to enter name
                std::string set_name;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 37,18 });
                std::cout << "Please enter your name and press enter to continue." << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 59,19 });
                std::getline(std::cin, set_name);
                // Constructs player with inputted name
                player p1(set_name);
                // Constructs opponent
                opponent o1;
                // Makes opponent and player pair
                player_pair = std::make_pair(p1, o1);
                // Returns game_mode 0, a single player game
                return game_mode = 0;
            }else {
                // Multiplayer game
                // Prints message, allows both players to input names
                std::string set_name_1;
                std::string set_name_2;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 30,18 });
                std::cout << "Player one, please enter your name and press enter to continue." << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 57,19 });
                std::getline(std::cin, set_name_1);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 30,20 });
                std::cout << "Player two, please enter your name and press enter to continue." << std::endl;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 57,21 });
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::getline(std::cin, set_name_2);

                // Constructs two players with inputted names
                player p1(set_name_1);
                player p2(set_name_2);
                // Makes player player pair
                multiplayer_pair= std::make_pair(p1, p2);
                // Returns game_mode 1, multiplayer game
                return game_mode = 1;
            }
            
            valid_input = true;
        }else {
            continue;
        }
    }
    
}

// Returns player opponent pair
std::pair <player, opponent> start_screen::get_player_pair() 
{
    return player_pair;
}

// Returns player player pair
std::pair <player, player> start_screen::get_multiplayer_pair() 
{
    return multiplayer_pair;
}

                           