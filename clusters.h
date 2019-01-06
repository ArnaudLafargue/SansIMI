#pragma once
#include "network.h"

int l(int x, int y);
int l2(int x, int y);

struct cluster
{
    cluster();

    int point_distribution;

    int size;
    vector<object> cluster_antennas;

    double x_max,
           x_min,
           y_max,
           y_min;
};


struct clusters
{
    //liste de groupes d'antennes, le groupe d'indice i est associe au point de distribution i
    vector<cluster> cluster_list;
    clusters();
};

const clusters Clusters_const;
