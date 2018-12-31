#include "recuit.h"


recuit::recuit(){}

int pop(antenna_group& group,int j){
    int output = group.antennas[j];
    int g[5];
    for (int i=0;i<group.group_size;i++){
        g[i]=group.antennas[i];
    }
    if (j+1 < group.group_size){
        for(int i =j;i<group.group_size;i++){
            group.antennas[i]=g[i+1];
        }
    }
    group.group_size -= 1;
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

solution recuit::heuristique(int n) {
    int cluster_size = Clusters_const.cluster_list[n].size;
    clusters C = Clusters_const;
    assert(cluster_size<600);
    int lastop = 8;
    InitRandom();

    solution x,
             xb,
             xprime,
             xseconde;

    double p,
           proba1;

    int loop_size = int(cluster_size/6)+1;

    x.loop_size = loop_size;
    x.first_solution(n);

    xb.loop_size = loop_size;
    xb.first_solution(n);

    while(loop_size<min(30,cluster_size)+1){

        cout << "boucle size" << loop_size << endl;

        InitRandom();
        T = 100.;
        proba1 = float(loop_size)/cluster_size;
        bool unchanged;
        //cout << "always working ? " << endl;
        while(T>1){
            for (int counter =0; counter<max_iter;counter++){

                if (x.simple_cost2(n) < xb.simple_cost2(n)){
                    x.copy(xb);
                    cout << xb.simple_cost2(n) << "ici"<< endl;
                }

                x.copy(xprime);

                unchanged = true;

                while (unchanged) {

                    int i = hasard(0,loop_size-1);
                    int j = hasard(0,loop_size-1);

                    p = proba();

                    if ((p<proba1*proba1) && (i!=j)){
                        antenna_group A = xprime.antenna_groups[i];
                        antenna_group B = xprime.antenna_groups[j];
                        int a1 = xprime.loop[i];
                        int b1 = xprime.loop[j];
                        xprime.loop[i]=b1;
                        xprime.loop[j]=a1;
                        xprime.antenna_groups[i]=B;
                        xprime.antenna_groups[j]=A;
                        unchanged = false;
                        lastop = 1;
                    }

                    else if ((p<proba1*proba1+2*proba1*(1-proba1)) && (xprime.antenna_groups[j].group_size!=0)) {
                        int j1=hasard(0,xprime.antenna_groups[j].group_size -1);
                        int a1 = xprime.loop[i];
                        int a2 = xprime.antenna_groups[j].antennas[j1];
                        xprime.loop[i] = a2;
                        xprime.antenna_groups[j].antennas[j1]= a1;

                        unchanged = false;
                        lastop = 2;

                    }

                    else if ((xprime.antenna_groups[i].group_size != 0) && (xprime.antenna_groups[j].group_size != 5)){
                            int i1 = hasard(0,xprime.antenna_groups[i].group_size-1);
                            int j1 = hasard(0,xprime.antenna_groups[j].group_size);
                            // on enlève le i1 élément de la première chaine et on le rajoute dans j

                            push(xprime.antenna_groups[j],pop(xprime.antenna_groups[i],i1),j1);
                            unchanged = false;
                            lastop = 3;

                        }
                    }


                int cxprime = xprime.simple_cost2(n);
                int cx = x.simple_cost2(n);
                if (cxprime<cx){
                    xprime.copy(x);
                }

                else if(p<exp(-(cxprime-cx)/T)){
                    xprime.copy(x);
                }



                x.copy(xseconde);

                int i = hasard(0,loop_size-1);
                int j = hasard(0,loop_size-1);


                if ((xseconde.antenna_groups[i].group_size != 0) && (xseconde.antenna_groups[j].group_size != 5)){

                    int i1 = hasard(0,xseconde.antenna_groups[i].group_size-1);
                    int j1 = hasard(0,xseconde.antenna_groups[j].group_size);

                    // on enlève le i1 élément de la première chaine et on le rajoute dans j

                    push(xseconde.antenna_groups[j],pop(xseconde.antenna_groups[i],i1),j1);
                }

                int cxseconde = xseconde.simple_cost2(n);
                cx = x.simple_cost2(n);
                if (cxseconde<cx){
                    xseconde.copy(x);
                }
                else if(p<exp(-(cxseconde-cx)/T)){
                    xseconde.copy(x);
                }



            }

            T= alpha*T;
        }

        unchanged = true;

        if(loop_size==cluster_size){
            loop_size+=1;//stopping condition
            unchanged= false;
        }

        while (unchanged){
            int i = hasard(0,loop_size-1);
            x.antenna_groups[loop_size].group_size = 0;
            if (x.antenna_groups[i].group_size != 0){
                x.antenna_groups[loop_size].group_size=0;
                // on rajoute un élément dans loop
                int i1 = hasard(0,x.antenna_groups[i].group_size-1);
                x.loop[loop_size]=pop(x.antenna_groups[i],i1);
                unchanged=false;
                x.loop_size+=1;
                loop_size+=1;
            }
        }


    }
    return xb;
}
