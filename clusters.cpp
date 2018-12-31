#include "clusters.h"

int l(int x, int y){
    return Network_const.distances[x*Network_const.size_antennas+y];
}


///////////////////////////////////////////////////////Cluster///////////////////////////////////////////////////////////////////////////

cluster::cluster(){
    size = 0;
}
void cluster::print() const{
    cout << size << endl;

    for (int i =0;i< size;i++){
        cout << cluster_antennas[i].index << endl;
    }
}

int cluster::pop(int j){
    int output = cluster_antennas[j].index;
    cluster_antennas.erase(cluster_antennas.begin()+j);
    size = size -1;
    return output;
}


//////////////////////////////////////////////////clusters/////////////////////////////////////////////////////////////////////////////////////

clusters::clusters(){
    network N = Network_const;
    for (int i=0; i < Network_const.size_distribution; i++){
        cluster Cluster;
        Cluster.point_distribution = i;
        Cluster.size =0;
        cluster_list.push_back(Cluster);
    }

    for (int terminal =0; terminal<Network_const.size_terminal; terminal++){
        int d_min = 100000;
        int j_min=0;

        for (int j=0;j<Network_const.size_distribution;j++){
            int d_j =l(Network_const.t_antennas[terminal].index,j);
            if (d_j<d_min){
                j_min=j;
                d_min = d_j;
            }
        }

        cluster_list[j_min].cluster_antennas.push_back(Network_const.t_antennas[terminal]);
        cluster_list[j_min].size ++;
    }
}





