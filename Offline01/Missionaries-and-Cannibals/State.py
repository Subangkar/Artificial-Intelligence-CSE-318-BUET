MAX_M = 5
MAX_C = 5
# MAX_B = 2
CAP_BOAT = 2


# Within this object, the state is represented as described in the lecture:
# The triple (m,c,b) holds the number of missionaries, cannibals and boats
# on the original shore.
class State(object):
	def __init__(self, missionaries, cannibals, dir):
		self.missionaries = missionaries
		self.cannibals = cannibals
		self.dir = dir
		self.action = ""
		self.level = -1
		self.missionariesPassed=0
		self.cannibalsPassed=0

	def successors(self):
		list = [];
		if not self.isValid() or self.is_goal_state():
			# print("?? ", end=" ")
			# print(self)
			return list
		if self.dir == 1:
			sgn = -1
			direction = "from the original shore to the new shore"
		else:
			sgn = 1
			direction = "back from the new shore to the original shore"
		for m in range(CAP_BOAT + 1):
			for c in range(CAP_BOAT + 1):
				# no point of taking only one from old to new shore when other exists --need to think more
				# if (self.dir == 1 and m + c < 2) and (self.missionaries != 0 and self.cannibals != 0):
				# 	continue
				if 1 <= m + c <= CAP_BOAT:  # check whether action and resulting state are valid
					newState = State(self.missionaries + sgn * m, self.cannibals + sgn * c, self.dir + sgn * 1);
					if newState.isValid():
						newState.action = "take %d missionaries and %d cannibals %s." % (m, c, direction)
						newState.missionariesPassed = self.missionariesPassed - sgn * m
						newState.cannibalsPassed = self.cannibalsPassed - sgn * c
						list.append(newState)
					# 	if self.missionaries == 3 and self.cannibals == 2 and m == 1 and c == 1 and self.dir == 1:
					# 		print(">>> ")
					# 		print(newState)
					# print(">> " + newState.__repr__())
					# self.action = "take %d missionaries and %d cannibals %s. %r" % (m, c, direction, newState)
		# yield action, newState
		return list

	def isValid(self):
		# first check the obvious
		if self.missionaries < 0 or self.cannibals < 0 or self.missionaries > MAX_M or self.cannibals > MAX_C or (
				self.dir != 0 and self.dir != 1):
			return False
		# then check whether missionaries outnumbered by cannibals
		if (self.cannibals > self.missionaries > 0) or (self.cannibalsPassed > self.missionariesPassed > 0):  # more cannibals then missionaries on original shore
			return False
		# if (MAX_M==MAX_C and self.cannibals < self.missionaries < MAX_C):  # more cannibals then missionaries on other shore
		# 	return False
		return True

	def is_goal_state(self):
		return self.cannibals == 0 and self.missionaries == 0 and self.dir == 0

	def __repr__(self):
		# return "< State (%d, %d, %d) >\n%s" % (self.missionaries, self.cannibals, self.dir,self.action)
		return "\n%s\n\n< @Depth:%d State (%d, %d, %d, %d, %d) >" % (self.action,self.level, self.missionaries, self.cannibals, self.dir,self.missionariesPassed,self.cannibalsPassed)

	def __eq__(self, other):
		return self.missionaries == other.missionaries and self.cannibals == other.cannibals and self.dir == other.dir

	def __hash__(self):
		return hash((self.missionaries, self.cannibals, self.dir))

	def __ne__(self, other):
		# Not strictly necessary, but to avoid having both x==y and x!=y
		# True at the same time
		return not (self == other)
