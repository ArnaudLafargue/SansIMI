#pragma once

#include<vector>
#include<iostream>
#include <string>
#include <cassert>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include<Imagine/Common.h>
#include<Imagine/Graphics.h>

using namespace std;
using namespace Imagine;

struct coordinates{
    double x;
    double y;
};

struct object{
    object();
    coordinates coords;
    int index;
    int type;
};



struct network{

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

