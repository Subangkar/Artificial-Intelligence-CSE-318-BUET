package Mancala.Player;


import Mancala.Heuristics.MancalaHeuristic;

import java.io.*;
import java.util.Random;

public class Main {
////*================================== DEBUG VARIABLES ==============================*/
	
	private static final int nBins = 6;
	private static final int nStones = 4;
	public static final boolean DEBUG = false;
	public static final int MAX_DEPTH = 15;
	private static final int nMaxStages = 150;
	private static final boolean PRINT_BOARD_CONFIG = true;
	private static final int NO_GAMES_PER_HEURISTIC = 50;
	private static final int MAX_ORDER = 1;
	private static final int[] HEURISTIC_PLAYER0 = { 1 , 2 , 3 , 4 };
	private static final int[] HEURISTIC_PLAYER1 = { 1 , 2 , 3 , 4 };
	private static final int[] OPTIMAL_MOVES = { 4 , 1 , 5 , 6 , 5 , 2 };
////*=================================================================================*/
	
	private static final PrintStream stdout_ = System.out;
	
	static void statPrint() throws IOException {
		PrintWriter logFile = new PrintWriter( new FileWriter( "log.log" ) );
		
		int h0, h1;
		for (int i : HEURISTIC_PLAYER0) {
			for (int j : HEURISTIC_PLAYER1) {
				for (int order = 0; order < MAX_ORDER; ++order) {
//					if (order == 1 && i == j) break;
					h0 = i;
					h1 = j;
					int n0 = 0, n1 = 0, nD = 0;
					long start_time = System.currentTimeMillis();
					for (int game = 0; game < NO_GAMES_PER_HEURISTIC; ++game) {
						int depth = new Random().nextInt( 4 ) + 8;
						int r = playLoop( selectStrategy( h0 ) , selectStrategy( h1 ) , depth );
						if (r == 0) ++n0;
						if (r == 1) ++n1;
						if (r == -1) ++nD;
						System.setOut( stdout_ );
//						if (i == 1 && j == 1) break;
					}
					logFile.println( "0>Heuristic " + h0 + " : " + n0 + "\n1>Heuristic " + h1 + " : " + n1 + "\n >Draw        : " + nD );
					logFile.println( "Execution time: " + (System.currentTimeMillis() - start_time) + "\n" );
					logFile.flush();
				}
				
			}
		}
		
	}
	
	public static void main( String[] args ) throws IOException {
		int h[] = { 0 , 0 };
		if (DEBUG) {
			statPrint();
		} else {
			for (int p = 0; p <= 1; ++p) {
				h[p] = Stdin.readIntInRange( 0 , 4 , "Select a heuristic [0-4] for player " + p + " (O for Human): " );
			}
			int depth = MAX_DEPTH;
			if (h[0] != 0 || h[1] != 0) depth = Stdin.readIntInRange( 1 , 15 , "Enter Depth to search @ each node: " );
			playLoop( selectStrategy( h[0] ) , selectStrategy( h[1] ) , depth );
		}
	}


///======================== IO Methods =======================================////
	
	public static int playLoop( MancalaHeuristic s0 , MancalaHeuristic s1 , int MAX_DEPTH ) {
		int bins = DEBUG ? nBins : Stdin.readIntInRange( 0 , 10 , "Specify the number of bins on each side: " );
		int stones = DEBUG ? nStones : Stdin.readIntInRange( 0 , 10 , "Specify the number of stones initially in each bin: " );
		if (DEBUG) try {
			System.setOut( new PrintStream( "out.log" ) );
			System.setErr( new PrintStream( "err.log" ) );
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		MancalaBoard.printBoardConfiguration();
		return play( bins , stones , s0 , s1 , MAX_DEPTH );
//		System.setOut( ps );
	}
	
	private static MancalaHeuristic selectStrategy( int n ) {
		return MancalaHeuristic.intToStrategy( n );
	}
	
	
	///======================== IO Methods =======================================////
//================================================================================
	
	private static int play( int bins , int stones , MancalaHeuristic s0 , MancalaHeuristic s1 , int MAX_DEPTH ) {
		MancalaBoard board = new MancalaBoard( bins , stones , s0 , s1 , MAX_DEPTH );
		
		if (DEBUG) {
			for (int m : OPTIMAL_MOVES) {
				if (PRINT_BOARD_CONFIG) System.out.println( board );
				board.move( m );
			}
		} else if (PRINT_BOARD_CONFIG) System.out.println( board );
		int round = 0;
		while (!board.isGameOver() && round < nMaxStages) {
			if (PRINT_BOARD_CONFIG) System.out.println( "------------" + round + "--------------" );
			int currentPlayer = board.currentPlayer();
			if (PRINT_BOARD_CONFIG) System.out.println( "Player " + currentPlayer + "\'s move." );
			int bin = board.move();
			if (bin <= 0) break;
			if (PRINT_BOARD_CONFIG) System.out.println( "Player " + currentPlayer + " selects "
					                                      + board.stonesMoved() + " stones from bin " + bin );
			if (PRINT_BOARD_CONFIG) System.out.println( board );
			if (PRINT_BOARD_CONFIG) System.out.println( "\n\n\n--------------------------\n\n\n" );
			round++;
		}
		System.out.println( "Final board configuration:\n" );
		System.out.println( board );
		if (board.getBin( 0 , 0 ) == board.getBin( 1 , 0 )) {
			if (PRINT_BOARD_CONFIG) System.out.println( "The game ends in a tie!" );
			return -1;
		} else if (board.getBin( 0 , 0 ) > board.getBin( 1 , 0 )) {
			if (PRINT_BOARD_CONFIG) System.out.println( "Player0 wins!" );
			return 0;
		} else {
			if (PRINT_BOARD_CONFIG) System.out.println( "Player1 wins!" );
			return 1;
		}
	}
	
	
}
