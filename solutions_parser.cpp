#include "solutions_parser.h"


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
