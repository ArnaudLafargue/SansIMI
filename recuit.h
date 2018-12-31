#pragma once
#include"solution.h"

class recuit{
public:
    int max_iter = 3000;
    float T = 100.;
    float alpha = 0.9;

    recuit();
    solution heuristique(int n) ;
    void test();

};

int pop(antenna_group& group,int j);
void push(antenna_group& group,int valeur, int position);
