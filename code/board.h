//board.h
//header file containing the snake and ladders board class
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include "counter.h"
#include "piece.h"

class opponent;
class player;

class board {

private:
    // Vector of base class shared pointers
    std::vector<std::shared_ptr<tile>> board_vector;

public:
    // Constructors
    board();
    //Print functions
    COORD get_tile_coords(int array_pos) const;
    void print_fancy();
    void print_snake() const;
    void print_ladder() const;
    int board_length() const;
    // Access functions
    bool is_ladder(int i) const;
    bool is_snake(int i) const;
    bool is_player(int i, const player& p) const;
    bool is_opponent(int i, const opponent& o) const;
    int length(int i) const;



    // Template functions
    // Prints counters for players or opponents, prints blank spaces to erase previous counter position
    template <class P, class Q> void print_players(const P& p, const Q& q, SHORT a, SHORT b, SHORT c, SHORT d)
    {
        // Sets console cursor position
        // Sets console text colour
        // Prints player one name versus player two name
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 45,0 });
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << p.get_name() << " '";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        std::cout << p.get_name()[0];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << "' versus " << q.get_name() << " '";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        std::cout << q.get_name()[0];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        std::cout << "'";

        // If players on board
        if (p.get_previous_position() != -1) {
            // If counters on board, prints blank space over previous position of counter
            // Get printing coordinates of previous position of counters 
            COORD previous_p_pos = get_tile_coords(p.get_previous_position());
            COORD previous_q_pos = get_tile_coords(q.get_previous_position());
            // Edit coordinates within single tile
            previous_p_pos.X += a;
            previous_p_pos.Y += b;
            previous_q_pos.X += c;
            previous_q_pos.Y += d;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), previous_p_pos);
            // Print in 188 if even tile, print in 156 if odd tile
            if (p.get_previous_position() % 2 == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                std::cout << " ";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                std::cout << " ";
            }
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), previous_q_pos);
            if (q.get_previous_position() % 2 == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 188);
                std::cout << " ";
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 156);
                std::cout << " ";
            }
        }
        // Prints representation of counter at position on the board
        // Get printing coordinates of position of counters
        COORD pos_p = get_tile_coords(p.get_position() - 1);
        COORD pos_q = get_tile_coords(q.get_position() - 1);
        // Edit coordinates within single tile
        pos_p.X += a;
        pos_p.Y += b;
        pos_q.X += c;
        pos_q.Y += d;
        // Get first letter of player name, print at coordinate position
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos_p);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        std::cout << p.get_name()[0];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos_q);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        std::cout << q.get_name()[0];
    }

    // Prints the values of the previous 20 rolls for players or opponents
    template < class P, class Q> void print_roll_values(const P& p, const Q& q, SHORT x, SHORT y) const
    {
        // For class P
        std::vector<int> print_p_roll = p.get_roll_values();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 45,(1 + x) });
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        std::cout << p.get_name() << " rolls: ";
        // Iterator to print out first 20 values
        if (print_p_roll.size() < 20) {
            for (auto it = print_p_roll.begin(); it != print_p_roll.end(); it++) {
                std::cout << *it << " ";
            }
        }
        // Iterator to print out last 20 rolls
        else {
            for (auto it = print_p_roll.end() - 20; it != print_p_roll.end(); it++) {
                std::cout << *it << " ";
            }
        }

        // For class Q
        std::vector<int> print_q_roll = q.get_roll_values();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 45, 1 + y });
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        std::cout << q.get_name() << " rolls: ";
        // Iterator to print out first 20 rolls
        if (print_q_roll.size() < 20) {
            for (auto it = print_q_roll.begin(); it != print_q_roll.end(); it++) {
                std::cout << *it << " ";
            }
        }
        // Iterator to print out last 20 rolls
        else {
            for (auto it = print_q_roll.end() - 20; it != print_q_roll.end(); it++) {
                std::cout << *it << " ";
            }
        }
    }
};

#endif