#pragma once
#include <iostream>
using namespace std;

class CSVReader
{
    string fileName;
    string delimeter;

public:
    CSVReader(string filename, string delm = ",") :
            fileName(filename), delimeter(delm)
    { }

    // Function to fetch data from a CSV File
    vector<vector<string> > getData();
};
