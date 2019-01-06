#include "clusters.h"

int l(int x, int y){
    return Network_const.distances[x*Network_const.size_antennas+y];
}

int l2(int x, int y){
    return Network_const.distances[x*Network_const.size_antennas+y] + Network_const.distances[y*Network_const.size_antennas+x];
}

///////////////////////////////////////////////////////Cluster///////////////////////////////////////////////////////////////////////////

cluster::cluster(){
    size = 0;
}


//////////////////////////////////////////////////clusters/////////////////////////////////////////////////////////////////////////////////////

clusters::clusters(){

    for (int i=0; i < Network_const.size_distribution; i++){
        cluster Cluster;
        Cluster.point_distribution = i;
        cluster_list.push_back(Cluster);
    }

    for (int terminal =0; terminal<Network_const.size_terminal; terminal++){
        int d_min = 100000;
        int j_min=0;

        for (int j=0;j<Network_const.size_distribution;j++){
            int d_j =l2(Network_const.t_antennas[terminal].index,j);
            if (d_j<d_min){
                j_min=j;
                d_min = d_j;
            }
        }

        cluster_list[j_min].cluster_antennas.push_back(Network_const.t_antennas[terminal]);
        cluster_list[j_min].size ++;
    }

    for (int i=0; i < Network_const.size_distribution; i++){


        cluster_list[i].x_min = 10000000;
        cluster_list[i].x_max = 0;
        cluster_list[i].y_min = 10000000;
        cluster_list[i].y_max = 0;

        for (int j=0; j<cluster_list[i].size;j++){
            coordinates c = cluster_list[i].cluster_antennas[j].coords;
                if (c.x <= cluster_list[i].x_min)
                    cluster_list[i].x_min = c.x;
                else if (c.x >=cluster_list[i].x_max)
                    cluster_list[i].x_max = c.x;
                if (c.y <= cluster_list[i].y_min)
                    cluster_list[i].y_min = c.y;
                else if (c.y >=cluster_list[i].y_max)
                    cluster_list[i].y_max = c.y;
         }
    }
}





