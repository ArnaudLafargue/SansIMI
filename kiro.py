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
        self.nodes = np.array(self.nodes)
        for i in range(self.nodes.shape[0]):
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

def binom(I: Instance):
    binoms = []
    length = len(I.terminal)
    not_paired = [I.terminal[i][0] for i in range(length)]
    shuffle(not_paired)

    for i_index in range(len(not_paired)):
        i = not_paired[i_index]
        min_dist = 10000000000
        print(i)

        for j_index in range(len(not_paired)):
            j = not_paired[j_index]
            if j!= i:
                dist = I.l(i,j)
                print(not_paired)
                if dist < min_dist:

                    min_dist = dist
                    binoms += [(i, j)]

                    m = min(i_index, j_index)
                    M = max(i_index, j_index)
                    if M + 1 == len(not_paired):
                        not_paired = not_paired[:m] + not_paired[m + 1:M]
                    else:
                        not_paired = not_paired[:m] + not_paired[m + 1:M] + not_paired[M+1:]

    return binoms
