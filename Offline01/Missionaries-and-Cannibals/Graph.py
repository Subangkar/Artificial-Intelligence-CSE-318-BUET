from collections import defaultdict
from State import State

listStates = [];


# This class represents a directed graph
# using adjacency list representation 
class Graph:

	# Constructor
	def __init__(self):

		# default dictionary to store graph
		self.bfs_path = None
		self.graph = defaultdict(list)
		self.bfs_parent = defaultdict(list)
		self.exploredBFS = 0;

	# function to add an edge to graph

	def addEdge(self, u, v):
		if not u in self.graph.keys():
			self.graph[u] = [];
		self.graph[u].append(v)

	# Function to print a BFS of graph
	def BFS(self, s):
		visited = defaultdict(list)
		for u in listStates:
			visited[u] = False

		queue = [s]

		visited[s] = True
		self.bfs_parent[s] = None
		s.level = 0

		while queue:
			self.exploredBFS += 1

			u = queue.pop(0)

			# print(u,end="\n [")
			# print(self.graph[u],end="]\n\n")

			if u.is_goal_state():
				print("No of Explored Nodes: " + str(self.exploredBFS));
				queue.clear()
				self.bfs_parent[State(-1, -1, 0)] = u
				return self.bfs_parent

			for v in self.graph[u]:
				if not visited[v]:
					self.bfs_parent[v] = u
					queue.append(v)
					visited[v] = True
					v.level = u.level + 1;
		return []

	def print(self):
		for u in listStates:
			print(u, end=" -> ")
			print(self.graph[u])

	def printPath(self, parentList, tail):
		if tail is None:
			return
		if parentList == {} or parentList is None:  # tail not in parentList.keys():
			print("No Solution")
			return
		# if tail != State(-1, -1, 0) and tail in parentList:
		self.printPath(parentList, parentList[tail])
		if tail != State(-1, -1, 0): print(tail)
# print(g.bfs_path)
# This code is contributed by Neelam Yadav
