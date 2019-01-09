#include "recuit.h"

recuit::recuit(){}

int pop(antenna_group& group,int j){
    assert(j<5);
    int output = group.antennas[j];
    int g[5];
    for (int i=0;i<group.group_size;i++)
        g[i]=group.antennas[i];

    if (j+1 < group.group_size)
        for(int i =j;i<group.group_size;i++)
            group.antennas[i]=g[i+1];


    group.group_size = group.group_size - 1;
    return output;
}

void push(antenna_group& group,int valeur, int position){

    int g[5];
    for (int i=0;i<group.group_size;i++){
        g[i]=group.antennas[i];
    }

    if (position = group.group_size){
        group.antennas[group.group_size]=valeur;
        group.group_size+=1;
        }
    else{
        group.antennas[position]=valeur;
        group.group_size+=1;
        for(int i=position+1;i<group.group_size;i++){
            group.antennas[i]=g[i];
        }
    }
}
double grad(const vector<coordinates>& cost_iteration){
    int i;
    if (cost_iteration.size()>30){
        int n = 30;

        double xsomme, ysomme, xysomme, xxsomme;
        double g;

        xsomme = 0.0; ysomme = 0.0;
        xysomme = 0.0; xxsomme = 0.0;

        for (i=cost_iteration.size()-(n+1);i<cost_iteration.size();i++)
          {
            double x = cost_iteration[i].x;
            double y = cost_iteration[i].y;
            xsomme = xsomme + x;
            ysomme = ysomme + y;
            xysomme = xysomme + x*y;
            xxsomme = xxsomme + x*x;
          }
        g = (n*xysomme - xsomme*ysomme)/(n*xxsomme - xsomme*xsomme);

        return g;
    }
    else return -1;
}




solution recuit::heuristique(int n){
    bool display = false;
    Window f;
    int w,h;
    return this->heuristique(n,display,f,w,h);
}

solution recuit::heuristique(int n, bool display, Window f, int w, int h){


    int cluster_size = Clusters_const.cluster_list[n].size;
    clusters C = Clusters_const;
    assert(cluster_size<600);
    InitRandom();

    solution x,
             x_best,
             x_prime;

    double p,
           proba1;

    int loop_size = int(cluster_size/6)+1;

    x.loop_size = loop_size;

    x.first_solution(n);
    x.compute_cost();
    x.copy(x_best);
    x.copy(x_prime);

    if (display){
        x.cluster_display(f,w,h,true);
        drawString(100,200,"iterations " + to_string(0),BLACK,15);

        click();
    }

    vector<vector<coordinates>> cost_iteration_per_loop;
    int best_loop = 0;

    x.loop_iterations =0;

    while(loop_size<min(30,cluster_size)+1){
        vector<coordinates> cost_iteration;
        x.copy(x_prime);
        double swaps =0;
        cout <<"Cluster: "<<n<< " loop size: " << loop_size << endl;
        T = 100.;
        proba1 = float (loop_size)/cluster_size;
        bool elements_to_swap;
        while(T>3){
            for (int counter =0; counter<max_iter;counter++){

                x.loop_iterations += 1;

                if (x.cost < x_best.cost){
                    best_loop = loop_size;
                    x.copy(x_best);

                    if (display){
                        x.cluster_display(f,w,h,true);
                        setActiveWindow(f);
                        capture("gif" + to_string(x.loop_iterations) + ".png");
                    }
                    else cout <<"best cost: "<< x_best.cost << endl;

                }


                elements_to_swap = true;

                while (elements_to_swap) {

                    int i = hasard(0,loop_size-1);
                    int j = hasard(0,loop_size-1);

                    p = proba();

                    if ((p<proba1*proba1) && (i!=j)){
                        // On echange les elements i et j de la boucle et les boucles de collecte associees
                        antenna_group a_g_i = x_prime.antenna_groups[i];
                        antenna_group a_g_j = x_prime.antenna_groups[j];
                        int l_i = x_prime.loop[i];
                        int l_j = x_prime.loop[j];
                        x_prime.loop[i]=l_j;
                        x_prime.loop[j]=l_i;
                        x_prime.antenna_groups[i]=a_g_j;
                        x_prime.antenna_groups[j]=a_g_i;
                        elements_to_swap = false;
                    }

                    else if ((p<proba1*proba1+2*proba1*(1-proba1)) && (x_prime.antenna_groups[j].group_size!=0)) {
                        // On echange l'element i de la boucle avec l'antenne k du groupe j
                        int k = hasard(0,x_prime.antenna_groups[j].group_size-1);
                        int l_i = x_prime.loop[i];
                        int a_g_j_a_k = x_prime.antenna_groups[j].antennas[k];
                        x_prime.loop[i] = a_g_j_a_k;
                        x_prime.antenna_groups[j].antennas[k]= l_i;

                        elements_to_swap = false;

                    }

                    else if ((x_prime.antenna_groups[i].group_size != 0) && (x_prime.antenna_groups[j].group_size != 5)){
                        //On remplace l'antenne j1 du groupe j par l'antenne i1 du groupe i
                        int i1 = hasard(0,x_prime.antenna_groups[i].group_size-1);
                        int j1 = hasard(0,x_prime.antenna_groups[j].group_size);

                        push(x_prime.antenna_groups[j],pop(x_prime.antenna_groups[i],i1),j1);
                        elements_to_swap = false;

                    }
                }


                //On calcule les couts
                x_prime.compute_cost();
                if (counter%max_iter/100 == 0)
                    cost_iteration.push_back(coordinates {swaps,x.cost});
                // si x_prime est meilleur ou au hasard si l'ecart de cout est pas trop grand
                if (x_prime.cost<x.cost || p<exp(-(x_prime.cost-x.cost)/T)){
                    x_prime.copy(x);
                    cost_iteration.push_back(coordinates {swaps,x.cost});
                }
                else
                    x.copy(x_prime);
                swaps +=1;


            }
            T = alpha*T;
        }

        bool change_size = true;

        if(loop_size==cluster_size || loop_size ==30){
            loop_size+=1;//stopping condition
            change_size= false;
        }
        if (loop_size == best_loop){
            cost_iteration_per_loop.clear();
            cost_iteration_per_loop.push_back(cost_iteration);
        }

        while (change_size){
            int i = hasard(0,loop_size-1);
            x.antenna_groups[loop_size].group_size = 0;
            if (x.antenna_groups[i].group_size != 0){
                x.antenna_groups[loop_size].group_size=0;
                // on rajoute un élément dans loop
                int i1 = hasard(0,x.antenna_groups[i].group_size-1);
                x.loop[loop_size]=pop(x.antenna_groups[i],i1);
                x.loop_size+=1;
                loop_size+=1;
                change_size=false;
            }
        }

        x.compute_cost();
    }

    if (display){
        x_best.cluster_display(f,w,h,true);
        drawString(100,160,"Cost: " + to_string(x_best.cost),GREEN,20);
        drawString(100,200,"iterations: " + to_string(x_best.loop_iterations),BLACK,15);
        cout<<"Click for next cluster"<<endl;
        click();
        draw_cost_iteration(h,w,cost_iteration_per_loop[0],best_loop);

    }

    return x_best;
}
