import sys

from Graph import Graph
from State import State

from State import MAX_M
from State import MAX_C

from Graph import listStates


def generateAllStates(nMissionaries, nCannibals):
	for m in range(nMissionaries + 1):
		for c in range(nCannibals + 1):
			for dir in [0, 1]:
				# print(str(m)+","+str(c)+","+str(int(not dir)))
				state = State(m, c, int(not dir))
				if not state.isValid():
					continue
				listStates.append(state);


def generateGraph(g):
	for state in listStates:
		childs = state.successors()
		# print(state,end=" -> ")
		# print(childs)
		for child in childs:
			g.addEdge(state, child)


def main():
	sys.stdout = open("out.txt", "w")
	# # solution = breadth_first_tree_search(initial_state)
	# if solution is None:
	#   print "no solution"
	# else:
	#   # print "solution (%d steps):" % len(solution)
	#   for step in solution:
	#     print "%s" % step
	# print "elapsed time: %.2fs" % time.clock()
	generateAllStates(MAX_M, MAX_C)
	g = Graph()
	generateGraph(g)
	# g.print()
	initial_state = State(MAX_M, MAX_C, 1)
	p = g.BFS(initial_state)
	# print(len(p))
	if len(p):
		g.printPath(p, State(-1, -1, 0))
	else:
		print("No Solution")


# g.print()
# print(State(3,3,1).successors().pop(2))
# print(State(3,3,1).successors().pop(2).successors())


if __name__ == '__main__':
	main()
