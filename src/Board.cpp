#include "Board.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>


using namespace std;

Board::Board(int n_rhs)
{
    queen_row_pos = new int[n_rhs];
    num_collisions = new int[n_rhs];

    num_queens = n_rhs;

    for (int k = 0; k < num_queens; k++)
        queen_row_pos[k] = k;


    for (int k = 0; k < num_queens; k++)
        num_collisions[k] = getNumCollisions(k);
}

Board::~Board()
{
    delete[] queen_row_pos;
    delete[] num_collisions;
}

void Board::printBoard()
{
    for (int r = 0; r < num_queens; r++){
        for (int c = 0; c < num_queens; c++){
            if (r == queen_row_pos[c]) cout << "Q|";
            else cout << "_|";
        }
        cout << endl;
    }
}

bool Board::isComplete()
{
    for (int k = 0; k < num_queens; k++)
        if (num_collisions[k] != 0)
            return false;
    return true;
}

void Board::swapCol(int a, int b)
{
    int temp = queen_row_pos[a];
    queen_row_pos[a] = queen_row_pos[b];
    queen_row_pos[b] = temp;
}

void Board::updateAllCollisions()
{
    for (int k = 0; k < num_queens; k++)
        num_collisions[k] = getNumCollisions(k);
}

//Should be called after updateAllCollisions() is called
int Board::getBadCol()
{
    vector<int> cols_with_collisions;

    for (int k = 0; k < num_queens; k++)
        if (num_collisions[k] > 0)
            cols_with_collisions.push_back(k);

    return cols_with_collisions[rand()%cols_with_collisions.size()];
}

int Board::getNumCollisions(int q_col)
{
    int num_colls = 0;

    for (int k = 0; k < q_col; k++)
        if (queen_row_pos[k] - queen_row_pos[q_col] == k - q_col || queen_row_pos[k] - queen_row_pos[q_col] == q_col - k)
                num_colls++;

    for (int k = q_col + 1; k < num_queens; k++)
        if (queen_row_pos[k] - queen_row_pos[q_col] == k - q_col || queen_row_pos[k] - queen_row_pos[q_col] == q_col - k)
                num_colls++;

    return num_colls;
}

int Board::getTotalNumCollisions()
{
    int sum = 0;
    for (int k = 0; k < num_queens; k++){
        sum += num_collisions[k];
    }
    return sum;
}

void Board::swapIfGood(int a, int b)
{
    int sum_orig = num_collisions[a] + num_collisions[b];
    swapCol(a, b);
    int sum_new = getNumCollisions(a) + getNumCollisions(b);

    if (sum_new > sum_orig && rand()%10000 > 1){
        swapCol(a, b);
    }
}

void Board::solve()
{
    srand(time(NULL));
    int wrst_col, rnd_col;

    while (!isComplete()){
        //printBoard();
        //cout << endl;
        wrst_col = getBadCol();
        //cout << "bad col: " << wrst_col;

        do rnd_col = rand() % (num_queens-1);
        while (rnd_col == wrst_col);
        //cout << ", rnd col: " << rnd_col << endl;

        swapIfGood(rnd_col, wrst_col);
        updateAllCollisions();
    }
}
