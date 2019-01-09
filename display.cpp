#include "display.h"

void capture(string s){
    Color *C;
    int w,h;
    captureWindow(C,w,h);
    //putColorImage(0,0,C,w,h);
    saveColorImage(stringSrcPath("images/" + s),C,w,h);

    delete[]C;
    //click();
}
void draw_cost_iteration(int h, int w,const vector<coordinates>& cost_iteration, int best_loop){
    clearWindow();
    double xmin=100000000000000,
        xmax=0,
        ymin=100000000000000,
        ymax=0;

    for (int i=0; i<cost_iteration.size();i++){
        if (cost_iteration[i].x<xmin)
            xmin = cost_iteration[i].x;
        if (cost_iteration[i].x>xmax)
            xmax = cost_iteration[i].x;
        if (cost_iteration[i].y<ymin)
            ymin = cost_iteration[i].y;
        if (cost_iteration[i].y>ymax)
            ymax = cost_iteration[i].y;
    }
    for (int j=0; j<cost_iteration.size();j++){
        int i = j;
        int x = normalize(cost_iteration[i].x,w,xmin,xmax);
        int y = h - normalize(log(1+cost_iteration[i].y-ymin),h,0,log(1+ymax-ymin));

        drawPoint(x,y,RED);
        y = h - normalize(cost_iteration[i].y,h,ymin,ymax);
        drawPoint(x,y,BLACK);



    }
    drawString(int(w/3),100,"Evolution du coût de la solution au fur et à mesure de l'exploration",BLACK,20);
    drawString(int(w/3)+300,140,"Taille de la boucle :" + to_string(best_loop),BLACK,15);
    drawString(int(3*w/4),300+155,"Echelle log",RED,15);
    drawString(int(3*w/4),300+185,"Echelle lineaire",BLACK,15);


    drawString(w-100,h-30,to_string(int(xmax)),BLACK,10);
    drawString(60,h-30,to_string(int(xmin)),BLACK,10);
    drawString(30,h-60,to_string(int(ymin)),BLACK,10);
    drawString(30,30,to_string((int)ymax),BLACK,10);


    capture("paris_cost_per_iteration.png");

    click();
}

void display_network(int w, int h){
    clearWindow();
    for (int i=0; i<Network_const.size_antennas;i++){
        object a = Network_const.antennas[i];
        int x = normalize(a.coords.x,w,Network_const.x_min,Network_const.x_max);
        int y = h-normalize(a.coords.y,h,Network_const.y_min,Network_const.y_max);

        if (a.type == 0){
            drawCircle(x,y,10,GREEN,5);
            drawString(x+14,y+7,to_string(a.index),GREEN,14);
        }
        else{
            drawCircle(x,y,5,RED,3);
            drawString(x+10,y+10,to_string(a.index),RED,10);


        }

    }
    click();
    capture("paris_network.png");
    clearWindow();
}

void display_clusters(int w, int h){
    clearWindow();
    for (int i=0; i<Clusters_const.cluster_list.size();i++){



        object d = Network_const.antennas[i];
        int xd = normalize(d.coords.x,w,Network_const.x_min,Network_const.x_max);
        int yd = h-normalize(d.coords.y,h,Network_const.y_min,Network_const.y_max);


        for (int j=0; j<Clusters_const.cluster_list[i].size;j++){
            int index = Clusters_const.cluster_list[i].cluster_antennas[j].index;
            object a = Network_const.antennas[index];
            int x = normalize(a.coords.x,w,Network_const.x_min,Network_const.x_max);
            int y = h-normalize(a.coords.y,h,Network_const.y_min,Network_const.y_max);

            drawCircle(x,y,5,RED,3);
            drawString(x+10,y+10,to_string(a.index),RED,10);

            drawLine(x,y,xd,yd,BLACK);


            }
        drawCircle(xd,yd,10,GREEN,5);
        drawString(xd+14,yd+7,to_string(d.index),GREEN,14);


        }
    click();
    capture("paris_clusters.png");
    clearWindow();
}
