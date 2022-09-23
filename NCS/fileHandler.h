#pragma once
#include <vector>
#include <fstream>
#include <complex>
using namespace std;
typedef unsigned short uint16;

// singleton class
class FileHandler
{
public:
    vector<string> data;
    fstream file;
    string buffer = "";

private:
    FileHandler() = default;

public:
    void inFile(string);
    void outFile(vector<string>);
    void outFile(vector<complex<float>>);
    void openFile(string);
    void closeFile();
    static FileHandler &getInstance()
    {
        static FileHandler instance;
        return instance;
    }
    // delete copy constructor -> className newInstanceName(oldInstanceName);
    FileHandler(const FileHandler &) = delete;
    // delete copy assignment operator -> className newInstanceName = oldInstanceName;
    FileHandler &operator=(const FileHandler &) = delete;
    // delete move constructor
    FileHandler(FileHandler &&) = delete;
    // delete move assignment operator
    FileHandler &operator=(FileHandler &&) = delete;
};
