// Manan Patel
// 3/28/2017
// CMPSC 441
// Programming assignment 2 - Minimax

#include <time.h>
#include <algorithm>
#include <iostream>

using namespace std;

void showBoard(int ** board, int row, int column);

int checkBoard(int ** board, int row, int column, int p, int ai, int oppo);

//minimax function declaration
int minimax(int **board, int row, int column, int ai, int oppo, int P);

//mmMin function declaration
int mmMin(int **board, int row, int column, int ai, int oppo, int P);

//mmMax function declaration
int mmMax(int **board, int row, int column, int ai, int oppo, int P);

const int EMPTY = 0;



int main()

{

	int row = 0;
	int column = 0;
	int pVal = 0;
	int redo;
	int pR, pC;
	int num = 2; // 1st player or 2nd player
	int whitePieces, whiteRow, whiteColumn;
	int blackPieces, blackRow, blackColumn;
	int ai = 0;
	int oppo = 0;

	//generate random numbers

	srand((unsigned)time(NULL));


	//get user entry
	while (row < 3)
	{
		cerr << "Enter # of rows >= 3" << endl;
		cin >> row;
		cerr << endl;
	}

	while (column < 3)
	{
		cerr << "Enter # of columns >= 3" << endl;
		cin >> column;
		cerr << endl;
	}

	while (pVal < 3)
	{
		cerr << "Enter # of pieces needed to have in a line in order to win" << endl;
		cin >> pVal;
		cerr << endl;
	}

	// allocate memory for the board

	int** board = new int*[row];

	for (int i = 0; i < row; i++) {
		board[i] = new int[column];
	}

	// initialize the board to be empty
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			board[i][j] = EMPTY;
		}
	}

	// board[][] is the current state
	showBoard(board, row, column);

	//Check if AI or human goes first
	while (num < 0 || num > 1)
	{
		cerr << "enter either a 1(for AI) or 0(for human)" << endl;
		cin >> num;

		//switch turns
		if (num == 0)
		{
			oppo = 1;
			ai = 2;
		}
		else if (num == 1)
		{
			oppo = 2;
			ai = 1;
		}
	}


	cerr << "Enter the number of white peices already placed: ";
	cin >> whitePieces;
	cerr << endl;

	//get the white pieces row and column numbers and place them on the board
	for (int i = 0; i < whitePieces; i++)
	{
	
	white:
		cerr << "Enter two numbers, the row and column of the white pieces location: " << endl;
		cin >> whiteRow;
		cin >> whiteColumn;
		cerr << endl;

		if (board[whiteRow][whiteColumn] == 0)
			board[whiteRow][whiteColumn] = 1;
		else
			goto white;

	}


	cerr << "Enter the number of black peices already placed: ";
	cin >> blackPieces;
	cerr << endl;

	//get the black pieces row and column numbers and place them on the board
	for (int i = 0; i < blackPieces; i++) 
	{
	black:
		cerr << "Enter two numbers, the row and column of the black pieces location: " << endl;
		cin >> blackRow;
		cin >> blackColumn;
		cerr << endl;

		if (board[blackRow][blackColumn] == 0)
			board[blackRow][blackColumn] = 2;
		else
			goto black;
	}

	// board[][] is the current state
	showBoard(board, row, column);

	//check the board for winner
	for (int i = 0; i < row*column; i++)
	{
		if (num == 1)
		{
			cerr << "it's AI's turn" << endl;
			redo = 1;
			minimax(board, row, column, ai, oppo, pVal); // call minimax function

		}
		else if (num == 0)
		{
			cerr << "it's players's turn" << endl;
			redo = 1;
			while (redo == 1)
			{
				cerr << "Enter row and column" << endl;
				cin >> pR >> pC;
				if (board[pR][pC] == EMPTY)
				{
					board[pR][pC] = oppo;
					cerr << pR << " " << pC << endl;
					redo = 0;
					checkBoard(board, row, column, pVal, ai, oppo);
					// board[][] is the current state
					showBoard(board, row, column);
				}
				else
				{
					redo = 1;
				}
			}
		}

		//switch turns
		if (num == 1)
		{
			num = 0;
		}
		else if (num == 0)
		{
			num = 1;
		}
	}

	// deallocate memory for the board
	for (int i = 0; i < row; i++) {
		delete[] board[i];
	}

	delete[] board;
	cerr << endl;
	cout.flush();
	system("pause");
	return 0;
}




// Shows the board on the screen

void showBoard(int ** board, int row, int column)
{
	cerr << "The current board:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cerr << board[i][j] << " ";
		}
		cerr << endl;
	}
}

// Returns the current state of the board
// 1 = AI wins, -1 = opponent wins
// 0 = tie, -2 = game not finished
int checkBoard(int ** board, int row, int column, int p, int ai, int oppo)
{
	bool gameOver = false;
	int returnValue = -2;
	// check each row
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column - (p - 1); j++)
		{
			int temp = board[i][j];
			if (temp != EMPTY)
			{
				bool skip = false;
				for (int k = 1; k < p; k++)
				{
					if (temp != board[i][j + k])
					{
						skip = true;
						break;
					}
				}

				if (skip == false)
				{
					gameOver = true;
					returnValue = temp;
					break;
				}
			}
		}
		if (gameOver == true)
		{
			break;
		}
	}

	if (gameOver == false)
	{
		// check each column
		for (int i = 0; i < row - (p - 1); i++)
		{
			for (int j = 0; j < column; j++)
			{
				int temp = board[i][j];
				if (temp != EMPTY)
				{
					bool skip = false;
					for (int k = 1; k < p; k++)
					{
						if (temp != board[i + k][j])
						{
							skip = true;
							break;
						}
					}
					if (skip == false)
					{
						gameOver = true;
						returnValue = temp;
						break;
					}
				}
			}
			if (gameOver == true)
			{
				break;
			}
		}
	}

	if (gameOver == false)
	{
		// check each forward diagonal
		for (int i = 0; i < row - (p - 1); i++)
		{
			for (int j = 0; j < column - (p - 1); j++)
			{
				int temp = board[i][j];
				if (temp != EMPTY)
				{
					bool skip = false;
					for (int k = 1; k < p; k++)
					{
						if (temp != board[i + k][j + k])
						{
							skip = true;
							break;
						}
					}

					if (skip == false)
					{
						gameOver = true;
						returnValue = temp;
						break;
					}
				}
			}

			if (gameOver == true)
			{
				break;
			}
		}
	}

	if (gameOver == false)
	{
		// check each reverse diagonal
		for (int i = 0; i < row - (p - 1); i++)
		{
			for (int j = p - 1; j < column; j++)
			{
				int temp = board[i][j];
				if (temp != EMPTY)
				{
					bool skip = false;
					for (int k = 1; k < p; k++)
					{
						if (temp != board[i + k][j - k])
						{
							skip = true;
							break;
						}
					}
					if (skip == false)
					{
						gameOver = true;
						returnValue = temp;
						break;
					}
				}
			}

			if (gameOver == true)
			{
				break;
			}
		}
	}
	
	if (gameOver == true)
	{
		if (returnValue == ai) // ai is a variable with value 1 (WHITE) or 2 (BLACK), depending on what the AI is playing
		{
			return 1;
		}
		else if (returnValue == oppo) // oppo is a variable with value 1 (WHITE) or 2 (BLACK), depending on what the opponent is playing
		{
			return -1;
		}
		else
			cerr << "Return value is invalid. Something is wrong!";
	}

	// check for a tie
	int countCell = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (board[i][j] != EMPTY)
				countCell++;
		}
	}

	// board is filled, this is a tie
	if (countCell >= row * column)
	{
		return 0;
	}
	// otherwise game is not finished
	return -2;
}

int minimax(int **board, int row, int column, int ai, int oppo, int P)
{
	int curr = -9999; // best current score
	int bx = -1, by = -1; //best x and best y values
	int w = -10; //score

	//traverse through the board
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (board[i][j] == 0)
			{
				board[i][j] = ai;
				//get the min
				w = mmMin(board, row, column, ai, oppo, P);
				//if its less than the best current value
				if (w > curr)
				{
					//switch and assign new best i and j
					curr = w;
					bx = i;
					by = j;
				}
				//make the move
				board[i][j] = 0;
			}
		}
	}

	//print the coordinates
	cout << bx << " " << by << endl;
	//assign to the board and then show the board
	board[bx][by] = ai;
	showBoard(board, row, column);
	checkBoard(board, row, column, P, ai, oppo);
	return 0;
}
int mmMax(int **board, int row, int column, int ai, int oppo, int P)
{
	//check the board
	int execute = checkBoard(board, row, column, P, ai, oppo);

	int w = -10; // score

	//if game has not finished 
	if (execute == -2)
	{
		//traverse the board
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (board[i][j] == 0)
				{
					//place a move for ai on the board
					board[i][j] = ai;
					//get the max from the min with the score passed in
					w = max(w, mmMin(board, row, column, ai, oppo, P));
					//put 0 on the board
					board[i][j] = 0;
				}
			}
		}
		//return the new w
		return w;
	}
	//otherwise execute or check the board
	else {
		return execute;
	}
}
int mmMin(int **board, int row, int column, int ai, int oppo, int P)
{	
	//check the board
	int execute = checkBoard(board, row, column, P, ai, oppo);
	int w = 10; // score

	//game has not finished
	if (execute == -2)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				//
				if (board[i][j] == 0)
				{
					//place a move for the opponent on the board
					board[i][j] = oppo;
					//get the min from the max function with the score passed in
					w = min(w, mmMax(board, row, column, ai, oppo, P));
					//place a 0 on the board 
					board[i][j] = 0;
				}
			}
		}
		//return the new w
		return w;
	}
	//otherwise execute or check the board
	else
	{
		return execute;
	}

}