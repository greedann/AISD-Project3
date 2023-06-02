#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

class GipfEngine
{
    // size, number of pieces to trigger collection, number of white pieces, number of black pieces
    int parameters[4];
    int black_reserve, white_reserve;
    char turn;
    bool is_empty = true;
    // board representation

public:
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

private:
    vector<vector<field>> board;

public:
    GipfEngine(int size, int collection, int white, int black)
    {
        size++;
        parameters[0] = size;
        parameters[1] = collection;
        parameters[2] = white;
        parameters[3] = black;
        black_reserve = white_reserve = collection;
        turn = 'W';
        for (int i = 0; i < size * 2 - 1; i++)
        {
            board.push_back(vector<field>());
            for (int j = 0; j < size; j++)
            {
                board[i].push_back(field::empty);
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

    int *move(int x, int y, direction direction)
    {
        if (x >= this->size())
        {
            if (direction == down_right or direction == right)
            {
                y--;
            }
            else if ((direction == left and x != this->size()) or (direction == up_left and x != this->size()))
            {
                y++;
            }
        }
        switch (direction)
        {
        case up_right:
            y++;
            break;
        case right:
            x++;
            y++;
            break;
        case down_right:
            x++;
            break;
        case down_left:
            y--;
            break;
        case left:
            x--;
            y--;
            break;
        case up_left:
            x--;
            break;
        }
        return new int[2]{x, y};
    }

    void resize(int size)
    {
        size++;
        parameters[0] = size;
        board.clear();
        for (int i = 0; i < (size * 2) - 1; i++)
        {
            board.push_back(vector<field>());
            for (int j = 0; j < size; j++)
            {
                board[i].push_back(field::empty);
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

    int size(bool borders = false) const
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

    bool is_neardy(int x1, int y1, int x2, int y2)
    {
        if (x1 == x2 and abs(y1 - y2) == 1)
        {
            return true;
        }
        if (abs(x1 - x2) == 1)
        {
            if (y1 == y2)
            {
                return true;
            }
            else if (x1 == this->size())
            {
                // dioganal check
                if (y1 == y2 + 1)
                {
                    return true;
                }
                return false;
            }
            else if (x1 < this->size())
            {
                // left border
                if (y2 == y1 + (x2 - x1))
                {
                    return true;
                }
                return false;
            }
            else
            {
                // right border
                if (y2 == y1 - (x2 - x1))
                {
                    return true;
                }
                return false;
            }
        }
        return false;
    }

    void printBoard()
    {
        if (is_empty)
        {
            cout << "EMPTY_BOARD" << endl;
            return;
        }
        cout << this->size() << " " << parameters[1] << " " << parameters[2] << " " << parameters[3] << endl;
        cout << white_reserve << " " << black_reserve << " " << turn << endl;
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
                switch (board[x + 1][start_y + 1])
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
        is_empty = true;
        bool correct_len = true;
        char symbol;
        string input;
        cin >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
        this->resize(parameters[0]);
        cin >> white_reserve >> black_reserve >> turn;
        int white_count = white_reserve, black_count = black_reserve;
        int end_y = this->size() * 2 - 2, end_x = this->size() - 1;
        getline(cin, input);
        for (int row = 0; row < this->size() * 2 - 1; row++)
        {
            int start_y = max(0, this->size() - row - 1);
            int start_x = max(0, row - this->size() + 1);
            getline(cin, input);
            int len = 0;
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
                    board[x + 1][start_y + 1] = empty;
                    break;
                case 'W':
                    board[x + 1][start_y + 1] = field::white;
                    white_count++;
                    break;
                case 'B':
                    board[x + 1][start_y + 1] = field::black;
                    black_count++;
                    break;
                }
                if (start_y < end_y)
                {
                    start_y++;
                }
            }
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
        if (white_count > parameters[2])
        {
            cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
            return;
        }
        if (black_count > parameters[3])
        {
            cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
            return;
        }
        int sequenses = this->count_sequence();
        if (sequenses != 0)
        {
            cout << "ERROR_FOUND_" << sequenses;
            if (sequenses > 1)
            {
                cout << "_ROWS_OF_LENGTH_K" << endl;
            }
            else
            {
                cout << "_ROW_OF_LENGTH_K" << endl;
            }
            return;
        }
        is_empty = false;
        cout << "BOARD_STATE_OK" << endl;
    }

    bool is_sequence(int x, int y, direction direction, field prev_field, int white_len = 0, int black_len = 0)
    {
        // char character = static_cast<char>(x + 97);
        // cout << character << y + 1 << " " << white_len << " " << black_len << endl;
        if (black_len >= parameters[1] or white_len >= parameters[1])
        {
            return true;
        }
        if (is_border(x, y))
        {
            return false;
        }
        if (board[x][y] == prev_field)
        {
            if (board[x][y] == field::white)
            {
                white_len++;
            }
            else if (board[x][y] == field::black)
            {
                black_len++;
            }
        }
        else
        {
            white_len = 1;
            black_len = 1;
        }
        int *new_pos = move(x, y, direction);
        int new_x = new_pos[0], new_y = new_pos[1];
        delete[] new_pos;
        return is_sequence(new_x, new_y, direction, board[x][y], white_len, black_len);
    }

    direction get_direction(int from_x, int from_y, int to_x, int to_y)
    {
        int *new_pos;
        if (is_neardy(from_x, from_y, to_x, to_y))
        {
            for (int i = 0; i < 6; i++)
            {
                new_pos = move(from_x, from_y, (direction)i);
                if (new_pos[0] == to_x && new_pos[1] == to_y)
                {
                    delete[] new_pos;
                    return (direction)i;
                }
                delete[] new_pos;
            }
        }
        else
        {
            for (int i = 0; i < 6; i++)
            {
                int current_x = from_x, current_y = from_y;
                while (!is_border(current_x, current_y))
                {
                    if (current_x == to_x && current_y == to_y)
                    {
                        return (direction)i;
                    }
                    new_pos = move(current_x, current_y, (direction)i);
                    current_x = new_pos[0];
                    current_y = new_pos[1];
                    delete[] new_pos;
                }
            }
        }
        throw "Wrong direction";
    }

    void erase(int x, int y, direction direction)
    {
        int *new_pos;
        while (!is_border(x, y))
        {
            // cout << "ERASE " << static_cast<char>(x + 97) << y + 1 << endl;
            new_pos = move(x, y, direction);
            x = new_pos[0];
            y = new_pos[1];
            delete[] new_pos;
            if (board[x][y] == field::empty)
            {
                break;
            }
            board[x][y] = field::empty;
        }
    }

    void take_off(int x, int y, direction direction)
    {
        queue<pair<int, int>> q;
        field prev_field = board[x][y];
        int *new_pos;
        while (!is_border(x, y))
        {
            if (board[x][y] == prev_field)
            {
                q.push(make_pair(x, y));
            }
            else
            {
                if (q.size() >= parameters[1])
                {
                    int _x = q.front().first, _y = q.front().second;
                    int opposite_direction = (((int)direction) + 3) % 6;
                    this->erase(_x, _y, (GipfEngine::direction)opposite_direction);
                    this->erase(q.back().first, q.back().second, direction);
                    while (!q.empty())
                    {
                        _x = q.front().first, _y = q.front().second;
                        if (board[_x][_y] == field::white)
                        {
                            white_reserve++;
                            // cout << "add points " << static_cast<char>(_x + 97) << _y + 1 << endl;
                        }
                        else if (board[_x][_y] == field::black)
                        {
                            black_reserve++;
                        }
                        board[_x][_y] = field::empty;
                        q.pop();
                    }
                }
                else
                {
                    while (!q.empty())
                    {
                        q.pop();
                    }
                    q.push(make_pair(x, y));
                }
            }
            prev_field = board[x][y];
            new_pos = move(x, y, direction);
            x = new_pos[0];
            y = new_pos[1];
            delete[] new_pos;
        }
        if (q.size() >= parameters[1])
        {
            int _x = q.front().first, _y = q.front().second;
            int opposite_direction = (((int)direction) + 3) % 6;
            this->erase(_x, _y, (GipfEngine::direction)opposite_direction);
            this->erase(q.back().first, q.back().second, direction);
            while (!q.empty())
            {
                _x = q.front().first, _y = q.front().second;
                if (board[_x][_y] == field::white)
                {
                    white_reserve++;
                    // cout << "add points " << static_cast<char>(_x + 97) << _y + 1 << endl;
                }
                else if (board[_x][_y] == field::black)
                {
                    black_reserve++;
                }
                board[_x][_y] = field::empty;
                q.pop();
            }
        }
    }

    int count_sequence(bool to_take_off = false)
    {
        int count = 0;
        for (int i = 0; i < 3; i++)
        {
            if (is_sequence(1, 1, (direction)i, board[1][1]))
            {
                count++;
                if (to_take_off)
                {
                    take_off(1, 1, (direction)i);
                }
            }
        }
        // left up diagonal
        for (int y = 2; y < board[1].size() - 1; y++)
        {
            for (int i = 1; i < 3; i++)
            {
                if (is_sequence(1, y, (direction)i, board[1][y]))
                {
                    count++;
                    if (to_take_off)
                    {
                        take_off(1, y, (direction)i);
                    }
                }
            }
            // char symbol = static_cast<char>(1 + 97);
            // cout << symbol << y + 1 << endl;
        }

        int x = 2, y = board[2].size() - 2;
        while (!is_border(x, y))
        {
            // char symbol = static_cast<char>(x + 97);
            // cout << symbol << y << endl;
            if (is_sequence(x, y, down_right, board[x][y]))
            {
                count++;
                if (to_take_off)
                {
                    take_off(x, y, down_right);
                }
            }
            x++;
            y++;
        }

        for (x = 2; x < board.size() - 1; x++)
        {
            if (is_sequence(x, 1, up_right, board[x][1]))
            {
                count++;
                if (to_take_off)
                {
                    take_off(x, 1, up_right);
                }
            }
            // if (x == this->size())
            // {
            //     cout << "---------" << endl;
            // }
            // char symbol = static_cast<char>(x + 97);
            // cout << symbol << 2 << endl;
        }
        return count;
    }

    bool doMove(int from_x, int from_y, int to_x, int to_y)
    {
        // cout << from_x << " " << from_y << " " << to_x << " " << to_y << endl;
        if (from_x < 0 || from_x >= board.size() || from_y < 0 || from_y >= this->board[from_x].size())
        {
            char character = static_cast<char>(from_x + 97);
            cout << "BAD_MOVE_" << character << from_y + 1 << "_IS_WRONG_INDEX" << endl;
            return false;
        }
        if (to_x < 0 || to_x >= board.size() || to_y < 0 || to_y >= this->board[to_x].size())
        {
            char character = static_cast<char>(to_x + 97);
            cout << "BAD_MOVE_" << character << to_y + 1 << "_IS_WRONG_INDEX" << endl;
            return false;
        }
        if (!is_border(from_x, from_y))
        {
            char character = static_cast<char>(from_x + 97);
            cout << "BAD_MOVE_" << character << from_y + 1 << "_IS_WRONG_STARTING_FIELD" << endl;
            return false;
        }
        if (!is_neardy(from_x, from_y, to_x, to_y))
        {
            cout << "UNKNOWN_MOVE_DIRECTION" << endl;
            return false;
        }
        if (is_border(to_x, to_y))
        {
            char character = static_cast<char>(to_x + 97);
            cout << "BAD_MOVE_" << character << to_y + 1 << "_IS_WRONG_DESTINATION_FIELD" << endl;
            return false;
        }
        direction direction = get_direction(from_x, from_y, to_x, to_y);
        switch (turn)
        {
        case 'B':
            if (this->move_stones(to_x, to_y, direction, field::black))
            {
                black_reserve--;
                turn = 'W';
            }
            else
            {
                cout << "BAD_MOVE_ROW_IS_FULL" << endl;
                return false;
            }
            break;
        case 'W':
            if (this->move_stones(to_x, to_y, direction, field::white))
            {
                white_reserve--;
                turn = 'B';
            }
            else
            {
                cout << "BAD_MOVE_ROW_IS_FULL" << endl;
                return false;
            }
            break;
        }
        return true;
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

    bool move_stones(int x, int y, direction direction, field stone)
    {
        if (is_border(x, y))
        {
            return false;
        }
        if (board[x][y] == field::empty)
        {
            board[x][y] = stone;
            return true;
        }
        else
        {
            int *new_coords = move(x, y, direction);
            int new_x = new_coords[0];
            int new_y = new_coords[1];
            delete[] new_coords;
            if (move_stones(new_x, new_y, direction, board[x][y]))
            {
                board[x][y] = stone;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool priority_erase(int from_x, int from_y, int to_x, int to_y, char color)
    {
        field stone = (color == 'B') ? field::black : field::white;
        if (board[from_x][from_y] != stone or board[to_x][to_y] != stone)
        {
            cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
            return false;
        }
        if (is_neardy(from_x, from_y, to_x, to_y))
        {
            cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
            return false;
        }
        direction dir = get_direction(from_x, from_y, to_x, to_y);
        take_off(from_x, from_y, dir);        
        return true;
    }
};

int main(int, char **)
{
    string input;
    GipfEngine gipf(4, 4, 15, 15);

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
            // cin >> input;
            from_x = input[8] - 97;
            from_y = input[9] - 49;
            to_x = input[11] - 97;
            to_y = input[12] - 49;
            success = gipf.doMove(from_x, from_y, to_x, to_y);
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
        cout << endl;
    }
}
