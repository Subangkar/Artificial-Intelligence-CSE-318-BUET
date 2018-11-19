#! /usr/bin/env python3
import sys
import time

from Graph import Graph

from State import State, Direction, TERMINAL_STATE

from Constants import CONST

CON_IN = sys.stdin
CON_OUT = sys.stdout


def genPossibleMoves(CAP_BOAT):
	moves = []
	for m in range(CAP_BOAT + 1):
		for c in range(CAP_BOAT + 1):
			if 0 < m < c:
				continue
			if 1 <= m + c <= CAP_BOAT:
				moves.append((m, c))
	return moves


def runBFS(g, INITIAL_STATE):
	sys.stdout = open("outBFS.txt", "w")
	print("\n\nBFS :: \n")
	start_time = time.time_ns()
	p = g.BFS(INITIAL_STATE)
	end_time = time.time_ns()
	# print("Printing Solution...")
	if len(p):
		g.printPath(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in BFS: %.2fms" % ((end_time - start_time) / (10 ** 6)))


def runDFS(g, INITIAL_STATE):
	sys.stdout = open("outDFS.txt", "w")
	print("\n\nDFS :: \n")
	start_time = time.time_ns()
	p = g.DFS(INITIAL_STATE)
	end_time = time.time_ns()
	if len(p):
		g.printPath(p, TERMINAL_STATE)
	else:
		print("No Solution")
	print("\n Elapsed time in DFS: %.2fms" % ((end_time - start_time) / (10 ** 6)))


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

	CNST = CONST(m, c, k, t, n)

	moves = genPossibleMoves(CNST.CAP_BOAT)
	print(str(moves.__len__())+" iterations per Node.")

	INITIAL_STATE = State(CNST.MAX_M, CNST.MAX_C, Direction.OLD_TO_NEW, 0, 0, 0, CNST, moves)
	# TERMINAL_STATE = State(-1, -1, Direction.NEW_TO_OLD, -1, -1, 0)

	g = Graph()
	sys.stdout = CON_OUT
	print("\nRunning BFS>")
	runBFS(g, INITIAL_STATE)
	sys.stdout = CON_OUT
	print("Executed BFS>")

	print("\nRunning DFS>")
	runDFS(g, INITIAL_STATE)
	sys.stdout = CON_OUT
	print("Executed DFS>")


if __name__ == '__main__':
	main()
