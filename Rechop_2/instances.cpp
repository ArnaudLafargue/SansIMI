#include "instances.h"

instances::instances(const parser& Parser)
{
    cluster_fn(Parser);
}
int instances::l(int x,int y,const parser& Parser) const
{
    return Parser.distances[x*size_antennes+y];
}
int instances::l2(int x,int y,const parser& Parser) const
{
    return Parser.distances[x*size_antennes+y] +Parser.distances[y*size_antennes+x];
}
void instances::cluster_fn(const parser& Parser){
    for (int i=0;i<size_distribution;i++){
        cluster Cluster;
        Cluster.point_distribution = i;
        Cluster.nombre_de_point =0;
        Cluster.copy(rangement[i]);
    }
    for (int terminal =0;terminal<size_terminal;terminal++){
        //cout << Parser.antennes[terminal]<<"autre"<<endl;
        int d = 100000;
        int j0=0;
        for (int j=0;j<size_distribution;j++){
            if (l2(Parser.antennes[terminal],j,Parser)<d){
                j0=j;
                d = l2(Parser.antennes[terminal],j,Parser);
            }
        }
        //cout << d << " d"<< endl;
        //cout << j0 << " j0" << endl;
        //cout <<rangement[1].liste_point[0]<<"test"<<endl;
        //cout << rangement[j0].liste_point[rangement[j0].nombre_de_point] << "variable" <<endl;
        rangement[j0].liste_point[rangement[j0].nombre_de_point] = Parser.antennes[terminal];
        rangement[j0].nombre_de_point ++;

        //cout <<rangement[1].liste_point[0]<<"test"<<endl;



    }
}
void instances::test() const{
    int j0 =0;
    for (int i =0;i<rangement[j0].nombre_de_point;i++){
        cout << rangement[j0].liste_point[i] << endl;
    }
    //cout << l2(12,0) << endl;
    //cout << l2(12,1) << endl;

}
void print(cluster Cluster){
    cout << Cluster.nombre_de_point << endl;

    for (int i =0;i< Cluster.nombre_de_point;i++){
        cout << Cluster.liste_point[i] << endl;
    }
}
int pop(cluster& CopyCluster,int j){
    int returne = CopyCluster.liste_point[j];
    int g[size_terminal];
    for(int i=0;i<CopyCluster.nombre_de_point;i++){
        g[i] = CopyCluster.liste_point[i];
    }
    if (j+1<CopyCluster.nombre_de_point)
    {
        for(int i=j;i<CopyCluster.nombre_de_point-1;i++){
            CopyCluster.liste_point[i]=g[i+1];
        }
    }

    CopyCluster.nombre_de_point = CopyCluster.nombre_de_point -1;
    return returne;
}

void cluster::copy(cluster& Cluster){
    Cluster.point_distribution = point_distribution;
    Cluster.nombre_de_point = nombre_de_point;
    for (int i=0;i<nombre_de_point;i++){
        Cluster.liste_point[i] = liste_point[i];
    }
}

cluster::cluster(){
    nombre_de_point=0;
}

