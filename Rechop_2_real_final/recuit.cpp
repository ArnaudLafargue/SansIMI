#include "recuit.h"
recuit::recuit(){
}

solution recuit::heuristique(parser& Parser, cluster& Cluster) {

InitRandom();

solution xprime=solution(Parser,Cluster,int(Cluster.nombre_de_point/6)+1);
solution xseconde=solution(Parser,Cluster,int(Cluster.nombre_de_point/6)+1);
solution x = solution(Parser,Cluster,int(Cluster.nombre_de_point/6)+1);
solution xb = solution(Parser,Cluster,int(Cluster.nombre_de_point/6)+1);
double proba1;
double p;
int bouclesize = int(Cluster.nombre_de_point/6)+1;
x.bouclesize = bouclesize;
x.first_solution(Parser,Cluster);
xb.bouclesize = bouclesize;
xb.first_solution(Parser,Cluster);
while(bouclesize<min(30,Cluster.nombre_de_point)+1){

    cout << "boucle size" << bouclesize << endl;

    InitRandom();
    T = 100.;
    proba1 = float(bouclesize)/Cluster.nombre_de_point;
    bool a;
    //cout << "always working ? " << endl;
    while(T>0.01){
        for (int compteur =0; compteur<taille;compteur++){

            if (x.cout_non_incremental(Parser,Cluster) < xb.cout_non_incremental(Parser,Cluster)){
                x.copy(xb);
                cout << xb.cout_non_incremental(Parser,Cluster) << "ici"<< endl;
            }

            x.copy(xprime);

            a = true;


            while (a) {
                p = proba();
                if (p<proba1*proba1){

                    int i=hasard(0,bouclesize-1);
                    int j=hasard(0,bouclesize-1);
                    //cout << i << endl;
                    if(i!=j){

                        antenne A = xprime.Antenne[i];
                        antenne B = xprime.Antenne[j];
                        int a1 = xprime.Boucle[i];
                        int b1 = xprime.Boucle[j];
                        xprime.Boucle[i]=b1;
                        xprime.Boucle[j]=a1;
                        xprime.Antenne[i]=B;
                        xprime.Antenne[j]=A;

                        a = false;
                    }
                    else{
                        a= true;
                    }
                }

                else if (p<proba1*proba1+2*proba1*(1-proba1)) {

                    int i = hasard(0,bouclesize-1);
                    int j = hasard(0,bouclesize-1);
                    if (xprime.Antenne[j].size_antennes==0){
                        a = true;
                    }
                    else{
                        int j1=hasard(0,xprime.Antenne[j].size_antennes -1);
                        int a1 = xprime.Boucle[i];
                        int a2 = xprime.Antenne[j].liste_antenne[j1];
                        xprime.Boucle[i] = a2;
                        xprime.Antenne[j].liste_antenne[j1]= a1;
                        a = false;
                    }
                }
                else{

                    int i = hasard(0,bouclesize-1);
                    int j = hasard(0,bouclesize-1);
                    if (xprime.Antenne[i].size_antennes == 0){
                        a = true;
                    }
                    else if(xprime.Antenne[j].size_antennes == 0){
                        a = true;
                    }

                    else{
                        int i1 = hasard(0,xprime.Antenne[i].size_antennes-1);
                        int j1 = hasard(0,xprime.Antenne[j].size_antennes-1);
                        int a1 = xprime.Antenne[i].liste_antenne[i1];
                        int a2 = xprime.Antenne[j].liste_antenne[j1];
                        xprime.Antenne[i].liste_antenne[i1] = a2;
                        xprime.Antenne[j].liste_antenne[j1]= a1;
                        a = false;
                    }
                }

            }
            int cxprime = xprime.cout_non_incremental(Parser,Cluster);
            int cx = x.cout_non_incremental(Parser,Cluster);
            if (cxprime<cx){
                xprime.copy(x);
            }

            else if(p<exp(-(cxprime-cx)/T)){
                xprime.copy(x);
            }



            x.copy(xseconde);

            int iseconde = hasard(0,bouclesize-1);
            int jseconde  = hasard(0,bouclesize-1);
            if (xseconde.Antenne[iseconde].size_antennes == 0){
                a = true;
            }
            else if(xseconde.Antenne[jseconde].size_antennes == 5){
                a = true;
            }

            else{
                int i1seconde = hasard(0,xseconde.Antenne[iseconde].size_antennes-1);
                int j1seconde = hasard(0,xseconde.Antenne[jseconde].size_antennes);
                // on enlève le i1 élément de la première chaine et on le rajoute dans j

                push(xseconde.Antenne[jseconde],pop(xseconde.Antenne[iseconde],i1seconde));
                a = false;
            }
            int cxseconde = xseconde.cout_non_incremental(Parser,Cluster);
            cx = x.cout_non_incremental(Parser,Cluster);
            if (cxseconde<cx){
                xseconde.copy(x);
            }
            else if(p<exp(-(cxseconde-cx)/T)){
                xseconde.copy(x);
            }



        }

        T= alpha*T;
    }

    a = true;
    while (a){
        int i = hasard(0,bouclesize-1);
        x.Antenne[bouclesize].size_antennes = 0;
        if(x.bouclesize == Cluster.nombre_de_point){
            a = false;
            bouclesize+=1;
        }
        else if (x.Antenne[i].size_antennes == 0){
            a= true;
        }
        else{
            x.Antenne[bouclesize].size_antennes=0;
            // on rajoute un élément dans boucle
            int i1 = hasard(0,x.Antenne[i].size_antennes-1);
            x.Boucle[bouclesize]=pop(x.Antenne[i],i1);
            a=false;
            x.bouclesize+=1;
            bouclesize+=1;
        }
    }

}
return xb;
}
void recuit::test(){
    int a=5;
    cout << a << endl;
}
