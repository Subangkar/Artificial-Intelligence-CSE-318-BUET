package Mancala.Heuristics;


import Algorithms.Minimax.Minimax;
import Mancala.Player.MancalaBoard;

public abstract class MancalaHeuristic {
	static final int MAX_WEIGHT = 5;
	
	public int selectMove( MancalaBoard board , int depth ) {
		int bin = 0;
		try {
			bin = Minimax.minimax( board , depth ) + 1; // index starts from 0 bt bin from 1
		} catch (Exception e) {
			e.printStackTrace();
		}
		return bin;
	}
	// Return the index of a non-empty bin to move.
	// Assumes that at least one move is possible.
	
	public static MancalaHeuristic intToStrategy( int i ) {
		// Returns a new MancalaHeuristic corresponding to the number between 0 and 4.
		switch (i) {
			case 1:
				return new Heuristic1();
			case 2:
				return new Heuristic2();
			case 3:
				return new Heuristic3();
			case 4:
				return new Heuristic4();
			default:
				return new UserHeuristic();
		}
	}
	
	
	public abstract int getHeuristicValue( MancalaBoard board );
}
