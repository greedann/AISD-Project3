#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Move
{
    int from_x, from_y, to_x, to_y;
    Move(int from_x, int from_y, int to_x, int to_y) : from_x(from_x), from_y(from_y), to_x(to_x), to_y(to_y) {}
};

class GipfEngine
{
private:
    enum field
    {
        empty,
        white,
        black,
    };

    enum direction
    {
        up_right,
        right,
        down_right,
        down_left,
        left,
        up_left,
    };

    // size, number of pieces to trigger collection, number of white pieces, number of black pieces
    int parameters[4];
    int black_reserve, white_reserve;
    char turn;
    bool is_empty = true;
    vector<vector<field>> board;

    bool move_stones(int x, int y, direction direction, field stone);

    void take_off(int x, int y, direction direction);

    direction get_direction(int from_x, int from_y, int to_x, int to_y);

    void erase(int x, int y, direction direction);

    bool is_sequence(int x, int y, direction direction, field prev_field, int white_len = 0, int black_len = 0);

    vector<Move> get_moves();

    int *move(int x, int y, direction direction);

    void resize(int size);

    void set(char sumbol, int num, field value);

    int size(bool borders = false) const;

    bool is_border(int x, int y);

    bool is_neardy(int x1, int y1, int x2, int y2);

public:
    GipfEngine(int size, int collection, int white, int black);

    void printBoard();

    void scanBoard();

    int count_sequence(bool to_take_off = false, int to_ignore = 1);

    bool doMove(Move move, bool to_print = true);

    bool priority_erase(int from_x, int from_y, int to_x, int to_y, char color);

    bool is_game_over();

    string get_winner() const;

    int count_posible_moves(bool check_is_game_over = false, bool print_moves = false);
};