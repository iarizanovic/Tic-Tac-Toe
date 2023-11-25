###############################################################################
# Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
#
# CMakeList.txt : CMake project file for Tic-Tac-Toe executable and game library
###############################################################################

# Source files of the game library
add_library(
  Game STATIC
  Game.cpp  Game.h
  BoardHandle.cpp BoardHandle.h
  GameStatus.h)

# Source files of the game binary
add_executable (
	Tic-Tac-Toe 
	Tic-Tac-Toe.cpp 
	Utils.cpp Utils.h
)

# Target library of the game binary
target_link_libraries(
  Tic-Tac-Toe PUBLIC
  Game
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tic-Tac-Toe PROPERTY CXX_STANDARD 20)
endif()
