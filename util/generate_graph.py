# !/usr/bin/python

from sys import argv
from random import randrange


number_nodes = int(argv[1])
density = int(argv[2])

if density > 100:
	density = 100
elif density < 1:
	density = 1

print("Creating graph with {} nodes and density {} )".format(number_nodes, density/100.0))



with open('graph_{}_{}.txt'.format(number_nodes, density), 'w') as graph:
	graph.write("%d\n" % number_nodes)
	for i in range(1, number_nodes + 1):
		for j in range(i+1, number_nodes + 1):
			if randrange(0, 100) <= density:
				graph.write("{},{}\n".format(i, j))

