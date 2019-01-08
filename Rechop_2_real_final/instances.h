#pragma once
#include "parser.h"
struct cluster
{
    int point_distribution;
    int nombre_de_point;
    int liste_point[100];
    void copy(cluster& Cluster);
    void destruction();
    cluster();
    //~cluster();
};
class instances
{
public:
    //int size_distribution = Parser.size_distribution;// grenoble
    //int size_terminal=size_antennes- size_distribution;
    cluster rangement[size_distribution];

    instances(const parser& Parser);

    int l(int x,int y,const parser& Parser) const;
    int l2(int x,int y,const parser& Parser) const;
    void test() const;
private:
    void cluster_fn(const parser& Parser);
};





void print(cluster Cluster);
int pop(cluster& CopyCluster,int j);
