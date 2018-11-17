#! /usr/bin/env python


import sys
import time
from Graph import Graph
from State import State, Direction, INITIAL_STATE, TERMINAL_STATE

from State import MAX_M
from State import MAX_C
from State import CAP_BOAT

from State import INITIAL_STATE, TERMINAL_STATE



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

	# MAX_M=3
	# MAX_C=3
	# CAP_BOAT=2
	# # State.MAX_M=30
	# # State.MAX_C=30
	# # State.CAP_BOAT=20
	#
	# INITIAL_STATE = State(MAX_M, MAX_C, Direction.OLD_TO_NEW, 0, 0,0)
	# TERMINAL_STATE = State(-1, -1, Direction.NEW_TO_OLD, -1, -1, 0)

	g = Graph()
	generateAllStates(MAX_M, MAX_C)
	# generateGraph(g)
	# g.printGraph()
	print("\nBFS\n")
	start_time = time.time_ns();
	p = g.BFS(INITIAL_STATE)
	if len(p):
		g.printPathL(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in BFS: %.2fms" % ((time.time_ns()-start_time)/(10**6)))

	print("\nDFS\n")

	start_time = time.time_ns();
	p = g.DFS(INITIAL_STATE)
	if len(p):
		# print(len(p))
		g.printPathL(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in DFS: %.2fms" % ((time.time_ns()-start_time)/(10**6)))


if __name__ == '__main__':
	main()
