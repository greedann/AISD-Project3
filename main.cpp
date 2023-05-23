#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

class GipfEngine
{
    // size, number of pieces to trigger collection, number of white pieces, number of black pieces
    int parameters[4];
    // board representation
    vector<vector<int>> board;

public:
    enum field
    {
        empty,
        white,
        black,
    };

    GipfEngine(int size, int collection, int white, int black)
    {
        size++;
        parameters[0] = size;
        parameters[1] = collection;
        parameters[2] = white;
        parameters[3] = black;
        for (int i = 0; i < size * 2 - 1; i++)
        {
            board.push_back(vector<int>());
            for (int j = 0; j < size; j++)
            {
                board[i].push_back(0);
            }
            if (i < parameters[0] - 1)
            {
                size++;
            }
            else
            {
                size--;
            }
        }
    }

    void resize(int size)
    {
        size++;
        parameters[0] = size;
        board.clear();
        for (int i = 0; i < (size * 2) - 1; i++)
        {
            board.push_back(vector<int>());
            for (int j = 0; j < size; j++)
            {
                board[i].push_back(0);
            }
            if (i < parameters[0] - 1)
            {
                size++;
            }
            else
            {
                size--;
            }
        }
    }

    void set(char sumbol, int num, field value)
    {
        int x = static_cast<int>(sumbol) - 97;
        int y = num - 1;
        if (x < 0 || x > this->size() * 2 - 1 || y < 0 || y >= board[x].size())
        {
            cout << "Invalid coordinates" << endl;
            return;
        }
        board[x][y] = value;
    }

    int size(bool borders = false)
    {
        if (borders)
        {
            return parameters[0];
        }
        return parameters[0] - 1;
    }

    bool is_border(int x, int y)
    {

        return x == 0 or x == board.size() - 1 or y == 0 or y == board[x].size() - 1;
    }

    void printBoard(bool borders = false)
    {
        int end_y = this->size() * 2 - 2, end_x = this->size() - 1;
        for (int row = 0; row < this->size() * 2 - 1; row++)
        {
            for (int i = 0; i < abs(this->size() - row - 1); i++)
            {
                cout << " ";
            }
            int start_y = max(0, this->size() - row - 1);
            int start_x = max(0, row - this->size() + 1);

            for (int x = start_x; x <= end_x; x++)
            {
                // char character = static_cast<char>(x+97);
                // cout << character << start_y+1 << " ";
                // if (borders and is_border(x, start_y))
                // {
                //     cout << "+ ";
                // }

                switch (board[x+1][start_y+1])
                {
                case empty:
                    cout << "_ ";
                    break;
                case white:
                    cout << "W ";
                    break;
                case black:
                    cout << "B ";
                    break;
                }
                if (start_y < end_y)
                {
                    start_y++;
                }
            }

            cout << endl;
            if (row < this->size() - 1)
            {
                end_x++;
            }
            end_y--;
        }
    }

    void scanBoard()
    {
        bool correct_len = true;
        int black, white, len = 0;
        char symbol, turn;
        string input;
        cin >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
        this->resize(parameters[0]);
        cin >> white >> black >> turn;
        int end_y = this->size() * 2 - 2, end_x = this->size() - 1;
        getline(cin, input);
        for (int row = 0; row < this->size() * 2 - 1; row++)
        {
            int start_y = max(0, this->size() - row - 1);
            int start_x = max(0, row - this->size() + 1);

            getline(cin, input);
            len = 0;
            for (int i = 0; i < input.length(); i++)
            {
                if (input[i] != ' ')
                {
                    len++;
                }
            }
            if (len != end_x - start_x + 1)
            {
                correct_len = false;
            }
            if (!correct_len)
            {
                continue;
            }
            int current_x = 0;
            for (int x = start_x; x <= end_x; x++)
            {
                while (input[current_x] == ' ')
                {
                    current_x++;
                }
                symbol = input[current_x];
                current_x++;
                switch (symbol)
                {
                case '_':
                    board[x+1][start_y+1] = empty;
                    break;
                case 'W':
                    board[x+1][start_y+1] = field::white;
                    white++;
                    break;
                case 'B':
                    board[x][start_y] = field::black;
                    black++;
                    break;
                }
                if (start_y < end_y)
                {
                    start_y++;
                }
            }

            // for (int x = start_x; x <= end_x; x++)
            // {
            //     // char character = static_cast<char>(x+97);
            //     // cout << character << start_y+1 << " ";
            //     cin >> symbol;
            //     switch (symbol)
            //     {
            //     case '_':
            //         board[x][start_y] = empty;
            //         break;
            //     case 'W':
            //         board[x][start_y] = field::white;
            //         white++;
            //         break;
            //     case 'B':
            //         board[x][start_y] = field::black;
            //         black++;
            //         break;
            //     }
            //     if (start_y < end_y)
            //     {
            //         start_y++;
            //     }
            // }
            if (row < this->size() - 1)
            {
                end_x++;
            }
            end_y--;
        }
        if (!correct_len)
        {
            cout << "WRONG_BOARD_ROW_LENGTH" << endl;
            return;
        }
        if (white != parameters[2])
        {
            cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
            return;
        }
        if (black != parameters[3])
        {
            cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
            return;
        }

        cout << "BOARD_STATE_OK" << endl;
    }

    void doMove(int from_x, int from_y, int to_x, int to_y)
    {
        cout << from_x << " " << from_y << " " << to_x << " " << to_y << endl;
        if (from_x < 0 || from_x >= board.size() || from_y < 0 || from_y >= this->board[from_x].size())
        {
            char character = static_cast<char>(from_x + 97);
            cout << "BAD_MOVE_" << character << from_y + 1 << "_IS_WRONG_INDEX" << endl;
            return;
        }
        if (to_x < 0 || to_x >= board.size() || to_y < 0 || to_y >= this->board[to_x].size())
        {
            char character = static_cast<char>(to_x + 97);
            cout << "BAD_MOVE_" << character << to_y + 1 << "_IS_WRONG_INDEX" << endl;
            return;
        }
    }

    void _test()
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main(int, char **)
{
    string input;
    GipfEngine gipf(4, 4, 15, 15);

    while (cin >> input)
    {
        if (input == "LOAD_GAME_BOARD")
        {
            gipf.scanBoard();
        }
        else if (input == "DO_MOVE")
        {
            int from_x, from_y, to_x, to_y;
            cin >> input;
            from_x = input[0] - 97;
            from_y = input[1] - 49;
            to_x = input[3] - 97;
            to_y = input[4] - 49;
            gipf.doMove(from_x, from_y, to_x, to_y);
        }
    }
}
