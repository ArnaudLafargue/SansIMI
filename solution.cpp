#include "solution.h"

/////////////////////////////////////////Random functions///////////////////////////////////////

void InitRandom() {
    srand((unsigned int)time(0));
}

// Renvoie un entier aleatoire entre a et b
int hasard(int a, int b){
    int c = rand ()%((b-a) + 1);
    return a +c;
}

//Renvoie une probabilite aleatoire
double proba(){
    return double(rand())/RAND_MAX;
}

///////////////////////////////////////       l    ////////////////////////////////////////////////


///////////////////////////////////////Solutions////////////////////////////////////////////////


solution::solution(int n,int Loop_size){
    loop_size = Loop_size;
    //first_solution();
}

solution::solution(int n){
    loop_size = hasard(int(Clusters_const.cluster_list[n].size/6)+1,min(30,Clusters_const.cluster_list[n].size));

    //first_solution();
}

solution::solution(){
    loop_size=0;
}

void solution::first_solution(int n){


    int cluster_copy[Clusters_const.cluster_list[n].size];

    for (int i=0; i<Clusters_const.cluster_list[n].size;i++)
        cluster_copy[i] = Clusters_const.cluster_list[n].cluster_antennas[i].index;

    for (int i=0; i<Clusters_const.cluster_list[n].size;i++){
        int j = hasard(0,Clusters_const.cluster_list[n].size-1);
        if (i!=j){
            int v_i = cluster_copy[i];
            int v_j = cluster_copy[j];
            cluster_copy[i] = v_j;
            cluster_copy[j] = v_i;
        }
    }

    int j=0;
    for (int i=0; i<loop_size;i++){
        loop[i] = cluster_copy[i];
        antenna_groups[i].group_size =0;
        }

    for (int i=0;i<Clusters_const.cluster_list[n].size-loop_size;i++)
    {
        bool a = true;
        while(a)
        {
            j = hasard(0,loop_size-1);
            if (antenna_groups[j].group_size < 5){
                antenna_groups[j].antennas[antenna_groups[j].group_size] =Clusters_const.cluster_list[n].cluster_antennas[i].index;
                antenna_groups[j].group_size+=1;
                a=false;
            }

        }
    }
}


int solution::simple_cost2(int n) const{

    int cost =0;
    cost += l(Clusters_const.cluster_list[n].point_distribution,loop[0]);
    if(loop_size>0){
    for (int i=0;i<loop_size-1;i++){
        cost+= l(loop[i],loop[i+1]);
    }

    cost += l(loop[loop_size-1],Clusters_const.cluster_list[n].point_distribution);
    }

    for (int i=0;i<loop_size;i++){
        assert (antenna_groups[i].group_size <=5);
        if(antenna_groups[i].group_size >0){
            cost += l(loop[i],antenna_groups[i].antennas[0]);

            if(antenna_groups[i].group_size>1){
            for(int j=0;j<antenna_groups[i].group_size-1;j++){
                cost+=l(antenna_groups[i].antennas[j],antenna_groups[i].antennas[j+1]);
            }
            }
        }
    }

    return cost;
}

void solution::copy(solution &Sol) const{

    Sol.loop_size = loop_size;
    Sol.cost = cost;

    for (int i=0;i<loop_size;i++){
        Sol.loop[i] = loop[i];
    }

    for (int i=0;i<loop_size;i++){
        Sol.antenna_groups[i].group_size = antenna_groups[i].group_size;

        for (int j=0;j<antenna_groups[i].group_size;j++){
            Sol.antenna_groups[i].antennas[j] = antenna_groups[i].antennas[j];
        }
    }
}


void solution::print(int n) const{
    cout << "b ";
    cout << Clusters_const.cluster_list[n].point_distribution;
    for (int i=0;i<loop_size;i++){
        cout <<" "<< loop[i];
    }
    cout << endl;

    for(int i=0;i<loop_size;i++){
        if(antenna_groups[i].group_size>0){
            cout << "c ";
            cout << loop[i];
            for(int j =0;j<antenna_groups[i].group_size;j++){
                cout <<" "<< antenna_groups[i].antennas[j];
            }
            cout << endl;
        }
    }

}


void solution::fichier(int n) const{
    ofstream f("/home/arnaud/Documents/Rechop/paris" +to_string(n) + ".txt");

    f << "b ";
    f << Clusters_const.cluster_list[n].point_distribution;
    for (int i=0;i<loop_size;i++){
        f <<" "<< loop[i];
    }
    f << endl;

    for(int i=0;i<loop_size;i++){
        if(antenna_groups[i].group_size>0){
            f << "c ";
            f << loop[i];
            for(int j =0;j<antenna_groups[i].group_size;j++){
                f <<" "<< antenna_groups[i].antennas[j];
            }
            f << endl;
        }
    }
}
