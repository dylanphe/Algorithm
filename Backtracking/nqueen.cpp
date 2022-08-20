#include <iostream>

using namespace std; 

class chess
{
private:
    int Q = 3;
    int N = 4;
    int* board[];;
public:
    chess();
    void printBoard();

    //Methods needed for solving nQueen
    bool isSafe(int i, int j);
    bool solveNQUtil(int src);
    void nQueen();
};

chess::chess()
{
    for (int i = 0; i < N; i++)
    {
        board[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }
}

void chess::printBoard()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j< N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

//Bounding function
bool chess::isSafe(int i, int j)
{
    //Check for row exclusitivity 
    for (int row = 0; row < N; row++)
    {
        if (row != i && board[row][j] == 1)
        {
            return false;
        }
    }

    //Exclusive column is already guarded by the the loop

    //Check for top-left diagonal
    for (int row = i-1, col = j-1; row >= 0 && col >= 0; row--, col--)
    {
        if (row >= 0 && col >= 0 && board[row][col] == 1)
        {
            return false;
        }
    }

    //Check for top-right diagonal
    for (int row = i-1, col = j+1; row >= 0 && col < N; row--, col++)
    {
        if (row >= 0 && col < N && board[row][col] == 1)
        {
            return false;
        }
    }

    //Bottom-left and right are guarded due to the queen being placed row by row.

    return true;
}

bool chess::solveNQUtil(int row)
{
    bool solved = 0;
    //If all queen are placed, print the answer
    if (row >= Q)
    {
        solved = true;
        printBoard();
        cout << endl;
        return solved;
    }

    //For each row, try out all columns
    for (int col = 0; col < N; col++)
    {
        //If the queen pass bonding function
        if (isSafe(row, col))
        {
            //Place the queen
            board[row][col] = 1;
            //Continue to place the next queen
            if (solveNQUtil(row + 1))
            {
                solved = true;
            }
            //Backtrack afterward to the next column
            board[row][col] = 0;
        }
    }
    return solved;
}

void chess::nQueen()
{   
    //If it returns false, there is no solution.
    if (!solveNQUtil(0))
    {
        cout << "No Solution!" << endl;
    }
}

int main()
{
    chess board;
    //board.printBoard();
    board.nQueen();
    return 0;
}