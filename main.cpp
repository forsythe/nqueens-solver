#include <iostream>
#include <random>
#include <vector>
#include <chrono>


#include "Board.h"

using namespace std;

int main()
{
    int input;
    cout << "Enter size of board:" << endl;
    cin >> input;

    if (input <= 3){
        cout << "Board size must be >= 4" << endl;
        return -1;
    }

    Board* b = new Board(input);

    auto begin = std::chrono::high_resolution_clock::now();
    b -> solve();
    auto end = std::chrono::high_resolution_clock::now();

    if(input < 300){
        b -> printBoard();
    } else {
        cout << "Solution found, but printing out board will take a while. Proceed? (Y/N)" << endl;
        string choice;
        cin >> choice;
        if (choice=="Y")
            b -> printBoard();
    }
    delete b;
    cout << "Solved in " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1000000000.0 << "s";
    return 0;
}
