from typing import Tuple, TextIO
import numpy as np

nodes_file = open("grenoble/nodes.csv")
distances_file = open("grenoble/distances.csv")

def parser_nodes(file):
    lines = file.readlines()
    lines.pop(0)
    lines = [line.strip().split(";") for line in lines]
    for ligne in lines:
        ligne[0] = float(ligne[0])
        ligne[1] = float(ligne[1])
        
    return lines

def parser_distances(file): 
    lin =distances_file.readlines()
    DataIn = np.loadtxt(lin)
    return DataIn

class Instance:

    def __init__(self):
        nodes_lines = parser(nodes_file)
        distances_lines = parser(distances_file)

        for line in nodes_lines:
            letter = line[2][0]
            line = [float(line[0])]+ [float(line[1])] + [letter]
