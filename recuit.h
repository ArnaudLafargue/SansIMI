#pragma once
#include"solutions_parser.h"
#include "display.h"

class recuit{
public:
    int max_iter = 30000;
    float T = 100.;
    float alpha = 0.9;

    recuit();
    solution heuristique(int n, bool display, Window f, int w, int h);
    solution heuristique(int n);
    void test();

};

int pop(antenna_group& group,int j);
void push(antenna_group& group,int valeur, int position);

double grad(const vector<coordinates>& cost_iteration);
