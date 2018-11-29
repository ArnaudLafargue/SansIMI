import tsp
from typing import Tuple, TextIO
import numpy as np
import random as ran

nodes_file = open("nice/nodes.csv")
distances_file = open("nice/distances.csv")


def parser_nodes(file):
    lines = file.readlines()
    lines.pop(0)
    lines = [line.strip().split(";") for line in lines]
    for line in lines:
        line[0] = float(line[0])
        line[1] = float(line[1])
        line[2] = line[2][0]

    return lines


def parser_distances(file):
    lin = distances_file.readlines()
    DataIn = np.loadtxt(lin)
    return DataIn


class Instance:

    def __init__(self):
        self.nodes = parser_nodes(nodes_file)
        self.distances = parser_distances(distances_file)
        self.terminal = self.list_terminal()

    def type(self, i):
        return self.nodes[i][2]

    def xy(self, i):
        return (self.nodes[i][0], self.nodes[i][1])

    def l(self, i, j):
        return self.distances[len(self.nodes) * i + j]

    def nodes_sorting(self):
        terminal = []
        distribution = []
        i = 0

        for i in range(len(self.nodes)):
            if self.nodes[i][2] == 't':
                terminal.append([i, float(self.nodes[i][0]), float(self.nodes[i][1])])
            if self.nodes[i][2] == 'd':
                distribution.append([i, float(self.nodes[i][0]), float(self.nodes[i][1])])
        return terminal, distribution

    def list_terminal(self):
        return self.nodes_sorting()[0]

    def list_distribution(self):
        return self.nodes_sorting()[1]


I = Instance()
group = I.nodes
mat = [[I.l(i,j)+I.l(j,i) for i in range(len(group))] for j in range(len(group))]

r = range(len(mat))
dist = {(i, j): mat[i][j] for i in r for j in r}
solution = tsp.tsp(r, dist)
print(solution)
output = open("grenoble/output.csv","w+")
line = ""
for i in range(len(solution[1])):
       line+= str(solution[1][i])+" "
print(line)
output.write("b "+line)
output.close()
