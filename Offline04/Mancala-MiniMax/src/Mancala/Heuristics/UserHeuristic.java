package Mancala.Heuristics;

import Mancala.Player.MancalaBoard;
import Mancala.Player.Stdin;

public class UserHeuristic extends MancalaHeuristic {
	@Override
	public int selectMove( MancalaBoard board , int depth ) {
		int player = board.currentPlayer();
		int bins = board.getBins();
		int bin = Stdin.readIntInRange( 1 , bins , "Please select a bin to move for Player" + player );
		while (board.getBin( bin ) == 0) {
			System.err.println( "Bin " + bin + " is empty. Please try again." );
			bin = Stdin.readIntInRange( 1 , bins , "Please select a bin to move for Player" + player );
		}
		System.out.println( "Ok" );
		return bin;
	}
	
	@Override
	public int getHeuristicValue( MancalaBoard board ) {
		return 0;
	}
}
