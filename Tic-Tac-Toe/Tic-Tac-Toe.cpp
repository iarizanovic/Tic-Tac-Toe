//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Tic-Tac-Toe.cpp : Program that utilizes the Tic-Tac-Toe game library
//-----------------------------------------------------------------------------

#include <iostream>
#include <thread>
#include <mutex>
#include "Game.h"
#include "Utils.h"

// Global variables
Utils::RESULTS results;
std::vector<std::string> fileList;
std::mutex mut;

// Read files function, which will be used in multi-thread
void ReadFiles()
{
	// Read the files, file per file
	while (TRUE) {
		// Check if fileList is empty
		mut.lock();
		if (fileList.empty()) {
			mut.unlock();
			break;
		}

		// Get the content of one file and remove it from filelist
		std::stringstream file_content = Utils::FileLoad(fileList[0]);
		fileList.erase(fileList.begin());
		mut.unlock();

		// Initialize the board
		boardHandle board = createBoard();

		// Read the commands from file content
		std::string command;
		Utils::RESULTS file_results;
		while (std::getline(file_content, command))
			file_results += processCommand(board, command.data(), (unsigned int)command.size());

		// Add the results of the file to global results
		mut.lock();
		results += file_results;
		mut.unlock();

		// Close the board
		closeBoard(board);
	};
};

// Main function
int main(int argc, const char* argv[])
{
	// Get the directory path of files
	if (argc != 2) {
		std::cout << "Error: Please add directory path of files in the following format: "
			      << "\".\\Tic-Tac-Toe.exe <path>\"\n";
		return -1;
	}
	std::string path = argv[1];

	// Add '\' as last char of path, if doesn't exist
	if (!path.empty() && path[path.size() - 1] != '\\')
		path += '\\';

	// Get the file list
	fileList = Utils::GetFileList(path);
	if (fileList.empty()) {
		std::cout << "Error: Added path of directory doesn't exist or doesn't contain files.\n";
		return -1;
	}

	// Creating the child threads
	std::vector<std::thread> threads;
	for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
		threads.push_back(std::thread(&ReadFiles));

	// Waits for all child threads
	for (std::thread &t : threads)
		t.join();

	// Save the results file
	if (Utils::FileSave(path + "RESULTS", results)) {
		std::cout << "Error: Results file cannot be saved on path: " << path + "RESULTS\n";
		return -1;
	}

	return 0;
}
