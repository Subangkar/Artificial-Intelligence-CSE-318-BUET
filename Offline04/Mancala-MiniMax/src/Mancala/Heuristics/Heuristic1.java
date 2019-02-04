package Mancala.Heuristics;

import Mancala.Player.MancalaBoard;

public class Heuristic1 extends MancalaHeuristic {
	@Override
	public int getHeuristicValue( MancalaBoard board ) {
		int maxPlayer = board.getMaxPlayer();//board.getMaxPlayer();
		int minPlayer = MancalaBoard.otherPlayer( maxPlayer );
		//heuristic-1: The evaluation function is
		//(stones_in_my_storage – stones_in_opponents_storage)
		int stones_in_my_storage = board.getStonesInStorage( maxPlayer );//board.getPlayersTotalStones( board.currentPlayer() );
		int stones_in_opponents_storage = board.getStonesInStorage( minPlayer );//board.getPlayersTotalStones( MancalaBoard.otherPlayer( board.currentPlayer() ) );
		return stones_in_my_storage - stones_in_opponents_storage;
	}
}
