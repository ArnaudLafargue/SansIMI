#include "recuit.h"
#include <thread>

struct cluster_cost{
    int cluster_index;
    int cost;
};


int main1()
{
    network Network;

    clusters Clusters;


    vector<std::thread> threads;
    int S = Network.size_distribution;
    S =1;
    cluster_cost parameters[S];
    for (int n=0;n<S;n++)
        parameters[n].cluster_index=n;

    for (int n=0;n<S;n++){

        std::thread t([] (cluster_cost& c_c){

            solution bestsol;
            recuit Recuit;
            Recuit.heuristique(c_c.cluster_index).copy(bestsol);
            bestsol.fichier(c_c.cluster_index);
            c_c.cost = bestsol.simple_cost2(c_c.cluster_index);
        }, std::ref(parameters[n]));


        threads.push_back(std::move(t));
    }

    for (int n=0; n<S;n++){
        threads[n].join();
    }
    threads.clear();
    int finalcost =0;
    for (int n=0;n<S;n++)
        finalcost += parameters[n].cost;
    cout << finalcost << "final"<<endl;

    return 0;
}

int main2()
{
    network Network;

    clusters Clusters;

    int finalcost =0;
    solution bestsol;
    int n =0;
    recuit Recuit;
    (Recuit.heuristique(n)).copy(bestsol);
    bestsol.fichier(n);
    finalcost +=bestsol.simple_cost2(n);

    cout << finalcost << "final"<<endl;

    return 0;
}
int main3()
{
    network Network;

    clusters Clusters;

    int finalcost =0;
    solution bestsol;
    int n =0;
    recuit Recuit;
    for (int n=0; n<Network.size_distribution;n++){
    (Recuit.heuristique(n)).copy(bestsol);
    bestsol.fichier(n);
    finalcost +=bestsol.simple_cost2(n);
    }
    cout << finalcost << "final"<<endl;

    return 0;
}

int main()
{ return main3();}

