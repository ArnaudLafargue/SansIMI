#include "recuit.h"
int cout_final(solutions& sol,parser& Parser, instances& Instances){
    int coutfin = 0;
    for (int i =0;i<sol.solutions_number;i++){
        coutfin += sol.solutions_list[i].cout_non_incremental(Parser,Instances.rangement[i]);
    }
    return coutfin;
}
int main2()
{
    parser Parser;

    instances Instances(Parser);
    int finalcost =0;
    solution bestsol;
    for (int n=0;n<size_distribution;n++){
        recuit Recuit;
        (Recuit.heuristique(Parser,Instances.rangement[n])).copy(bestsol);
        bestsol.fichier(Parser,Instances.rangement[n]);
        finalcost +=bestsol.cout_non_incremental(Parser,Instances.rangement[n]);
    }
    cout << finalcost << "final"<<endl;

    return 0;
}
int main()
{
    parser Parser;
    instances Instances(Parser);
    solutions sol,sol2,sol3,solfinal;

    InitRandom();

    solfinal = solutions_parser();
    sol = solfinal;
    int taille_final = 100000;
    int cost_final = cout_final(sol,Parser,Instances);
    double T,p;
    cout << cost_final << endl;
    // recherche locale sol.solutions_ sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]= sol.solutions_list[i]=list[i]=
    int i,j,iboucle,jboucle,cout_intermediaire,i1,j1,a1,a2;
    T = 10;
    while(T>0.1){

        for(int compteur =0;compteur < taille_final;compteur++){
            if (cout_final(solfinal,Parser,Instances)>cout_final(sol,Parser,Instances)){
                solfinal = sol;
                cout << cout_final(solfinal,Parser,Instances) << endl;
            }
            sol2 = sol;
            // on change un point de place
            p = proba();
            bool a = true;
            while (a){
                i = hasard(0,sol.solutions_number-1);
                j = hasard(0,sol.solutions_number-1);
                iboucle = hasard(0,sol.solutions_list[i].bouclesize-1);
                jboucle = hasard(0,sol.solutions_list[j].bouclesize-1);
                if (sol2.solutions_list[i].Antenne[iboucle].size_antennes == 0 || sol2.solutions_list[j].Antenne[jboucle].size_antennes == 5 ){
                    a = true;
                }

                else{
                    i1 = hasard(0,sol2.solutions_list[i].Antenne[iboucle].size_antennes-1);
                    //i1 = 0;
                    j1 = hasard(0,sol2.solutions_list[j].Antenne[jboucle].size_antennes);
                    //j1 =2;
                    push(sol2.solutions_list[j].Antenne[jboucle],pop(sol2.solutions_list[i].Antenne[iboucle],i1),j1);
                    a = false;
                }
            }
            //xi.copy(sol.solutions_list[i]);
            //xj.copy(sol.solutions_list[j]);
            // calcul du cout

            //cout_intermediaire = cost_final - sol.solutions_list[i].cout_non_incremental(Parser,Instances.rangement[i]) -sol.solutions_list[j].cout_non_incremental(Parser,Instances.rangement[j]) + xi.cout_non_incremental(Parser,Instances.rangement[i]) + xj.cout_non_incremental(Parser,Instances.rangement[j]);
            if ( cout_final(sol2,Parser,Instances)<cout_final(sol,Parser,Instances)){

                sol = sol2;
                cost_final = cout_final(sol,Parser,Instances);
            }
            else if(p < exp((cout_final(sol,Parser,Instances) - cout_final(sol2,Parser,Instances))/T)){
                sol = sol2;
            }

        // on remplit aussi la distribution
            if (p<1/20){
                sol3 = sol;
                a= true;
                while (a) {
                    i = hasard(0,sol3.solutions_number-1);
                    j = hasard(0,sol3.solutions_number-1);
                    iboucle = hasard(-1,sol3.solutions_list[i].bouclesize-1);
                    jboucle = -1;
                    if (iboucle == -1 && sol3.solutions_list[i].Antenne_distribution.size_antennes >0){
                        i1 = hasard(0,sol3.solutions_list[i].Antenne_distribution.size_antennes-1);
                        j1 = hasard(0,sol3.solutions_list[j].Antenne_distribution.size_antennes);
                        push(sol3.solutions_list[j].Antenne_distribution,pop(sol3.solutions_list[i].Antenne_distribution,i1),j1);
                        a = false;

                    }
                    else if(iboucle == -1 && sol3.solutions_list[i].Antenne_distribution.size_antennes == 0){
                        a = true;
                    }
                    else if (sol3.solutions_list[i].Antenne[iboucle].size_antennes == 0 || sol3.solutions_list[j].Antenne_distribution.size_antennes== 5 ){
                        a = true;
                    }
                    else{
                        i1 = hasard(0,sol3.solutions_list[i].Antenne[iboucle].size_antennes-1);
                        //i1 = 0;
                        j1 = hasard(0,sol3.solutions_list[j].Antenne_distribution.size_antennes);
                        //j1 =2;
                        push(sol3.solutions_list[j].Antenne_distribution,pop(sol3.solutions_list[i].Antenne[iboucle],i1),j1);
                        a = false;
                    }
                }
                if ( cout_final(sol3,Parser,Instances)<cout_final(sol,Parser,Instances)){

                    sol = sol3;
                    cost_final = cout_final(sol,Parser,Instances);
                    //cout << cost_final << endl;
                }
                else if(p < exp((cout_final(sol,Parser,Instances) - cout_final(sol3,Parser,Instances))/T)){
                    sol = sol3;
                }
            }

        }
        T = T*0.99;


    }

    for (int k =0;k<sol.solutions_number;k++){
        solfinal.solutions_list[k].fichier(Parser,Instances.rangement[k]);
    }
    cout << cost_final << endl;
    return 0;
}
