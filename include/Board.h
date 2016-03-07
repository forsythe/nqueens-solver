#ifndef BOARD_H
#define BOARD_H


class Board
{
    public:
        explicit Board(int);
        ~Board();
        void printBoard();
        void solve();

    protected:

    private:
        int num_queens;
        int* queen_row_pos; //Index is col pos, value is row pos
        int* num_collisions;

        int getNumCollisions(int); //Only need to calculate diagonal, row & col already satisfied
        void updateAllCollisions();
        int getTotalNumCollisions();
        int getBadCol();
        void swapIfGood(int, int);
        void swapCol(int, int);
        bool isComplete();


};

#endif // BOARD_H
