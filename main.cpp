#include "recuit.h"

int main1()
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

int main2()
{
    parser Parser;

    instances Instances(Parser);
//    int finalcost =0;
//    solution bestsol;
//    for (int n=0;n<size_distribution;n++){
//        recuit Recuit;
//        (Recuit.heuristique(Parser,Instances.rangement[n])).copy(bestsol);
//        bestsol.fichier(Parser,Instances.rangement[n]);
//        finalcost +=bestsol.cout_non_incremental(Parser,Instances.rangement[n]);
//    }
//    cout << finalcost << "final"<<endl;

    solutions sols;
    sols = solutions_parser();

    return 0;
}

int main3(){
    solutions sols;
    sols = solutions_parser();
    return 0;
}


int main(){
    return main2();
}
