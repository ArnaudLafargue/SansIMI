#pragma once
#include"solution.h"
class recuit{
public:
    int taille = 500;
    float T = 100.;
    float alpha = 0.9;

    recuit();
    solution heuristique(parser& Parser, cluster& Cluster) ;
    void test();
};
