from typing import Tuple, TextIO
import numpy as np
from random import randint, shuffle

nodes_file = open("grenoble/nodes.csv")
distances_file = open("grenoble/distances.csv")


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
T = [i for i in I.terminal]

def binom(I):
    terminal = I.terminal
    binome = []
    while len(terminal)>2:
        i = ran.randint(0,len(terminal)-1)
        min = 1000000000000
        j0=0
        for j in range(len(terminal)):
            if (i!=j):
                if I.l(terminal[i][0],terminal[j][0]) +I.l(terminal[j][0],terminal[i][0])< min :
                    j0 =j
                    min = I.l(terminal[i][0],terminal[j][0]) +I.l(terminal[j][0],terminal[i][0])
        if j0 <i :
            binome.append ([terminal.pop(i)[0], terminal.pop(j0)[0]])
        if j0 >i:
            binome.append ([terminal.pop(i)[0], terminal.pop(j0-1)[0]])
    return binome,terminal


        
def quadrunome(binome,terminal):
    
    while len(binome)>4:
        i = ran.randint(0,len(binome)-1)
        min = 1000000000000
        j0=0
        for j in range(len(binome)):
            if (i!=j):
                if I.l(binome[i][0],binome[j][0]) +I.l(binome[j][0],binome[i][0])< min :
                    j0 =j
                    min = I.l(terminal[i][0],terminal[j][0]) +I.l(terminal[j][0],terminal[i][0])
        if j0 <i :
            binome.append ([terminal.pop(i)[0], terminal.pop(j0)[0]])
        if j0 >i:
            binome.append ([terminal.pop(i)[0], terminal.pop(j0-1)[0]])
    return binome,terminal
       
