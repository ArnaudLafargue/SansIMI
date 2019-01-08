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
    Antenne_distribution.size_antennes=0;
    //first_solution();
}
solution::solution(const parser& Parser,const cluster& Cluster)
{

    bouclesize = hasard(int(Cluster.nombre_de_point/6)+1,min(30,Cluster.nombre_de_point));
    Antenne_distribution.size_antennes=0;
    //first_solution();
}
solution::solution(){
    bouclesize=0;
    Antenne_distribution.size_antennes=0;
}
void solution::first_solution(parser& Parser, cluster& Cluster)
{
    cluster CopyCluster;
    Cluster.copy(CopyCluster);
    Antenne_distribution.size_antennes=0;
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
    // rajout
    if (Antenne_distribution.size_antennes >0){
        cost+= Parser.l(Cluster.point_distribution,Antenne_distribution.liste_antenne[0]);
        if(Antenne_distribution.size_antennes>1){
        for(int j=0;j<(Antenne_distribution.size_antennes)-1;j++){
            cost+=Parser.l(Antenne_distribution.liste_antenne[j],Antenne_distribution.liste_antenne[j+1]);
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
    if (Sol.Antenne_distribution.size_antennes >0){
        cout << "c ";
        cout << Cluster.point_distribution;
        for (int j=0;j<(Sol.Antenne_distribution.size_antennes);j++){
            cout << " "<< Sol.Antenne_distribution.liste_antenne[j];
        }
        cout << endl;
    }

}


ofstream f("/home/azam/Documents/Rechop_2/grenoble2.txt");
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
    if (Antenne_distribution.size_antennes >0){
        f << "c ";
        f << Cluster.point_distribution;
        for (int j=0;j<(Antenne_distribution.size_antennes);j++){
            f <<" "<< Antenne_distribution.liste_antenne[j];
        }
        f << endl;
    }


}

solutions solutions_parser(){

    ifstream bestsols_file("/home/azam/Documents/Rechop_2/grenoble.txt", ios::in); // on ouvre le fichier en lecture

    vector<vector<int>> file_table;
    solutions sols;
    int sol_count = 0;
    for (string line; getline(bestsols_file,line);){
        vector<int> line_table;
        if (line[0] == 'b')
            line_table.push_back(-1);
        else
            line_table.push_back(0);
        int l = line.length();

        int i=2;
        while (i<l){

            string number;
            while (line[i] != ' ' && i<l){
                number += line[i];
                i+=1;
            }
            i+=1;
            line_table.push_back(stoi(number));
        }
        file_table.push_back(line_table);
    }

    int i =0;
    int count =0;
    while (i<file_table.size()){
        int collect_lines_number = 0;
        if (file_table[i][0] == -1){
            solution bestsol;

            bool a = true;
            while (i+collect_lines_number+1<file_table.size() && a)
                if (file_table[i+collect_lines_number+1][0] == 0)
                        collect_lines_number += 1;
                    else a = false;
            bestsol.bouclesize = file_table[i].size()-2;
            //bestsol.cluster_id = file_table[i][1];
            for (int j=0;j<bestsol.bouclesize;j++)
                bestsol.Boucle[j] = file_table[i][j+2];

            for (int k=0; k<30;k++)
                bestsol.Antenne[k].size_antennes =0;

            if (collect_lines_number !=0)
                for (int k=0;k<collect_lines_number;k++)
                    for (int j=0;j<bestsol.bouclesize;j++)
                        if (bestsol.Boucle[j] == file_table[i+k+1][1]){
                            bestsol.Antenne[j].size_antennes = file_table[i+k+1].size() - 2;
                            for (int n=0;n< bestsol.Antenne[j].size_antennes; n++)
                                bestsol.Antenne[j].liste_antenne[n] = file_table[i+k+1][n+2];
                        }

            sols.solutions_list[count] = bestsol;
            count+=1;
            sols.solutions_number +=1;
            }


        i+=max(1,collect_lines_number);
    }

    bestsols_file.close();
    for (int k =0;k<sols.solutions_number;k++){
        sols.solutions_list[k].Antenne_distribution.size_antennes=0;
    }
    return sols;
}
int pop(antenne& Antenne,int pos){
    int returne = Antenne.liste_antenne[pos];
    int g[5];
    for (int i=0;i<Antenne.size_antennes;i++){
        g[i]=Antenne.liste_antenne[i];
    }
    if (pos < Antenne.size_antennes){
        for(int i =pos;i<Antenne.size_antennes-1;i++){
            Antenne.liste_antenne[i]=g[i+1];
        }
    }
    Antenne.size_antennes = Antenne.size_antennes -1;
    return returne;

}
void push(antenne& Antenne,int valeur){
    int g[5];
    for (int i=0;i<Antenne.size_antennes;i++){
        g[i]=Antenne.liste_antenne[i];
    }
    int position = hasard(0,Antenne.size_antennes);
    if (position == Antenne.size_antennes){
        Antenne.liste_antenne[Antenne.size_antennes]=valeur;
        Antenne.size_antennes+=1;
        }
    else{
        Antenne.liste_antenne[position]=valeur;
        Antenne.size_antennes+=1;
        for(int i=position+1;i<Antenne.size_antennes;i++){
            Antenne.liste_antenne[i]=g[i-1];// peut être à changer
        }
    }


}
