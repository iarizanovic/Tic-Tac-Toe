//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Game.cpp : Tic-Tac-Toe game library
//-----------------------------------------------------------------------------

#include "Game.h"

boardHandle createBoard()
{
	return new BoardHandle;
};

void closeBoard(boardHandle board)
{
	delete board;
};

gameStatus processCommand(boardHandle board, char* msg, unsigned int len)
{
	return board->process(msg, len);
};