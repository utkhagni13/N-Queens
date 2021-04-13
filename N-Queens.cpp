#include <bits/stdc++.h>
using namespace std;

#define N 8
//state: term used to define how many queens attack each other

void configureRandomly(int board[][N], int *state) // take random board as input
{
    srand(time(0)); // seed for the random function

    for (int i = 0; i < N; i++)
    {
        state[i] = rand() % N;
        board[state[i]][i] = 1; // place queen randomly on the board
    }
}

void inputBoard(int board[][N]) // take input of the initial board
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cin >> board[i][j];
    }
}

void printBoard(int board[][N]) // print the board
{

    for (int i = 0; i < N; i++)
    {
        cout << " ";
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void printState(int *state) // print and check the state of the board
{
    for (int i = 0; i < N; i++)
    {
        cout << " " << state[i] << " ";
    }
    cout << endl;
}

bool compareStates(int *state1, int *state2) // compares the two states(arrays)
{
    for (int i = 0; i < N; i++)
    {
        if (state1[i] != state2[i])
            return false;
    }
    return true;
}

void fill(int board[][N], int value) // fill up the board with corresponding state values
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            board[i][j] = value;
    }
}

int calculateObjective(int board[][N], int *state) // calculate the objective value of the state
{
    int attacking = 0;
    int row, col;

    // Check the states and place the queens
    for (int i = 0; i < N; i++)
    {
        row = state[i], col = i - 1;
        while (col >= 0 && board[row][col] != 1)
        {
            col--;
        }
        if (col >= 0 && board[row][col] == 1)
        {
            attacking++;
        }

        row = state[i], col = i + 1;
        while (col < N && board[row][col] != 1)
        {
            col++;
        }
        if (col < N && board[row][col] == 1)
        {
            attacking++;
        }

        row = state[i] - 1, col = i - 1;
        while (col >= 0 && row >= 0 && board[row][col] != 1)
        {
            col--;
            row--;
        }
        if (col >= 0 && row >= 0 && board[row][col] == 1)
        {
            attacking++;
        }

        row = state[i] + 1, col = i + 1;
        while (col < N && row < N && board[row][col] != 1)
        {
            col++;
            row++;
        }
        if (col < N && row < N && board[row][col] == 1)
        {
            attacking++;
        }

        row = state[i] + 1, col = i - 1;
        while (col >= 0 && row < N && board[row][col] != 1)
        {
            col--;
            row++;
        }
        if (col >= 0 && row < N && board[row][col] == 1)
        {
            attacking++;
        }

        row = state[i] - 1, col = i + 1;
        while (col < N && row >= 0 && board[row][col] != 1)
        {
            col++;
            row--;
        }
        if (col < N && row >= 0 && board[row][col] == 1)
        {
            attacking++;
        }
    }

    // return the attacking pairs
    return (int)(attacking / 2);
}

void generateBoard(int board[][N], int *state) // generate board configuration for a particular the state.
{

    fill(board, 0);
    for (int i = 0; i < N; i++)
    {
        board[state[i]][i] = 1;
    }
}

void copyState(int *state1, int *state2) //copy contents of state2 to state1.
{

    for (int i = 0; i < N; i++)
    {
        state1[i] = state2[i];
    }
}

// get the neighbour of the current state having the least objective value
// amongst all neighbours as well as the current state.
void getNeighbour(int board[][N], int *state)
{
    int opBoard[N][N];
    int opState[N];

    copyState(opState, state);
    generateBoard(opBoard, opState);

    int opObjective = calculateObjective(opBoard, opState);

    int NeighbourBoard[N][N];
    int NeighbourState[N];

    copyState(NeighbourState, state);
    generateBoard(NeighbourBoard, NeighbourState);

    // Iterating through all possible neighbours of the board.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Check to skip the current state
            if (j != state[i])
            {
                NeighbourState[i] = j;
                NeighbourBoard[NeighbourState[i]][i] = 1;
                NeighbourBoard[state[i]][i] = 0;

                int temp = calculateObjective(NeighbourBoard, NeighbourState);
                if (temp <= opObjective)
                {
                    opObjective = temp;
                    copyState(opState, NeighbourState);
                    generateBoard(opBoard, opState);
                }

                NeighbourBoard[NeighbourState[i]][i] = 0;
                NeighbourState[i] = state[i];
                NeighbourBoard[state[i]][i] = 1;
            }
        }
    }
    copyState(state, opState);
    fill(board, 0);
    generateBoard(board, state);
}

void hillClimbing(int board[][N], int *state)
{
    int neighbourBoard[N][N] = {};
    int neighbourState[N];

    copyState(neighbourState, state);
    generateBoard(neighbourBoard, neighbourState);

    do
    {
        copyState(state, neighbourState);
        generateBoard(board, state);

        getNeighbour(neighbourBoard, neighbourState);

        if (compareStates(state, neighbourState))
        {
            printBoard(board);
            break;
        }
        else if (calculateObjective(board, state) == calculateObjective(neighbourBoard, neighbourState))
        {
            // If neighbour and current are not equal but their objectives are equal
            // then jump to a random neighbour to escape it
            neighbourState[rand() % N] = rand() % N;
            generateBoard(neighbourBoard, neighbourState);
        }

    } while (true);
}

int main()
{
    char choice;
    int state[N] = {};
    int board[N][N] = {};

    cout << "\nPress 'i' to input a board / 'r' to randomly generate a board: ";
    cin >> choice;

    if (choice == 'i')
    {
        cout << "\n\nInput the board in form of a 2D Matrix..\n[1 should represent the Queen's position on the board]\n\n";
        inputBoard(board);
    }
    else
    {
        cout << "[1 represents the Queen's position on the board]\n\n";
        configureRandomly(board, state);
    }

    cout << "\nInitial state of the queens:\n";
    printBoard(board);

    cout << "\n\nFinal state of the queens:\n";
    hillClimbing(board, state);

    return 0;
}
