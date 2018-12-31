#pragma once
#include "clusters.h"


void InitRandom();
int hasard (int a ,int b);
double proba();

struct antenna_group
{
    int group_size;
    int antennas[5];
};


class solution
{
public:
    solution();
    solution(int n);
    solution(int n,int Loop_size);

    int loop_size;
    int loop[30];
    antenna_group antenna_groups[30];

    double cost;

    void first_solution(int n);

    int simple_cost2(int n) const;

    void copy(solution& Solution) const;
    void print(int n) const;

    void fichier(int n) const;
    //~solution();

};

