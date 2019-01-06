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

solution recuit::heuristique(int n, bool display) {

    Window f;
    int w;
    int h;

    if (display){
        w = 1500;
        h = 1000;
        f = openWindow(w,h);
    }

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
        click();
    }

    while(loop_size<min(30,cluster_size)+1){
        x.copy(x_prime);

        cout <<"Cluster: "<<n<< " loop size: " << loop_size << endl;

        T = 100.;
        proba1 = float (loop_size)/cluster_size;
        bool elements_to_swap;
        while(T>1){
            for (int counter =0; counter<max_iter;counter++){

                if (x.cost < x_best.cost){
                    x.copy(x_best);
                    if (display)
                        x.cluster_display(f,w,h,true);

                    cout <<"best cost: "<< x_best.cost << endl;
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

                // si x_prime est meilleur ou au hasard si l'ecart de cout est pas trop grand
                if (x_prime.cost<x.cost || p<exp(-(x_prime.cost-x.cost)/T))
                    x_prime.copy(x);
                else
                    x.copy(x_prime);

            }

            T= alpha*T;
        }

        bool change_size = true;

        if(loop_size==cluster_size || loop_size ==30){
            loop_size+=1;//stopping condition
            change_size= false;
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
        click();
        closeWindow(f);
    }
    return x_best;
}
