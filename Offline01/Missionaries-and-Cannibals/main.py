#! /usr/bin/env python


import sys
import time
from Graph import Graph
from State import State

from State import MAX_M
from State import MAX_C

from State import INITIAL_STATE
from State import TERMINAL_STATE

from Graph import listStates


def generateAllStates(nMissionaries, nCannibals):
	for m in range(nMissionaries + 1):
		for c in range(nCannibals + 1):
			for dir in [0, 1]:
				state = State(m, c, int(not dir), 0, 0, 0)
				if not state.isValid():
					continue
				listStates.append(state)


def generateGraph(g):
	for state in listStates:
		childs = state.successors()
		# print(state,end=" -> ")
		# print(childs)
		for child in childs:
			g.addEdge(state, child)


def main():
	sys.stdout = open("out.txt", "w")
	start_time = time.time_ns();
	g = Graph()
	# generateAllStates(MAX_M, MAX_C)
	# generateGraph(g)
	# g.print()
	p = g.BFS(INITIAL_STATE)
	if len(p):
		g.printPath(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in BFS: %.2fms" % ((time.time_ns()-start_time)/(10**6)))


if __name__ == '__main__':
	main()
