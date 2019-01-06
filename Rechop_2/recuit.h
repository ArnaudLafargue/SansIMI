#pragma once
#include"solution.h"
class recuit{
public:
    int taille = 50000;
    float T = 100.;
    float alpha = 0.9;

    recuit();
    solution heuristique(parser& Parser, cluster& Cluster) ;
    void test();
};
int pop(antenne& Antenne,int j);
void push(antenne& Antenne,int valeur, int position);
