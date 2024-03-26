# Study project
## The subject of algorithms and data structures

The goal of the project is to write an application that will represent an engine for the gipf game.

More information about rules can be found in the rules.txt file

The solution was written in OOP style

The engine for the game is implemented as a class and independently performs all actions in the game. The functions are available to the user to perform actions. To perform a move, the user needs to call the appropriate function and pass the `Move` parameter with the appropriate values to it. The engine allows you to perform the following actions:
* Read game state
* Print current board
* Count all posible moves and optionally print them
* Make a move
* Check if there is a winner and which player it is


## Launching

The project was written in C++ language and uses CMake for building. To build the project, you need to have CMake installed on your computer

After compilation, you can run the application and test it by typing into the console according to the rules described in the rules.txt file. There is also a set of tests in the tests directory. To run them you can pass them as standard input to the program. By default, in the project root directory execute the command:
```bash
$ build/aisd-3 < tests/<test_number>.in
```
And result will be displayed in console. You can check the correctness of the work by comparing the obtained output with the sample output in the files in the directory tests