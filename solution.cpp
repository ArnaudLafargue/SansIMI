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
    InitRandom();

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
        antenna_groups[i].group_size =0;;
        }

    for (int i=0;i<Clusters_const.cluster_list[n].size-loop_size;i++)
    {
        bool a = true;
        while(a)
        {
            j = hasard(0,loop_size-1);
            if (antenna_groups[j].group_size < 5){
                antenna_groups[j].antennas[antenna_groups[j].group_size] =cluster_copy[i+loop_size-1];
                antenna_groups[j].group_size=antenna_groups[j].group_size+ 1;
                a=false;
            }

        }
    }
}


int solution::simple_cost2(int n) {

    cost =0;
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
    Sol.dist_id = dist_id;

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
ofstream f("/home/arnaud/Documents/Rechop/paris0.txt");

void solution::fichier(int n) const{
    //ofstream f("/home/arnaud/Documents/Rechop/paris" +to_string(n) + ".txt");

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
using namespace Imagine;

int normalize(double x, int  w, double xmin, double xmax){
    int result = int((x-xmin)/(xmax-xmin)*w);
    if (result<0)
        result =0;
    if (result>w)
        result =w;
    return result;
}
void solution::full_display(int n, Window f, int w, int h) const{

    double xmin = 10000000;
    double xmax = 0;
    double ymin = 10000000;
    double ymax = 0;
    coordinates ccfirst,cclast;
    coordinates distrib_point = Network_const.antennas[Clusters_const.cluster_list[n].point_distribution].coords;
    for (int i=0; i<Network_const.size_antennas;i++){

            coordinates c = Network_const.antennas[i].coords;
            if (c.x <= xmin)
                xmin = c.x;
            else if (c.x >=xmax)
                xmax = c.x;
            if (c.y <= ymin)
                ymin = c.y;
            else if (c.y >=ymax)
                ymax = c.y;
    }

    int index;
    for (int i=0; i<loop_size;i++){
        coordinates cl1 = Network_const.antennas[loop[i]].coords;
        index = Network_const.antennas[loop[i]].index;

        int xl1 = normalize(cl1.x,w,xmin,xmax);
        int yl1 = normalize(cl1.y,h,ymin,ymax);
        drawString(xl1+10,yl1,to_string(index),BLACK,12);
        drawCircle(xl1,yl1,6,BLACK,3);

        if (i<loop_size -1){
            coordinates cl2 = Network_const.antennas[loop[i+1]].coords;
            int xl2 = normalize(cl2.x,w,xmin,xmax);
            int yl2 = normalize(cl2.y,h,ymin,ymax);
            drawLine(xl1,yl1,xl2,yl2,BLUE,2);
        }
        if (i==0)
            ccfirst = cl1;
        if (i==loop_size-1)
            cclast = cl1;


        if (antenna_groups[i].group_size>0){
            coordinates cc = Network_const.antennas[antenna_groups[i].antennas[0]].coords;
            int xc = normalize(cc.x,w,xmin,xmax);
            int yc = normalize(cc.y,h,ymin,ymax);

            drawLine(xl1,yl1,xc,yc, BLACK,1);
            for (int j=0; j<antenna_groups[i].group_size;j++){
                coordinates cc = Network_const.antennas[antenna_groups[i].antennas[j]].coords;
                index = Network_const.antennas[antenna_groups[i].antennas[j]].index;
                int xc = normalize(cc.x,w,xmin,xmax);
                int yc = normalize(cc.y,h,ymin,ymax);
                drawString(xc+10,yc+20,to_string(index),RED,10);

                drawCircle(xc,yc,5,RED,3);
                if (j < antenna_groups[i].group_size -1){
                    coordinates ccp1 = Network_const.antennas[antenna_groups[i].antennas[j+1]].coords;
                    int xcp1 = normalize(ccp1.x,w,xmin,xmax);
                    int ycp1 = normalize(ccp1.y,h,ymin,ymax);
                    drawLine(xc,yc,xcp1,ycp1, BLACK,1);
                }

            }
        }
    }
    int cc1x = normalize(ccfirst.x,w,xmin,xmax);
    int cc1y = normalize(ccfirst.y,h,ymin,ymax);

    int cclx = normalize(cclast.x,w,xmin,xmax);
    int ccly = normalize(cclast.y,h,ymin,ymax);

    int xd = normalize(distrib_point.x,w,xmin,xmax);
    int yd = normalize(distrib_point.y,h,ymin,ymax);

    drawLine(cc1x,cc1y,xd,yd,BLUE,2);
    drawLine(xd,yd,cclx,ccly,BLUE,2);
    drawCircle(xd,yd,10,GREEN,5);
    drawString(xd+14,yd+7,to_string(n),GREEN,14);

}

void solution::cluster_display(int n, Window f, int w, int h, bool timed) const{
    clearWindow();


    drawString(100,100,to_string(cost),RED,40);
    double xmin = 10000000;
    double xmax = 0;
    double ymin = 10000000;
    double ymax = 0;

    coordinates ccfirst,cclast;
    assert (n == Clusters_const.cluster_list[n].point_distribution);
    coordinates distrib_point = Network_const.antennas[Clusters_const.cluster_list[n].point_distribution].coords;
    for (int i=0; i<loop_size;i++){
        for (int j=0; j<antenna_groups[i].group_size;j++){

            double x = Network_const.antennas[antenna_groups[i].antennas[j]].coords.x;
            double y = Network_const.antennas[antenna_groups[i].antennas[j]].coords.y;
            if (x <= xmin)
                xmin = x;
            else if (x >=xmax)
                xmax = x;
            if (y <= ymin)
                ymin = y;
            else if (y >=ymax)
                ymax = y;
        }

        double x = Network_const.antennas[loop[i]].coords.x;
        double y = Network_const.antennas[loop[i]].coords.y;
        if (x <= xmin)
            xmin = x;
        else if (x >=xmax)
            xmax = x;
        if (y <= ymin)
            ymin = y;
        else if (y >=ymax)
            ymax = y;
    }
    int index;

    for (int i=0; i<loop_size;i++){
        coordinates cl1 = Network_const.antennas[loop[i]].coords;
        index = Network_const.antennas[loop[i]].index;

        int xl1 = normalize(cl1.x,w,xmin,xmax);
        int yl1 = normalize(cl1.y,h,ymin,ymax);
        drawString(xl1+7,yl1+7,to_string(index),BLACK,12);
        drawCircle(xl1,yl1,6,BLACK,3);

        if (i==0)
            ccfirst = cl1;
        if (i==loop_size-1)
            cclast = cl1;

        if (i<loop_size -1){
            coordinates cl2 = Network_const.antennas[loop[i+1]].coords;
            int xl2 = normalize(cl2.x,w,xmin,xmax);
            int yl2 = normalize(cl2.y,h,ymin,ymax);
            drawLine(xl1,yl1,xl2,yl2,BLUE,2);
        }

        if (antenna_groups[i].group_size>0){
            coordinates cc = Network_const.antennas[antenna_groups[i].antennas[0]].coords;
            int xc = normalize(cc.x,w,xmin,xmax);
            int yc = normalize(cc.y,h,ymin,ymax);

            drawLine(xl1,yl1,xc,yc, BLACK,1);
            for (int j=0; j<antenna_groups[i].group_size;j++){
                coordinates cc = Network_const.antennas[antenna_groups[i].antennas[j]].coords;
                index = Network_const.antennas[antenna_groups[i].antennas[j]].index;
                int xc = normalize(cc.x,w,xmin,xmax);
                int yc = normalize(cc.y,h,ymin,ymax);
                drawString(xc+7,yc+7,to_string(index),RED,10);

                drawCircle(xc,yc,5,RED,3);
                if (j < antenna_groups[i].group_size -1){
                    coordinates ccp1 = Network_const.antennas[antenna_groups[i].antennas[j+1]].coords;
                    int xcp1 = normalize(ccp1.x,w,xmin,xmax);
                    int ycp1 = normalize(ccp1.y,h,ymin,ymax);
                    drawLine(xc,yc,xcp1,ycp1, BLACK,1);
                }

            }
        }
    }
    int cc1x = normalize(ccfirst.x,w,xmin,xmax);
    int cc1y = normalize(ccfirst.y,h,ymin,ymax);

    int cclx = normalize(cclast.x,w,xmin,xmax);
    int ccly = normalize(cclast.y,h,ymin,ymax);

    int xd = normalize(distrib_point.x,w,xmin,xmax);
    int yd = normalize(distrib_point.y,h,ymin,ymax);

    drawLine(cc1x,cc1y,xd,yd,BLUE,2);
    drawLine(xd,yd,cclx,ccly,BLUE,2);
    drawCircle(xd,yd,10,GREEN,5);
    drawString(xd+14,yd+7,to_string(n),GREEN,14);

    if (timed)
        milliSleep(30);
    else click();
}


solutions solutions_parser(){

    ifstream bestsols_file("/home/arnaud/Documents/Rechop/paris_test.txt", ios::in); // on ouvre le fichier en lecture

    vector<vector<int>> file_table;
    solutions sols;
    sols.solutions_number =0;

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
            bestsol.loop_size = file_table[i].size()-2;
            bestsol.dist_id = file_table[i][1];
            for (int j=0;j<bestsol.loop_size;j++)
                bestsol.loop[j] = file_table[i][j+2];

            for (int k=0; k<30;k++)
                bestsol.antenna_groups[k].group_size =0;

            if (collect_lines_number !=0)
                for (int k=0;k<collect_lines_number;k++)
                    for (int j=0;j<bestsol.loop_size;j++)
                        if (bestsol.loop[j] == file_table[i+k+1][1]){
                            bestsol.antenna_groups[j].group_size = file_table[i+k+1].size() - 2;
                            for (int n=0;n< bestsol.antenna_groups[j].group_size; n++)
                                bestsol.antenna_groups[j].antennas[n] = file_table[i+k+1][n+2];
                        }
            sols.solutions_list[count] = bestsol;
            count+=1;
            sols.solutions_number +=1;

            }


        i+=max(1,collect_lines_number);
    }

    bestsols_file.close();
    return sols;
}
