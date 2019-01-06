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
    //S =1;
    cluster_cost parameters[S];

    for (int n=0;n<S;n++)
        parameters[n].cluster_index=n;

    for (int n=0;n<S;n++){

        std::thread t([] (cluster_cost& c_c){

            solution bestsol;
            recuit Recuit;
            Recuit.heuristique(c_c.cluster_index,false).copy(bestsol);
            bestsol.save_to_file(c_c.cluster_index);
            c_c.cost = bestsol.compute_cost();
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
    (Recuit.heuristique(n,true)).copy(bestsol);
    bestsol.save_to_file(n);
    finalcost +=bestsol.compute_cost();

    cout << finalcost << "final"<<endl;


    return 0;
}
int main3()
{
    int finalcost =0;
    solution bestsol;
    recuit Recuit;
    vector<solution> sols;

    for (int n=0; n<Network_const.size_distribution;n++){
        (Recuit.heuristique(n,false)).copy(bestsol);
        bestsol.save_to_file(n);
        sols.push_back(bestsol);
        finalcost +=bestsol.compute_cost();

    }
    cout << finalcost << "final"<<endl;

    return 0;
}


int main4(){
    solutions sols;
    sols = solutions_parser();

    //clusters c;

    int w = 3000;
    int h = 2000;
    Window f = openWindow(w,h);
    for (int i=0; i<sols.solutions_number;i++){
        sols.solutions_list[i].full_display(f,w,h);
        //click();
    }
    click();
    return 0;

}




int main()
{ return main3();}

