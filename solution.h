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

    int dist_id;
    int loop_size;
    int loop[30];
    antenna_group antenna_groups[30];

    int cost;

    void first_solution(int n);

    int simple_cost2(int n);

    void copy(solution& Solution) const;
    void print(int n) const;

    void fichier(int n) const;
    //~solution();
    void cluster_display(int n, Window f, int w, int h, bool timed) const;
    void full_display(int n, Window f, int w, int h) const;
    void parser();

};

int x(double x, int  w, double xmin, double xmax);
int y(double y, int  h, double ymin, double ymax);

struct solutions{
    solution solutions_list[40];
    int solutions_number;
};

solutions solutions_parser();
