#include "gipfengine.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input;
    GipfEngine gipf(2, 4, 15, 15);

    while (getline(cin, input))
    {
        if (input == "LOAD_GAME_BOARD")
        {
            gipf.scanBoard();
        }
        else if (input.find("DO_MOVE") != string::npos)
        {
            int from_x, from_y, to_x, to_y;
            bool success;
            from_x = input[8] - 97;
            from_y = input[9] - 49;
            to_x = input[11] - 97;
            to_y = input[12] - 49;
            Move move(from_x, from_y, to_x, to_y);
            success = gipf.doMove(move);
            if (input.find(':') != string::npos)
            {
                char color = input[14] - 32;
                from_x = input[17] - 97;
                from_y = input[18] - 49;
                to_x = input[20] - 97;
                to_y = input[21] - 49;
                success = gipf.priority_erase(from_x, from_y, to_x, to_y, color);
            }
            if (success)
            {
                cout << "MOVE_COMMITTED" << endl;
            }
            gipf.count_sequence(true);
        }
        else if (input == "PRINT_GAME_BOARD")
        {
            gipf.printBoard();
        }
        else if (input == "GEN_ALL_POS_MOV_NUM")
        {
            cout << gipf.count_posible_moves() << "_UNIQUE_MOVES" << endl;
        }
        else if (input == "GEN_ALL_POS_MOV")
        {
            gipf.count_posible_moves(false, true);
        }
        else if (input == "GEN_ALL_POS_MOV_EXT_NUM")
        {
            cout << gipf.count_posible_moves(true) << "_UNIQUE_MOVES" << endl;
        }
        else if (input == "GEN_ALL_POS_MOV_EXT")
        {
            gipf.count_posible_moves(true, true);
        }
        else if (input == "IS_GAME_OVER")
        {
            if (gipf.is_game_over())
            {
                cout << "THE_WINNER_IS_" << gipf.get_winner() << endl;
            }
            else
            {
                cout << "GAME_IN_PROGRESS" << endl;
            }
        }
        cout << endl;
    }
}
