#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
#include <string>
#include <cassert>
#include <cmath>
#include <vector>

// le parser a pour objectif de sortir 3 tableaux fixes avec leurs tailles
// on fait 3 paramètres différents en fonction que des 3 villes.
//const int size_distances=68*68;
//const int size_distribution = 3;// nice
//const int size_antennes=68;//nice
//const int size_terminal =65;
const int size_distances=543*543;
const int size_distribution = 11;//paris
const int size_antennes=543;//paris
const int size_terminal =532;
//const int size_distances=13*13;
//const int size_distribution = 2;//grenoble
//const int size_antennes=13;//grenoble
//const int size_terminal =11;
class parser{
public:

    int distances[size_distances];
    int distribution[size_distribution];
    int antennes[size_antennes-size_distribution];
    parser();
    void test();
    int l(int x,int y) const;
private:
    void distances_fn();



    // on ne fait pas de destructeurs pour le moment, on en aura besoin tout le programme
};


