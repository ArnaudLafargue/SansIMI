#pragma once
#include "network.h"

int l(int x, int y);

class cluster
{
public:

    int size;
    vector<object> cluster_antennas;

    cluster();
    void print() const;
    int pop(int j);
    //~cluster();


    int point_distribution;
};


class clusters
{
public:

    //liste de groupes d'antennes, le groupe d'indice i est associe au point de distribution i
    vector<cluster> cluster_list;
    clusters();

};

const clusters Clusters_const;
