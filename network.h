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

    vector<object> antennas,
                   t_antennas,
                   d_antennas;

    vector<int> distances;
    int size_distances,
        size_distribution,
        size_antennas,
        size_terminal;

    double x_max,
           x_min,
           y_max,
           y_min;
};

const network Network_const;

