Mancala is one of the oldest known games to still be widely played today. Mancala is a generic name for a family of two-player turn-based strategy board games played with small stones, beans, or seeds and rows of holes or pits in the earth, a board or other playing surface. The objective is usually to capture all or some set of the opponent's pieces. Versions of the game date back to the 7th century, and evidence suggests the game existed in ancient Egypt.
  
This repository contains Java implementation of a mancala AI Bot which takes decision at each level via Minimax adversarial search algorithm with alpha beta pruning.  

Heuristics in consideration:
 - heuristic-0: Takes input from user to select move.  
 
 - heuristic-1: The evaluation function is  
   (#stones_in_my_storage – #stones_in_opponents_storage)
 
 - heuristic-2: The evaluation function is  
   3 * (#stones_in_my_storage – #stones_in_opponents_storage) + 2 * (#stones_on_my_side – #stones_on_opponents_side)
 
 - heuristic-3: The evaluation function is  
   4 * (#stones_in_my_storage – #stones_in_opponents_storage) + 2 * (#stones_on_my_side – #stones_on_opponents_side) + 2 * (#additional_move_earned)
 
 - heuristic-4: The evaluation function is  
   4 * (#stones_in_my_storage – #stones_in_opponents_storage) + 2 * (#stones_on_my_side – #stones_on_opponents_side) + 2 * (#additional_move_earned) + 1 * (#stones_captured)  
   
Run `Mancala.Player.Main.java` to start.   

Game playing options:  
 - Human vs Human  
 - Human vs Computer
   
This implementation was an home assignment task on Adversarial Search Algorithm Implementation of Artificial Intelligence Lab in Level-3, Term-2 of CSE, BUET.  
  
Visit [wikipedia](https://en.wikipedia.org/wiki/Mancala) to see detail info of the game and [this site](https://www.thesprucecrafts.com/how-to-play-mancala-409424) to know the rules of playing this game.