#include "network.h"

using namespace std;

object::object(){
    coordinates = vector<double> (0 ,0);
    index = 0;
    type = 0;

}

network::network()
{
    ifstream distances_file("/home/arnaud/Documents/KIRO/paris/distances.csv", ios::in); // on ouvre le fichier en lecture
    ifstream coordinates_file("/home/arnaud/Documents/KIRO/paris/nodes.csv", ios::in);

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

        vector<double> c;
        c.push_back(stod(x));
        c.push_back(stod(y));

        object o;
        o.coordinates = c;
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
}


