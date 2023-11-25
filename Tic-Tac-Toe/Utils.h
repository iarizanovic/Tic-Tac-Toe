//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Utils.h : Utility components
//-----------------------------------------------------------------------------

#pragma once
#include <vector>
#include <windows.h>
#include <sstream>
#include "GameStatus.h"

class Utils
{
public:
	// Structure of the results
	struct RESULTS {
		int X_wins = 0;
		int O_wins = 0;
		int draws = 0;

		void operator+=(gameStatus status) {
			switch (status) {
			case X_WINS: X_wins++; break;
			case O_WINS: O_wins++; break;
			case DRAW:   draws++; break;
			default:     break;
			}
		}

		void operator+=(RESULTS res) {
			X_wins += res.X_wins;
			O_wins += res.O_wins;
			draws += res.draws;
		}
	};

	/**
	* @brief Get the file list.
	*
	* This function returns the list of files inside the provided path.
	*
	* @param path Path of file which should be read.
	* @return It returns list of the files.
	*/
	static std::vector<std::string> GetFileList(std::string path);

	/**
	* @brief Load the file with messages.
	*
	* This function load the file from provided path and return the content of the file.
	*
	* @param path Path of file which should be read.
	* @return It returns content of the file.
	*/
	static std::stringstream FileLoad(std::string path);

	/**
	* @brief Save the file with results.
	*
	* This function save the file with provided results on provided path.
	*
	* @param path Path where file have to be saved.
	* @param results Structure of the results.
	* @return It can return negative value if something went wrong or 0 if success.
	*/
	static int FileSave(std::string path, RESULTS results);
};
