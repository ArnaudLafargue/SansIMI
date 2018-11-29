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
        return self.distances[self.distances.shape[0] * i + j]

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
    index = [i for i in range(length)]
    shuffle(index)
    not_paired = [j for j in range(length)]

    for i in index:
        antenna_index = I.terminal[i][0]
        min_dist = 10000000000

        for j_index in range(len(not_paired)):
            j = not_paired[j_index]
            print(antenna_index,j)
            dist = I.l(antenna_index, j)

            if dist < min_dist:

                min_dist = dist
                binoms += [(i, j)]

                i_not_paired_index = not_paired.index(i)
                m = min(i_not_paired_index, k)
                M = max(i_not_paired_index, k)
                if M + 1 == len(not_paired):
                    not_paired = not_paired[:m] + not_paired[m + 1:] + not_paired[:M]
                else:
                    not_paired = not_paired[:m] + not_paired[m + 1:] + not_paired[:M] + not_paired[M + 1:]

            return binoms

binom(I)
