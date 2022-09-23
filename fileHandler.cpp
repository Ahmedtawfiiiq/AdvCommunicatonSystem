#include "fileHandler.h"
#include <iostream>

void FileHandler::inFile(string path)
{

    fstream file;
    string line;

    file.open(path, ios::in);
    if (file.fail())
        cout << "file did not open" << endl;
    while (!file.eof())
    { // untill we reach end of the file
        getline(file, line);
        if (file.fail())
            break;
        data.push_back(line);
    }
    file.close();
}

void FileHandler::outFile(vector<string> vec)
{
    for (uint16 i = 0; i < vec.size(); i++)
    {
        FileHandler::file << vec[i] << "\n";
    }
    FileHandler::file << "\n";
}

void FileHandler::outFile(vector<complex<float>> vec)
{
    for (uint16 i = 0; i < vec.size(); i++)
    {
        FileHandler::file << vec[i] << "\n";
    }
    FileHandler::file << "\n";
}

void FileHandler::openFile(string path)
{
    FileHandler::file.open(path, ios::out);
}

void FileHandler::closeFile()
{
    FileHandler::file.close();
}
