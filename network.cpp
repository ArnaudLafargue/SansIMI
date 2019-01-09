#include "network.h"

using namespace std;

object::object(){
    coords = {0,0};
    index = 0;
    type = 0;

}

network::network()
{
    ifstream distances_file(srcPath("instances/paris/distances.csv"), ios::in); // on ouvre le fichier en lecture
    ifstream coordinates_file(srcPath("instances/paris/nodes.csv"), ios::in);

    string line;

    // Iterate through each line and split the content using
    getline(coordinates_file, line,'\n');
    int index = 0;
    while (getline(coordinates_file, line,'\n'))
    {
        string x = string();
        string y = string();
        int i = 0;
        while (line[i]!=';'){x+=line[i]; i+=1;}
        i+=1;
        while (line[i]!=';'){y+=line[i]; i+=1;}
        i+=1;

        char t = line[i];

        coordinates c = {stod(x),stod(y)};
        object o;
        o.coords = c;
        o.index = index;
        if (t == 't'){
            o.type = 1;
            t_antennas.push_back(o);
        }
        else {
            d_antennas.push_back(o);
        }

        antennas.push_back(o);
        index+=1;
    }

    coordinates_file.close();

    for (string line; getline(distances_file,line); )
    {
        distances.push_back(stoi(line));
    }

    distances_file.close();

    size_distances = distances.size();
    size_distribution = d_antennas.size();
    size_antennas = antennas.size();
    size_terminal = t_antennas.size();

    x_min = 1000000;
    x_max = 0;
    y_min = 1000000;
    y_max = 0;

    for (int i=0; i<size_antennas;i++){

            coordinates c = antennas[i].coords;
            if (c.x <= x_min)
                x_min = c.x;
            else if (c.x >=x_max)
                x_max = c.x;
            if (c.y <= y_min)
                y_min = c.y;
            else if (c.y >=y_max)
                y_max = c.y;
    }
}


