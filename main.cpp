#include "recuit.h"
#include <thread>

struct cluster_cost{
    int cluster_index;
    int cost;
};


int threads()
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
            Recuit.heuristique(c_c.cluster_index).copy(bestsol);
            bestsol.save_to_file();
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

int compute_solution_to_file(int n, bool display)
{
    Window f;
    int h,w;

    if (display){
        w = 1500;
        h = 1000;
        f = openWindow(w,h);
    }

    int finalcost =0;
    solution bestsol;
    recuit Recuit;
    (Recuit.heuristique(n,display,f,w,h)).copy(bestsol);
    bestsol.save_to_file();
    finalcost +=bestsol.compute_cost();

    cout << finalcost << "final"<<endl;

    return 0;
}

int compute_solutions_to_files(bool display)
{
    Window f;
    int h,w;

    if (display){
        w = 1500;
        h = 1000;
        f = openWindow(w,h);
    }

    int finalcost =0;
    solution bestsol;
    recuit Recuit;
    vector<solution> sols;

    for (int n=0; n<Network_const.size_distribution;n++){
        (Recuit.heuristique(n,display,f,w,h)).copy(bestsol);
        bestsol.save_to_file();
        sols.push_back(bestsol);
        finalcost +=bestsol.compute_cost();

    }
    cout << finalcost << "final"<<endl;

    return 0;
}


int parse_solutions(string path){
    solutions sols = solutions_parser(path);


    int w = 3000;
    int h = 3000;

    Window f = openWindow(w,h);

    display_network(w,h);
    display_clusters(w,h);

    int total_cost = 0;
    for (int i=0; i<sols.solutions_number;i++){
        sols.solutions_list[i].full_display(f,w,h);
        total_cost += sols.solutions_list[i].cost;
        //click();
    }
    cout<<total_cost;
    drawRect(470,80,500,100,RED,3);
    drawString(500,150, "Cout total  " + to_string(total_cost),BLACK,40);
    setActiveWindow(f);

    capture("best.png");
    click();


    return 0;
}


///Mettre les bons chemins dans network.cpp, solution.cpp pour calculer les solutions
///Dans le main ci dessous pour les afficher seulement

int main()
{
    /// Compute with one of the following

    ///Multithreaded (very bad)
    //threads();

    ///Choose which cluster to compute
    //int n=0;
    //compute_solution_to_file(n);

    ///Default computation
    //compute_solutions_to_files(true);

    ///Print solutions
    string path = "/home/arnaud/Documents/Rechop/grenoble2.txt";
    parse_solutions(path);

    return 0;
}

