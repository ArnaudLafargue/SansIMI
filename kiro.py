from typing import Tuple, TextIO

nodes_file = open("grenoble/nodes.csv")
distances_file = open("grenoble/distances.csv")


def parser(file):
    lines = file.readlines()
    lines = [line.strip().split(";") for line in lines]
    return lines

class Instance:

    def __init__(self):
        nodes_lines = parser(nodes_file)
        distances_lines = parser(distances_file)

        for line in nodes_lines:
            letter = line[2][0]
            line = [float(line[0])]+ [float(line[1])] + [letter]
