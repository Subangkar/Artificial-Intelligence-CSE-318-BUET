package Mancala.Heuristics;

import Mancala.Player.MancalaBoard;

import java.util.Random;

public class Heuristic2 extends MancalaHeuristic {
	int W1 = 3, W2 = 2, W3 = 0, W4 = 0;
	
	@Override
	public int getHeuristicValue( MancalaBoard board ) {
		if (W1 == 0) {
			W1 = new Random().nextInt( MAX_WEIGHT ) + 1;
			W2 = new Random().nextInt( MAX_WEIGHT ) + 1;
		}
		int maxPlayer = board.getMaxPlayer();
		int minPlayer = MancalaBoard.otherPlayer( maxPlayer );
		//W1 * (stones_in_my_storage – stones_in_opponents_storage) + W2 * (stones_on_my_side –
		//stones_on_opponents_side)
		int stones_in_my_storage = board.getStonesInStorage( maxPlayer );//board.getPlayersTotalStones( board.currentPlayer() );
		int stones_in_opponents_storage = board.getStonesInStorage( minPlayer );//board.getPlayersTotalStones( MancalaBoard.otherPlayer( board.currentPlayer() ) );
		int stones_in_my_side = board.getPlayersTotalStones( maxPlayer );
		int stones_in_opponents_side = board.getPlayersTotalStones( minPlayer );
		return W1 * (stones_in_my_storage - stones_in_opponents_storage) + W2 * (stones_in_my_side - stones_in_opponents_side);
	}
}
