# MAX_M = 3
# MAX_C = 3
# CAP_BOAT = 2

# import Constants

# from Constants import MAX_M
# from Constants import MAX_C
# from Constants import CAP_BOAT

# from Constants import INITIAL_STATE
# from Constants import TERMINAL_STATE

from Constants import Direction

# from Constants import TERMINAL_STATE, INITIAL_STATE


# class CONST:
MAX_M = 30
MAX_C = 30
CAP_BOAT = 20
CNST = None


# MAX_M = Constants.MAX_M


# Within this object, the state is represented as described in the lecture:
# The triple (m,c,b) holds the number of missionaries, cannibals and boats
# on the original shore.
class State(object):

	def __init__(self, missionaries, cannibals, dir, missionariesPassed, cannibalsPassed, level, CONSTS):
		self.missionaries = missionaries
		self.cannibals = cannibals
		self.dir = dir
		self.action = ""
		self.level = level
		self.missionariesPassed = missionariesPassed
		self.cannibalsPassed = cannibalsPassed
		self.CONSTANTS = CONSTS

		global MAX_M
		global MAX_C
		global CAP_BOAT
		global CNST

		if not CONSTS is None:
			CNST = CONSTS

			MAX_M = CONSTS.MAX_M
			MAX_C = CONSTS.MAX_C
			CAP_BOAT = CONSTS.CAP_BOAT

	# print(MAX_M)

	def successors(self):
		listChild = []
		if not self.isValid() or self.isGoalState():
			# print("?? ", end=" ")
			# print(self)
			return listChild
		if self.dir == Direction.OLD_TO_NEW:
			sgn = -1
			direction = "from the original shore to the new shore"
		else:
			sgn = 1
			direction = "back from the new shore to the original shore"
		for m in range(CAP_BOAT + 1):
			for c in range(CAP_BOAT + 1):
				# no point of taking only one from old to new shore when other exists --need to think @not sure
				if (self.dir == Direction.OLD_TO_NEW and m + c < 2) and (
						self.missionaries != 0 and self.cannibals != 0):
					continue

				# missionaries < cannibals on boat
				if 0 < m < c:
					continue

				if 1 <= m + c <= CAP_BOAT:  # check whether action and resulting state are valid

					newState = State(self.missionaries + sgn * m, self.cannibals + sgn * c, self.dir + sgn * 1,
					                 self.missionariesPassed - sgn * m, self.cannibalsPassed - sgn * c, self.level + 1,
					                 self.CONSTANTS)
					if newState.isValid():
						newState.action = " take %d missionaries and %d cannibals %s." % (m, c, direction)
						listChild.append(newState)
		return listChild

	def isValid(self):
		# obvious
		if self.missionaries < 0 or self.cannibals < 0 or self.missionaries > MAX_M or self.cannibals > MAX_C or (
				self.dir != 0 and self.dir != 1):
			return False

		# then check whether missionaries outnumbered by cannibals
		if (self.cannibals > self.missionaries > 0) or (
				self.cannibalsPassed > self.missionariesPassed > 0):  # more cannibals then missionaries on original shore
			return False

		# if (MAX_M==MAX_C and self.cannibals < self.missionaries < MAX_C):  # more cannibals then missionaries on other shore
		# 	return False

		return True

	def isGoalState(self):
		return self.cannibals == 0 and self.missionaries == 0 and self.dir == 0

	def __repr__(self):
		return "\n%s\n\n< @Depth:%d State (%d, %d, %d, %d, %d) >" % (
			self.action, self.level, self.missionaries, self.cannibals, self.dir, self.missionariesPassed,
			self.cannibalsPassed)

	def __eq__(self, other):
		return self.missionaries == other.missionaries and self.cannibals == other.cannibals and self.dir == other.dir

	def __hash__(self):
		return hash((self.missionaries, self.cannibals, self.dir))

	def __ne__(self, other):
		return not (self == other)


TERMINAL_STATE = State(-1, -1, Direction.NEW_TO_OLD, -1, -1, 0, CNST)
# INITIAL_STATE = State(MAX_M, MAX_C, Direction.OLD_TO_NEW, 0, 0, 0, CNST)
