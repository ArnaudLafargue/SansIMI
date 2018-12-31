#pragma once

#include<vector>
#include<iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class object{
public:
    object();
    vector<double> coordinates;
    int index;
    int type;


};



class network{
public:
    network();
    vector<object> antennas;
    vector<int> distances;
    vector<object> t_antennas;
    vector<object> d_antennas;

    int size_distances;
    int size_distribution;
    int size_antennas;
    int size_terminal;
};

const network Network_const;

