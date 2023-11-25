//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// BoardHandle.h : Unique board handle that can be used to manage and interact with the game
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include <cctype>
#include "GameStatus.h"

class BoardHandle
{
private:
	// Matrix of board
	std::vector<std::vector<char>> board;
	// Player which had last move
	char lastPlayer;

	// Initialization
	void init();

	/**
	* @brief Set the field on board.
	*
	* This function plays the move provided by message and also checks the provided message.
	*
	* @param msg A string representing the command.
	* @param len The length of the command string.
	* @return The game status after processing the command.
	*/
	gameStatus setField(char* msg, unsigned int len);

	/**
	* @brief Check if there is a winner.
	*
	* This function checks all possibility for win or draw.
	*
	* @return It can return X_WINS or O_WINS status if some player is won,
	*         DRAW if all fields are played or 0 if there is no won or draw.
	*/
	gameStatus checkWinner();

	/**
	* @brief Check the board.
	*
	* This function checks the board of the game.
	*
	* @return It can return UNKNOWN_GAME if something went wrong or 0 if board is ok.
	*/
	gameStatus checkBoard();

public:
	// Constructor
	BoardHandle();

	/**
	* @brief Handle process.
	*
	* This function plays the move provided by message or restart the board. It also checks
	* the game board, provided message and checks if there is a winner.
	*
	* @param msg A string representing the command.
	* @param len The length of the command string.
	* @return The game status after processing the command.
	*/
	gameStatus process(char* msg, unsigned int len);
};
