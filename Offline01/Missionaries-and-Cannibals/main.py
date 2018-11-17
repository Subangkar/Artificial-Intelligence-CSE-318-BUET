#! /usr/bin/env python


import sys
import time
from Graph import Graph
from State import State, Direction, TERMINAL_STATE

# # from State import MAX_M
# from State import MAX_C
# from State import CAP_BOAT


from Constants import CONST

from Graph import listStates


def generateAllStates(nMissionaries, nCannibals):
	for m in range(nMissionaries + 1):
		for c in range(nCannibals + 1):
			for dir in [0, 1]:
				state = State(m, c, int(not dir), 0, 0, 0, None)
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


def runBFS(g, INITIAL_STATE):
	sys.stdout = open("outBFS.txt", "w")
	print(">>>>>>>>>>>\n\nBFS\n")
	start_time = time.time_ns()
	p = g.BFS(INITIAL_STATE)
	# print(p)
	if len(p):
		g.printPathL(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in BFS: %.2fms" % ((time.time_ns() - start_time) / (10 ** 6)))


def runDFS(g, INITIAL_STATE):
	sys.stdout = open("outDFS.txt", "w")
	print(">>>>>>>>>>>\n\nDFS\n")
	start_time = time.time_ns()
	p = g.DFS(INITIAL_STATE)
	if len(p):
		g.printPathL(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in DFS: %.2fms" % ((time.time_ns() - start_time) / (10 ** 6)))


def main():
	sys.stdin = open("in.txt", "r")

	m = int(input("m="))
	print(m, end="\n")
	c = int(input("c="))
	print(c, end="\n")
	k = int(input("k="))
	print(k, end="\n")
	t = int(input("TIME_LIMIT_s="))
	print(t, end="\n")
	n = int(input("NODE_LIMIT="))
	print(n, end="\n")

	# sys.stdout = open("out.txt", "w")

	CNST = CONST(m, c, k, t, n)

	INITIAL_STATE = State(CNST.MAX_M, CNST.MAX_C, Direction.OLD_TO_NEW, 0, 0, 0, CNST)
	# TERMINAL_STATE = State(-1, -1, Direction.NEW_TO_OLD, -1, -1, 0)

	g = Graph()
	generateAllStates(CNST.MAX_M, CNST.MAX_C)
	# generateGraph(g)
	# g.printGraph()

	runBFS(g, INITIAL_STATE)

	runDFS(g, INITIAL_STATE)


if __name__ == '__main__':
	main()
