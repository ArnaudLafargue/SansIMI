from typing import Tuple, TextIO
import numpy as np

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
        nodes = parser_nodes(nodes_file)
        distances = parser_distances(distances_file)
        print(nodes)
        print(distances)
    
    def type(self,i):
        return self.nodes[i][2]
