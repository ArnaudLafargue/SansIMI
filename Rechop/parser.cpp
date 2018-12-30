#include "parser.h"

parser::parser(){
    distances_fn();
    for(int i =0;i<size_distribution;i++){
        distribution[i]=i;
    }
    for(int i=size_distribution;i<size_antennes;i++){
        antennes[i-size_distribution]= i;
    }
}
void parser::distances_fn()
{
    ifstream fichier_distances("/home/azam/Documents/instances/paris/distances.csv", ios::in); // on ouvre le fichier en lecture
    string contenu;
    int test_distances=0;

    for (string line; getline(fichier_distances,line); )
    {

        distances[test_distances]=stoi(line);
        test_distances++;
    }
    fichier_distances.close();
    assert(test_distances==size_distances);
}

void parser::test()
{
    for (int i =0;i<size_distances;i++){
        cout<< distances[i]<< "distance"<<endl;
    }
    for (int i=0;i<size_distribution;i++){
        cout << distribution[i] << "distri"<< endl;
    }
    for (int i=0;i<size_terminal;i++){
        cout << antennes[i]<< "antennes"<< endl;
    }
}

int parser::l(int x,int y) const
{

    return distances[x *size_antennes+y];
}
