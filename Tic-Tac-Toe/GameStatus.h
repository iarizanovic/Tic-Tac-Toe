//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Status.h : Game statuses
//-----------------------------------------------------------------------------

#pragma once

#define UNKNOWN_GAME	  0x0001
#define MESSAGE_MALFORMED 0x0002
#define ILLEGAL_MOVE	  0x0004

#define X_MOVES_NEXT	  0x0010
#define O_MOVES_NEXT	  0x0020

#define X_WINS			  0x0100
#define O_WINS			  0x0200
#define DRAW			  0x0400

typedef int gameStatus;
