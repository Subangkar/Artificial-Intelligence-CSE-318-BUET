package Algorithms.Minimax;

import java.util.ArrayList;

public class Minimax {
	
	private static final boolean DEBUG = false;
	private static final double INF = 10000000;
	
	private static class Solution {
		MinimaxProblem instance;
		double v;
		
		Solution( MinimaxProblem instance , double v ) {
			this.instance = instance;
			this.v = v;
		}
		
		static Solution max( Solution sol1 , Solution sol2 ) {
			if (sol2 == null || (sol1 != null && sol1.v >= sol2.v)) return sol1;
			else return sol2;
		}
		
		static Solution min( Solution sol1 , Solution sol2 ) {
			if (sol2 == null || (sol1 != null && sol1.v <= sol2.v)) return sol1;
			else return sol2;
		}
	}
	
	public static int minimax( MinimaxProblem root , int maxDepth ) {
		Solution opt = alphabeta( root , -INF , INF , true , maxDepth );
		ArrayList< MinimaxProblem > list = root.successors();
		if (DEBUG) System.err.println( "Optimum v: " + opt.v + "\n" + opt.instance );
		for (int i = 0; i < list.size(); ++i) {
			if (list.get( i ) != null && list.get( i ).equals( opt.instance )) return i;
		}
//		for (MinimaxProblem suc : root.successors()) {
//			if (suc != null && suc.equals( opt.instance )) return suc;
//		}
		return -1;
	}
	
	
	private static Solution alphabeta( MinimaxProblem state , double alpha , double beta , boolean isMaximizing , int maxdepth ) {
		if (state.isTerminal() || maxdepth == 0) {
			if (DEBUG && state.isTerminal())
				System.err.println( (state.isMaximizing() ? "max @" : "min @") + (maxdepth) + " current v: " + state.heuristicValue() + "\n" + state );
			return new Solution( state , state.heuristicValue() );
		}
		if (isMaximizing) {
			Solution maxSolution = new Solution( null , -INF );
			for (MinimaxProblem s : state.successors()) {
				if (s == null) continue;
				Solution solution = new Solution( s , alphabeta( s , alpha , beta , s.isMaximizing() , maxdepth - 1 ).v );
				maxSolution = Solution.max( maxSolution , solution );
				alpha = Math.max( alpha , maxSolution.v );
				if (alpha >= beta) break; //beta-cut-off
			}
			return maxSolution;
			
		} else {
			Solution minSolution = new Solution( null , INF );
			
			for (MinimaxProblem s : state.successors()) {
				if (s == null) continue;
				Solution solution = new Solution( s , alphabeta( s , alpha , beta , s.isMaximizing() , maxdepth - 1 ).v );
				minSolution = Solution.min( minSolution , solution );
				beta = Math.min( beta , minSolution.v );
				if (alpha >= beta) break; //alpha-cut-off
			}
			return minSolution;
		}
	}
	
	
}
