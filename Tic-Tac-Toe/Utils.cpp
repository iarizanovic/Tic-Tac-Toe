//-----------------------------------------------------------------------------
// Author: Ivan Arizanovic <ivanarizanovic@yahoo.com>
// 
// Utils.cpp : Utility components
//-----------------------------------------------------------------------------

#include "Utils.h"
#include <fstream>

std::vector<std::string>
Utils::GetFileList(std::string path)
{
    WIN32_FIND_DATA data;
    std::vector<std::string> list;

    // Initialize the handle
    HANDLE handle = FindFirstFile((path + '*').c_str(), &data);

    // Get the list of files
    if (handle != INVALID_HANDLE_VALUE) {
        while (FindNextFile(handle, &data) != 0)
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                list.push_back(path + data.cFileName);

        // Close the handle
        FindClose(handle);
    }

    return list;
};

std::stringstream
Utils::FileLoad(std::string path)
{
    std::ifstream file(path);
    std::stringstream file_content;
    file_content << file.rdbuf();
    file.close();

    return file_content;
}

int
Utils::FileSave(std::string path, RESULTS results)
{
    std::ofstream file(path, std::ios::out);
    if (!file)
        return -1;

    file << "X: " << results.X_wins << std::endl;
    file << "O: " << results.O_wins << std::endl;
    file << "D: " << results.draws  << std::endl;
    file.close();
    return 0;
}
