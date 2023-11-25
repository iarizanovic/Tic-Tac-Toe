//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Game.h : Tic-Tac-Toe game library
//-----------------------------------------------------------------------------

#pragma once
#include "BoardHandle.h"

typedef BoardHandle* boardHandle;

/**
 * @brief Creates a new Tic-Tac-Toe game board and returns its unique board handle.
 *
 * This function initializes a new game board of Tic-Tac-Toe and provides a unique board handle
 * that can be used to manage and interact with the game.
 *
 * @return An identifier for the newly created board.
 */
boardHandle createBoard();

/**
 * @brief Closes a Tic-Tac-Toe game and releases associated resources.
 *
 * This function ends the specified Tic-Tac-Toe game board and frees any resources
 * associated with it. It should be called when the board is no longer needed.
 *
 * @param boardHandle The identifier of the game to end.
 */
void closeBoard(boardHandle board);

/**
 * @brief Processes a command for a Tic-Tac-Toe game.
 *
 * This function processes a command for the specified Tic-Tac-Toe game. The command
 * is provided as a string (msg) with a specified length (len).
 *
 * @param boardHandle The identifier of the game board to process the command for.
 * @param msg A string representing the command.
 * @param len The length of the command string.
 * @return The game status after processing the command.
 */
gameStatus processCommand(boardHandle board, char* msg, unsigned int len);