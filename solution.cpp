#include "solution.h"
int hasard(int a, int b){
    int c = rand ()%((b-a) + 1);
    return a +c;
}
double proba(){
    return double(rand())/RAND_MAX;
}
void InitRandom() {
    srand((unsigned int)time(0));
}

solution::solution(const parser& Parser,const cluster& Cluster,int boucle_size)
{

    bouclesize = boucle_size;

    //first_solution();
}
solution::solution(const parser& Parser,const cluster& Cluster)
{

    bouclesize = hasard(int(Cluster.nombre_de_point/6)+1,min(30,Cluster.nombre_de_point));

    //first_solution();
}
solution::solution(){
    bouclesize=0;
};
void solution::first_solution(parser& Parser, cluster& Cluster)
{
    cluster CopyCluster;
    Cluster.copy(CopyCluster);
    //print (Cluster);
    //print(CopyCluster);
    //cout << " au debut" << CopyCluster.nombre_de_point<< endl;
    int j=0;
    for (int i=0; i<bouclesize;i++)
    {
        j = hasard(0,CopyCluster.nombre_de_point-1);
        Boucle[i] = pop(CopyCluster,j);
        Antenne[i].size_antennes =0;
    }
    //print(Cluster);
    //print(Cluster);
    //cout << " apres"<< endl;

    for (int i=0;i<CopyCluster.nombre_de_point;i++)
    {
        bool a = true;
        while(a)
        {
            j = hasard(0,bouclesize-1);
            if (Antenne[j].size_antennes < 5){
                Antenne[j].liste_antenne[Antenne[j].size_antennes]= CopyCluster.liste_point[i];
                Antenne[j].size_antennes+=1;
                a=false;
            }

        }
    }
//print(Cluster);
//print(CopyCluster);
//delete[] CopyCluster.liste_point;
}
int solution::cout_non_incremental(const parser& Parser, const cluster& Cluster) const
{
    int cost =0;
    cost += Parser.l(Cluster.point_distribution,Boucle[0]);
    if(bouclesize>0){
    for (int i=0;i<bouclesize-1;i++){
        cost+= Parser.l(Boucle[i],Boucle[i+1]);
    }

    cost += Parser.l(Boucle[bouclesize-1],Cluster.point_distribution);
    }
    for (int i=0;i<bouclesize;i++)
    {
        if(Antenne[i].size_antennes >0){
            cost += Parser.l(Boucle[i],Antenne[i].liste_antenne[0]);
           //cout << "ok2"<< endl;
            if(Antenne[i].size_antennes>1){
            for(int j=0;j<(Antenne[i].size_antennes)-1;j++){
                cost+=Parser.l(Antenne[i].liste_antenne[j],Antenne[i].liste_antenne[j+1]);
            }
            }
        }
    }

    return cost;
}

void solution::copy(solution &Sol){
    Sol.bouclesize = bouclesize;
    for (int i=0;i<bouclesize;i++){
        Sol.Boucle[i]=Boucle[i];
    }
    for (int i=0;i<bouclesize;i++){
        Sol.Antenne[i].size_antennes = Antenne[i].size_antennes;
        for (int j=0;j<Antenne[i].size_antennes;j++){
            Sol.Antenne[i].liste_antenne[j] = Antenne[i].liste_antenne[j];
        }
    }
}
void print(solution Sol,const parser& Parser, const cluster& Cluster){
    cout << "b ";
    cout << Cluster.point_distribution;
    for (int i=0;i<Sol.bouclesize;i++){
        cout <<" "<< Sol.Boucle[i];
    }
    cout << endl;

    for(int i=0;i<Sol.bouclesize;i++){
        if(Sol.Antenne[i].size_antennes>0){
            cout << "c ";
            cout << Sol.Boucle[i];
            for(int j =0;j<Sol.Antenne[i].size_antennes;j++){
                cout <<" "<< Sol.Antenne[i].liste_antenne[j];
            }
            cout << endl;
        }
    }

}


ofstream f("/home/azam/Documents/Rechop/grenoble.txt");
void solution::fichier(const parser& Parser, const cluster& Cluster){

    f << "b ";
    f << Cluster.point_distribution;
    for (int i=0;i<bouclesize;i++){
        f <<" "<< Boucle[i];
    }
    f << endl;

    for(int i=0;i<bouclesize;i++){
        if(Antenne[i].size_antennes>0){
            f << "c ";
            f << Boucle[i];
            for(int j =0;j<Antenne[i].size_antennes;j++){
                f <<" "<< Antenne[i].liste_antenne[j];
            }
            f << endl;
        }
    }

}
