#pragma once
#include "clusters.h"
#include<Imagine/Graphics.h>

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

    int cost;
    int dist_id;
    int loop_size;
    int loop[30];
    antenna_group antenna_groups[30];


    void first_solution(int n);

    int compute_cost();

    void copy(solution& Solution) const;

    void save_to_file(int n) const;

    void cluster_display(Window f, int w, int h, bool timed) const;
    void full_display(Window f, int w, int h) const;

    void parser();

};

int normalize(double x, int  w, double xmin, double xmax);

