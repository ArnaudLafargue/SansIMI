from typing import Tuple, TextIO
import numpy as np
import random as ran
from operator import itemgetter, attrgetter, methodcaller

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
        self.distribution = self.list_distribution()

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
    while len(terminal) > 1:
        i = ran.randint(0, len(terminal) - 1)
        min = 1000000000000
        j0 = 0
        for j in range(len(terminal)):
            if (i != j):
                if I.l(terminal[i][0], terminal[j][0]) + I.l(terminal[j][0], terminal[i][0]) < min:
                    j0 = j
                    min = I.l(terminal[i][0], terminal[j][0]) + I.l(terminal[j][0], terminal[i][0])
        if j0 < i:
            binome.append([terminal.pop(i)[0], terminal.pop(j0)[0]])
        if j0 > i:
            binome.append([terminal.pop(i)[0], terminal.pop(j0 - 1)[0]])
    return (binome, terminal)


def quadrunome(I):
    bino = binom(I)
    binome = bino[0]
    terminal = bino[1]
    quadrunome = []
    while len(binome) > 1:
        i = ran.randint(0, len(binome) - 1)
        inf = 1000000000000
        j0 = 0
        for j in range(len(binome)):
            if (i != j):
                if min((I.l(binome[i][0], binome[j][0]) + I.l(binome[j][0], binome[i][0]),
                        I.l(binome[i][0], binome[j][1]) + I.l(binome[j][1], binome[i][0]),
                        I.l(binome[i][1], binome[j][0]) + I.l(binome[j][0], binome[i][1]),
                        I.l(binome[i][1], binome[j][1]) + I.l(binome[j][1], binome[i][1]))) < inf:
                    j0 = j
                    inf = min((I.l(binome[i][0], binome[j][0]) + I.l(binome[j][0], binome[i][0]),
                               I.l(binome[i][0], binome[j][1]) + I.l(binome[j][1], binome[i][0]),
                               I.l(binome[i][1], binome[j][0]) + I.l(binome[j][0], binome[i][1]),
                               I.l(binome[i][1], binome[j][1]) + I.l(binome[j][1], binome[i][1])))
        if j0 < i:
            var = binome.pop(i)
            var2 = binome.pop(j0)
            quadrunome.append([var[0], var[1], var2[0], var2[1]])
        if j0 > i:
            var = binome.pop(i)
            var2 = binome.pop(j0 - 1)
            quadrunome.append([var[0], var[1], var2[0], var2[1]])

       compteur = 0        
    if (len(binome)>0):
        a = binome[0][0]
        b = binome[0][1]
        compteur = 2
    if len(binome)>0:
        c = terminal[0][0]
        if compteur == 2 :
            compteur = 3
        if compteur == 0 :
            compteur = 1
    if compteur == 1:
        quadrunome.append([c])
    if compteur == 2: 
        quadrunome.append([a,b])
    if compteur == 3:
        quadrunome.append([a,b,c])
    return quadrunome

Q = quadrunome(I)

class Antenna_group():
    def __init__(self, index):
        self.antennas = Q[index]
        self.representative = self.antennas[ran.randint(0,len(self.antennas)-1)]

    def dist(self, t_antenna):
        return I.l(self.representative,t_antenna)+ I.l(t_antenna,self.representative)


Antenna_groups = [Antenna_group(i) for i in range(len(Q))]

D = I.distribution
groups = []
for i in range(len(D)):
    d = D[i][0]
    distances = []
    for j in range(len(Antenna_groups)):
        distances += [(Antenna_groups[j].dist(d),j)]
    sorted_distances = sorted(distances, key=itemgetter(0))
    group = sorted_distances[:min(len(sorted_distances),6)]
    group = [group[i][1] for i in range(len(group))]
    group = [Antenna_groups[group[i]] for i in range(len(group))]

    for k in group:
        Antenna_groups.pop(Antenna_groups.index(k))

    groups += [[d] + group]


