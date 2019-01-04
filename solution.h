#pragma once
#include "instances.h"
int hasard (int a ,int b);
double proba();
struct antenne
{
    int size_antennes;
    int liste_antenne[5];
};

class solution
{
public:
    solution();
    solution(const parser& Parser,const cluster& Cluster);
    solution(const parser& Parser,const cluster& Cluster,int boucle_size);
    int bouclesize;
    int Boucle[30];
    antenne Antenne[30];
    void first_solution(parser& Parser, cluster& Cluster);
    int cout_non_incremental(const parser& Parser, const cluster& Cluster) const;
    void copy(solution& Solution);
    void fichier(const parser& Parser, const cluster& Cluster);
    //~solution();
};
void print(solution Sol,const parser& Parser, const cluster& Cluster);
void InitRandom();

struct solutions{
    solution solutions_list[40];
    int solutions_number;
};

solutions solutions_parser();
