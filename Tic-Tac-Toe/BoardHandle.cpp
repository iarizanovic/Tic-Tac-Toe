//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// BoardHandle.cpp : Unique board handle that can be used to manage and interact with the game
//-----------------------------------------------------------------------------

#include "BoardHandle.h"

BoardHandle::BoardHandle()
{
	init();
}

void
BoardHandle::init()
{
	// Initialize the clean board
	board = { {' ',' ',' '},
			  {' ',' ',' '},
			  {' ',' ',' '} };

	lastPlayer = 'O'; // 'O' because 'X' starts the game
};

gameStatus
BoardHandle::setField(char* msg, unsigned int len)
{
	// Check the format of msg
	if (len != 5 || msg[1] != ' ' || msg[3] != ' ')
		return MESSAGE_MALFORMED;

	// Get the values
	char player = msg[0];
	int row = msg[2] - '0';
	int column = msg[4] - '0';

	// Check the values of msg
	if ((player != 'X' && player != 'O') ||
		row < 0 || row > 2 || column < 0 || column > 2)
		return MESSAGE_MALFORMED;

	// Check the illegal moves
	// (if the player is not on move or if field is not free)
	if (player == lastPlayer || board[row][column] != ' ')
		return ILLEGAL_MOVE;

	// Set the field
	board[row][column] = player;
 	lastPlayer = player;

	// Return the information about the next move
	if (player == 'X')
		return O_MOVES_NEXT;
	else
		return X_MOVES_NEXT;
};

gameStatus
BoardHandle::checkWinner()
{
	char winner = ' ';

	// Check diagonals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
		winner = board[0][0];
	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
		winner = board[0][2];
	// Check rows and columns
	else {
		for (int i = 0; i < 3 && winner == ' '; i++) {
			if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
				winner = board[i][0];
			else if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
				winner = board[0][i];
		}
	}

	// Return the status about the winner
	if (winner == 'X')
		return X_WINS;
	else if (winner == 'O')
		return O_WINS;

	// Check if all fields are played
	for (auto row : board)
		for (auto field : row)
			if (field == ' ')
				return 0;

	// Return DRAW status if all fields are played
	return DRAW;
}

gameStatus
BoardHandle::checkBoard()
{
	// Board has to have 3 rows 
	if (board.size() != 3)
		return UNKNOWN_GAME;

	// All rows have to have 3 fields
	for (auto row : board)
		if (row.size() != 3)
			return UNKNOWN_GAME;

	// Check the fields
	for (auto row : board)
		for (auto field : row)
			if (field != ' ' && field != 'X' && field != 'O')
				return UNKNOWN_GAME;

	return 0;
}

gameStatus
BoardHandle::process(char* msg, unsigned int len)
{
	// Check the board
	if (checkBoard())
		return UNKNOWN_GAME;

	// Convert msg to uppercase
	for (unsigned int i = 0; i < len; i++)
		msg[i] = std::toupper(msg[i]);

	// Resets game state
	if (len == 3 && !strcmp(msg, "RST")) {
		init();
		return X_MOVES_NEXT;
	}

	// Set the move
	gameStatus retc = setField(msg, len);

	// Check if there is a winner
	if (retc == X_MOVES_NEXT || retc == O_MOVES_NEXT) {
		gameStatus winner = checkWinner();
		if (winner) {
			init();
			return winner;
		}
	}

	return retc;
};